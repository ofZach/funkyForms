//
//  PlantManager.cpp
//  PlantSpring
//
//  Created by Zerc on 8/5/16.
//
//

#include "PlantManager.hpp"
// --------------- setup
void PlantManager::setup(){
    setupGui();

//    for (int i = 0; i < 4; i++) {
//        addBgPlant( ofVec2f(ofRandomWidth(), ofGetHeight() ) );
//    }
    for (int i = 0; i < 40; i++) {
        randSwatchIndex.push_back((int)ofRandom(4));
    }
}
void PlantManager::addBgPlant(ofVec2f _pos){
    bgPlants.push_back( *new Plant );
    int i = bgPlants.size()-1;
    
    bgPlants[i].rig.cbCount = ofRandom(5, 7) ;
    bgPlants[i].rig.mbCount = ofRandom(4, 6) ;
    
    bgPlants[i].rig.dir = ofVec2f(0, -1);
    bgPlants[i].rig.mbLengthMax = 200 ;
    bgPlants[i].rig.mbLengthMin = 100 ;
    bgPlants[i].rig.cbLengthMax = 70 ;
    bgPlants[i].rig.cbLengthMin = 20 ;
    bgPlants[i].rig.timeSpeed = 0.01;
    
    bgPlants[i].mbWidth = 50;
    bgPlants[i].cbWidth = 10;
    bgPlants[i].rig.pos = _pos;
    
    ofFloatColor col = swatch[(int)ofRandom(4)];
    col.setBrightness(col.getBrightness()/2);
    bgPlants[i].color = col;
    
    bgPlants[i].setup();
    bgPlants[i].ageMax = ofRandom(600, 1000);
    bgPlants[i].fadeIn();
}
void PlantManager::addPlant(ofVec2f _pos, int id){
    plants.push_back( *new Plant );
    int i = plants.size()-1;
    
    plants[i].id = id;
    plants[i].pointLinkId = ofRandom(pointLinkCount);
    
    // calc direction
    ofPolyline &line = (*(cvData->trackedContours))[id].resampleSmoothed;
    
    ofVec2f *point = new ofVec2f[pointLinkCount];
    int step = line.size()/pointLinkCount;
    int k = 0;
    ofVec2f a(0, 0);
    for (int j = 0; j < line.size(); j += step ) {
        point[k] = line.getVertices()[j];
        a += point[k];
        k++;
    }
    ofVec2f centroid = a/pointLinkCount;
    // find centroid
    
    ofVec2f &p1 = point[plants[i].pointLinkId];
    ofVec2f delta = p1 - centroid;
    float x = delta.x;
    float y = delta.y;
    
    ofVec2f dir;
    if (abs(y) > abs(x)) {
        dir.set(0, -1); // up or down
    } else {
        if (x > 0){ // right
            dir.set(1, 0);
        } else{ // left
            dir.set(-1, 0);
        }
    }
    
    plants[i].rig.dir = dir;
    
    plants[i].rig.cbCount = ofRandom(3, 6) ;
    plants[i].rig.mbCount = ofRandom(5, 6) ;
    
    plants[i].rig.mbLengthMax = mainBranchWMax ;
    plants[i].rig.mbLengthMin = mainBranchWMin ;
    plants[i].rig.cbLengthMax = childBranchWMax ;
    plants[i].rig.cbLengthMin = childBranchWMin ;
    
    plants[i].mbWidth = mainBranchWMin;
    plants[i].cbWidth = childBranchWMin;
    plants[i].rig.pos = _pos;
    
    plants[i].color = swatch[(int)ofRandom(4)];

    plants[i].setup();
    plants[i].fadeIn();
    
}
void PlantManager::setupGui(){
    parameters.setName("PlantManager");
    parameters.add(plantScale.set("plantScale", 1.0, 0.1, 2.0));
    parameters.add(mainBranchWMin.set("mainBranchWMin", 5, 1, 200));
    parameters.add(mainBranchWMax.set("mainBranchWMax", 5, 1, 200));
    parameters.add(childBranchWMin.set("childBranchWMin", 5, 1, 200));
    parameters.add(childBranchWMax.set("childBranchWMax", 5, 1, 200));
    gui.setup(parameters);
    gui.loadFromFile("settings.xml");
}
void PlantManager::remove(int id){
    for(auto &p : plants){
        if(p.id == id){
            p.fadeOut();
            p.setPos(getClosestPoint(p.getPos(), peoplePoints), 0.5);
        }
    }
//    plants.erase(
//                    std::remove_if(
//                                   plants.begin(),
//                                   plants.end(),
//                                   [&](Plant & p){return p.id == id;}),
//                    plants.end());
}
void PlantManager::reset(){
    plants.clear();
}
ofVec2f PlantManager::getClosestPoint(ofVec2f target, vector<ofVec2f> &points){
    float mindist = 2000;
    int index = 0;
    for(int i = 0; i < points.size(); i++){
        float dist = target.distance(points[i]);
        if(dist < mindist){
            mindist = dist;
            index = i;
        }
    }
    return points[index];
}
// --------------- update
void PlantManager::update(){
    updatePlantsParameters();
    updateBgPlants();
//    updateBgPlantsRemoval();
    updatePlants();
    updatePlantRemoval();
    updatePeoples();
}
void PlantManager::updatePlants(){
    peoplePoints.clear();
    for(auto &id: cvData->idsThisFrame){
        ofPolyline line = (*(cvData->trackedContours))[id].resampleSmoothed;
        for (int j = 0; j < line.size(); j += line.size()/10 ) {
            peoplePoints.push_back(line.getVertices()[j]);
        }
    }
    for(auto &p: plants){
        p.update();
        int id = p.id;
        int whichBlob = cvData->idToBlobPos[id];
        ofPolyline line = (*(cvData->trackedContours))[id].resampleSmoothed;
        
        ofVec2f *point = new ofVec2f[pointLinkCount];
        int step = line.size()/pointLinkCount;
        int k = 0;
        for (int j = 0; j < line.size(); j += step ) {
            point[k] = line.getVertices()[j];
            k++;
        }
        if(!p.isFading){
            p.setPos(point[p.pointLinkId], 0.5);
        }else{
            p.setPos(getClosestPoint(p.getPos(), peoplePoints), 0.5);
        }
    }
}
void PlantManager::updateBgPlants(){
    for(auto &p: bgPlants){
        p.update();
    }
}
void PlantManager::updateBgPlantsRemoval(){
//    for (int i =0; i < bgPlants.size(); i++) {
//        if(bgPlants[i].isFadeFinished()){
//            ofVec2f pos = ofVec2f(IM->targets[(int)ofRandom(IM->targets.size()-1)].pos.x, ofGetHeight());
//            addBgPlant(pos);
//            bgPlants.erase(bgPlants.begin()+i);
//        }
//    }
}
void PlantManager::updatePlantsParameters(){
    for(auto &p: plants){
        p.scale = plantScale;
    }
}
void PlantManager::updatePlantCreation(){

}
void PlantManager::updatePlantRemoval(){
    for (int i =0; i<plants.size(); i++) {
        if(plants[i].isFadeFinished()){
            plants.erase(plants.begin()+i);
        }
    }
}
void PlantManager::updatePeoples(){
}
// --------------- draw
void PlantManager::draw(){
    drawBgPlants();
    drawPlants();
//    drawPeoples();
    gui.draw();
}
void PlantManager::drawPlants(){
    for(auto &p: plants){
        p.draw();
    }
}
void PlantManager::drawBgPlants(){
    for(auto &p: bgPlants){
        p.draw();
    }
}
void PlantManager::drawPeoples(){
    int j = 0;
    for(auto &p: peoplePoints){
        ofFill();
        ofSetColor(ofColor::white);
        ofDrawCircle(p, 5);
    }
}
