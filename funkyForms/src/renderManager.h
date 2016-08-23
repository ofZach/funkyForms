#pragma once

#include "ofMain.h"
#include "ofxSVG.h"
//#include "ofxSvgLoader.h"


#define RENDER_ASPECT 0.785
#define RENDER_WIDTH ((1920*3)*0.3)                               // not sure!
#define RENDER_HEIGHT (RENDER_WIDTH * RENDER_ASPECT)


enum screenName {
    SCREEN_LEFT,
    SCREEN_RIGHT,
    SCREEN_CENTER,
    SCREEN_TOP
};

class renderManager {
    
public:
    
    void setup();
    void update();
    void draw();
    
    ofRectangle getRectForScreen( screenName );
    
    ofRectangle getWholeRectangle(){
        return ofRectangle(0,0,fbo.getWidth(), fbo.getHeight());
    }
    
    void drawBuidling();
    
    float getWidth(){
        return fbo.getWidth();
    }
    
    float getHeight(){
        return fbo.getHeight();
    }
    
    ofFbo fbo;
    ofxSVG blocks;
    ofxSVG windows;
    
    //ofxSvgLoader svg;
    
    vector < ofPolyline > innerWindows;
    vector < ofPolyline > outerWindows;
    vector < ofPolyline > engraving;
    vector < ofPolyline > pillar;
    vector < ofPolyline > blocks2;
    vector < ofPolyline > edges;
    
};