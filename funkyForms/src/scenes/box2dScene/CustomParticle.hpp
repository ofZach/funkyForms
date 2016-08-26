//
//  CustomParticle.hpp
//  funkyForms
//
//  Created by Qinzi Tan on 8/25/16.
//
//

#ifndef CustomParticle_hpp
#define CustomParticle_hpp

#include "ofMain.h"
#include "ofxBox2d.h"
//#define N 100

#endif /* CustomParticle_hpp */

class CustomParticle : public ofxBox2dCircle {
    
public:
    CustomParticle();
    
    void update();
    void draw(float _scale, int _length);
    void drawTrail(int _length);
    
    vector<ofPath> circles;
    ofColor color;
    string myString;
    
    ofPolyline modifiedPolyline;
    ofPolyline originalPolyline;
    
    //    vector<ofPolyline> trail;
    
    ofPolyline trail;
};
