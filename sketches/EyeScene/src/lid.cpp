//
//  lid.cpp
//  EyeScene
//
//  Created by Zerc on 7/12/16.
//
//

#include "lid.hpp"
void lid::setup(int _width, int _height){
    width = _width;
    height = _height;
    
    lidHole.setCurveResolution(6);
}
void lid::update(){
    lidHole.clear();

    if(isBlink){
        int maxCount = 2*pi*blinkSpeed;
        float sine = (-cos(blinkCounter*1.0/blinkSpeed+pi)+1)/2.0;
        float sine2 = (-cos(blinkCounter*1.0/blinkSpeed+pi)+1)/2.0;
        scaleY = sine*scale;
        
        if(blinkCounter > maxCount){
            scaleY = scale;
            blinkCounter = 0;
            isBlink = false;
            
        }else{
            blinkCounter++;
        }
    }
    
    // create rig
    ofPoint p0(-width/2, 0);
    ofPoint p1(0, -height/2);
    ofPoint p2(width/2, 0);
    ofPoint p3(0, height/2);
    
    lidHole.lineTo(p0);
    lidHole.bezierTo(p0, p1, p2);
    lidHole.lineTo(p2);
    lidHole.bezierTo(p2, p3, p0);
    
    lidHole.scale(scaleX, scaleY);
    lidHole.rotate(angle, ofVec3f(0, 0, 1));
}
