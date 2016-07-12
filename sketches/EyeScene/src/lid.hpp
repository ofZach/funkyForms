//
//  lid.hpp
//  EyeScene
//
//  Created by Zerc on 7/12/16.
//
//

#ifndef lid_hpp
#define lid_hpp

#include "ofMain.h"

class lid{
public:
    ofMesh mesh;
    ofMesh mesh2;
    ofMesh sclera;

    int step = 4;
    
    int height = 20;
    int width = 100;
    
    int topHeight = height;
    int bottomHeight = height/2;
    
    int topHeight2 = -height;
    int bottomHeight2 = -height/2;
    
    float scale = 0.8;
    float scaleX = scale;
    float scaleY = scale;
    ofVec2f pos;
    int blinkCounter = 0;
    ofPolyline topline;

    int count = width;
    int blinkSpeed = 2;
    
    ofPath path;
    ofPath lidHole;
    bool isBlink;
    
    void setup(int _width, int _height);
    void drawSclera(){ sclera.draw(); }
    void drawLids();
    void update();
    void close(){}
    void open(){}
    void setSize(float _w, float _h){width = _w; height = _h;}
};

#endif /* lid_hpp */
