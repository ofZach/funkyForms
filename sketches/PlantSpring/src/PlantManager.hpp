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
#include "particle.h"

class PlantManager{
public:
    // plants
    vector<Plant> plants;
    
    // input manager
    inputManager *IM;
    
    // gui
    ofParameterGroup parameters;
    ofxPanel gui;
    ofParameter<float> mainBranchWMax;
    ofParameter<float> mainBranchWMin;
    ofParameter<float> childBranchWMin;
    ofParameter<float> childBranchWMax;
    
    // colors
    ofFloatColor swatch[4] = {
        ofFloatColor(0.367864,0.692656,0.469682),
        ofFloatColor(0.938711,0.923981,0.347339),
        ofFloatColor(0.732369,0.920703,0.257683),
        ofFloatColor(0.872385,0.169879,0.152076)
    };
    
    // particles
    ofParameter<int> particleCount = 10;
    vector<particle> particles;
    ofParameter<float> particleRepulseRadius = 10;
    ofParameter<float> particleRepulseForce = 0.2;
    ofParameter<float> particleAttractRadius = 100;
    ofParameter<float> particleAttractForce = 0.2;
    
    void setup();
    void setupParticles();
    void setInputManager(inputManager *_IM){ IM = _IM;};
    void setupGui();
    void addPlant(ofVec2f _pos);
    void onNewPlant();
    
    void update();
    void updateParticles();
    void updatePlants();
    void updatePlantCreation();
    void updatePlantsParameters();
    void updatePlantRemoval();
    
    void draw();
    void drawPlants();
    void drawParticles();
};

#endif /* PlantManager_hpp */
