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
    
    float mbLengthMax = ofRandom(100, 300);
    float mbLengthMin = ofRandom(10, 100);
    
    float cbLengthMax = ofRandom(50, 100);
    float cbLengthMin = ofRandom(10, 50);
    
    plants[i].rig.mbLengthMax = mbLengthMax ;
    plants[i].rig.mbLengthMin = mbLengthMin ;
    plants[i].rig.cbLengthMax = cbLengthMax ;
    plants[i].rig.cbLengthMin = cbLengthMin ;
    
    plants[i].mbWidth = mbLengthMin;
    plants[i].cbWidth = cbLengthMin;
    plants[i].rig.pos = ofVec2f(ofRandomWidth(), ofGetHeight());
    if(i%2==0){
        plants[i].color = ofColor::honeyDew;
    }else{
        plants[i].color = ofColor::greenYellow;
    }
    plants[i].setup();
    plants[i].fadeIn();
        
    
}
void PlantManager::setupGui(){
    parameters.setName("PlantManager");
    
}
// --------------- update
void PlantManager::update(){
    updatePlants();
    updatePlantCreation();
    updatePlantRemoval();
}
void PlantManager::updatePlants(){
    if(!IM->isEmpty){
        for(auto &p: plants){
            inputManager::Target &t = IM->getClosesetTo( p.pos );
            t.isBusy = true;
//            updateParameters(&p.plant);
//            if(t.rect.height/t.rect.width < 1.3 && t.rect.height>120 ){
//                p.plant.addSpike();
//            }else{
//                p.plant.delSpike();
//            }
            
            p.setPos(t.pos, 0.99);
            p.update();
        }
    }
}
void PlantManager::updatePlantCreation(){
//    for(auto &t: IM->targets){
//        if(!t.isBusy && t.vel.length() > 2){
//            addPlant(t.pos);
//        }
//    }
    IM->onNewTarget(this, &PlantManager::onNewPlant);
}
void PlantManager::updatePlantRemoval(){
}
// --------------- draw
void PlantManager::draw(){
    drawPlants();
}
void PlantManager::drawPlants(){
    for(auto &p: plants){
        p.draw();
    }
}
