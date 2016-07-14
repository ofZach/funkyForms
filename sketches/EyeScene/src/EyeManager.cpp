//
//  EyeManager.cpp
//  EyeScene
//
//  Created by Zerc on 7/12/16.
//
//

#include "EyeManager.hpp"
void EyeManager::setup(){
    parameters.add(count.set("count", 50, 1, 500));
    parameters.add(initButton.set("initButton", true));
    parameters.add(attractionForce.set("attractionForce", 0.5, 0.01, 2));
    parameters.add(repulsionForce.set("repulsionForce", 2.5, 0.01, 10));
    parameters.add(repulsionRadius.set("repulsionRadius", 2, 0.5, 5));
    parameters.add(attractionRadius.set("attractionRadius", 1000, 10, 2000));
    parameters.add(scaleSpeed.set("scaleSpeed", 0.07, 0.01, 0.2));
    parameters.add(scaleMax.set("scaleMax", 3., 1.0, 7));
    parameters.add(scaleRadius.set("scaleRadius", 200, 10, 2000));
    initButton.addListener(this, &EyeManager::reset);
    gui.setup(parameters);
    gui.loadFromFile("settings.xml");


    
    behavior = B_ATTACK;
    
    init();
}
void EyeManager::reset(bool &b){
    init();
}
void EyeManager::init(){
    eyes.clear();
    particles.clear();
    for (int i = 0; i < count; i++){
        particle myParticle;
        float x = ofRandom(0,ofGetWidth());
        float y = ofRandom(0,ofGetHeight());
        myParticle.setInitialCondition(x,y,0,0);
        particles.push_back(myParticle);
        eyes.push_back(*new eye());
        eyes[i].setup(ofVec2f(x, y), 50, 50);
        eyes[i].setEyeColor(ofColor::darkGray);
        eyes[i].setScale(ofRandom(1, 2));
    }
}
void EyeManager::update(float x, float y){
    ofVec2f mPos(x, y);
    switch (behavior) {
        case B_ATTACK:
            behaveAttack();
            break;
        case B_WAIT:
            behaveWait();
            break;
        case B_RANDOM:
            behaveRandom();
            break;
        default:
            break;
    }
}

void EyeManager::open(){
    for(auto &eye: eyes){
        eye.open();
    }
}
void EyeManager::close(){
    for(auto &eye: eyes){
        eye.close();
    }
}
// ---------------------------------- Behavior
void EyeManager::behaveRandom(){
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
    for(auto &t: *targets){
        for (int i = 0; i < particles.size(); i++){
            eyes[i].lookAtNear(t.pos);
            eyes[i].addScaleForce(t.pos, scaleRadius, scaleSpeed, scaleMax);
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
void EyeManager::behaveWait(){
    for (int i = 0; i < particles.size(); i++){
        for(auto &t: *targets){
            eyes[i].addScaleForce(t.pos, scaleRadius, scaleSpeed, scaleMax);
            eyes[i].lookAtNear(t.pos);
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
        for(auto &t: *targets){
            particles[i].addRepulsionForce(t.pos.x, t.pos.y, 100, ofMap(t.vel.x, -10, 10, 0, 0.2, true));
        }
    }
    for (int i = 0; i < particles.size(); i++){
        particles[i].addDampingForce();
        particles[i].update();
    }
    
}
void EyeManager::behaveAttack(){
    for (int i = 0; i < particles.size(); i++){
        for(auto &t: *targets){
            eyes[i].addScaleForce(t.pos, scaleRadius, scaleSpeed, scaleMax);
            eyes[i].lookAtNear(t.pos);
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
        for(auto &t: *targets){
            particles[i].addAttractionForce(t.pos.x, t.pos.y, 1000, ofMap(t.vel.x, -10, 10, 0, 1, true));
        }
        
    }
    for (int i = 0; i < particles.size(); i++){
        particles[i].addDampingForce();
        particles[i].update();
    }
}

// ---------------------------------- Draw
void EyeManager::draw(){
    ofSetColor(ofColor::lightBlue);
    for (int i = 0; i < particles.size(); i++){
        eyes[i].draw();
    }
    gui.draw();
}
