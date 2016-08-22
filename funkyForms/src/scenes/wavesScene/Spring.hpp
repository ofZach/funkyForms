//
//  Spring.hpp
//  WaveScene
//
//  Created by Zerc on 7/25/16.
//
//

#ifndef Spring_hpp
#define Spring_hpp

#include "ofMain.h"

class Point_{
public:
    ofVec2f p;
    ofVec2f pp;
    bool isFixed;
};

class Spring{
public:
    bool isRelax;
    float strength;
    float restLength;
    float mamb;
    float invMass;
    
    void setup(float _strength, float _restLength, float _invMass);
    void update(Point_ *prevPoint, Point_ *point);
};
#endif /* Spring_hpp */
