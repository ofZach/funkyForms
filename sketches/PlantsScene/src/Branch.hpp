//
//  Branch.hpp
//  Plant
//
//  Created by Zerc on 6/28/16.
//
//

#ifndef Branch_hpp
#define Branch_hpp

#include "ofMain.h"
#include "iColor.hpp"

class Branch{
public:
    ofPoint points[14];
    int colorOffsetMult = 1;
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
    int resolution = 50;
        
    ofPolyline centerLine;
    float impulsePercent = 0;
    bool isImpulse = false;
    bool isImpulseFinished = false;
    
    void setup();
    void update(ofVec2f pos, ofVec2f leftRectSize, ofVec2f topRectSize, float radius, iColor &icolor);
    void drawDebug();
    void drawCenterLine();
    void setColorOffset(int _offset){ colorOffsetMult = _offset; }
    void impulse(ofColor &color);
    void draw();
    
    struct RangeColor{
        ofColor color;
        float start;
        float end;
    };
    
    ofColor pallete[9] = {
        ofColor(251,49,1),
        ofColor(190,130,19),
        ofColor(247,198,11),
        ofColor(36,202,144),
        ofColor(164,208,240),
        ofColor(42,137,222),
        ofColor(105,133,166),
        ofColor(3,82,221),
        ofColor(170,178,170)
    };
    ofColor currColor;
    ofColor prevColor;
};

#endif /* Branch_hpp */
