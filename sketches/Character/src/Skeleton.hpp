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
#include "ofxGui.h"
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
//            ofLog() << angle;
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

class head{
public:
    ofNode head;
    
};

class Skeleton{
public:
    ofNode root;
    ofNode torso;
    
    vector<limb> limbs;
    vector<head> heads;
    vector<ofNode *> parentNodes;
    
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
    limb *getLimb(int id){
        if(id<limbs.size()){
            return &limbs[id];
        }else{
            ofLog() << "limbId out of bounds!";
            return;
        }
    }
    ofNode *getLimbNode(int limbId, int nodeId ){
        if(limbId<limbs.size()){
            return limbs[limbId].getNodeAt(nodeId);
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
        float a = ofMap(ofGetMouseX(), 0, ofGetWidth(), -90, 90);
        torsoRoot.setOrientation(ofVec3f(0, 0, a));

        torso.setParent(torsoRoot);
        torso.setPosition(0, -200, 0);
        
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
class ShapeBase {
public:
    ofRectangle rect;
    
    limb *limb;
    int jointId;
    float width;
    
    void setup(int _width, class limb *_limb, int _jointId){
        width = _width;
        jointId = _jointId;
        limb = _limb;
        float height = limb->getPos(jointId).distance(limb->getPos(jointId+1));
        rect.set(-width/2, 0, width, height);
    }
    void update(){
        float height = limb->getPos(jointId).distance(limb->getPos(jointId+1));
        rect.set(-width/2, 0, width, height);
    }
    
};
class TriangleShape: public ShapeBase{
public:
    ofPath path;
    void draw(){
        path.clear();
        path.triangle(rect.getTopLeft(), rect.getTopRight(), ofPoint(rect.getTopLeft().x+width/2, rect.getBottom()));
        path.rotate(limb->getAngle(jointId), ofVec3f(0, 0, 1));
        path.translate(limb->getPos(jointId));
        path.setFillColor(ofColor::lightBlue);
        path.draw();
    }
};
class EllipseShape: public ShapeBase{
public:
    ofPath path;
    void draw(){
        ofPushMatrix();
        ofTranslate(limb->getPos(jointId));
        ofRotate(limb->getAngle(jointId));
        ofSetColor(ofColor::yellow);
        ofDrawEllipse(rect.getCenter(), rect.getWidth(), rect.getHeight());
        ofPopMatrix();
    }
};
class Character{
public:
    Skeleton skeleton;
    TriangleShape trShape;
    EllipseShape elShape;
    void setup(){
        skeleton.addLimb(ofVec2f(-100, 0), 45, 4, 120,  &skeleton.torso);
        skeleton.addLimb(ofVec2f(100, 0), -90, 4, 120, &skeleton.torso);
        skeleton.addLimb(ofVec2f(-70, 0), 0, 3, 150, &skeleton.root);
        skeleton.addLimb(ofVec2f(70, 0), 0, 3, 150, &skeleton.root);
        trShape.setup(50, skeleton.getLimb(0), 0);
        elShape.setup(70, skeleton.getLimb(0), 2);
    }
    void update(){
        trShape.update();
        elShape.update();
    }
    void draw(){
        skeleton.draw();
        trShape.draw();
        elShape.draw();
    }
};
#endif /* Skeleton_hpp */
