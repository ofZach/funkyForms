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
    vector<float> nodeAngle;
    ofVec2f pos;
    float angle;
    
    void setup(int count, ofVec2f _pos, float _angle){
        angle = _angle;
        pos = _pos;
        for (int i = 0; i < count; i++) {
            ofNode node;
            nodes.push_back(node);
            nodePos.push_back(ofVec2f(0, 0));
            nodeAngle.push_back(0);
        }
        setPos(0, pos);
    }
    void update(){
        for (int i = 0; i < nodes.size(); i++) {
            if(i>0)
                nodes[i].setParent(nodes[i-1]);
            float angle = quatToEuler(nodes[i].getGlobalOrientation()).z;
            nodeAngle[i] = ofRadToDeg( angle);
            nodePos[i] = nodes[i].getGlobalPosition();
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
        _angle += angle;
        for (int i = 0; i < nodes.size(); i++) {
            _angle *= 0.5;
            
            nodes[i].setOrientation(ofVec3f(0, 0, _angle));
        }
    }
    void setAngle(int id, float angle){
        if(id<nodes.size()){
            nodes[id].setOrientation(ofVec3f(0, 0, angle));
        }else{
            ofLog() << "out of bounds!";
        }
    }
    void connect(){
        for (int i = 0; i < nodes.size(); i++) {
            if(i>0)
                nodes[i].setParent(nodes[i-1]);
        }
    }
    void getLengthAt(int id){
        if(id<nodes.size()){
            nodes[id].setOrientation(ofVec3f(0, 0, angle));
        }else{
            ofLog() << "out of bounds!";
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
    float getAngle(int id){
        if(id<nodes.size()){
            connect();
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
