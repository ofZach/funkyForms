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
    
    ofParameter<float> init_bottomW;
    ofParameter<float> init_bottomH;
    ofParameter<float> init_topW;
    ofParameter<float> init_topH;
    ofParameter<float> init_radius;
    
    ofParameter<float> init_m_bottomW;
    ofParameter<float> init_m_bottomH;
    ofParameter<float> init_m_topW;
    ofParameter<float> init_m_topH;
    ofParameter<float> init_m_radius;
    
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
    void updateParameters(Plant *p);
    void addPlant(ofVec2f _pos);
    void draw();
};

#endif /* PlantManager_hpp */
