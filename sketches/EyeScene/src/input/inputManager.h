#pragma once

#include "ofMain.h"
#include "cvManager.h"


class inputManager {
private:
    
    cvManager CVM;
    
    ofVideoPlayer player;
    
    vector < cv::Point2f > inputQuad;
    
    ofImage blah;
    
    
    
public:
    ofVec2f pos;
    ofVec2f averagePos;
    
    struct Target{
        ofVec2f pos;
        ofVec2f vel;
    };
    vector<Target> targets;
    
    void setup();
    void update();
    void updateTargets();
    void calcAveragePos();
    void draw();
    Target *getFastestTarget();
    
    ofVec2f getAveragePos(){return averagePos;}
    ofVec2f getFastestPos(){
        if(targets.size()>0){
            return getFastestTarget()->pos;
        }else{
            return ofVec2f(0, 0);
        }
    }
    
};