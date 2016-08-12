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
    stencilWaves.setupGui();
    stencilWaves.cvData = cvData;
    waveManager.cvData = cvData;
    waveManager.setupGui();
    setupGui();
    waveManager.setup();
    stencilWaves.setup();
}
void wavesScene::setupGui(){
    gui.setup("settings_wavesScene", "settings_wavesScene.xml");
    parameters.add(isStencilWaveMode.set("isStencilWaveMode", true));
    parameters.add(isWaveManagerMode.set("isWaveManagerMode", false));
    parameters.setName("wavesSceneParameters");
    gui.add(parameters);
    gui.add(waveManager.parameters);
    gui.add(stencilWaves.parameters);
    gui.loadFromFile("settings_wavesScene.xml");
}
// ------------ Update
void wavesScene::update(){
    if(isWaveManagerMode) waveManager.update();
    if(isStencilWaveMode) stencilWaves.update();
}
// ------------ Draw
void wavesScene::draw(){
    if(isWaveManagerMode) waveManager.draw();
    if(isStencilWaveMode) stencilWaves.draw();

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