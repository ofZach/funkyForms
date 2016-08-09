#pragma once

#include "ofMain.h"
#include "cvManager.h"
#include "trackedContour.hpp"


class inputManager {
    
public:
    
    // player pos
    ofVec2f pos;
    
    // group of people can move something
    ofVec2f averagePos;
    
    // targets
    bool isEmpty; // if targets are empty
    struct Target{
        ofVec2f pos;
        ofVec2f vel;
        ofVec2f topVel;
        ofPolyline *line;
        vector<ofVec2f> points;
        int pointIndex;
        ofRectangle rect;
        bool isBusy = false;
        float age = 0;
    };
    Target defaultTarget;
    vector<Target> targets;
    int newTargetIndex = 0;
    
    // CV manager
    cvManager CVM;
    
    // input
    ofVideoPlayer player;
    vector < cv::Point2f > inputQuad;
    ofImage blah;
    
    // trackedCountour
    struct Point{
        bool isBusy = false;
        ofVec2f pos;
    };
    vector <Point> peoplePoints;
    
    void setup();
    
    void update();
    
    void updateTargets();
    void updatePlayer();
    void calcAveragePos();

    // when new target appear bind function
    template <typename OBJECT, typename FUNC>
    void onNewTarget( OBJECT obj, FUNC func){
        int i = 0;
        for(auto t: targets){
            if(t.age == 60){
                (obj->*func)();
                newTargetIndex = i;
            }
            i++;
        }
    }
    
    Target *    getFastestTarget();
    Target &    getNewTarget (){ return targets[newTargetIndex];}
    ofVec2f     getAveragePos (){ return averagePos;}
    Target &    getClosesetToPerson ( ofVec2f _pos );
    ofVec2f     getClosesetToPoints ( ofVec2f _pos );

    map < int, trackedContour >  & getTrackedContours() { return CVM.trackedContours; }
    
    ofVec2f getFastestPos (){
        if(targets.size()>0){
            return getFastestTarget()->pos;
        }else{
            return ofVec2f(0, 0);
        }
    }
    
    
    void draw();
    
};