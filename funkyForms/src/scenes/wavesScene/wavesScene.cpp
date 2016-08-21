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
    // size
    int w = RM->getWidth();
    int h = RM->getHeight();
    
    // setup parameters
    stencilWaves.setupGui();
    gradientWaves.setupGui();
    
    // setup gui
    setupGui();
    
    // setup obj
    gradientWaves.setup(w, h);
    stencilWaves.screenLeft = RM->getRectForScreen(SCREEN_LEFT);
    stencilWaves.screenRight = RM->getRectForScreen(SCREEN_RIGHT);
    stencilWaves.screenCenter = RM->getRectForScreen(SCREEN_CENTER);
    stencilWaves.setup(w, h);
}
void wavesScene::setupGui(){
    gui.setup("settings_wavesScene", "settings_wavesScene.xml");
    parameters.add(isStencilWaveMode.set("isStencilWaveMode", true));
    parameters.add(isGradientWavesMode.set("isGradientWavesMode", false));
    parameters.setName("wavesSceneParameters");
    gui.add(parameters);
    gui.add(gradientWaves.parameters);
    gui.add(stencilWaves.parameters);
    gui.loadFromFile("settings_wavesScene.xml");
}
// ------------ Update
void wavesScene::update(){
    updateInput();
    if(isGradientWavesMode) gradientWaves.update();
    if(isStencilWaveMode) stencilWaves.update();
}
void wavesScene::updateInput(){
    for (int z = 0; z < 2; z++){
        for(int i=0; i< cvData[z]->blobs.size(); i++) {
            ofPolyline line = cvData[z]->blobs[i].blob;
    
            ofVec2f pt = cvData[z]->blobs[i].centroidSmoothed;
            pt = cvData[z]->remapForScreen(z == 0 ? SCREEN_LEFT : SCREEN_RIGHT, pt);
    
            for (auto & p : line.getVertices()){
                p = cvData[z]->remapForScreen(z == 0 ? SCREEN_LEFT : SCREEN_RIGHT, p);
            }
            if(isStencilWaveMode){
                stencilWaves.addPath(line);
    
                ofVec2f vel = cvData[z]->blobs[i].avgVel;
                for(auto &w: stencilWaves.waves){
                    for(auto &p: w.points){
                        if(p.p.distance(pt)<100 && vel.dot(ofVec2f(0, -1)) > 0){
                            w.addForceTo(&p, vel.normalize().y);
                        }
                    }
                }
            }
            if(isGradientWavesMode){
                ofVec2f vel = cvData[z]->blobs[i].avgVel;
                for(auto &w: gradientWaves.waves){
                    for(auto &p: w.points){
                        if(p.p.distance(pt)<100 && vel.dot(ofVec2f(0, -1)) > 0){
                            w.addForceTo(&p, vel.normalize().y);
                        }
                    }
                }
            }
        }
    }
}
// ------------ Draw
void wavesScene::draw(){

    if(isGradientWavesMode) gradientWaves.draw();
    if(isStencilWaveMode) stencilWaves.draw();

//    drawPeople();
}
void wavesScene::drawGui(){
     gui.draw();
}
void wavesScene::drawPeople(){
    for (int i = 0; i < cvData[0]->blobs.size(); i++){
        ofSetColor(255);
        ofPolyline line = cvData[0]->blobs[i].blob;
        for (auto & pt : line){
            pt = cvData[0]->remapForScreen(SCREEN_LEFT, pt);
        }
        line.draw();
    }
}
// ------------ Events
void wavesScene::start(){
}
void wavesScene::stop(){
    
}
void wavesScene::blobBorn(int packetId, int id){
    
}
void wavesScene::blobDied(int packetId, int id){
    
}