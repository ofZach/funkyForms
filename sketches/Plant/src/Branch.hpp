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
class Branch{
public:
    ofPoint points[14];

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
    
    ofEvent<ofColor> onImpulseFinished;
    ofEvent<ofColor> *onTrigger;
    
    ofPolyline centerLine;
    float impulsePercent = 0;
    bool isImpulse = false;
    bool isImpulseFinished = false;
    
    void setup(ofEvent<ofColor> *event);
    void update(ofVec2f pos, ofVec2f leftRectSize, ofVec2f topRectSize, float radius);
    void drawDebug();
    void drawCenterLine();
    void impulse(ofColor &color);
    void draw();
    
    struct RangeColor{
        ofColor color;
        float start;
        float end;
    };
    
    ofColor currColor;
    ofColor prevColor;
};

#endif /* Branch_hpp */
