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

class eye {
private:
    ofVec2f pos;
    ofVec2f lookAtPos;
    
    float width;
    float height;
    float initWidth;
    float initHeight;
    
    bool isMove;
    ofVec2f movePos;
    int moveCounter;

    ofPath ball;
    ofPath pupil;
    lid lids;
    
    float scale = 1.0;
    
    ofColor eyeColor;
public:
    void setup(ofVec2f _pos, float _width, float _height);
    void update(ofVec2f _pos);
    void draw();
    void blink();
    void lookAt(ofVec2f _pos){lookAtPos = _pos;};
    
    float getWidth(){return width;}
    float getHeight(){return height;}
    ofVec2f getPos(){return pos;}
    float getScale(){return scale;};
    
    void addScaleForce(ofVec2f _pos, float _radius, float _speed, float _maxScale);

    float setScale(float _scale){scale = _scale;}
    void setEyeColor(ofColor color){eyeColor = color;};
};

#endif /* eye_hpp */
