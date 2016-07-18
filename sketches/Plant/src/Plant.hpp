//
//  Plant.hpp
//  Plant
//
//  Created by Zerc on 6/28/16.
//
//

#ifndef Plant_hpp
#define Plant_hpp

#include "ofMain.h"
#include "SvgPlant.hpp"

class Plant{
public:
    vector<SvgPlant> mainBranch;
    vector<SvgPlant> branches;
    float mainBranchCount = 4;
    ofVec2f pos;
    ofVec2f velocity;
    float scale = 1.0;
    float size = 0.5;
    ofEvent<ofColor> onImpulse;
    
    struct branchSettings{
        ofVec2f pos;
        ofVec2f leftRect;
        ofVec2f topRect;
        float radius;
        bool isLeft;
    };
    
    void smooth(ofVec2f *val, ofVec2f newVal);
    branchSettings mainBSettings(int counter);

    void setup();
    void update();
    void draw();

    void setVelocity ( ofVec2f _vel ){ smooth(&velocity, _vel);}
    void setPosition ( ofVec2f _pos ){ smooth(&pos, _pos);}
    void setScale (float _scale){ scale = _scale;};
    
    ofVec2f getPosition(){return pos;}
    ofVec2f getVelocity(){return velocity;}
    float getScale(){return scale;}
    
    void randomize();
    void impulse(int colNum);
    int timer = 0;
    ofColor colors[4] = {
        ofColor::violet,
        ofColor::black,
        ofColor::lightGreen,
        ofColor::yellow
    };
    
};

#endif /* Plant_hpp */
