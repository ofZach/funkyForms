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
    eyeParticlesMode.setupGui();
    eyeLinkerMode.setupGui();
    setupGui();
    
    // setup
    eyePairMode.setup();

    eyeLinker.setSize(eyeLinkerMode.width, eyeLinkerMode.height);
    eyeLinkerMode.setup();
    
    eyeParticlesMode.setup();
    
    eyeLinker.setup();
    
    eyeLinkerMode.isEnabled = true; // first showed
    eyePairMode.isEnabled = false;
    eyeLinkerMode.isEnabled = false;
    
    modes.push_back(&eyeLinkerMode);
    modes.push_back(&eyeParticlesMode);
    modes.push_back(&eyePairMode);
}
void eyesScene::setupGui(){
    parameters.setName("eyesSceneParameters");
    gui.setup("settings_eyesScene", "settings_eyesScene.xml");
    gui.add(parameters);
    gui.add(eyeParticlesMode.parameters);
    gui.add(eyeLinkerMode.parameters);
    gui.loadFromFile("settings_eyesScene.xml");
}
modeBase *eyesScene::getMode(string name){
    if(name == "eyeLinkerMode") return modes[0];
    if(name == "eyeParticlesMode") return modes[1];
    if(name == "eyePairMode") return modes[2];
}
void eyesScene::advanceMode(){
    // 1. fade out cur mode
    // 2. whait till it finished
    // 3. fade in next mode
    
    modes[curMode]->fadeOut();
    modes[curMode]->isFading = true;
    curMode++ ;
    curMode = curMode%3 ;
    ofLog() << "curMode: " << curMode;
    modes[curMode]->fadeIn();
    modes[curMode]->isEnabled = true;
    modes[curMode]->isFading = false;
    modes[curMode]->isFadeFinished = false;
}
// ------------ update
void eyesScene::update(){
   
    updateTargets();
    updateModeSwitch();
    updateAveragePos();
    updateFastestPos();
    updateEyes();
    updateModes();
//    updateEyeLinker();
}
void eyesScene::updateModes(){
    if((ofGetFrameNum()+3)%380 == 0){
        advanceMode();
    }
    for(auto &m : modes){
        if(m->isFading && m->isFadeFinished){
            m->isEnabled = false;
        }
    }

    ofLog() << "eyePairMode enabled:" << getMode("eyePairMode")->isEnabled;
    ofLog() << "eyeParticlesMode enabled:" << getMode("eyeParticlesMode")->isEnabled;
    ofLog() << "eyeLinkerMode enabled:" << getMode("eyeLinkerMode")->isEnabled;
    
}
void eyesScene::updateModeSwitch(){
}
void eyesScene::updateTargets(){
    for(auto &id : cvData->idsThisFrame){
        ofPoint pt = cvData->getTopPointAt(id);
        ofVec2f vel = cvData->getVelAvgSmoothAt(id);
        pt =  cvData->remapForScreen(SCREEN_LEFT, pt);
        
        eyeLinkerMode.setTargetPos(id, pt);
        eyeParticlesMode.setTargetPos(id, pt);
        eyeParticlesMode.setTargetVel(id, vel);
    }
}
void eyesScene::updateEyes(){
    if(getMode("eyePairMode")->isEnabled){
        eyePairMode.update(averagePos);
        eyePairMode.lookAtSmart(fastestPos);
    }
    if(getMode("eyeParticlesMode")->isEnabled){
        eyeParticlesMode.update();
    }
    if(getMode("eyeLinkerMode")->isEnabled){
        eyeLinkerMode.update();
    }
}
void eyesScene::updateEyeLinker(){
    eyeLinker.setPos(ofVec2f(ofGetMouseX(), ofGetMouseY()));
    if(ofGetKeyPressed('k')){
        eyeLinker.out();
    }
    if(ofGetKeyPressed('p')){
        eyeLinker.eyes[0].open();
    }
    eyeLinker.setScale(eyeLinkerMode.scale);
    eyeLinker.isGlow = eyeLinkerMode.isGlow;
    eyeLinker.glowRadius = eyeLinkerMode.glowRadius;
    eyeLinker.glowResolution = eyeLinkerMode.glowResolution;
    eyeLinker.glowOpacity = eyeLinkerMode.glowOpacity;
    
    eyeLinker.eyes[0].setAngle(ofGetFrameNum()%360);
    eyeLinker.update();
}
void eyesScene::updateAveragePos(){
    ofVec2f p;
    float posYmax = ofGetHeight();
    
    int size =  cvData->idsThisFrame.size();
    for(auto &id: cvData->idsThisFrame){
        if ((*(cvData->trackedContours))[id].data.resampleSmoothed.size() > 0){
        ofVec2f pos = (*(cvData->trackedContours))[id].data.resampleSmoothed.getVertices()[0];
        pos = cvData->remapForScreen(SCREEN_LEFT, pos);
        p += pos;
        if(pos.y < posYmax){
            posYmax = pos.y;
        }
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
    if ((*(cvData->trackedContours))[targetId].data.resampleSmoothed.size() > 0){
        fastestPos = (*(cvData->trackedContours))[targetId].data.resampleSmoothed.getVertices()[0];
        fastestPos = cvData->remapForScreen(SCREEN_LEFT, fastestPos);
    }
    
}
// ------------ draw
void eyesScene::draw(){
    drawEyes();
    drawPeople();
//    drawEyeLinker();
}
void eyesScene::drawGui(){
    gui.draw();
}
void eyesScene::drawEyeLinker(){
    eyeLinker.draw();
    ofSetColor(ofColor::red);

    ofPushMatrix();
    ofTranslate(eyeLinker.eyes[0].getPos());
    eyeLinker.eyes[0].lids.draw();
    ofPopMatrix();
}
void eyesScene::drawEyes(){
    for(auto &m : modes){
        if(m->isEnabled){
            m->draw();
        }
    }
}
void eyesScene::drawPeople(){
    for (int i = 0; i < cvData->blobs.size(); i++){
        ofSetColor(255);
        ofPolyline line = cvData->blobs[i].blob;
        for (auto & pt : line){
            pt = cvData->remapForScreen(SCREEN_LEFT, pt);
        }
        line.draw();
    }
}
// ------------ events
void eyesScene::start(){
    
}
void eyesScene::stop(){
    eyeLinkerMode.clear();
}
void eyesScene::blobBorn(int id){
    ofPoint pt = cvData->getTopPointAt(id);
    pt = cvData->remapForScreen(SCREEN_LEFT, pt);
    if(!getMode("eyeLinkerMode")->isFading) eyeLinkerMode.addEye(id, pt);
}
void eyesScene::blobDied(int id){
    if(!getMode("eyeLinkerMode")->isFading) eyeLinkerMode.removeEye(id);
}

