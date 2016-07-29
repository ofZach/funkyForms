//
//  wave.cpp
//  Wave
//
//  Created by Zerc on 6/21/16.
//
//

#include "wave.hpp"
// ------- setup
void wave::setup(int _ypos, ofFloatColor _color, int _width){
    width = _width;
    color = _color;
    ypos = _ypos;
    
    fbo.allocate(100, 100);
    fbo.begin();
    fbo.end();
    img.load("shadow.png");
//            restLength.addListener(this, &wave::reload);
//            strength.addListener(this, &wave::reload);
//            invMass.addListener(this, &wave::reload);
//            amount.addListener(this, &wave::reload);
//    
//            gui.loadFromFile("settings.xml");
    setupSpring();
    m.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    strokeMesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    
    shapeTypes.push_back(PEBEL1);
    shapeTypes.push_back(PEBEL2);
    shapeTypes.push_back(PEBEL3);
    shapeTypes.push_back(BLOB1);
}
void wave::setupSpring(){
    points.clear();
    springs.clear();
    for (int i = 0; i < amount; i++) {
        Spring spring;
        spring.setup( strength, restLength, invMass);
        springs.push_back( spring );
        
        Point_ point;
        
        float step = width/(amount*1.0-1.0);
        
        ofVec2f pos(i*step , ypos);
        
        point.p = pos;
        point.pp = pos;
        if(i == 0 || i == amount-1 ){
            point.isFixed = true;
        }else{
            point.isFixed = false;
        }
        points.push_back(point);
    }
}
void wave::addSplash(){
    particles.clear();
    for (int i = 0; i < 50; i++){
        particle myParticle;
        float randomAngle = ofRandom(-0.1, 0.1) + 3 * PI / 2.0;
        float randomRadius = ofRandom(1,2);
        ofPoint frc = randomRadius * ofPoint(cos(randomAngle), sin(randomAngle));
        myParticle.setInitialCondition(fishPos.x, fishPos.y, frc.x, frc.y);
        myParticle.radius = ofRandom(0.5, 8);
        myParticle.damping = 0.02 + ofRandom(0,0.04);
        myParticle.color = baseColor;
        particles.push_back(myParticle);
    }
}
void wave::addFish(){
    fishPos = polyline.getPointAtPercent(ofRandom(0, 1));
    fishes.clear();
    shapes.clear();
    particle myParticle;
    myParticle.setInitialCondition(fishPos.x, fishPos.y, 0, ofRandom(-0.7, -0.8));
    fishGravity = ofRandom(-3, -0.8);
    fishDirection = ofRandom(-0.7, 0.7);
    myParticle.radius = ofRandom(20, 30);
    fishes.push_back(myParticle);
    
    ofPath p;
    float  scale = 100;
    float angle = 0;
    float r = ofRandom(30, 60);
    
    int index = (int)ofRandom(shapeTypes.size());
    ShapeType t = shapeTypes[index];
    ShapeBase* s = ShapeFactory(t);
    s->setColor(baseColor);
    s->setup();
    shapes.push_back(s);
}
// ------- update
void wave::update(vector<inputManager::Target> &targets){
    updateForces(targets);
    updatePolyline();
    updateMesh();
    updateSplashes();
}
void wave::updateForces(vector<inputManager::Target> &targets){
    float force2 = 1 - friction * timeStep * timeStep;
    
    for (int i = 0; i < points.size(); i++) {
        for(auto &t: targets ){
            if(t.pos.distance(points[i].p)<30){
                if (!points[i].isFixed) {
                    points[i].p.y += t.vel.normalize().y*force;
                }
            }
        }
        float dy = (points[i].p.y - points[i].pp.y) * force2;
        points[i].pp = points[i].p;
        points[i].p.y = MAX(points[i].p.y + dy, 0);
    }
    for (int i = 0; i < springs.size(); i++) {
        if(i>0){
            springs[i].update(&points[i-1], &points[i]);
        }
    }
}
void wave::updatePolyline(){
    polyline.clear();
    for (int i = 0; i < points.size(); i++) {
        polyline.addVertex(points[i].p);
    }
}
void wave::updateMesh(){
    m.clear();
    strokeMesh.clear();
    
    for (int i = 0; i < polyline.getVertices().size(); i++) {
        ofVec2f p = polyline.getVertices()[i];
        ofVec2f p2 = ofVec2f(p.x, ofGetHeight());
        ofVec3f dir = polyline.getTangentAtIndex(i);
        float angle = atan2(dir.x, dir.y)*(180)/pi;
        ofColor col = color;
        int a = angle/2+col.getHueAngle()/2+ofGetFrameNum()/5.;
        col.setHueAngle(a%360);
        ofColor cc = baseColor;
        
        float pct = ofMap(p.y, ypos-energyHighlightSize, ypos, 1, 0, true);
        
        col.r = pct * cc.r + (1-pct) * col.r;
        col.g = pct * cc.g + (1-pct) * col.g;
        col.b = pct * cc.b + (1-pct) * col.b;
        
        m.addVertex(points[i].p);
        m.addColor(ofFloatColor(col, 1));
        m.addVertex(p2);
        m.addColor(ofFloatColor(col, 1));

//        ofNode node;
//        ofNode child;
//        child.setParent(node);
//        child.setPosition(ofVec3f(0, ofMap(pct, 0, 1, 0, 20), 0));
//        
//        node.setPosition(p);
//        ofQuaternion q = ofQuaternion(0, ofVec3f(1, 0, 0), 0, ofVec3f(0, 1, 0), angle, ofVec3f(0, 0, 1));
//        node.setOrientation(q);
//
//        strokeMesh.addVertex(node.getGlobalPosition());
//        strokeMesh.addVertex(child.getGlobalPosition());
    }

}
void wave::updateSplashes(){
    if(ofGetFrameNum()%(int)ofRandom(120, 300)==0){
        addFish();
        addSplash();
    }
    for (int i = 0; i < particles.size(); i++){
        particles[i].resetForce();
    }
    for (int i = 0; i < particles.size(); i++){
        for(auto &p: points){
            particles[i].addAttractionForce(p.p.x, p.p.y, 200, 0.2);
        }
        particles[i].addForce(0, 0.9);
        
        for (int j = 0; j < i; j++){
            particles[i].addRepulsionForce(particles[j], 20, 0.7);
            particles[i].addAttractionForce(particles[j], 500, 0.005);
        }
    }
    for (int i = 0; i < particles.size(); i++){
        particles[i].addDampingForce();
        particles[i].update();
    }
    for (int i = 0; i < fishes.size(); i++){
        fishes[i].resetForce();
    }
    for(auto &f: fishes){
        f.addForce(fishDirection, fishGravity);
    }
    for(auto &f: fishes){
        f.addDampingForce();
        f.update();
    }
    fishGravity += 0.06;
}
// ------- draw
void wave::draw(){
    for (int i = 0; i < polyline.getVertices().size(); i++) {
        ofVec2f p = polyline.getVertices()[i];
        ofSetColor(255, shadowOpacity);
        
        img.draw(p-ofVec2f(shadowRadius, shadowRadius), shadowRadius*2, shadowRadius*2);
    }
    drawSplashes();
    m.draw();
//    strokeMesh.draw();
}
void wave::drawSplashes(){
    for (int i = 0; i < particles.size(); i++){
        particles[i].draw();
    }
    for (int i = 0; i < shapes.size(); i++){
        ofPushMatrix();
        ofTranslate(fishes[i].pos);
        ofRotateZ(fishes[i].vel.x/2*ofGetFrameNum());
        shapes[i]->draw();
        ofPopMatrix();
    }

}