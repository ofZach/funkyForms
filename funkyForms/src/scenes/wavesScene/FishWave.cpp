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
    addFishParticle();
    addShape();
}
void FishWave::addShape(){
    SpikeShape spikeShape;
    ofPath path;
    int numSides = ofRandom(spikeCountMin, spikeCountMax);
    ofVec2f p1(0, ofRandom(shapeInRadius, shapeInRadius/2));
    ofVec2f p2(0, ofRandom(shapeOutRadius, shapeOutRadius/2));
    p2.rotate((360.0/numSides)/2);
    for(int i = 0; i < numSides; i++){
        p1.rotate(360.0/numSides);
        p2.rotate(360.0/numSides);
        path.lineTo(p1);
        path.lineTo(p2);
    }
    spikeShape.path = path;
    spikeShape.pos = fishPos;
    shapes.push_back(spikeShape);
}
void FishWave::addFishParticle(){
    particleWithAge myParticle;
    myParticle.setInitialCondition(fishPos.x, fishPos.y, 0, ofRandom(-0.7, -0.8));
    myParticle.ageMax = ofRandom(floatAge, floatAge*1.5);
    fishGravity = ofRandom(-3, -0.8);
    fishDirection = ofRandom(-0.7, 0.7);
    particlesBouey.push_back(myParticle);
}
// ------- update
void FishWave::updateFishWave(){
    updateFade();
    updateMesh();
    updateSplashes();
    updateFishParticles();
    updateFishRemoval();
}
void FishWave::updateFade(){
    fadeAnimator.update();

}
void FishWave::updateFishParticles(){    
    for (int i = 0; i < particlesBouey.size(); i++){
        particlesBouey[i].resetForce();
        particlesBouey[i].age++;
    }
    
    int time = ofGetFrameNum();
    
    for (int i = 0; i < particlesBouey.size(); i++){
        // gravity
        if(particlesBouey[i].age > particlesBouey[i].ageMax){
            // gravity up
            particlesBouey[i].addForce(0, -0.2);
        }else{
            // gravity down
            particlesBouey[i].addForce(0, 0.2);
        }
        
        // attraction
        ofVec2f pPos = particlesBouey[i].pos; // particle pos
        for (int k = 0; k < points.size(); k++){
            ofVec2f wPos = points[k].p;
            particlesBouey[i].addAttractionForce(wPos.x, wPos.y, 50, 0.5);
        }
        
        // add noise
        ofPoint pos = particlesBouey[i].pos;
        float speed = ofMap(time-particlesBouey[i].age, 1, 5, 1, 0, true);
        float xNoise = ofSignedNoise(pos.x * 0.1, pos.y * 0.1, i, time * 0.1);
        float yNoise = ofSignedNoise(pos.x * 0.1, pos.y * 0.1, i, time * 0.1 + 100000);
        particlesBouey[i].addForce(xNoise*0.2 * speed, -fabs(yNoise) * 0.2 * speed);
    }
    
    for(auto &f: particlesBouey){
        f.addDampingForce();
        f.update();
    }
    fishGravity += 0.06;
}
void FishWave::updateFishRemoval(){
    for (int i = 0; i < particlesBouey.size(); i++) {
        if(particlesBouey[i].pos.y < 0){
            shapes.erase(shapes.begin()+i);
        }
    }
    particlesBouey.erase(std::remove_if(
                                     particlesBouey.begin(),
                                     particlesBouey.end(),
                                     
                                     [&](particleWithAge & p){
                                         return (p.pos.y < 0);
                                     }
                                     ),
                      particlesBouey.end()
                      );
}
void FishWave::updateMesh(){
    m.clear();
    strokeMesh.clear();
    
    for (int i = 0; i < polyline.getVertices().size(); i++) {
        ofVec2f p = polyline.getVertices()[i];
        ofVec2f p2 = ofVec2f(p.x, screenH);
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

}
// ------- draw
void FishWave::draw(){
    for (int i = 0; i < polyline.getVertices().size(); i++) {
        ofVec2f p = polyline.getVertices()[i];
        ofSetColor(0, shadowOpacity);
        img.draw(p-ofVec2f(shadowRadius * sf, shadowRadius * sf ), shadowRadius * sf * 2, shadowRadius * sf * 2);
    }
//    drawSplashes();
    float opacity = ofMap(fadeAnimator.getValue(), 0, 1, 0, 255);
    ofSetColor(opacity);
    drawShapes();
    m.draw();
    //    strokeMesh.draw();
}
void FishWave::drawShapes(){
    for (int i = 0; i < shapes.size(); i++){
        shapes[i].pos =  shapes[i].pos * 0.9 + 0.1 *particlesBouey[i].pos;
        ofPushMatrix();
        ofTranslate(shapes[i].pos);
//        ofRotateZ(particlesBouey[i].vel.normalize().x/2*ofGetFrameNum());
        shapes[i].path.setFillColor(ofColor(shapes[i].path.getFillColor(), shapeOpacity));
        shapes[i].path.draw();
        ofPopMatrix();
    }
}
void FishWave::drawSplashes(){
    for (int i = 0; i < particles.size(); i++){
        ofFill();
        particles[i].draw();
        ofSetColor(particles[i].color);
        ofDrawCircle(particles[i].pos, particles[i].radius);
    }

    
}
