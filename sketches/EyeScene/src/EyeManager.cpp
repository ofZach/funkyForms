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
        eyes[i].setup(ofVec2f(x, y), 100, 100);
        eyes[i].setEyeColor(ofColor::lightBlue);
        eyes[i].setScale(ofRandom(1, 2));
    }
}
void EyeManager::update(float x, float y){
    ofVec2f mPos(x, y);
    
    for (int i = 0; i < particles.size(); i++){
        eyes[i].addScaleForce(mPos, 200, 0.07, 3.);
        eyes[i].update(particles[i].getPos());
        particles[i].resetForce();
    }
    for (int i = 0; i < particles.size(); i++){
        float radius = eyes[i].getWidth()/2;
        for (int j = 0; j < i; j++){
            float radius2 = eyes[j].getWidth()/2;
            particles[i].addRepulsionForce(particles[j], radius + radius2, 2.5);
        }
        particles[i].addAttractionForce(x, y, 1000, 0.5);
    }
    for (int i = 0; i < particles.size(); i++){
        particles[i].addDampingForce();
        particles[i].update();
    }
}
void EyeManager::draw(){
    for (int i = 0; i < particles.size(); i++){
        particles[i].draw();
        eyes[i].draw();
    }
}