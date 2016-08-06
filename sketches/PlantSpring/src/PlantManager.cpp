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
            p.update();
            inputManager::Target &t = IM->getClosesetToPerson( p.getPos() );
            int pIndex = t.pointIndex;
            if(pIndex > t.points.size()-1){
                pIndex = 0;
            }
            p.setPos(t.points[pIndex], 0.7);
            t.isBusy = true;
//            updateParameters(&p.plant);
//            if(t.rect.height/t.rect.width < 1.3 && t.rect.height>120 ){
//                p.plant.addSpike();
//            }else{
//                p.plant.delSpike();
//            }
            

        }
    }
}
void PlantManager::updatePlantCreation(){
    for(auto &t: IM->targets){
        if(!t.isBusy && t.vel.length() > 2){
            addPlant(t.pos);
            t.pointIndex = ofRandom(t.points.size()-1);
        }
    }
//    IM->onNewTarget(this, &PlantManager::onNewPlant);
}
void PlantManager::updatePlantRemoval(){
    for (int i =0; i<plants.size(); i++) {
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
}
void PlantManager::drawPlants(){
    for(auto &p: plants){
        p.draw();
    }
}
