//
//  wavesScene.cpp
//  funkyForms
//
//  Created by Gordey on 8/9/16.
//
//

#include "wavesScene.hpp"
// ------------ Setup
void wavesScene::setup(){
//    stencilWaves.setup();
    waveManager.cvData = cvData;
    waveManager.setupGui();
    setupGui();
    waveManager.setup();
}
void wavesScene::setupGui(){
    gui.setup("settings_wavesScene", "settings_wavesScene.xml");
    gui.add(waveManager.parameters);
    gui.loadFromFile("settings_wavesScene.xml");
}
// ------------ Update
void wavesScene::update(){
    waveManager.update();
}
// ------------ Draw
void wavesScene::draw(){
    waveManager.draw();
    drawPeople();
    gui.draw();
}

void wavesScene::drawPeople(){
    for (int i = 0; i < cvData->blobs.size(); i++){
        ofSetColor(255);
        ofPolyline line = cvData->blobs[i].blob;
        line.draw();
    }
}
// ------------ Events
void wavesScene::start(){
    
}
void wavesScene::stop(){
    
}
void wavesScene::blobBorn(int id){
    
}
void wavesScene::blobDied(int id){
    
}