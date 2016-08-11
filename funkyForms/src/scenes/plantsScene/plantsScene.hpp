//
//  plantsScene.hpp
//  funkyForms
//
//  Created by Gordey on 8/8/16.
//
//

#ifndef plantsScene_hpp
#define plantsScene_hpp

#include "ofMain.h"
#include "baseScene.h"
#include "PlantManager.hpp"

class plantsScene : public baseScene {
public:
    
    // plants
    PlantManager plantManager;
    
    // people
    ofImage glow;
    ofParameter<float> glowRadius;
    ofParameter<float> glowOpacity;
    
    // gui
    ofParameterGroup parameters;
    ofxPanel gui;
    
    void setup();
    void setupGui();
    
    void update();
    
    void draw();
    
    void start();
    void stop();
    
    void blobBorn(int id);
    void blobDied(int id);
    
    void drawPeople();
    
};

#endif /* plantsScene_hpp */
