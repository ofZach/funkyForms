//
//  EyeManager.cpp
//  EyeScene
//
//  Created by Zerc on 7/12/16.
//
//

#include "EyeManager.hpp"
void EyeManager::setup(){
    for (int i = 0; i < 20; i++){
        particle myParticle;
        float x = ofRandom(0,ofGetWidth());
        float y = ofRandom(0,ofGetHeight());
        myParticle.setInitialCondition(x,y,0,0);
        particles.push_back(myParticle);
        eyes.push_back(*new eye());
        float w = ofRandom(50,200);
        float h = w/ofRandom(0.7, 2.);
        eyes[i].setup(ofVec2f(x, y), w, w);
    }
}
void EyeManager::update(float x, float y){
    for (int i = 0; i < particles.size(); i++){
        particles[i].resetForce();
    }
    for (int i = 0; i < particles.size(); i++){
        float radius = eyes[i].getWidth();
        for (int j = 0; j < i; j++){
            particles[i].addRepulsionForce(particles[j], radius, 2.5);
        }
        particles[i].addAttractionForce(x, y, 1000, 0.5);
    }
    for (int i = 0; i < particles.size(); i++){
        particles[i].addDampingForce();
        particles[i].update();
        eyes[i].update(particles[i].getPos());
    }
}
void EyeManager::draw(){
    for (int i = 0; i < particles.size(); i++){
        particles[i].draw();
        eyes[i].draw();
    }
}