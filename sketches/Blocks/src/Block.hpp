//
//  Block.hpp
//  Blocks
//
//  Created by Zerc on 7/6/16.
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
        ofVec2f dir;
        ofPolyline line;
        ofMesh mesh;
    };
    bool isLeft = false;
    vector<Face> faces;
    
    float rectFrontW  = 100;
    float rectFrontH = 200;
    float rectBackW = 50;
    float rectBackH = 20;
    float maxDist = 300;
    ofVec2f pos;
    
    ofColor rectFrontColor, rectBackColor;
    ofColor colors[10] = {
        ofColor::lightCoral,
        ofColor::lightSalmon,
        ofColor::lightCyan,
        ofColor::lightSkyBlue,
        ofColor::lightGoldenRodYellow,
        ofColor::pink,
        ofColor::lightSlateGray,
        ofColor::sandyBrown,
        ofColor::seaShell,
        ofColor::black
    };
    float distance;
    float rectDistance;
    void setup(ofVec2f _pos, int _w, int _h);
    void update(int x, int y);
    void draw();
    ofVec2f getPos(){return pos;}
    
};

#endif /* Block_hpp */
