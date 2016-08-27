//
//  eyeLinkerMode.cpp
//  funkyForms
//
//  Created by Gordey on 8/10/16.
//
//

#include "eyeLinkerMode.hpp"
// ------------------- setup
void eyeLinkerMode::setup(){
    
}
void eyeLinkerMode::setupGui(){
    parameters.setName("eyeLinkerParameters");
    parameters.add(width.set("width", 100, 10, 600));
    parameters.add(height.set("height", 100, 10, 600));
    parameters.add(scale.set("scale", 1.0, 0.2, 6));
    parameters.add(inputScaleRange.set("inputScaleRange", 1.0, 0.5, 2));
    parameters.add(velSmooth.set("velSmooth", 0.9, 0.8, 0.999));
    parameters.add(outputScaleRange.set("outputScaleRange", 1.0, 0.5, 5.0));
    parameters.add(scaleClip.set("scaleClip", false));
    parameters.add(isGlow.set("isGlow", true));
    
    // particles
    parameters.add(particleTreshold.set("particleTreshold", 0.5, 0.1, 1));
    parameters.add(particleForce.set("particleForce", 0.1, 0.1, 1));
    parameters.add(particleRadius.set("particleRadius", 50, 10, 500));
    parameters.add(particleSize.set("particleSize", 5, 1, 30));

    parameters.add(glowRadius.set("glowRadius", 20, 5, 70));
    parameters.add(glowOpacity.set("glowOpacity", 120, 0, 255));
    parameters.add(glowResolution.set("glowResolution", 20, 5, 200));
//    scale.addListener(this, &eyeLinkerMode::setupParameters);
}
void eyeLinkerMode::setupParameters(float &v){
    for(auto &e : eyeLinkers){
        e.setScale(scale);
    }
}
void eyeLinkerMode::addEye(int packetId, int id, ofVec2f pos){
    EyeLinker eyelinker;
    eyeLinkers.push_back(eyelinker);
    int i = eyeLinkers.size()-1;
    eyeLinkers[i].id = id;
    eyeLinkers[i].packetId = packetId;
    eyeLinkers[i].pos = pos;
    eyeLinkers[i].setSize(width, height);
    eyeLinkers[i].setup();
    eyeLinkers[i].setScale(scale);
}
void eyeLinkerMode::removeEye(int packetId, int id){
    for(auto &e : eyeLinkers ){
        if(e.id == id && e.packetId == packetId){
            e.out();
        }
    }
}
void eyeLinkerMode::fadeIn(){
    eyeLinkers.clear();
    for(auto &e : eyeLinkers ){
        for(auto &ee: e.eyes){
            ee.open();
        }
    }
}
void eyeLinkerMode::fadeOut(){
    for(auto &e : eyeLinkers ){
        e.out();
    }
}
void eyeLinkerMode::setTargetPos(int packetId, int id, ofVec2f pos){
    targets[packetId][id].pos = pos;
}
void eyeLinkerMode::setTargetVel(int packetId, int id, ofVec2f vel){
    targets[packetId][id].vel = vel;
}
void eyeLinkerMode::clear(){
    bool isEnabled = false;
    bool isFadeFinished = false;
    bool isFading = false;
    eyeLinkers.clear();
}
// ------------------- udpate
void eyeLinkerMode::update(){
    updateFadeCheck();
    updateParameters();
    updateEyeRemoval();
    updateEye();
    targets[0].clear();
    targets[1].clear();
}
void eyeLinkerMode::updateFadeCheck(){
    bool isFin = true;
    
    // tell eyelinker stop to creating new particles
    if(isFading){
        for(auto &e: eyeLinkers){
            e.isFading = true;
        }
    }
    for(auto &e : eyeLinkers ){
        for(auto &eye: e.eyes){
            if(!eye.isCloseFinished()){
                isFin = false;
                break;
            }
        }
    }
    if(isFin){
        isFadeFinished = true;
    }else{
        isFadeFinished = false;
    }
}
void eyeLinkerMode::updateParameters(){
    for(auto &e : eyeLinkers ){
        e.isGlow = isGlow;
        e.glowRadius = glowRadius;
        e.glowOpacity = glowOpacity;
        e.glowResolution = glowResolution;
        e.velSmooth = velSmooth;
        e.particleTreshold = particleTreshold;
        e.particleForce = particleForce;
        e.particleRadius = particleRadius;
        e.particleSize = particleSize;
    }
}
void eyeLinkerMode::updateEye(){
    for(auto &e : eyeLinkers ){
        for (int i = 0; i < 2; i++) {
            for(auto &t : targets[i]){
                if(i == e.packetId && t.first == e.id ){
                    ofVec2f pos = t.second.pos;
                    e.setPos(pos);
                }
            }
        }
        float s = ofMap(e.vel.length(), -inputScaleRange, inputScaleRange, scale-outputScaleRange, scale+outputScaleRange, scaleClip);
        e.setScale(s);
        e.update();
    }
}
void eyeLinkerMode::updateEyeRemoval(){
    eyeLinkers.erase(std::remove_if(
                                     eyeLinkers.begin(),
                                     eyeLinkers.end(),
                                     
                                     [&](EyeLinker & e){
                                         return e.isFinished();
                                     }
                                     ),
                      eyeLinkers.end()
                      );
}
// ------------------- draw
void eyeLinkerMode::draw(){
    for(auto &e : eyeLinkers ){
        e.draw();
    }
}
