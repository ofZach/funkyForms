//
//  PlantManager.hpp
//  PlantsScene
//
//  Created by Zerc on 7/18/16.
//
//

#ifndef PlantManager_hpp
#define PlantManager_hpp

#include "ofMain.h"
#include "inputManager.h"
#include "Plant.hpp"
#include "ofxGui.h"

class PlantManager{
public:
    // gui
    ofParameter<float> posSmooth;
    ofParameter<float> scaleSmooth;
    ofParameter<float> velSmooth;
    ofParameterGroup parameters;
    ofxPanel gui;
    
    struct Anchor{
        ofVec2f pos;
        Plant plant;
    };

    vector<Anchor> plants;
    inputManager *IM;
    void setup(inputManager *_IM);
    void onNewTarget();
    void update();
    void addPlant(ofVec2f _pos);
    void draw();
};

#endif /* PlantManager_hpp */
