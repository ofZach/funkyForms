//
//  lid.hpp
//  EyeScene
//
//  Created by Zerc on 7/12/16.
//
//

#ifndef lid_hpp
#define lid_hpp

#include "ofMain.h"

class lid{
public:
    float angle = 0;
    int step = 4;
    
    int height = 20;
    int width = 100;
    
    int blinkCounter = 0;
    
    int count = width;
    
    float scale = 0.8;
    float scaleX = scale;
    float scaleY = scale;
    int delayCounter = 0;
    int randomDelay;
    float scaleVel = 0.2;
    float scaleSpeed = 0.2;
    float topLidPos;
    float topLidPercent = 0;

    int blinkSpeed = 2;
    ofVec2f pos;
    
    ofPath lidHole;
    
    // Polyline
    ofPolyline contour;
    
    bool isOpening = true;
    bool isEyeOpen = false;
    bool isClosing = false;
    bool isBlinking;
    
    void setup(int _width, int _height);
    void open();
    void close();
    void update();
    void updateScaleForce();
    
    float getTopLidPos(){return topLidPos;}
    float getHeight(){return height;}
    float getWidth(){return width;}
    
    ofPath getPath(){return lidHole;}
    
    void setSize(float _w, float _h){width = _w; height = _h;}
    void setAngle(float _angle){angle = _angle;}
    void setScaleSpeed(float speed){scaleSpeed = speed;}
    void setScale(float _scale){scaleY = _scale;}
    void setTopLidPos(float percent);

    void draw();
};

#endif /* lid_hpp */
