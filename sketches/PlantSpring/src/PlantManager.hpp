//
//  PlantManager.hpp
//  PlantSpring
//
//  Created by Zerc on 8/5/16.
//
//

#ifndef PlantManager_hpp
#define PlantManager_hpp

#include "ofMain.h"
#include "Plant.hpp"
#include "inputManager.h"
#include "ofxGui.h"

class PlantManager{
public:
    // plants
    vector<Plant> plants;
    
    // input manager
    inputManager *IM;
    
    // gui
    ofParameterGroup parameters;
    ofxPanel gui;
    
    
    void setup();
    void setInputManager(inputManager *_IM){ IM = _IM;};
    void setupGui();
    void addPlant(ofVec2f _pos);
    void onNewPlant();
    
    void update();
    void updatePlants();
    void updatePlantCreation();
    void updatePlantRemoval();
    
    void draw();
    void drawPlants();
};

#endif /* PlantManager_hpp */
