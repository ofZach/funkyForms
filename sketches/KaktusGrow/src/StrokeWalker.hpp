//
//  StrokeWalker.hpp
//  KaktusGrow
//
//  Created by Zerc on 6/17/16.
//
//

#ifndef StrokeWalker_hpp
#define StrokeWalker_hpp

#include "ofMain.h"
#include "ofxGui.h"
class walker{
public:
    int distance = 0;
    ofVec3f up;
    ofVec3f down;
    ofVec3f left;
    ofVec3f right;
    ofVec3f curDir;
    ofVec3f targetDir;
    ofVec3f rotateVec;
    float step = 1/140.0;
    void turn(int dir){
        if(curDir.x == 0){
            targetDir.set( dir, 0, 0);
            if(curDir.y>0 && dir>0){
                rotateVec.set(dir*step, -dir*step, 0);
            }
            if(curDir.y>0 && dir<0){
                rotateVec.set(dir*step, dir*step, 0);
            }
            if(curDir.y<0 && dir>0){
                rotateVec.set(dir*step, dir*step, 0);
            }
            if(curDir.y<0 && dir<0){
                rotateVec.set(dir*step, -dir*step, 0);
            }
            
        }else if(curDir.y == 0){
            targetDir.set( 0, dir, 0);
            if(curDir.x>0 && dir>0){
                rotateVec.set(-dir*step, dir*step, 0);
            }
            if(curDir.x>0 && dir<0){
                rotateVec.set(dir*step, dir*step, 0);
            }
            if(curDir.x<0 && dir>0){
                rotateVec.set(dir*step, dir*step, 0);
            }
            if(curDir.x<0 && dir<0){
                rotateVec.set(-dir*step, dir*step, 0);
            }
        }

//        ofLog() << "turn--------------";
//        ofLog() << "curDir: " << curDir ;
//        ofLog() << "targetDir: " << targetDir;
    }
    void setup(){
        up.set(0, -1, 0);
        down.set(0, 1, 0);
        left.set(-1, 0, 0);
        right.set(1, 0, 0);
        curDir = up;
    }
    void go(ofNode *node, float timeOffset){
        if(!curDir.match(targetDir,  0.1)){
            curDir += rotateVec;
        }
//        ofLog() << "curDir: " << curDir;
        ofVec3f r(cos((ofGetFrameNum()+timeOffset)/20.001)/50, sin((ofGetFrameNum()+timeOffset)/12.001)/50, 0);
        node->setPosition(node->getPosition()+curDir+r);
    }
};
class StrokeWalker{
public:    
    ofParameter<int> angle;
    ofParameter<int> growCounter;
    ofParameter<int> strokeWidth;
    ofParameter<int> radius;
    ofParameter<int> step;
    ofParameter<int> turnCount;
    ofParameter<int> minDist;
    ofParameter<int> maxDist;
    ofParameter<float> stroke;
    ofParameterGroup parameters;
    
    float opacity = 1;
    int growSpeed;
    int brunchCount = 0;
    int maxGrowCount = 200;
    float endWidth;
    ofFloatColor endColor;
    float timeOffset;
    vector<int> randomTurns;
    vector<int> randomDist;
    ofVec3f initPos;
    ofVec3f curPos;
    
    ofMesh mesh;
    ofPolyline line;
    
    bool isGrow = false;
    bool isTrackPoint = false;
    int trackingIndex;
    vector<int> trackingIndexs;
    vector<ofVec3f> trackingPoints;
    vector<int> trackingWidth;
    ofVec3f trackingPoint;
    
    void setup();
    void update();
    void addTurns(int & p);
    void addPointsToMesh(ofMesh *m, ofNode l, ofNode r, int i);
    void draw();
    void grow(int speed);
    void randomize();
    void startTrackPointAt(int index);
    void drawDebug();
};

#endif /* StrokeWalker_hpp */
