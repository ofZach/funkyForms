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
    for (int i = 0; i < 4; i++) {
        addBgPlant( ofVec2f(ofRandomWidth(), ofGetHeight() ) );
    }
    for (int i = 0; i < 40; i++) {
        randSwatchIndex.push_back((int)ofRandom(4));
    }
}
void PlantManager::addBgPlant(ofVec2f _pos){
    Plant plant;
    bgPlants.push_back(plant);
    int i = bgPlants.size()-1;
    
    bgPlants[i].rig.cbCount = ofRandom(5, 7) ;
    bgPlants[i].rig.mbCount = ofRandom(4, 6) ;
    
    bgPlants[i].rig.dir = ofVec2f(0, -1);
    bgPlants[i].rig.mbLengthMax = bgMainBranchWMax ;
    bgPlants[i].rig.mbLengthMin = bgMainBranchWMin ;
    bgPlants[i].rig.cbLengthMax = bgChildBranchWMax ;
    bgPlants[i].rig.cbLengthMin = bgChildBranchWMin ;
    bgPlants[i].rig.timeSpeed = 0.01;
    
    bgPlants[i].mbWidth = bgMainBranchWMin;
    bgPlants[i].cbWidth = bgChildBranchWMin;
    bgPlants[i].rig.pos = _pos;
    
    ofFloatColor col = swatch[(int)ofRandom(4)];
    col.setBrightness(col.getBrightness()/2);
    bgPlants[i].color = col;
    
    bgPlants[i].setup();
    bgPlants[i].ageMax = ofRandom(600, 1000);
    bgPlants[i].fadeIn();
}
void PlantManager::addPlant(ofVec2f _pos, int id){
    
    ofRectangle src(0,0,cvData->width, cvData->height);
    ofRectangle dst = src;
    ofRectangle target = RM->getRectForScreen(SCREEN_LEFT);
    dst.scaleTo(target);
    
    
    Plant plant;
    plants.push_back(plant );
    int i = plants.size()-1;
    
    plants[i].id = id;
    plants[i].pointLinkId = ofRandom(pointLinkCount);
    
    // calc direction
    ofPolyline line = (*(cvData->trackedContours))[id].data.resampleSmoothed;
    for (auto & pt : line){
        pt =cvData->remapForScreen(SCREEN_LEFT, pt);
    }
    
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
    // plant
    parameters.add(plantScale.set("plantScale", 1.0, 0.1, 2.0));
    parameters.add(mainBranchWMin.set("mainBranchWMin", 5, 1, 200));
    parameters.add(mainBranchWMax.set("mainBranchWMax", 5, 1, 200));
    parameters.add(childBranchWMin.set("childBranchWMin", 5, 1, 200));
    parameters.add(childBranchWMax.set("childBranchWMax", 5, 1, 200));
    // bgPlant
    parameters.add(bgMainBranchWMin.set("bgMainBranchWMin", 5, 1, 200));
    parameters.add(bgMainBranchWMax.set("bgMainBranchWMax", 5, 1, 200));
    parameters.add(bgChildBranchWMin.set("bgChildBranchWMin", 5, 1, 200));
    parameters.add(bgChildBranchWMax.set("bgChildBranchWMax", 5, 1, 200));
    parameters.add(createBgPlant.set("createBgPlant", false));
    // shadow
    parameters.add(shadowRadius.set("shadowRadius", 5, 1, 300));
    parameters.add(shadowOpacity.set("shadowOpacity", 100, 0, 255));
    
    createBgPlant.addListener(this, &PlantManager::triggerBgPlant);


}
void PlantManager::remove(int id){
    for(auto &p : plants){
        if(p.id == id){
            p.fadeOut();
            p.setPos(getClosestPoint(p.getPos(), peoplePoints), 0.5);
        }
    }
}
void PlantManager::reset(){
    bgPlants.clear();
    plants.clear();
    for (int i = 0; i < 4; i++) {
        addBgPlant( ofVec2f(ofRandomWidth(), ofGetHeight() ) );
    }
}
void PlantManager::triggerBgPlant(bool &b){
    if(plants.size()>0){
        int pId = (int)ofRandom(plants.size());
        int id = plants[pId].id;
        float x = plants[pId].getPos().x;
        ofVec2f pos = ofVec2f(x, ofGetHeight());
        addBgPlant(pos);
        bgPlants.erase(bgPlants.begin());
    }
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
    updateBgPlantsRemoval();
    updatePlants();
    updatePlantRemoval();
}
void PlantManager::updatePlants(){
    
    ofRectangle src(0,0,cvData->width, cvData->height);
    ofRectangle dst = src;
    ofRectangle target = RM->getRectForScreen(SCREEN_LEFT);
    dst.scaleTo(target);
    
    
    peoplePoints.clear();
    for(auto &id: cvData->idsThisFrame){
        ofPolyline line = (*(cvData->trackedContours))[id].data.resampleSmoothed;
        for (auto & pt : line){
            pt =cvData->remapForScreen(SCREEN_LEFT, pt);
        }
        for (int j = 0; j < line.size(); j += line.size()/10 ) {
            peoplePoints.push_back(line.getVertices()[j]);
        }
    }
    for(auto &p: plants){
        p.update();
        int id = p.id;
        int whichBlob = cvData->idToBlobPos[id];
        ofPolyline line = (*(cvData->trackedContours))[id].data.resampleSmoothed;
        for (auto & pt : line){
            pt =cvData->remapForScreen(SCREEN_LEFT, pt);
        }
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
    for (int i =0; i < bgPlants.size(); i++) {
        if(bgPlants[i].isFadeFinished()){
            int pId = (int)ofRandom(plants.size());
            int id = plants[pId].id;
            float x = plants[pId].getPos().x;
            ofVec2f pos = ofVec2f(x, ofGetHeight());
            addBgPlant(pos);
            bgPlants.erase(bgPlants.begin()+i);
        }
    }
}
void PlantManager::updatePlantsParameters(){
    for(auto &p: plants){
        p.scale = plantScale;
        p.shadowRadius = shadowRadius;
        p.shadowOpacity = shadowOpacity;
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
// --------------- draw
void PlantManager::draw(){
    drawBgPlants();
//    drawShadow();
    drawPlants();
//    drawPeoples();
//    gui.draw();
}




//void PlantManager::drawParticles(){
//    for (int i = 0; i < particles.size(); i++){
//        particles[i].draw();
//    }
//}
void PlantManager::drawShadow(){
    for(auto &p: plants){
        p.drawShadow();
    }
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
