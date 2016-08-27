//
//  modeBase.hpp
//  funkyForms
//
//  Created by Gordey on 8/18/16.
//
//

#ifndef modeBase_hpp
#define modeBase_hpp

#include "ofMain.h"
#include "cvManager.h"
class modeBase{
public:
    // Input
    ofRectangle screenLeft, screenTop, screenCenter, screenRight, screenBottom;
    
    bool isEnabled = true;
    bool isFadeFinished = false;
    bool isFading = false;
    virtual void fadeIn() = 0;
    virtual void fadeOut() = 0;
    virtual void draw() = 0;
    virtual void clear() = 0;
    cvPacket * cvData[2];
};

#endif /* modeBase_hpp */
