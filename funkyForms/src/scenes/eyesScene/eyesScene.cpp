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
}
void eyesScene::updateModeSwitch(){
}
void eyesScene::updateTargets(){
    for(auto &id : cvData[0]->idsThisFrame){
        ofPoint pt = cvData[0]->getTopPointAt(id);
        ofVec2f vel = cvData[0]->getVelAvgSmoothAt(id);
        pt =  cvData[0]->remapForScreen(SCREEN_LEFT, pt);
        
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
    
//    ofVec2f p;
//    float posYmax = ofGetHeight();
//    
//    int size =  cvData[0]->idsThisFrame.size();
//    for(auto &id: cvData[0]->idsThisFrame){
//        
//        
//        //if ((*(cvData[0]->trackedContours))[id].data.resampleSmoothed.size() > 0){
//        ofVec2f pos = (*(cvData[0]->trackedContours))[id].data.resampleSmoothed.getVertices()[0];
//        pos = cvData[0]->remapForScreen(SCREEN_LEFT, pos);
//        p += pos;
//        if(pos.y < posYmax){
//            posYmax = pos.y;
//        }
//        //}
//    }
//    p = ofVec2f(p.x/(size+1), posYmax);
//    float s = 0.9;
//    averagePos = averagePos*s + (1-s)*p;
    
    // rewritten without trackers
    
    ofPoint p;
    float posYmax = ofGetHeight();

    int size = 0;
    for(auto &blob: cvData[0]->blobs){

        for (auto pos : blob.blob){
            //if ((*(cvData[0]->trackedContours))[id].data.resampleSmoothed.size() > 0){
            //ofVec2f pos = (*(cvData[0]->trackedContours))[id].data.resampleSmoothed.getVertices()[0];
            pos = cvData[0]->remapForScreen(SCREEN_LEFT, pos);
            p += pos;
            size++;
            if(pos.y < posYmax){
                posYmax = pos.y;
            }
        }
        //}
    }
    p = ofPoint(p.x/(size+1), posYmax);
    float s = 0.9;
    averagePos = averagePos*s + (1-s)*p;
}


void eyesScene::updateFastestPos(){
    
    // need something better here!
    
//    int targetId = 0;
//    ofVec2f zero(0, 0);
//    ofVec2f vel(0, 0);
//
//    for(auto &id: cvData[0]->idsThisFrame){
//        ofVec2f curVel = (*(cvData[0]->trackedContours))[id].velAvgSmooth;
//        if(curVel.distance(zero) > vel.distance(zero)){
//            vel = curVel;
//            targetId = id;
//        }
//    }
//    if ((*(cvData[0]->trackedContours))[targetId].data.resampleSmoothed.size() > 0){
//        fastestPos = (*(cvData[0]->trackedContours))[targetId].data.resampleSmoothed.getVertices()[0];
//        fastestPos = cvData[0]->remapForScreen(SCREEN_LEFT, fastestPos);
//    }
    
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
    for (int i = 0; i < cvData[0]->blobs.size(); i++){
        ofSetColor(255);
        ofPolyline line = cvData[0]->blobs[i].blob;
        for (auto & pt : line){
            pt = cvData[0]->remapForScreen(SCREEN_LEFT, pt);
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
void eyesScene::blobBorn(int packetId, int id){
    
    if (packetId == 1) return;
    
    ofPoint pt = cvData[0]->getTopPointAt(id);
    pt = cvData[0]->remapForScreen(SCREEN_LEFT, pt);
    if(!getMode("eyeLinkerMode")->isFading) eyeLinkerMode.addEye(id, pt);
}
void eyesScene::blobDied(int packetId, int id){
    
    if (packetId == 1) return;
    
    if(!getMode("eyeLinkerMode")->isFading) eyeLinkerMode.removeEye(id);
}

