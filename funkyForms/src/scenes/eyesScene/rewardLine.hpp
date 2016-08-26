//
//  rewardLine.hpp
//  funkyForms
//
//  Created by Gordey on 8/24/16.
//
//

#ifndef rewardLine_hpp
#define rewardLine_hpp

#include "ofMain.h"
#include "Animator.hpp"

class rewardLine{
public:
    ofPolyline polyline;
    ofPath line;
    float lineWidth = 2;
    float lineLength = 100;
    float delay = 0.5;

    Animator lineAnim;
    bool isFinished = false;
    
    void setup();
    void update();
    
    void onLineFadeInEnd();
    void onLineFadeInStart();
    
    void fadeIn();
    void fadeOut();
    
    void draw();
    void drawLine();
    void drawCircle();
};

#endif /* rewardLine_hpp */
