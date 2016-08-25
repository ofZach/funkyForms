//
//  Light.hpp
//  funkyForms
//
//  Created by Qinzi Tan on 8/25/16.
//
//

#ifndef Light_hpp
#define Light_hpp


#include "ofMain.h"
#include "LightSystem2D.h"

class Light : public ofBaseApp{
    
public:
    
    void setup(ofPoint _pos, int _direction,ofPoint speedDiff, float _angleDiff);
    void addBoundary(float _w,float _h,float r);
    void addSinMove(float h,int _amplitude, float _angleVel, float _xVel, float _centerY);
    
    
    ofPoint pos;
    ofPoint vel;
    ofPoint acc;
    ofPoint originPos;
    float angle;
    int direction;
    float angleAcc;
};


#endif /* Light_hpp */
