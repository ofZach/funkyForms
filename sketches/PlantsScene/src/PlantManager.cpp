//
//  PlantManager.cpp
//  PlantsScene
//
//  Created by Zerc on 7/18/16.
//
//

#include "PlantManager.hpp"
void PlantManager::setup(inputManager *_IM){
    IM = _IM;
    
    plants.push_back(*new Plant);
    plants[0].setup();
    plants[0].setPosition(ofVec2f(0, 0));
}
void PlantManager::update(){
    for(auto &p: plants){
        p.update();
        p.setVelocity(ofVec2f(0, 0));
        ofVec2f tPos = IM->getClosesetPosTo( p.getPosition() );
        p.setPosition(tPos);
    }
}
void PlantManager::draw(){
    for(auto &p: plants){
        p.draw();
    }
}