//
//  Kaktus.hpp
//  KaktusGrow
//
//  Created by Zerc on 6/20/16.
//
//

#ifndef Kaktus_hpp
#define Kaktus_hpp

#include "ofMain.h"
#include "StrokeWalker.hpp"

class Kaktus{
public:
    vector<StrokeWalker> branches;
    StrokeWalker rootBranch;
    ofVec3f curPos;
    ofVec3f initPos;
    bool isNewBranch = false;
    int mainCounter = 0;
    int growCountMin;
    int growCountMax;
    // fade
    float opacity = 1;
    float fadeSpeed = 0.02;
    bool isFade = false;
    
    void fade(){
        isFade = true;
    }
    void setup(ofVec3f pos){
        initPos = pos;
        grow();
    }
    void addRootBranch(){
        StrokeWalker branch;
        branch.setup();
        branch.initPos = initPos;
        branch.maxGrowCount = ofRandom(800, 800);
        branch.turnCount = ofRandom(7, 10);
        branch.strokeWidth = ofRandom(20, 40);
        branch.minDist = 20;
        branch.maxDist = 400;
        branch.grow(10); 
        branches.push_back(branch);
    }
    void addBranch(ofVec3f pos){
        StrokeWalker branch;
        branch.setup();
        branch.initPos = pos;
        branch.maxGrowCount = ofRandom(100, 300);
        branch.turnCount = ofRandom(3, 5);
        branch.strokeWidth = ofRandom(20, 40);
        branch.minDist = 36;
        branch.maxDist = 131;
        branch.grow(5);
        branches.push_back(branch);
    }
    void update(){
        if(isFade){
            opacity -= fadeSpeed;
        }
        if(branches[0].isGrow){
            mainCounter++;
            int index = 0;
            for (int i = 0; i < 5; i++) {
                if(mainCounter == index){
                    addBranch(branches[0].curPos);
                    branches[0].startTrackPointAt(branches[0].growCounter);
                }
                index += 50;
            }
        }
        for (int i = 0; i < branches.size(); i++) {
            if(i!=0){
                branches[i].initPos = branches[0].trackingPoints[i-1];
                branches[i].strokeWidth = branches[0].trackingWidth[i-1];
            }
            branches[i].opacity = opacity;
            branches[i].update();
        }
    }
    void draw(){
        for (int i = 0; i < branches.size(); i++) {
            branches[i].draw();
//            branches[i].drawDebug();
        }
    }
    void grow(){
        mainCounter = 0;
        branches.clear();
        addRootBranch();
        isNewBranch = true;
        for (int i = 0; i < branches.size(); i++) {
            branches[i].grow(ofRandom(2, 10));
        }
    }
};
#endif /* Kaktus_hpp */
