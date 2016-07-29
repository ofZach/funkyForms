//
//  StencilWaves.hpp
//  WaveScene
//
//  Created by Zerc on 7/29/16.
//
//

#ifndef StencilWaves_hpp
#define StencilWaves_hpp

#include "ofMain.h"
#include "inputManager.h"

class StencilWaves{
public:
    inputManager *IM;
    vector<ofPath> contours;
    ofFbo peopleFbo;
    
    void setup();
    void setInputManager(inputManager *_IM){ IM = _IM; }

    void update();
    void updateFbos();
    void updateContours();

    void draw();
};

#endif /* StencilWaves_hpp */
