//
//  rewardLines.hpp
//  RewardLine
//
//  Created by Gordey on 8/25/16.
//
//

#ifndef rewardLines_hpp
#define rewardLines_hpp

#include "ofMain.h"
#include "rewardLine.hpp"

class rewardLines{
public:
    struct rewardCircle{
        float radius;
        ofPoint pos;
        vector<rewardLine> lines;
    };
    vector<rewardCircle> rewardCircles;

    float lineLength = 500;
    float lineRadius = 100;
    
    void setup();
    
    void reward(ofPoint pos);
    void clear();
    
    void update();
    void updateLines();
    void updateRemoval();
    
    void draw();
    void drawLines();
};

#endif /* rewardLines_hpp */
