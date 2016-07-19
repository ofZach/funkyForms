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
    int count = 7;
    for (int i = 0; i < count; i++) {
        plants.push_back(*new Plant);
        plants[i].setup();
        plants[i].setScale(ofRandom(0.1, 0.5));
        plants[i].setPosition(ofVec2f(ofRandomWidth(), ofRandomHeight()));
    }
}
void PlantManager::onNewTarget(){
    Plant *p = new Plant();
    p->setup();
    p->setScale(ofRandom(0.3, 0.5));
    p->setPosition(IM->getNewTarget().pos);
    plants.push_back(*p);
}
void PlantManager::update(){
    if(!IM->isEmpty){
        for(auto &p: plants){
            inputManager::Target &t = IM->getClosesetTo( p.getPosition() );
            p.setSmoothPosition(t.pos, 0.9);
            p.setSmoothVelocity(t.vel*40, 0.998);
            p.update();
        }
    }
    
    for (int i =0; i<plants.size(); i++) {
        for(int j = 0; j<plants.size(); j++){
            if(i!=j){
                if (plants[i].getPosition().distance(plants[j].getPosition())<0.2) {
                    plants.erase(plants.begin()+i);
                }
            }
        }
    }

    IM->onNewTarget(this, &PlantManager::onNewTarget);
}
void PlantManager::draw(){
    for(auto &p: plants){
        p.draw();
    }
    ofSetColor(ofColor::violet);
}