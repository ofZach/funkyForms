//
//  eyeParticlesMode.cpp
//  EyeScene
//
//  Created by Zerc on 7/12/16.
//
//

#include "eyeParticlesMode.hpp"
// ---------------------------------- setup
void eyeParticlesMode::setup(){
    behavior = B_ATTACK;
    init();
}
void eyeParticlesMode::setupGui(){
    parameters.setName("eyeParticlesModeParameters");
    parameters.add(behaviorMode.set("behaviorMode", 0, 0, 2));
    parameters.add(count.set("count", 50, 1, 500));
    parameters.add(initButton.set("initButton", true));
    parameters.add(attractionForce.set("attractionForce", 0.5, 0.01, 1));
    parameters.add(repulsionForce.set("repulsionForce", 2.5, 0.01, 10));
    parameters.add(repulsionRadius.set("repulsionRadius", 2, 0.5, 5));
    parameters.add(attractionRadius.set("attractionRadius", 1000, 10, 2000));
    parameters.add(scaleSpeed.set("scaleSpeed", 0.07, 0.01, 0.2));
    parameters.add(scaleMax.set("scaleMax", 3., 1.0, 7));
    parameters.add(scaleRadius.set("scaleRadius", 200, 10, 2000));
    initButton.addListener(this, &eyeParticlesMode::reset);
}
void eyeParticlesMode::reset(bool &b){
    init();
}
void eyeParticlesMode::init(){
    eyes.clear();
    particles.clear();
    for (int i = 0; i < count; i++){
        eyeParticle myParticle;
        float x = ofRandom(0,ofGetWidth());
        float y = ofRandom(0,ofGetHeight());
        myParticle.setInitialCondition(x,y,0,0);
        particles.push_back(myParticle);
        
        eye eye;
        eyes.push_back(eye);
        eyes[i].setup(ofVec2f(x, y), 50, 50);
        eyes[i].delay = ofRandom(20);
        eyes[i].setEyeColor(ofColor::darkGray);
        eyes[i].setScale(ofRandom(1, 2));
    }
}
void eyeParticlesMode::setTargetPos(int id, ofVec2f pos){
    targets[id].pos = pos;
}
void eyeParticlesMode::setTargetVel(int id, ofVec2f vel){
    targets[id].vel = vel;
}
void eyeParticlesMode::fadeIn(){
    for(auto &eye: eyes){
        eye.open();
    }
}
void eyeParticlesMode::fadeOut(){
    for(auto &eye: eyes){
        eye.close();
    }
}
// ---------------------------------- Update
void eyeParticlesMode::update(){
    updateFadeCheck();
    switch (behaviorMode) {
        case 0:
            behaveAttack();
            break;
        case 1:
            behaveWait();
            break;
        case 2:
            behaveRandom();
            break;
        default:
            break;
    }
    targets.clear();
}
void eyeParticlesMode::updateFadeCheck(){
    bool isFin = true;
    for(auto &eye: eyes){
        if(!eye.isCloseFinished()){
            isFin = false;
            break;
        }
    }
    if(isFin){
        isFadeFinished = true;
    }else{
        isFadeFinished = false;
    }
}
// ---------------------------------- Behavior
void eyeParticlesMode::behaveRandom(){
    for (int i = 0; i < particles.size(); i++){
        eyes[i].update(particles[i].getPos());
        eyes[i].setAngle(ofRadToDeg(particles[i].getAngle()));
        particles[i].resetForce();
    }
    for (int i = 0; i < particles.size(); i++){
        
        float radius = eyes[i].getWidth()/repulsionRadius;
        for (int j = 0; j < i; j++){
            if (i != j){
                particles[i].addForFlocking(particles[j]);
            }
            float radius2 = eyes[j].getWidth()/repulsionRadius;
        }
    }
    // todo: scale doesn't work properly
    for(auto &t: targets){
        ofPoint pos = t.second.pos;
        for (int i = 0; i < particles.size(); i++){
            eyes[i].lookAtNear(pos);
            eyes[i].addScaleForce(pos, scaleRadius, scaleSpeed, scaleMax);
        }
    }
    for (int i = 0; i < particles.size(); i++){
        particles[i].addDampingForce();
        particles[i].addFlockingForce();
        particles[i].update();
        
        ofVec2f pos = particles[i].pos;
        if (pos.x < 0) pos.x = ofGetWidth();
        if (pos.x > ofGetWidth()) pos.x = 0;
        if (pos.y < 0) pos.y = ofGetHeight();
        if (pos.y > ofGetHeight()) pos.y = 0;
        particles[i].pos = pos;
    }
}
void eyeParticlesMode::behaveWait(){
    for (int i = 0; i < particles.size(); i++){
        for(auto &t: targets){
            ofPoint pos = t.second.pos;
            ofVec2f vel = t.second.vel;
            eyes[i].addScaleForce(pos, scaleRadius, scaleSpeed, scaleMax);
            eyes[i].lookAtNear(pos);
        }
        eyes[i].update(particles[i].getPos());
        eyes[i].setAngle(ofRadToDeg(particles[i].getAngle()));
        particles[i].resetForce();
    }
    for (int i = 0; i < particles.size(); i++){
        float radius = eyes[i].getWidth()/repulsionRadius;
        for (int j = 0; j < i; j++){
            float radius2 = eyes[j].getWidth()/repulsionRadius;
            particles[i].addRepulsionForce(particles[j], radius + radius2, repulsionForce);
        }
        for(auto &t: targets){
            ofPoint pos = t.second.pos;
            ofVec2f vel = t.second.vel;
            particles[i].addRepulsionForce(pos.x, pos.y, 100, ofMap(vel.y, -10, 10, 0, 0.2, true));
        }
    }
    for (int i = 0; i < particles.size(); i++){
        particles[i].addDampingForce();
        particles[i].update();
    }
    
}
void eyeParticlesMode::behaveAttack(){
    for (int i = 0; i < particles.size(); i++){
        for(auto &t: targets){
            ofPoint pos = t.second.pos;
            ofVec2f vel = t.second.vel;
            eyes[i].lookAtNear(pos);
            eyes[i].addScaleForce(pos, scaleRadius, scaleSpeed, scaleMax);
        }
        eyes[i].update(particles[i].getPos());
        eyes[i].setAngle(ofRadToDeg(particles[i].getAngle()));
        particles[i].resetForce();
    }
    for (int i = 0; i < particles.size(); i++){
        float radius = eyes[i].getWidth()/repulsionRadius;
        for (int j = 0; j < i; j++){
            float radius2 = eyes[j].getWidth()/repulsionRadius;
            particles[i].addRepulsionForce(particles[j], radius + radius2, repulsionForce);
        }
        for(auto &t: targets){
            ofPoint pos = t.second.pos;
            ofVec2f vel = t.second.vel;
            eyes[i].lookAtNear(pos);
            particles[i].addAttractionForce(pos.x, pos.y, 1000, attractionForce);
        }
        
    }
    for (int i = 0; i < particles.size(); i++){
        particles[i].addDampingForce();
        particles[i].update();
    }
}
// ---------------------------------- Draw
void eyeParticlesMode::draw(){
    ofSetColor(ofColor::lightBlue);
    for (int i = 0; i < particles.size(); i++){
        eyes[i].draw();
    }
}