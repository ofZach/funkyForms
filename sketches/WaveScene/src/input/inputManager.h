#pragma once

#include "ofMain.h"
#include "cvManager.h"

class inputManager {
private:
    cvManager CVM;
    ofVideoPlayer player;
    vector < cv::Point2f > inputQuad;
    ofImage blah;
    int newTargetIndex = 0;
public:
    ofVec2f pos;
    ofVec2f averagePos;
    bool isEmpty;
    bool isMouse = false;
    ofVec2f mousePos;
    
    struct Anchor{
        ofVec2f pos;
        int childCount;
    };
    struct Target{
        ofVec2f pos;
        ofVec2f vel;
        ofVec2f topVel;
        ofRectangle rect;
        bool isBusy = false;
        float age = 0;
    };
    
    Target defaultTarget;
    vector<Target> targets;
    
    void setup();
    void update();
    void draw();

    void calcAveragePos();
    void updateTargets();
    
    void setInputToMouse(){ targets.push_back(*new Target); isMouse = true; }
    void setMouse(ofVec2f _mousePos, ofVec2f _vel){
        targets[0].pos = _mousePos;
        targets[0].vel = _vel;
    }
    
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
    Target *getFastestTarget();
    Target &getNewTarget (){return targets[newTargetIndex];}
    ofVec2f getAveragePos (){ return averagePos;}
    ofVec2f getPos() {return pos;}
    Target &getClosesetTo (ofVec2f _pos);
    ofxCv::ContourFinder *getContourFinder(){return CVM.getContourFinder();}

    ofVec2f getFastestPos (){
        if(targets.size()>0){
            return getFastestTarget()->pos;
        }else{
            return ofVec2f(0, 0);
        }
    }
    
};