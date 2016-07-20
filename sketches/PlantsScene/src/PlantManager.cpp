//
//  PlantManager.cpp
//  PlantsScene
//
//  Created by Zerc on 7/18/16.
//
//

#include "PlantManager.hpp"
void PlantManager::setup(inputManager *_IM){
    parameters.setName("PlantManager");
    parameters.add(posSmooth.set("posSmooth", 0.9, 0.9, 0.99999));
    parameters.add(velSmooth.set("velSmooth", 0.9, 0.99, 0.99999));
    parameters.add(scaleSmooth.set("scaleSmooth", 0.9, 0.9, 0.99999));
    gui.setup(parameters);
    gui.loadFromFile("settings.xml");
    
    IM = _IM;
    int count = 3;
    for (int i = 0; i < count; i++) {
        plants.push_back(*new Anchor);
        plants[i].plant.setup();
        plants[i].plant.setScale(ofRandom(0.1, 0.5));
        plants[i].plant.setPosition(ofVec2f(ofRandomWidth(), ofRandomHeight()));
        plants[i].plant.grow();
        float x = ofRandom(-30, 30);
        float y = ofRandom(-30, 30);
        plants[i].pos = ofVec2f(x, y);
    }
}
void PlantManager::onNewTarget(){
    addPlant(IM->getNewTarget().pos);
}
void PlantManager::addPlant(ofVec2f _pos){
    plants.push_back(*new Anchor);
    int i = plants.size()-1;
    plants[i].plant.setup();
    plants[i].plant.setScale(ofRandom(0.3, 0.7));
    plants[i].plant.setPosition(_pos);
    plants[i].plant.grow();
    float x = ofRandom(-30, 30);
    float y = ofRandom(-30, 30);
    plants[i].pos = ofVec2f(x, y);
}
void PlantManager::update(){
    if(!IM->isEmpty){
        for(auto &p: plants){
            inputManager::Target &t = IM->getClosesetTo( p.plant.getPosition() );
            t.isBusy = true;
            if(t.rect.height/t.rect.width < 1.3 && t.rect.height>120 ){
                p.plant.addSpike();
            }else{
                p.plant.delSpike();
            }
            
            p.plant.setSmoothPosition(t.pos+p.pos, posSmooth);
            p.plant.setSmoothVelocity(t.vel.normalize(), velSmooth);
            p.plant.setSmoothScale(ofMap(t.vel.normalize().y, -1, 1, 0.2, 0.9, true), scaleSmooth);
            p.plant.update();
        }
    }
    for(auto &t: IM->targets){
        if(!t.isBusy && t.vel.length() > 2){
            addPlant(t.pos);
        }
    }
    for (int i =0; i<plants.size(); i++) {
        for(int j = 0; j<plants.size(); j++){
            if(i!=j){
                if (plants[i].plant.getPosition().distance(plants[j].plant.getPosition())<20) {
                    plants[i].plant.collapse();
                }
            }
        }
    }
    for (int i =0; i<plants.size(); i++) {
        if(plants[i].plant.getFinished()){
            plants.erase(plants.begin()+i);
        }
    }
    IM->onNewTarget(this, &PlantManager::onNewTarget);
}
void PlantManager::draw(){
    for(auto &t: IM->targets){
        
    }
    for(auto &p: plants){
        p.plant.draw();
    }
    gui.draw();
}