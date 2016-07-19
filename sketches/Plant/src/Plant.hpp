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
#include "Branch.hpp"

class Plant{
public:
    vector<Branch> mainBranch;
    vector<Branch> branches;
    float mainBranchCount = 4;
    ofVec2f pos;
    ofVec2f velocity;
    float scale = 1.0;
    float size = 0.5;
    
    struct branchSettings{
        ofVec2f pos;
        ofVec2f leftRect;
        ofVec2f topRect;
        float radius;
        bool isLeft;
    };
    
    void smooth(ofVec2f *val, ofVec2f newVal, float _speed);
    branchSettings mainBSettings(int counter);

    void setup();
    void update();
    void draw();

    void setSmoothVelocity ( ofVec2f _vel , float _speed){ smooth(&velocity, _vel, _speed);}
    void setSmoothPosition ( ofVec2f _pos , float _speed){ smooth(&pos, _pos, _speed);}
    void setPosition ( ofVec2f _pos ){ pos = _pos;}
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
