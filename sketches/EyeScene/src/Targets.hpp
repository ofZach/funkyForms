//
//  Targets.hpp
//  EyeScene
//
//  Created by Zerc on 7/14/16.
//
//

#ifndef Targets_hpp
#define Targets_hpp

#include "ofMain.h"
#include "ofxXmlSettings.h"

class Targets{
public:
    ofxXmlSettings settings;
    int dataCount;
    ofVec2f fstPosSmoothed; // fastest position smoothed
    
    
    struct Target{
        ofVec2f posOffset;
        ofVec2f pos;
        ofVec2f prevPos;
        ofVec2f vel;
        ofColor col;
        int counter = 0;
        int counterVel = 1;
    };
    vector<Target> targets;

    void setup();
    void update(int x, int y);
    void draw();
    
    ofVec2f getFastestPos () {return fstPosSmoothed;}
    float getLeftEnergy () {return leftEnergy;}
    float getRightEnergy () {return rightEnergy;}
    
private:
    float leftEnergy = 0;
    float rightEnergy = 0;

    void calcEnergy();
    Target *getFastest();
    
};

#endif /* Targets_hpp */
