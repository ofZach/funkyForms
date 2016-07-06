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
    ofVec2f velocity;
    ofVec2f pos;
    float size = 1;
    ofEvent<bool> onImpulse;
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
};

#endif /* Plant_hpp */
