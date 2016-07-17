//
//  EyePair.hpp
//  EyeScene
//
//  Created by Zerc on 7/15/16.
//
//

#ifndef EyePair_hpp
#define EyePair_hpp

#include "ofMain.h"
#include "eye.hpp"
#include "Targets.hpp"

class EyePair{
private:
public:
    ofVec2f pos;
    vector<Targets::Target> *targets;
    Targets *targetManager;
    
    vector<eye> eyes;
    bool isEyeBig;
    
    float scaleL = 1.;
    float scaleR = 1.;
    float angleL = 0.;
    float angleR = 0.;
    bool isHit = false;
    float scaleMin = 0.5;
    float scaleMax = 2;
    
    void setTargets( vector<Targets::Target> *t){ targets = t; }
    void setTargetManager( Targets *t){ targetManager = t; }
    void addScaleForce();
    void setPos(ofVec2f _pos){pos = _pos;}
    void setup();
    void update(ofVec2f _pos);
    void setLookAt(ofVec2f _pos);
    void lookAtSmart(ofVec2f _pos){for(auto &e: eyes){ e.lookAtSmart(_pos);}};
    void hitStart(){isHit = true;}
    void hitEnd(){isHit = false;}
    void draw();
};

#endif /* EyePair_hpp */
