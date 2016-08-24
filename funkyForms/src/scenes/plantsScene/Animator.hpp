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
    bool isAnimatingPrev = false;
    
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
    
    void in(){
        isGrow = true;
        isIn = true;
        isOut = false;
    }
    void out(){
        isGrow = false;
        isOut = true;
        isIn = false;
    }
    
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
        isAnimating = true;
        
        if(pct<0){
            isFinished = true;
            isAnimating = false;
        }
        if(pct>1){
            isAnimating = false;
        }
        pct = ofClamp(pct, 0, 1);
        resultValue = ofInterpolateCosine(valueMin, valueMax, pct+pctOffset);
    }
    
    float getValue(){
        return resultValue;
    }
    
    // events should called in every frame
    // update()
    // onFade..(this, &myClass::onFade..); -- just run event you need
    // onFade..(this, &myClass::onFade..);
    // onEventEnd();
    template <typename OBJECT, typename FUNC>
    void onFadeInStart( OBJECT obj, FUNC func){
        if(isAnimatingPrev != isAnimating && pct < 0.5 && isIn){
            (obj->*func)();
        }
    };
    template <typename OBJECT, typename FUNC>
    void onFadeInEnd( OBJECT obj, FUNC func){
        if(isAnimatingPrev != isAnimating && pct > 0.5 && isIn){
            (obj->*func)();
        }
    }
    template <typename OBJECT, typename FUNC>
    void onFadeOutStart( OBJECT obj, FUNC func){
        if(isAnimatingPrev != isAnimating && pct > 0.5 && isOut){
            (obj->*func)();
        }
    }
    template <typename OBJECT, typename FUNC>
    void onFadeOutEnd( OBJECT obj, FUNC func){
        if(isAnimatingPrev != isAnimating && pct < 0.5 && isOut){
            (obj->*func)();
        }
    }
    void onEventEnd(){
        isAnimatingPrev = isAnimating;
    }
};
#endif /* Animator_hpp */
