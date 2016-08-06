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
    addPlant(ofVec2f(100, 100));
}
void PlantManager::onNewPlant(){
    addPlant(IM->getNewTarget().pos);
}
void PlantManager::addPlant(ofVec2f _pos){
    plants.push_back( *new Plant );
    int i = plants.size()-1;
        
    plants[i].rig.cbCount = ofRandom(3, 6) ;
    plants[i].rig.mbCount = ofRandom(5, 6) ;
    
    float mbLengthMax = ofRandom(50, 70);
    float mbLengthMin = ofRandom(10, 20);
    
    float cbLengthMax = ofRandom(20, 30);
    float cbLengthMin = ofRandom(10, 20);
    
    plants[i].rig.mbLengthMax = mbLengthMax ;
    plants[i].rig.mbLengthMin = mbLengthMin ;
    plants[i].rig.cbLengthMax = cbLengthMax ;
    plants[i].rig.cbLengthMin = cbLengthMin ;
    
    plants[i].mbWidth = mbLengthMin;
    plants[i].cbWidth = cbLengthMin;
    plants[i].rig.pos = _pos;
    
    plants[i].color = swatch[(int)ofRandom(4)];

    plants[i].setup();
    plants[i].fadeIn();
        
    
}
void PlantManager::setupGui(){
    parameters.setName("PlantManager");
    parameters.add(mainBranchWMin.set("mainBranchWMin", 5, 1, 200));
    parameters.add(mainBranchWMax.set("mainBranchWMax", 5, 1, 200));
    parameters.add(childBranchWMin.set("childBranchWMin", 5, 1, 200));
    parameters.add(childBranchWMax.set("childBranchWMax", 5, 1, 200));
    gui.setup(parameters);
    gui.loadFromFile("settings.xml");
}
// --------------- update
void PlantManager::update(){
    updatePlantsParameters();
    updatePlants();
    updatePlantCreation();
    updatePlantRemoval();
}
void PlantManager::updatePlants(){
    if(!IM->isEmpty){
        for(auto &p: plants){
            p.update();
            inputManager::Target &t = IM->getClosesetToPerson( p.getPos() );
            
            int pIndex = t.pointIndex;
            if(pIndex > t.points.size()-1){
                pIndex = 0;
            }
            p.setPos(t.points[pIndex], 0.7);
            t.isBusy = true;
        }
    }
}
void PlantManager::updatePlantsParameters(){
    for(auto &p: plants){
        
    }
}
void PlantManager::updatePlantCreation(){
    for(auto &t: IM->targets){
        if(!t.isBusy && t.vel.length() > 2){
            addPlant(t.pos);
            t.pointIndex = ofRandom(t.points.size()-1);
        }
    }
    IM->onNewTarget(this, &PlantManager::onNewPlant);
}
void PlantManager::updatePlantRemoval(){
    for (int i =0; i<plants.size(); i++) {
//        inputManager::Target &t = IM->getClosesetToPerson( plants[i].getPos() );
//        if(plants[i].getPos().distance(t.pos) >120){
//            plants[i].fadeOut();
//        }
        for(int j = 0; j<plants.size(); j++){
            if(i!=j){
                if (plants[i].getPos().distance(plants[j].getPos())<20) {
                    plants[i].fadeOut();
                }
            }
        }
    }
    for (int i =0; i<plants.size(); i++) {
        if(plants[i].isFadeFinished()){
            plants.erase(plants.begin()+i);
        }
    }
}
// --------------- draw
void PlantManager::draw(){
    drawPlants();
    gui.draw();
}
void PlantManager::drawPlants(){
    for(auto &p: plants){
        p.draw();
    }
}
