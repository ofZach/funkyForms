//
//  Block.hpp
//  BlocksOrtho
//
//  Created by Zerc on 7/7/16.
//
//

#ifndef Block_hpp
#define Block_hpp

#include "ofMain.h"
#include "iColor.hpp"

class Block{
public:
    iColor icolor;
    ofRectangle rectFront;
    ofRectangle rectBack;
    struct Face{
        ofColor color;
        ofPolyline lineT;
        ofPolyline lineB;
        ofMesh mesh;
        ofVec3f points[4];
    };
    vector<Face> faces;
    
    enum Direction{
        LEFT,
        RIGHT,
        TOPLEFT,
        TOPRIGHT
    };
    
    Direction direction = LEFT;
    bool isLeft = true;
    bool runOnce = true;
    ofColor colors[9] = {
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
    bool isOver = false;
    bool isOverPast = false;
    float randomOffset;
    float rectDistance;
    float faceResolution = 100;
    int w, h;
    ofVec3f pos;
    float maxDist = 200;
    float maxRadius = 200;
    float lightRadius = 200;
    ofMesh mesh;
    void setup(ofVec2f _pos, int _w, int _h);
    void update(int x, int y);
    void draw();
};

#endif /* Block_hpp */
