//
//  Skeleton.hpp
//  Character
//
//  Created by Zerc on 6/23/16.
//
//

#ifndef Skeleton_hpp
#define Skeleton_hpp

#include "ofMain.h"
#include "limb.hpp"

class head{
public:
    ofNode head;
    
};

class Skeleton{
public:
    ofNode root;
    
    vector<limb> limbs;
    vector<head> heads;
    vector<string> names;
    vector<ofNode *> parentNodes;
    
    float torsoHeight = 200;
    float torsoAngle;
    
    void addLimb(ofVec2f pos, float angle, int count, int length, ofNode *parentNode){
        limb l;
        l.setup(count, pos, angle);
        for (int i = 0; i < count; i++) {
            float _length = length - i*5.5;
            if(i == 0){
                l.setPos(0, pos);
                l.setAngle(0, angle);
            }else{
                l.setPos(i, ofVec3f(0, length, 0));
            }
        }
        l.update();
        parentNodes.push_back(parentNode);
        limbs.push_back(l);
    }
    void setPivot(int limbId, int jointId, ofVec2f _pos){
        if(limbId < limbs.size())
            limbs[limbId].setPivot(jointId, _pos);
    }
    limb *getLimb(int id){
        if(id<limbs.size()){
            return &limbs[id];
        }else{
            ofLog() << "limbId out of bounds!";
            return;
        }
    }
    void addHead(ofVec2f pos, float angle){
        
    }
    void setup(){

    }
    void draw(float velocity){
        ofVec2f rootPos(ofGetMouseX(), ofGetMouseY());
        root.setPosition(rootPos);

        ofSetColor(ofColor::fireBrick);
        ofDrawCircle(rootPos, 10);
        
        // body parts
        for (int i = 0; i < limbs.size(); i++) {
            limbs[i].update();
            limbs[i].getRootNode()->setParent(*parentNodes[i]);
            
            // body part joints
            for (int j = 0; j < limbs[i].getChainCount(); j++) {
                float speed = 3;
                float rotation = cos(ofGetFrameNum()/speed+j*100)*velocity ;
                if(j==0)
                    rotation += limbs[i].getLimbAngle(j);
                limbs[i].setAngle(j, rotation);
                ofSetColor(ofColor::white);
                ofDrawCircle(limbs[i].getPos(j), 10);
                ofSetColor(ofColor::white);
                if(j>0)
                    ofDrawLine(limbs[i].getPos(j-1), limbs[i].getPos(j));
            }
        }
    }
};

#endif /* Skeleton_hpp */
