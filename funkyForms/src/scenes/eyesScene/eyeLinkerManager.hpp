//
//  eyeLinkerManager.hpp
//  funkyForms
//
//  Created by Gordey on 8/10/16.
//
//

#ifndef eyeLinkerManager_hpp
#define eyeLinkerManager_hpp

#include "ofMain.h"
#include "EyeLinker.hpp"
#include "cvManager.h"

class eyeLinkerManager{
public:
    // Pos, size, vel
    
    
    // Input
    cvPacket * cv;
    
    // Eyes
    vector <EyeLinker> eyes;
    
    // Gui
    ofParameterGroup parameters;
    ofParameter<float> width;
    ofParameter<float> height;
    ofParameter<float> scale;
    
    void setup();
    void setupGui();
    void setupParameters(float &v);
    void addEye(int id, ofVec2f pos);
    void removeEye(int id);
    
    void update();
    void updateEye();
    void updateEyeRemoval();
    
    void draw();
};

#endif /* eyeLinkerManager_hpp */
