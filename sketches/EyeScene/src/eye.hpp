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
#include "lid.hpp"

class eye{
private:
    lid lids;
    ofVec2f pos;
    ofMesh sclera;
    float width;
    float height;
    bool isMove;
    ofVec2f movePos;
    int moveCounter;
    ofPath ball;
    ofPath pupil;
public:
    void setup(ofVec2f _pos, float _width, float _height);
    void update(ofVec2f _pos);
    void draw();
    float getWidth(){return width;}
    float getHeight(){return height;}
};

#endif /* eye_hpp */
