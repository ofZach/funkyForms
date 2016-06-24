//
//  eye.hpp
//  Eye
//
//  Created by Zerc on 6/22/16.
//
//

#ifndef eye_hpp
#define eye_hpp

#include "ofMain.h"
#include "ofxGui.h"
class lid{
public:
    ofMesh mesh;
    ofMesh mesh2;
    ofMesh sclera;

    ofPath path;
    ofPath path2;
    
    int step = 4;
    
    int height = 20;
    int width = 100;
    
    int count = width;
    int topHeight = height;
    int bottomHeight = height/2;
    
    int topHeight2 = -height;
    int bottomHeight2 = -height/2;
    
    float scale = 0.8;
    float scaleX = scale;
    float scaleY = scale;
    ofVec2f pos;
    int blinkCounter = 0;
    int blinkSpeed = 2;
    bool isBlink;
    ofPolyline topline;
    
    void setup(int _width, int _height){
        width = _width;
        height = _height;
        
        topHeight = height;
        bottomHeight = height/2;
        
        int c = width;
        while(c%step!=0){
            c++;
        }
        count = c;
        
        topHeight2 = -height;
        bottomHeight2 = -height/2;
        mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
        mesh2.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
        sclera.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    }
    void drawSclera(){
        sclera.draw();
    }
    void drawLids(){
        path.setFillColor(ofColor::red);
        path.draw();
        
        path2.setFillColor(ofColor::green);
        path2.draw();
    }
    void update(){
        path.clear();
        path2.clear();

        ofNode root;
        ofNode top;
        ofNode bottom;
        
        ofNode root2;
        ofNode top2;
        ofNode bottom2;
//
        if(isBlink){
            int maxCount = 2*pi*blinkSpeed;
            float sine = (-cos(blinkCounter*1.0/blinkSpeed+pi)+1)/2.0;
            float sine2 = (-cos(blinkCounter*1.0/blinkSpeed+pi)+1)/2.0;
            scaleY = sine*scale;
            
            if(blinkCounter > maxCount){
                scaleY = scale;
                blinkCounter = 0;
                isBlink = false;
                
            }else{
                blinkCounter++;
            }
        }
        
        top.setParent(root);
        bottom.setParent(root);
        top.setPosition(0, 0, topHeight);
        bottom.setPosition(0, 0, bottomHeight);
        
        top2.setParent(root2);
        bottom2.setParent(root2);
        top2.setPosition(0, 0, topHeight2);
        bottom2.setPosition(0, 0, bottomHeight2);
        
        for (int i = 0; i < count; i+=step) {
            root.setPosition(i, 0, 0);
            
            if(i>0) root.rotate(180.0/((count/step)-1), ofVec3f(1, 0, 0));
            ofVec2f topPos = top.getGlobalPosition();
            ofVec2f bottomPos = bottom.getGlobalPosition();
            
            path.lineTo(topPos);
        }
        for (int i = count-1; i > 0; i-=step) {
            root2.setPosition(i, 0, 0);
            
            if(i>0) root2.rotate(180.0/((count/step)-1), ofVec3f(1, 0, 0));
            ofVec2f topPos2 = top2.getGlobalPosition();
            ofVec2f bottomPos2 = bottom2.getGlobalPosition();

            path.lineTo(topPos2);
        }
        path2.append(path);
        path2.scale(scaleX, scaleY);
        ofPoint p((count - (count*scale))/2.0, 0);
        path2.translate(p);
    }
    void close(){
        
    }
    void open(){
        
    }
};
class eye{
public:
    lid lids;
    ofVec2f pos;
    ofMesh sclera;
    int width;
    int height;
    bool isMove;
    ofVec2f movePos;
    int moveCounter;
    ofPath ball;
    ofPath pupil;
    
    void setup(ofVec2f _pos, int _width, int _height){
        width = _width;
        height = _height;
        pos = _pos;
        lids.setup(width, height);
        movePos.set(0, 0);
    }
    void update(){
        
    }
    void draw(int x, int y){
        ball.clear();
        pupil.clear();
        
        lids.update();
        
        if(ofGetFrameNum()%(int)ofRandom(50, 200)==0){
            lids.isBlink = true;
            float blinkSpeed = ofRandom(1.2, 3);
            lids.blinkSpeed = blinkSpeed;
        }
        if(ofGetFrameNum()%(int)ofRandom(20, 70)==0){
            isMove = true;
        }
        if(isMove){
            movePos = ofVec2f(ofNoise(moveCounter/12.0+1000)* height/1.5, ofNoise(moveCounter/15.0)* height/1.5);
            moveCounter ++;
        }
        if(moveCounter%(int)ofRandom(2, 10)==0){
            isMove = false;
        }
//        // sclera
//        ofPushMatrix();
//        ofTranslate(pos);
//        lids.drawSclera();
//        ofPopMatrix();
//        
        // eyeball
        ofNode root;
        ofNode child;
        child.setParent(root);
        root.setPosition(pos.x+lids.count/2+movePos.x, pos.y+movePos.y, -200);
        child.setPosition(0, 0, -height/2.5);
        root.lookAt(ofVec3f(x, y, 0));
        
        
        float radius = height/1.2;
        ofVec2f ballPos = child.getGlobalPosition();

        lids.path.translate(pos);
        lids.path2.translate(pos);
        
        pupil.circle(ballPos, radius/2);
        pupil.setPolyWindingMode(OF_POLY_WINDING_ABS_GEQ_TWO );
        pupil.append(lids.path2);
        
        ball.circle(ballPos, radius);
        ball.setPolyWindingMode(OF_POLY_WINDING_ABS_GEQ_TWO );
        ball.append(lids.path2);
        
        lids.path.setFillColor(ofColor::black);
        lids.path.draw();
        lids.path2.draw();
        ball.setFillColor(ofColor::black);
        ball.draw();
        
        pupil.setFillColor(ofColor::darkRed);
        pupil.draw();
//        // lids
//        ofPushMatrix();
//        ofTranslate(pos);
//        lids.drawLids();
//        ofTranslate(pos);
//        ofPopMatrix();
    }
};

#endif /* eye_hpp */
