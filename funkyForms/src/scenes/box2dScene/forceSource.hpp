//
//  forceSource.hpp
//  funkyForms
//
//  Created by Qinzi Tan on 8/25/16.
//
//

#ifndef forceSource_hpp
#define forceSource_hpp

#include "ofMain.h"

class forceSource
{
public:
    
    void setup(ofPoint _pos, int _direction,ofPoint speedDiff, float _angleDiff);
    void update();
    void addBoundary(float _w,float _h,float r);
    void addSinMove(float h,int _amplitude, float _angleVel, float _xVel, float _centerY);
    void draw();

    
    
    ofPoint pos;
    ofPoint vel;
    ofPoint acc;
    ofPoint originPos;
    float angle;
    int direction;
    //    ofPoint speedDiff;
    float angleAcc;
};

#endif /* forceSource_hpp */