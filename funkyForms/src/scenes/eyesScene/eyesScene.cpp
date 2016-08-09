//
//  eyesScene.cpp
//  funkyForms
//
//  Created by Gordey on 8/9/16.
//
//

#include "eyesScene.hpp"
// ------------ setup
void eyesScene::setup(){
    eyePair.setup();
    setupGui();
//    eyeLinker.setup();
    eyeParticles.cvData = cvData;
    eyeParticles.setup();
}
void eyesScene::setupGui(){
    parameters.setName("eyesSceneParameters");
    parameters.add(isEyePairMode.set("isEyePairMode", true));
    parameters.add(isEyeParticleMode.set("isEyeParticleMode", true));
    parameters.add(isEyeLinkerMode.set("isEyeLinkerMode", true));
    gui.setup("eyesScene_settings", "eyesScene_settings.xml");
    gui.add(parameters);
    gui.loadFromFile("eyesScene_settings.xml");
}
// ------------ update
void eyesScene::update(){
    updateAveragePos();
    updateFastestPos();
    if(isEyePairMode){
        eyePair.update(averagePos);
        eyePair.lookAtSmart(fastestPos);
    }
    if(isEyeParticleMode){
        eyeParticles.update();
    }

}
void eyesScene::updateAveragePos(){
    ofVec2f p;
    float posYmax = ofGetHeight();
    
    int size =  cvData->idsThisFrame.size();
    for(auto &id: cvData->idsThisFrame){
        ofVec2f pos = (*(cvData->trackedContours))[id].resampleSmoothed.getVertices()[0];
        p += pos;
        if(pos.y < posYmax){
            posYmax = pos.y;
        }
    }
    p = ofVec2f(p.x/(size+1), posYmax);
    float s = 0.9;
    averagePos = averagePos*s + (1-s)*p;
}
void eyesScene::updateFastestPos(){
    int targetId = 0;
    ofVec2f zero(0, 0);
    ofVec2f vel(0, 0);

    for(auto &id: cvData->idsThisFrame){
        ofVec2f curVel = (*(cvData->trackedContours))[id].velAvgSmooth;
        if(curVel.distance(zero) > vel.distance(zero)){
            vel = curVel;
            targetId = id;
        }
    }
    fastestPos = (*(cvData->trackedContours))[targetId].resampleSmoothed.getVertices()[0];
}
// ------------ draw
void eyesScene::draw(){
    if(isEyePairMode){
        eyePair.draw();
    }
    if(isEyeParticleMode){
        eyeParticles.draw();
    }
    drawPeople();
    gui.draw();
}
void eyesScene::drawPeople(){
    for (int i = 0; i < cvData->blobs.size(); i++){
        ofSetColor(255);
        ofPolyline line = cvData->blobs[i].blob;
        line.draw();
    }
}
// ------------ events
void eyesScene::start(){
    
}
void eyesScene::stop(){

}
void eyesScene::blobBorn(int id){

}
void eyesScene::blobDied(int id){

}

