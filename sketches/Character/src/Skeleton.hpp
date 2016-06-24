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
    ofNode torso;
    ofNode torsoCenterNode;
    ofVec2f torsoCenter;
    
    vector<limb> limbs;
    vector<head> heads;
    vector<ofNode *> parentNodes;
    
    float torsoHeight = 200;
    float torsoAngle;
    
    void addLimb(ofVec2f pos, float angle, int count, int length, ofNode *parentNode){
        limb l;
        l.setup(count, pos, angle);
        for (int i = 0; i < count; i++) {
            float _length = length - i*5.5;
            l.setPos(i+1, ofVec3f(0, _length, 0));
        }
        l.update();
        parentNodes.push_back(parentNode);
        limbs.push_back(l);
    }
    ofVec2f getTorsoCenter(){
        return torsoCenter;
    }
    void setPivot(int limbId, int jointId, ofVec2f _pos){
        if(limbId < limbs.size())
            limbs[limbId].setPivot(jointId, _pos);
    }
    float getTorsoAngle(){
        return torsoAngle;
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
    void draw(){
        ofNode torsoRoot;
        torsoRoot.setParent(root);
        torsoCenterNode.setParent(root);
        torsoAngle = ofMap(ofGetMouseX(), 0, ofGetWidth(), -90, 90);
        torsoRoot.setOrientation(ofVec3f(0, 0, torsoAngle));

        torso.setParent(torsoRoot);
        torso.setPosition(0, -torsoHeight, 0);
        torsoCenterNode.setPosition(0, -torsoHeight/2, 0);

        torsoCenter = torso.getGlobalPosition();
        
        ofNode left;
        ofNode right;

        left.setPosition(-100, 0, 0);
        right.setPosition(100, 0, 0);
        left.setParent(torso);
        right.setParent(torso);
        
        ofVec2f rootPos(ofGetMouseX(), 500);
        root.setPosition(rootPos);

        ofSetColor(ofColor::yellow);
        ofDrawCircle(rootPos, 10);
        
        ofSetColor(ofColor::blue);
        ofDrawLine(rootPos, torso.getGlobalPosition());
        ofDrawCircle(torso.getGlobalPosition(), 10);

        ofSetColor(ofColor::cadetBlue);
        ofDrawLine(left.getGlobalPosition(), right.getGlobalPosition());
        
        for (int i = 0; i < limbs.size(); i++) {
            limbs[i].update();
            limbs[i].getRootNode()->setParent(*parentNodes[i]);
            
            float angle = ofMap(ofGetMouseX(), 0, ofGetWidth(), -360, 360);
            
            limbs[i].setChainAngle(angle);
            for (int j = 0; j < limbs[i].getChainCount()-1; j++) {
                ofSetColor(ofColor::green);
                ofDrawCircle(limbs[i].getPos(j), 10);
                ofSetColor(ofColor::red);
                ofDrawLine(limbs[i].getPos(j), limbs[i].getPos(j+1));
            }
        }
    }
};

#endif /* Skeleton_hpp */
