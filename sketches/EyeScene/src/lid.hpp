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
private:
    float angle = 0;
    int step = 4;
    
    int height = 20;
    int width = 100;
    
    int blinkCounter = 0;
    
    int count = width;
    
    float scale = 0.8;
    float scaleX = scale;
    float scaleY = scale;
    
public:
    int blinkSpeed = 2;
    ofVec2f pos;
    
    ofPath lidHole;
    
    bool isBlink;
    
    void setup(int _width, int _height);
    void update();
    void setSize(float _w, float _h){width = _w; height = _h;}
    void setAngle(float _angle){angle = _angle;}
};

#endif /* lid_hpp */
