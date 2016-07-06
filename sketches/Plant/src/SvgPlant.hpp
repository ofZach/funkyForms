//
//  SvgPlant.hpp
//  Plant
//
//  Created by Zerc on 6/28/16.
//
//

#ifndef SvgPlant_hpp
#define SvgPlant_hpp

#include "ofMain.h"
#include "ofxSvg.h"
class SvgPlant{
public:
    ofPoint points[14];
    ofxSVG svg;
    ofTessellator tess;
    vector<ofPolyline> outlines;
    ofPolyline polyLeft;
    ofPolyline polyTop;
    ofMesh mesh;
    ofRectangle rectLeft, rectTop;
    float leftRectW, leftRectH;
    float topRectW, topRectH;
    float w, h;
    bool isLeft;
    bool isCap = false;
    bool isTopRound = false;
    ofColor color;
    ofPolyline stroke1, stroke2;
    
    ofRectangle rect1;
    ofRectangle rect2;
    ofRectangle rect3;
    ofRectangle rect4;
    ofRectangle rect5;
    ofRectangle rect6;
    
    ofEvent<bool> onImpulseFinished;
    ofEvent<bool> *onTrigger;
    
    ofPolyline centerLine;
    float impulsePercent = 0;
    bool isImpulse = false;
    bool isImpulseFinished = false;
    
    void setup(ofEvent<bool> *event);
    void update(ofVec2f pos, ofVec2f leftRectSize, ofVec2f topRectSize, float radius);
    void drawDebug();
    void drawCenterLine();
    void impulse(bool &b);
    void draw();
    
    struct RangeColor{
        ofColor color;
        float start;
        float end;
    };
//    vector<RangeColor> colors;
    ofColor colors[4] = {
        ofColor::pink,
        ofColor::lightGreen,
        ofColor::magenta,
        ofColor::yellow
    };
    ofColor currColor;
    ofColor prevColor;
};

#endif /* SvgPlant_hpp */
