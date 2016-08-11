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
    // gui
    eyeParticles.setupGui();
    eyeLinkerManager.setupGui();
    setupGui();
    
    // setup
    eyePair.setup();
    eyeLinkerManager.cv = cvData;
    eyeLinkerManager.setup();
    eyeParticles.cvData = cvData;
    eyeParticles.setup();
    
    eyeLinker.setup();
}
void eyesScene::setupGui(){
    parameters.setName("eyesSceneParameters");
    parameters.add(isEyePairMode.set("isEyePairMode", true));
    parameters.add(isEyeParticleMode.set("isEyeParticleMode", true));
    parameters.add(isEyeLinkerMode.set("isEyeLinkerMode", true));
    gui.setup("settings_eyesScene", "settings_eyesScene.xml");
    gui.add(parameters);
    gui.add(eyeParticles.parameters);
    gui.add(eyeLinkerManager.parameters);
    gui.loadFromFile("settings_eyesScene.xml");
}
// ------------ update
void eyesScene::update(){
    updateAveragePos();
    updateFastestPos();
    updateEyes();
//    updateEyeLinker();
}
void eyesScene::updateEyes(){
    if(isEyePairMode){
        eyePair.update(averagePos);
        eyePair.lookAtSmart(fastestPos);
    }
    if(isEyeParticleMode){
        eyeParticles.update();
    }
    if(isEyeLinkerMode){
        eyeLinkerManager.update();
    }
}
void eyesScene::updateEyeLinker(){
    eyeLinker.setPos(ofVec2f(ofGetMouseX(), ofGetMouseY()));
    if(ofGetKeyPressed('k')){
        eyeLinker.out();
    }
    if(ofGetKeyPressed('o')){
        eyeLinker.eyes[0].open();
    }
    eyeLinker.update();
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
    drawEyes();
    drawPeople();
//    drawEyeLinker();
    gui.draw();
}
void eyesScene::drawEyeLinker(){
    eyeLinker.draw();
}
void eyesScene::drawEyes(){
    if(isEyePairMode){
        eyePair.draw();
    }
    if(isEyeParticleMode){
        eyeParticles.draw();
    }
    if(isEyeLinkerMode){
        eyeLinkerManager.draw();
    }
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
    eyeLinkerManager.addEye(id, cvData->getTopPointAt(id));
}
void eyesScene::blobDied(int id){
    eyeLinkerManager.removeEye(id);
}

