//
//  Animator.hpp
//  PlantsScene
//
//  Created by Zerc on 7/21/16.
//
//

#ifndef Animator_hpp
#define Animator_hpp

#include "ofMain.h"

class Animator{
public:
    bool isGrow = false;
    bool isFinished = false;
    float valueMax;
    float valueMin;
    float pct = 0; // percent 0 - 1
    float pctSpeed = 0.02; // percent speed
    float pctOffset = 0;
    void in(){isGrow = true;}
    void out(){isGrow = false;}
    
    void setup(float _valueMin, float _valueMax){
        valueMax = _valueMax;
        valueMin = _valueMin;
    }
    float setSpeed(float speed){
        pctSpeed = speed;
    }
    float setPctOffset(float offset){
        pctOffset = offset;
    }
    float getValue(){
        if(isGrow){
            pct += pctSpeed;
        }else{
            pct -= pctSpeed;
        }
        if(pct<0) isFinished = true;
        pct = ofClamp(pct, 0, 1);
        return ofInterpolateCosine(valueMin, valueMax, pct+pctOffset);
    }
};
#endif /* Animator_hpp */
