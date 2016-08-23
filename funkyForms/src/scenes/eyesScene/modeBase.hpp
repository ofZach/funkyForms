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
};

#endif /* modeBase_hpp */
