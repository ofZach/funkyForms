//
//  Shapes.hpp
//  WaveScene
//
//  Created by Zerc on 7/29/16.
//
//

#ifndef Shapes_hpp
#define Shapes_hpp

#include "ofMain.h"
class ShapeBase{
public:
    ofPath path;
    virtual void setup() = 0;
    void setColor(ofColor color){path.setFillColor(color);}
    virtual void draw(){path.draw();}
};

enum ShapeType {
    PEBEL1,
    PEBEL2,
    PEBEL3,
    BLOB1
};

ShapeBase* ShapeFactory(enum ShapeType type);

class ShapePebel1 : public ShapeBase {
public:
    void setup(){
        path.lineTo(50,11);
        path.bezierTo(45,27,24,35,0,35);
        path.bezierTo(-24,35,-50,26,-50,10);
        path.bezierTo(-50,-6,-22,-35,5,-35);
        path.bezierTo(41,-34,54,-4,50,11);
    }
};
class ShapePebel2 : public ShapeBase {
public:
    void setup(){
        path.lineTo(-30,9);
        path.bezierTo(-38,-13,-20,-31,-4,-31);
        path.bezierTo(14,-31,33,-12,32,8);
        path.bezierTo(30,44,-23,32,-30,9);
    }
};
class ShapePebel3 : public ShapeBase {
public:
    void setup(){
        path.lineTo(-24,-2);
        path.bezierTo(-30,-26,-8,-38,6,-30);
        path.bezierTo(24,-22,28,-1,23,19);
        path.bezierTo(15,51,-19,18,-24,-2);
    }
};
class ShapeBlob1 : public ShapeBase {
public:
    void setup(){
        path.lineTo(-15,1);
        path.bezierTo(-39,-21,-17,-44,-3,-23);
        path.bezierTo(6,-9,17,-13,27,-24);
        path.bezierTo(51,-46,72,4,34,-4);
        path.bezierTo(13,-9,-6,10,11,28);
        path.bezierTo(29,45,7,60,5,44);
        path.bezierTo(4,22,-5,10,-15,1);
    }
};

#endif /* Shapes_hpp */
