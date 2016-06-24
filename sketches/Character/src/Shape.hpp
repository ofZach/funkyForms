//
//  Shape.hpp
//  Character
//
//  Created by Zerc on 6/24/16.
//
//

#ifndef Shape_hpp
#define Shape_hpp

#include "ofMain.h"
#include "limb.hpp"

class ShapeBase {
public:
    ofRectangle rect;
    
    limb *limb;
    int jointId;
    float width;
    float angle;
    ofVec2f pos;
    bool isNode = false;
    ofNode pivot;
    
    void setup(int _width, class limb *_limb, int _jointId){
        width = _width;
        jointId = _jointId;
        limb = _limb;
        float height = limb->getPos(jointId).distance(limb->getPos(jointId+1));
        rect.set(-width/2, 0, width, height);
    }
    void update(){
        pos = limb->getPivotPos(jointId);
        angle = limb->getAngle(jointId);
        float height = limb->getPos(jointId).distance(limb->getPos(jointId+1));
        rect.set(-width/2, 0, width, height);
    }
};
class TriangleShape: public ShapeBase{
public:
    ofPath path;
    void draw(){
        path.clear();
        path.triangle(rect.getTopLeft(), rect.getTopRight(), ofPoint(rect.getTopLeft().x+width/2, rect.getBottom()));
        path.rotate(angle, ofVec3f(0, 0, 1));
        path.translate(pos);
        path.setFillColor(ofColor::lightBlue);
        path.draw();
    }
};
class EllipseShape: public ShapeBase{
public:
    ofPath path;
    void draw(){
        ofPushMatrix();
        ofTranslate(pos);
        ofRotate(angle);
        ofSetColor(ofColor::yellow);
        ofDrawEllipse(rect.getCenter(), rect.getWidth(), rect.getHeight());
        ofPopMatrix();
    }
};

#endif /* Shape_hpp */
