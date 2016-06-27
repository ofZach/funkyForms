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
    
    std::map <string, limb> limbs;
    std::map <string, ofNode *> parentNodes;
    float torsoHeight = 200;
    float torsoAngle;

    void addLimb(ofVec2f pos, float angle, int count, int length, string name,  ofNode *parent){
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
        l.setInitAngle(0, angle);
        l.update();
        limbs[name] = l;
        parentNodes[name] = parent;
        parentNodes["torso"] = &root;
    }
    void initAngles(){
    }
    limb *getLimb(string name){
        return &limbs[name];
    }
    void setPivot(string name, int jointId, ofVec2f _pos){
        limbs[name].setPivot(jointId, _pos);
    }
    void setup(){

    }
    void draw(float velocity){
        ofVec2f rootPos(ofGetMouseX(), ofGetMouseY());
        root.setPosition(rootPos);
        ofSetColor(ofColor::white);

        // body parts
        for (auto &pair: limbs) {
            limb *limb = &pair.second;
            limb->update();
            limb->getRootNode()->setParent(*parentNodes[pair.first]);
        
            // body part joints
            for (int j = 0; j < limb->getChainCount(); j++) {
                float speed = 3;
                float smooth = 0.9;
                float rotation = velocity*cos(j*4.0)*limb->getRandomNum(j);
                float min = limb->getInitAngle(j) - limb->getAngleRange(j)*(j+1);
                float max = limb->getInitAngle(j) + limb->getAngleRange(j)*(j+1);

//                float angle = limb->getAngle(j) + velocity;
//                limb->getNodeAt(j)->rotate(velocity, ofVec3f(0, 0, 1));
//                limb->getNodeAt(j)->rotate(velocity, ofVec3f(0, 0, 1));
                limb->setAngle(j, limb->getAngle(j)+rotation);
                if(limb->getAngle(j) < min){
                    limb->setAngle(j, min);
                }
                if(limb->getAngle(j) > max){
                    limb->setAngle(j, max);
                }
                
                ofSetColor(ofColor::white);
                ofDrawCircle(limb->getPos(j), 10);
                ofSetColor(ofColor::white);
                if(j>0)
                    ofDrawLine(limb->getPos(j-1), limb->getPos(j));
            }
        }
    }
};

#endif /* Skeleton_hpp */
