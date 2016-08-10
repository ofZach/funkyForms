//
//  plantsScene.cpp
//  funkyForms
//
//  Created by Gordey on 8/8/16.
//
//

#include "plantsScene.hpp"
void plantsScene::setup(){
    plantManager.cvData = cvData;
    plantManager.setupGui();
    glow.load("assets/glow.png");
    setupGui();
    plantManager.setup();
}
void plantsScene::setupGui(){
    parameters.setName("plantsSceneParameters");
    parameters.add(glowRadius.set("glowRadius", 10, 1, 50));
    parameters.add(glowOpacity.set("glowOpacity", 100, 0, 255));
    gui.setup("settings_plantsScene", "settings_plantsScene.xml");
    gui.add(parameters);
    gui.add(plantManager.parameters);
    gui.loadFromFile("settings_plantsScene.xml");
}
void plantsScene::update(){
    plantManager.update();
}
void plantsScene::draw(){
    plantManager.draw();
    drawPeople();
    gui.draw();
}
void plantsScene::drawPeople(){
    for (int i = 0; i < cvData->blobs.size(); i++){
        ofPath p;
        p.setFillColor(ofColor::black);
        ofPolyline line = cvData->blobs[i].blob;
        line.simplify();
        for(auto &l : line){
            p.lineTo(l);
            float x = l.x - glowRadius;
            float y = l.y - glowRadius;
            ofSetColor(255, glowOpacity);
            glow.draw(x, y, glowRadius*2, glowRadius*2);
        }
        p.draw();
    }
}
void plantsScene::blobBorn(int id){
    int whichBlob = cvData->idToBlobPos[id];
    ofPoint centroid = cvData->blobs[whichBlob].blob.getCentroid2D();
    plantManager.addPlant(centroid, id);
}
void plantsScene::blobDied(int id){
    plantManager.remove(id);
}
void plantsScene::start(){
    plantManager.reset();
}
void plantsScene::stop(){
}