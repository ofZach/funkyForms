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
    ofVec2f eyeballPos;
    ofVec2f lookAtPos;
    

    
    bool isMove;
    ofVec2f movePos;
    int moveCounter;

    ofPath ball;
    ofPath pupil;
    float pupilScale = 1.0;
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
    int delay = 0;
    
    void closeEye();
    void openEye();
    void blinking();
    void createEyeball();
    void calcEyeballPos();
    void calcEyeballMovements();
    bool isUpdateBlink = true;
    float topLidPercent = 0;
    bool isSynced = false;
    eye *eyeTarget;
    ofVec2f LookAtSmartPos;
public:
    float closeEyeSpeed = 0.02;
    float openEyeSpeed = 0.05;
        bool isCloseFinished();
    float width;
    float height;
    float initWidth;
    float initHeight;
    
    float scaleSpeed = 0.1;
    int blinkInterval = 70;
    void setup(ofVec2f _pos, float _width, float _height);
    void update(ofVec2f _pos);
    void open();
    void close();
    void draw();
    void blink();

    void lookAt(ofVec2f _pos){lookAtPos = _pos;};
    void lookAtSmart(ofVec2f _pos);
    void lookAtNear(ofVec2f _pos);
    
    float getWidth(){return width;}
    float getHeight(){return height;}
    float getScaledWidth(){return width*scale;}
    float getScaledHeight(){return height*scale;}
    ofVec2f getPos(){return pos;}
    ofVec2f getEyeBalPos(){return eyeballPos;}
    ofVec2f getLookAtPos(){return lookAtPos;}
    float getScale(){return scale;};
    bool getEyeOpen(){return lids.isEyeOpen;}
    lid *getLids(){return &lids;}

    void setUpdateBlink(bool b){isUpdateBlink = b;}
    void addScaleForce(ofVec2f _pos, float _radius, float _speed, float _maxScale);
    void addAngryForce(bool isClose, float speed, float max);
    void setSyncEye(eye *_eyeTarget){isSynced = true; eyeTarget = _eyeTarget;}
    void setAngle(float _angle){lids.setAngle(_angle);}
    void setScale(float _scale){scale = _scale;}
    void setPupulScale(float _scale){pupilScale = _scale;};
    void setEyeLidScale(float _scale){lids.setScale(_scale);}
    void setEyeColor(ofColor color){eyeColor = color;};
};

#endif /* eye_hpp */
