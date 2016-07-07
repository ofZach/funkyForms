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
class Block{
public:
    ofRectangle rectFront;
    ofRectangle rectBack;
    struct Face{
        ofColor color;
        ofPolyline line;
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
    
    Direction direction;
    bool isLeft = true;
    
    ofColor colors[10] = {
        ofColor::lightCoral,
        ofColor::magenta,
        ofColor::lightCyan,
        ofColor::lightSkyBlue,
        ofColor::lightGoldenRodYellow,
        ofColor::pink,
        ofColor::yellow,
        ofColor::sandyBrown,
        ofColor::seaShell,
        ofColor::gainsboro
    };
    float rectDistance;
    int w, h;
    ofVec3f pos;
    float maxDist = 200;
    float maxRadius = 200;
    float lightRadius = 500;
    ofMesh mesh;
    void setup(ofVec2f _pos, int _w, int _h);
    void update(int x, int y);
    void draw();
};

#endif /* Block_hpp */
