//
//  EyeManager.cpp
//  EyeScene
//
//  Created by Zerc on 7/12/16.
//
//

#include "EyeManager.hpp"
void EyeManager::setup(){
    parameters.add(attractionForce.set("attractionForce", 0.5, 0.01, 2));
    parameters.add(repulsionForce.set("repulsionForce", 2.5, 0.01, 10));
    parameters.add(repulsionRadius.set("repulsionRadius", 2, 0.5, 5));
    parameters.add(attractionRadius.set("attractionRadius", 1000, 10, 2000));
    parameters.add(scaleSpeed.set("scaleSpeed", 0.07, 0.01, 0.2));
    parameters.add(scaleMax.set("scaleMax", 3., 1.0, 7));
    parameters.add(scaleRadius.set("scaleRadius", 200, 10, 2000));
    gui.setup(parameters);
    gui.loadFromFile("settings.xml");
    
    for (int i = 0; i < 200; i++){
        particle myParticle;
        float x = ofRandom(0,ofGetWidth());
        float y = ofRandom(0,ofGetHeight());
        myParticle.setInitialCondition(x,y,0,0);
        particles.push_back(myParticle);
        eyes.push_back(*new eye());
        eyes[i].setup(ofVec2f(x, y), 20, 20);
        eyes[i].setEyeColor(ofColor::darkGray);
        eyes[i].setScale(ofRandom(1, 2));
    }
}
void EyeManager::update(float x, float y){
    ofVec2f mPos(x, y);
    
    for (int i = 0; i < particles.size(); i++){
        eyes[i].addScaleForce(mPos, scaleRadius, scaleSpeed, scaleMax);
        eyes[i].update(particles[i].getPos());
        particles[i].resetForce();
    }
    for (int i = 0; i < particles.size(); i++){
        float radius = eyes[i].getWidth()/repulsionRadius;
        for (int j = 0; j < i; j++){
            float radius2 = eyes[j].getWidth()/repulsionRadius;
            particles[i].addRepulsionForce(particles[j], radius + radius2, repulsionForce);
        }
        particles[i].addAttractionForce(x, y, 1000, attractionForce);
    }
    for (int i = 0; i < particles.size(); i++){
        particles[i].addDampingForce();
        particles[i].update();
    }
}
void EyeManager::draw(){
    for (int i = 0; i < particles.size(); i++){
        eyes[i].draw();
//        particles[i].draw();
    }
    gui.draw();
}