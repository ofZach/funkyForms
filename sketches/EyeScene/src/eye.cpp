//
//  eye.cpp
//  Eye
//
//  Created by Zerc on 6/22/16.
//
//

#include "eye.hpp"
void eye::setup(ofVec2f _pos, float _width, float _height){
    width = _width;
    height = _height;
    pos = _pos;
    lids.setup(width, height);
    movePos.set(0, 0);
}
void eye::draw(){
    lids.lidHole.draw();
    
    ball.setFillColor(ofColor::darkRed);
    ball.draw();
    
    pupil.setFillColor(ofColor::black);
    pupil.draw();
}
void eye::update(ofVec2f _pos){
    pos = _pos;
    
    ball.clear();
    pupil.clear();
    
    lids.update();
    
    if(ofGetFrameNum()%(int)ofRandom(50, 200)==0){
        lids.isBlink = true;
        float blinkSpeed = ofRandom(1.2, 5);
        lids.blinkSpeed = blinkSpeed;
    }
    if(ofGetFrameNum()%(int)ofRandom(50, 170)==0){
        isMove = true;
    }
    if(isMove){
        movePos = ofVec2f(ofNoise(moveCounter/12.0+1000), ofNoise(moveCounter/15.0));
        moveCounter ++;
    }
    if(moveCounter%(int)ofRandom(2, 10)==0){
        isMove = false;
    }
    
    ofVec2f offsetPos(ofMap(movePos.x, 0, 1, -width/2., width/2.),
                      ofMap(movePos.y, 0, 1, -height/2., height/2.)
                      );
    ofVec2f ballPos = pos+offsetPos;
    
    lids.lidHole.translate(pos);
    
    float radius = height/5.6;
    
    pupil.circle(ballPos, radius/2);
    pupil.setPolyWindingMode(OF_POLY_WINDING_ABS_GEQ_TWO );
    pupil.append(lids.lidHole);
    
    ball.circle(ballPos, radius);
    ball.setPolyWindingMode(OF_POLY_WINDING_ABS_GEQ_TWO );
    ball.append(lids.lidHole);

}