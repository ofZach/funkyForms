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
    bool isAnimating = false;
    bool isGrow = false;
    bool isFinished = false;
    bool isIn = false;
    bool isOut = false;
    float valueMax = 1;
    float valueMin = 0;
    float pct = 0; // percent 0 - 1
    float pctSpeed = 0.02; // percent speed
    float pctOffset = 0;
    float resultValue;
    void in(){isGrow = true;}
    void out(){isGrow = false;}
    
    void setup(float _valueMin, float _valueMax){
        valueMax = _valueMax;
        valueMin = _valueMin;
    }
    void setIn(){
        isGrow = true;
        pct = 1;
    }
    float setSpeed(float speed){
        pctSpeed = speed;
    }
    float setPctOffset(float offset){
        pctOffset = offset;
    }
    void update(){
        if(isGrow){
            pct += pctSpeed;
        }else{
            pct -= pctSpeed;
        }
        isIn = false;
        isOut = false;
        isAnimating = true;
        if(pct<0){
            isFinished = true;
            isIn = true;
            isAnimating = false;
        }
        if(pct>1){
            isOut = true;
            isAnimating = false;
        }
        pct = ofClamp(pct, 0, 1);
        resultValue = ofInterpolateCosine(valueMin, valueMax, pct+pctOffset);
    }
    float getValue(){
        return resultValue;
    }
};
#endif /* Animator_hpp */
