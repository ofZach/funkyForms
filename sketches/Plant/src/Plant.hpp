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
    ofVec2f velocity;
    ofVec2f pos;
    float size = 1;
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
    void update(ofVec2f _velocity);
    void draw(int x, int y);
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
