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
    void setup(string file, int l_size, int r_size);
    void update();
    void draw(float x, float y);
};

#endif /* SvgPlant_hpp */
