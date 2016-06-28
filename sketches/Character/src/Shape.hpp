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
    virtual ~ShapeBase(){}
    ofRectangle rect;

    limb *limb;
    int jointId;
    float width;
    float angle;
    ofVec2f pos;
    bool isNode = false;
    ofNode pivot;
    ofColor color;
    int extraHeight;
    virtual void draw() = 0;
    void setup( int _width, int _extraHeight, class limb *_limb, int _jointId){
        extraHeight = _extraHeight;
        color = ofColor::lightGreen;
        width = _width;
        jointId = _jointId;
        limb = _limb;
        float height = limb->getPos(jointId).distance(limb->getPos(jointId+1));
        rect.set(-width/2, 0, width, height);
    }
    void update(){
        pos = limb->getPivotPos(jointId);
        angle = limb->getAngle(jointId);
        float height = limb->getPos(jointId).distance(limb->getPos(jointId+1))+extraHeight;
        rect.set(-width/2, 0, width, height);
    }
    void setColor(ofColor col){
        color = col;
    }
};

enum shapeType {
    shape_triangle,
    shape_ellipse,
    shape_rectangle,
    shape_claw,
    shape_last,
};

ShapeBase* ShapeFactory(enum shapeType type);

class TriangleShape: public ShapeBase{
public:
    ofPath path;
    void draw(){
        path.clear();
        path.triangle(rect.getTopLeft(), rect.getTopRight(), ofPoint(rect.getTopLeft().x+width/2, rect.getBottom()));
        path.rotate(angle, ofVec3f(0, 0, 1));
        path.translate(pos);
        path.setFillColor(color);
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
        ofSetColor(color);
        ofDrawEllipse(rect.getCenter(), rect.getWidth(), rect.getHeight());
        ofPopMatrix();
    }
};
class RectShape: public ShapeBase{
public:
    ofPath path;
    void draw(){
        ofPushMatrix();
        ofTranslate(pos);
        ofRotate(angle);
        ofSetColor(color);
        
        //ofDrawRectangle(rect.getTopLeft(), rect.getWidth(), rect.getHeight());

        
        
//        ofPath temp;
//        temp.moveTo(rect.getTopLeft());
//        
        ofPopMatrix();
    }
};

class ClawShape: public ShapeBase{
public:
    ofPath path;
    void draw(){
        path.clear();
        int count = 3;
        for (int i = 0; i < count; i++) {
            float w = width/count;
            float x = rect.getTopLeft().x;
            path.triangle(x + w * i,
                          rect.getTop(),
                          x + w * (i+1),
                          rect.getTop(),
                          x + w * i + w/2,
                          rect.getBottom()
                          );
        }
        path.rotate(angle, ofVec3f(0, 0, 1));
        path.translate(pos);
        path.setFillColor(color);
        path.draw();
    }
};
class EllipseHead: public ShapeBase{
public:
    ofPath path;
    void draw(){
        ofPushMatrix();
        ofTranslate(pos);
        ofRotate(angle);
        ofSetColor(color);
        ofDrawRectangle(rect.getTopLeft(), rect.getWidth(), rect.getHeight());
        ofPopMatrix();
    }
};


#endif /* Shape_hpp */
