//
//  FishWave.cpp
//  WaveScene
//
//  Created by Zerc on 7/29/16.
//
//

#include "FishWave.hpp"
// ------- setup
void FishWave::setupFishWave(){
    
    img.load("assets/glow.png");
    
    m.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    strokeMesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    
    shapeTypes.push_back(PEBEL1);
    shapeTypes.push_back(PEBEL2);
    shapeTypes.push_back(PEBEL3);
    shapeTypes.push_back(BLOB1);
}
void FishWave::addSplash(){
    particles.clear();
    for (int i = 0; i < 50; i++){
        particle2 myParticle;
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
void FishWave::addFish(){
    fishPos = polyline.getPointAtPercent(ofRandom(0, 1));
    fishes.clear();
    shapes.clear();
    particle myParticle;
    myParticle.setInitialCondition(fishPos.x, fishPos.y, 0, ofRandom(-0.7, -0.8));
    fishGravity = ofRandom(-3, -0.8);
    fishDirection = ofRandom(-0.7, 0.7);
//    myParticle.radius = ofRandom(20, 30);
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
void FishWave::updateFishWave(){
    updateMesh();
    updateSplashes();
}
void FishWave::updateMesh(){
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
void FishWave::updateSplashes(){
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
void FishWave::draw(){
    for (int i = 0; i < polyline.getVertices().size(); i++) {
        ofVec2f p = polyline.getVertices()[i];
        ofSetColor(0, shadowOpacity);
        img.draw(p-ofVec2f(shadowRadius, shadowRadius), shadowRadius*2, shadowRadius*2);
    }
    drawSplashes();
    m.draw();
    //    strokeMesh.draw();
}
void FishWave::drawSplashes(){
    for (int i = 0; i < particles.size(); i++){
        ofFill();
        particles[i].draw();
        ofSetColor(particles[i].color);
        ofDrawCircle(particles[i].pos, particles[i].radius);
    }
    for (int i = 0; i < shapes.size(); i++){
        ofPushMatrix();
        ofTranslate(fishes[i].pos);
        ofRotateZ(fishes[i].vel.x/2*ofGetFrameNum());
        shapes[i]->draw();
        ofPopMatrix();
    }
    
}
