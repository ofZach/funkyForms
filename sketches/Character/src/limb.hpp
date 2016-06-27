//
//  limb.hpp
//  Character
//
//  Created by Zerc on 6/24/16.
//
//

#ifndef limb_hpp
#define limb_hpp

#include "ofMain.h"

class limb{
private:
public:
    vector<ofNode> nodes;
    vector<ofVec2f> nodePos;
    vector<ofNode> pivots;
    vector<ofVec2f> pivotPos;
    vector<float> nodeAngle;
    vector<float> initAngle;
    vector<float> angleRange;
    vector<float> randomNumbers;
    string name;
    float limbAngle;
    ofVec2f pos;
    
    void setup(int count, ofVec2f _pos, float _angle){
        limbAngle = _angle;
        pos = _pos;
        for (int i = 0; i < count; i++) {
            ofNode node;
            nodes.push_back(node);
            ofNode n;
            n.setPosition(0, 0, 0);
            pivots.push_back(n);
            
            nodePos.push_back(ofVec2f(0, 0));
            pivotPos.push_back(ofVec2f(0, 0));
            nodeAngle.push_back(0);
            initAngle.push_back(0);
            angleRange.push_back(20);
            randomNumbers.push_back(ofRandom(-1, 1));
        }
        setPos(0, pos);
    }
    float getRandomNum(int id){
        return randomNumbers[id];
    }
    float getAngleRange(int id){
        return angleRange[id];
    }
    void setAngleRange(int id, float range){
        angleRange[id] = range;
    }
    void setInitAngle(int id, float _angle){
        initAngle[id] = _angle;
    }
    void initAngles(){
        for (int i = 0; i < nodes.size(); i++) {
            initAngle[i] = nodeAngle[i];
        }
    }
    float getInitAngle(int id){
        if(id<nodes.size()){
            return initAngle[id];
        }else{
            ofLog() << "out of bounds!";
            return NULL;
        }
    }
    void update(){
        for (int i = 0; i < nodes.size(); i++) {
            if(i>0){
                nodes[i].setParent(nodes[i-1]);
                pivots[i].setParent(nodes[i]);
            }else{
                pivots[i].setParent(nodes[i]);
            }
            nodes[i].setOrientation(ofVec3f(0, 0, nodeAngle[i]+initAngle[i]));
//            float angle = quatToEuler(nodes[i].getOrientationQuat()).z;
            nodePos[i] = nodes[i].getGlobalPosition();
            pivotPos[i] = pivots[i].getGlobalPosition();
        }
    }
    void setPivot(int id, ofVec2f _pos){
        if(id<nodes.size()){
            pivots[id].setPosition(_pos);
        }else{
            ofLog() << "out of bounds!";
        }
    }
    ofVec3f quatToEuler(const ofQuaternion & rotation) {
        ofVec3f euler;
        const static double PI_OVER_2 = PI * 0.5;
        const static double EPSILON = 1e-10;
        double sqw, sqx, sqy, sqz;
        
        // quick conversion to Euler angles to give tilt to user
        sqw = rotation[3] * rotation[3];
        sqx = rotation[0] * rotation[0];
        sqy = rotation[1] * rotation[1];
        sqz = rotation[2] * rotation[2];
        
        euler[1] = asin(2.0 * (rotation[3] * rotation[1] - rotation[0] * rotation[2]));
        if (PI_OVER_2 - fabs(euler[1]) > EPSILON) {
            euler[2] = atan2(2.0 * (rotation[0] * rotation[1] + rotation[3] * rotation[2]),
                             sqx - sqy - sqz + sqw);
            euler[0] = atan2(2.0 * (rotation[3] * rotation[0] + rotation[1] * rotation[2]),
                             sqw - sqx - sqy + sqz);
        }
        else {
            // compute heading from local 'down' vector
            euler[2] = atan2(2 * rotation[1] * rotation[2] - 2 * rotation[0] * rotation[3],
                             2 * rotation[0] * rotation[2] + 2 * rotation[1] * rotation[3]);
            euler[0] = 0.0;
            
            // If facing down, reverse yaw
            if (euler[1] < 0)
                euler[2] = PI - euler[2];
        }
        return euler;
    }
    
    void setPos(int id, ofVec2f pos){
        if(id<nodes.size()){
            nodes[id].setPosition(pos);
        }
    }
    void setChainAngle(float _angle){
        _angle += limbAngle;
        for (int i = 0; i < nodes.size(); i++) {
            _angle *= 0.5;
            
            nodes[i].setOrientation(ofVec3f(0, 0, _angle));
        }
    }
    void setAngle(int id, float angle){
        if(id<nodes.size()){
            nodeAngle[id] = angle;
        }else{
            ofLog() << "out of bounds!";
        }
    }
    float getLimbAngle(int id){
        return limbAngle;
    }
    void connect(){
        for (int i = 0; i < nodes.size(); i++) {
            if(i>0)
                nodes[i].setParent(nodes[i-1]);
        }
    }
    ofVec2f getPos(int id){
        if(id<nodes.size()){
            connect();
            return nodePos[id];
        }else{
            ofLog() << "out of bounds!";
            return ofVec2f(0, 0);
        }
    }
    ofVec2f getPivotPos(int id){
        if(id<nodes.size()){
            connect();
            return pivotPos[id];
        }else{
            ofLog() << "out of bounds!";
            return ofVec2f(0, 0);
        }
    }
    float getAngle(int id){
        if(id<nodes.size()){
            return nodeAngle[id];
        }else{
            ofLog() << "out of bounds!";
            return NULL;
        }
    }
    int getChainCount(){
        return nodes.size();
    }
    ofNode *getNodeAt(int id){
        if(id<nodes.size()){
            connect();
            return &nodes[id];
        }else{
            ofLog() << "out of bounds!";
            return;
        }
    }
    ofNode *getRootNode(){
        return &nodes[0];
    }
};

#endif /* limb_hpp */
