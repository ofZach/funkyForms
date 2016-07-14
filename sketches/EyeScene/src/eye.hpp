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
    void randomBlink();
    bool isBlinking = false;
    bool isEyeOpening = true;
    bool isEyeClosing = false;
    bool isEyeOpen = false;
    bool isEyeClose = false;
    int blinkCounter = 0;
    int delayCounter = 0;
    int delay;
    
    void closeEye();
    void openEye();
    void blinking();
public:
    
    void setup(ofVec2f _pos, float _width, float _height);
    void update(ofVec2f _pos);
    void open();
    void close();
    void draw();
    void blink();

    void lookAt(ofVec2f _pos){lookAtPos = _pos;};
    void lookAtNear(ofVec2f _pos);
    
    float getWidth(){return width;}
    float getHeight(){return height;}
    ofVec2f getPos(){return pos;}
    float getScale(){return scale;};
    bool getEyeOpen(){return lids.isEyeOpen;}

    void addScaleForce(ofVec2f _pos, float _radius, float _speed, float _maxScale);

    void setAngle(float _angle){lids.setAngle(_angle);}
    void setScale(float _scale){scale = _scale;}
    void setEyeColor(ofColor color){eyeColor = color;};
};

#endif /* eye_hpp */
