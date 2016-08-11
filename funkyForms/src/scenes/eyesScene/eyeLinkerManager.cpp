//
//  eyeLinkerManager.cpp
//  funkyForms
//
//  Created by Gordey on 8/10/16.
//
//

#include "eyeLinkerManager.hpp"
// ------------------- setup
void eyeLinkerManager::setup(){
    
}
void eyeLinkerManager::setupGui(){
    parameters.setName("eyeLinkerParameters");
    parameters.add(width.set("width", 100, 10, 600));
    parameters.add(height.set("height", 100, 10, 600));
    parameters.add(scale.set("scale", 1.0, 0.2, 6));
    parameters.add(inputScaleRange.set("inputScaleRange", 1.0, 0.5, 2));
    parameters.add(velSmooth.set("velSmooth", 0.9, 0.8, 0.999));
    parameters.add(outputScaleRange.set("outputScaleRange", 1.0, 0.5, 5.0));
    parameters.add(scaleClip.set("scaleClip", false));
    parameters.add(isGlow.set("isGlow", true));
    parameters.add(glowRadius.set("glowRadius", 20, 5, 70));
    parameters.add(glowOpacity.set("glowOpacity", 120, 0, 255));
    parameters.add(glowResolution.set("glowResolution", 20, 5, 200));
//    scale.addListener(this, &eyeLinkerManager::setupParameters);
}
void eyeLinkerManager::setupParameters(float &v){
    for(auto &e : eyes){
        e.setScale(scale);
    }
}
void eyeLinkerManager::addEye(int id, ofVec2f pos){
    EyeLinker eyelinker;
    eyes.push_back(eyelinker);
    int i = eyes.size()-1;
    eyes[i].id = id;
    eyes[i].pos = pos;
    eyes[i].setSize(width, height);
    eyes[i].setup();
    eyes[i].setScale(scale);
}
void eyeLinkerManager::removeEye(int id){
    for(auto &e : eyes ){
        if(e.id == id){
            e.out();
        }
    }
}
// ------------------- udpate
void eyeLinkerManager::update(){
    updateParameters();
    updateEyeRemoval();
    updateEye();
}
void eyeLinkerManager::updateParameters(){
    for(auto &e : eyes ){
        e.isGlow = isGlow;
        e.glowRadius = glowRadius;
        e.glowOpacity = glowOpacity;
        e.glowResolution = glowResolution;
        e.velSmooth = velSmooth;
    }
}
void eyeLinkerManager::updateEye(){
    for(auto &e : eyes ){
        for(auto &id : cv->idsThisFrame){
            if(id == e.id){
                e.setPos(cv->getTopPointAt(id));
                float s = ofMap(e.vel.length(), -inputScaleRange, inputScaleRange, scale-outputScaleRange, scale+outputScaleRange, scaleClip);
                e.setScale(s);
            }
        }
        e.update();
    }
}
void eyeLinkerManager::updateEyeRemoval(){
    for(int i = 0; i < eyes.size(); i++){
        if(eyes[i].isFinished()){
            eyes.erase(eyes.begin() + i);
        }
    }
}
// ------------------- draw
void eyeLinkerManager::draw(){
    for(auto &e : eyes ){
        e.draw();
    }
}
