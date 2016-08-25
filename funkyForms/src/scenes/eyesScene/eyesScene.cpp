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
    eyePairMode.setupGui();
    setupGui();
    
    // Set screens
    eyeParticlesMode.screenLeft = RM->getRectForScreen(SCREEN_LEFT);
    eyeParticlesMode.screenRight = RM->getRectForScreen(SCREEN_RIGHT);
    eyeParticlesMode.screenCenter = RM->getRectForScreen(SCREEN_CENTER);
    eyeParticlesMode.screenTop = RM->getRectForScreen(SCREEN_TOP);
    eyeParticlesMode.cvData[0] = cvData[0];
    eyeParticlesMode.cvData[1] = cvData[1];
    
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
    
    advanceMode();
}
void eyesScene::setupGui(){
    parameters.setName("eyesSceneParameters");
    parameters.add(changeMode.set("changeMode", true));
    parameters.add(isAutoChangeMode.set("isAutoChangeMode", false));
    gui.setup("settings_eyesScene", "settings_eyesScene.xml");
    gui.add(parameters);
    gui.add(eyePairMode.parameters);
    gui.add(eyeLinkerMode.parameters);
    gui.add(eyeParticlesMode.parameters);
    gui.loadFromFile("settings_eyesScene.xml");
    
    changeMode.addListener( this, &eyesScene::triggerAdvance);
}
void eyesScene::triggerAdvance(bool &b){
    advanceMode();
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
    modes[curMode]->fadeIn();
    modes[curMode]->isEnabled = true;
    modes[curMode]->isFading = false;
    modes[curMode]->isFadeFinished = false;
}
// ------------ update
void eyesScene::update(){
    updatePeopleEnergy();
    updateTargets();
    updateModeSwitch();
    updateAveragePos();
    updateFastestPos();
    updateEyes();
    updateModes();
//    updateEyeLinker();
}
void eyesScene::updatePeopleEnergy(){
    if(leftEnergy>100 && rightEnergy>100){
        leftEnergy = 0;
        rightEnergy =0;
    }
    for (int z = 0; z < 2; z++){
        for(int i=0; i< cvData[z]->blobs.size(); i++) {
            ofVec2f vel = cvData[z]->blobs[i].avgVel;
            if(z == 0){ // left
                leftEnergy += vel.length();
            }else{
                rightEnergy += vel.length();
            }
        }
    }
}
void eyesScene::updateModes(){
    if(isAutoChangeMode && ofGetFrameNum()%360 == 0){
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
    int idCounter = 0;

    for (int z = 0; z < 2; z++){
        for(auto &id : cvData[z]->idsThisFrame){
            int blobId = cvData[z]->idToBlobPos[id];
            ofVec2f pt = cvData[z]->blobs[blobId].blob.getCentroid2D();
            ofVec2f ptTop = cvData[z]->getTopPointAt(id);
            ptTop = cvData[z]->remapForScreen(z == 0 ? SCREEN_LEFT : SCREEN_RIGHT, ptTop);
            pt = cvData[z]->remapForScreen(z == 0 ? SCREEN_LEFT : SCREEN_RIGHT, pt);
            ofVec2f vel = cvData[z]->blobs[blobId].avgVel;
            eyeLinkerMode.setTargetPos(z, id, ptTop);
            ofPolyline l = cvData[z]->getResampledLineAt(id, 10);
            for (int i = 0; i < l.size(); i ++ ) {
                ofPoint pos = l.getVertices()[i];
                pos = cvData[z]->remapForScreen(z == 0 ? SCREEN_LEFT : SCREEN_RIGHT, pos);
                eyeParticlesMode.setTargetPos(idCounter, pos);
//                eyeParticlesMode.setTargetVel(idCounter, vel);
                idCounter++;
            }
        }
    }
}
void eyesScene::updateEyes(){
    if(getMode("eyePairMode")->isEnabled){
        eyePairMode.setEnergy(leftEnergy, rightEnergy);
        float x = RM->getRectForScreen(SCREEN_CENTER).getCenter().x;
        eyePairMode.update(ofVec2f(averagePos.x+x, averagePos.y));
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

    ofPoint p;
    float posYmax = ofGetHeight();

    int size = 0;
    
    for (int z = 0; z < 2; z++){
        for(int i=0; i< cvData[z]->blobs.size(); i++) {
            
            ofVec2f pt = cvData[z]->blobs[i].centroidSmoothed;
            pt = cvData[z]->remapForScreen(SCREEN_LEFT , pt);
            size++;
            ofVec2f curVel = cvData[z]->blobs[i].avgVel;
            
            if(pt.y < posYmax){
                posYmax = pt.y;
            }
        }
    }
    
    p = ofPoint(p.x/(size+1), posYmax);
    float s = 0.9;
    averagePos = averagePos*s + (1-s)*p;
}
void eyesScene::updateFastestPos(){
    
    // need something better here!

    int targetPacketId = 0;
    int targetId = 0;
    
    ofVec2f zero(0, 0);
    ofVec2f vel(0, 0);

    for (int z = 0; z < 2; z++){
        for(int i=0; i< cvData[z]->blobs.size(); i++) {
            
            ofVec2f pt = cvData[z]->blobs[i].centroidSmoothed;
            pt = cvData[z]->remapForScreen(z == 0 ? SCREEN_LEFT : SCREEN_RIGHT, pt);
            
            ofVec2f curVel = cvData[z]->blobs[i].avgVel;
            
            if(curVel.distance(zero) > vel.distance(zero)){
                vel = curVel;
                targetId = i;
                targetPacketId = z;
            }
        }
    }
    
    fastestPos = cvData[targetPacketId]->blobs[targetId].blob.getCentroid2D();
    fastestPos = cvData[0]->remapForScreen(targetPacketId == 0 ? SCREEN_LEFT : SCREEN_RIGHT, fastestPos);
}
// ------------ draw
void eyesScene::draw(){
    drawPeople();
    drawEyes();
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
    for (int z = 0; z < 2; z++){
        for(int i=0; i< cvData[z]->blobs.size(); i++) {
            ofPolyline &line = cvData[z]->blobs[i].blob;
            
            ofVec2f pt = cvData[z]->blobs[i].centroidSmoothed;
            pt = cvData[z]->remapForScreen(z == 0 ? SCREEN_LEFT : SCREEN_RIGHT, pt);
            
            for (auto & p : line.getVertices()){
                p = cvData[z]->remapForScreen(z == 0 ? SCREEN_LEFT : SCREEN_RIGHT, p);
            }
            ofVec2f vel = cvData[z]->blobs[i].avgVel;
            ofPath path;
            for(auto &p : line){
                path.lineTo(p);
            }
            path.setFillColor(255);
            path.draw();
        }
    }
}
// ------------ events
void eyesScene::start(){
    
}
void eyesScene::stop(){
    eyeLinkerMode.clear();
}
void eyesScene::blobBorn(int packetId, int id){
    ofPoint pt = cvData[packetId]->getTopPointAt(id);
    pt = cvData[packetId]->remapForScreen(packetId == 0 ? SCREEN_LEFT : SCREEN_RIGHT, pt);
    if(!getMode("eyeLinkerMode")->isFading) eyeLinkerMode.addEye(packetId, id, pt);
}
void eyesScene::blobDied(int packetId, int id){
    ofPoint pt = cvData[packetId]->getTopPointAt(id);
    pt = cvData[packetId]->remapForScreen(packetId == 0 ? SCREEN_LEFT : SCREEN_RIGHT, pt);
    if(!getMode("eyeLinkerMode")->isFading) eyeLinkerMode.removeEye(packetId, id);
}

