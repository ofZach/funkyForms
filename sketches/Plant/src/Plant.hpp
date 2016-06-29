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
    struct branchSettings{
        ofVec2f pos;
        ofVec2f leftRect;
        ofVec2f topRect;
        float radius;
        bool isLeft;
    };
    void setup();
    void update();
    void draw();
    void randomize();
};

#endif /* Plant_hpp */
