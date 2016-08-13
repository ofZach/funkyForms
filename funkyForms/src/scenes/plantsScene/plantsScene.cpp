//
//  plantsScene.cpp
//  funkyForms
//
//  Created by Gordey on 8/8/16.
//
//

#include "plantsScene.hpp"
void plantsScene::setup(){
    sceneName = "plantsScene";
    plantManager.cvData = cvData;
    plantManager.setup();
}
void plantsScene::update(){
    plantManager.update();
}
void plantsScene::draw(){
    plantManager.draw();
    drawPeople();
}
void plantsScene::drawGui(){
    plantManager.drawGui();
}

void plantsScene::drawPeople(){
    for (int i = 0; i < cvData->blobs.size(); i++){
        ofPath p;
        p.setFillColor(ofColor::gray);
        ofPolyline line = cvData->blobs[i].blob;
        line.simplify();
        for(auto &l : line){
            p.lineTo(l);
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
}
void plantsScene::stop(){
}