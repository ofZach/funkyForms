//
//  Character.hpp
//  Character
//
//  Created by Zerc on 6/24/16.
//
//

#ifndef Character_hpp
#define Character_hpp

#include "ofMain.h"
#include "Skeleton.hpp"
#include "Shape.hpp"

class Character{
public:
    Skeleton skeleton;
    TriangleShape trShape;
    TriangleShape trShape2;
    TriangleShape trShape3;
    EllipseShape elShape;
    EllipseShape torso;
    EllipseShape head;
    RectShape rectShape;
    RectShape rectShape2;
    RectShape rectShape3;
    RectShape rectShape4;
    
    ofFloatColor colors[4] = {
        ofColor::lightGreen,
        ofColor::red,
        ofColor::mistyRose,
        ofColor::yellow
    };
    void setup(){
        skeleton.addLimb(ofVec2f(0, 0), 180, 3, 80, "torso", &skeleton.root); // torso 0
        ofNode *torso = skeleton.getLimb("torso")->getNodeAt(2);
        skeleton.addLimb(ofVec2f(-100, 0), 120, 3, 120, "l_hand", torso);
        skeleton.addLimb(ofVec2f(100, 0), -120, 3, 120, "r_hand", torso);
        skeleton.addLimb(ofVec2f(0, 20), 0, 3, 80, "head", torso); // head 3
        skeleton.addLimb(ofVec2f(-70, 0), 10, 3, 150, "l_leg", &skeleton.root); // left leg 4
        skeleton.addLimb(ofVec2f(70, 0), -10, 3, 150, "r_leg", &skeleton.root); // right leg 5

        rectShape.setup(140, skeleton.getLimb("torso"), 0);
        rectShape.setColor(colors[(int)ofRandom(0, 4)]);
        rectShape2.setup(300, skeleton.getLimb("torso"), 1);
        rectShape2.setColor(colors[(int)ofRandom(0, 4)]);
        head.setup(140, skeleton.getLimb("head"), 0);
        head.setColor(colors[(int)ofRandom(0, 4)]);
//        trShape.setup(50, skeleton.getLimb(1), 0);
//        trShape.setColor(colors[(int)ofRandom(0, 4)]);
//        trShape2.setup(80, skeleton.getLimb(4), 0);
//        trShape2.setColor(colors[(int)ofRandom(0, 4)]);
//        trShape3.setup(80, skeleton.getLimb(5), 0);
//        trShape3.setColor(colors[(int)ofRandom(0, 4)]);
//        rectShape3.setup(10, skeleton.getLimb(4), 1);
//        rectShape3.setColor(colors[(int)ofRandom(0, 4)]);
//        rectShape4.setup(10, skeleton.getLimb(5), 1);
//
//        elShape.setup(70, skeleton.getLimb(1), 1);
    }
    void update(){
//        trShape.update();
//        trShape2.update();
//        trShape3.update();
//        elShape.update();
        rectShape.update();
        rectShape2.update();
        head.update();
    }
    void draw(float velocity){
        rectShape.draw();
        rectShape2.draw();
//        trShape.draw();
//        trShape2.draw();
//        trShape3.draw();
//        elShape.draw();
        head.draw();
        skeleton.draw(velocity);
    }
};
#endif /* Character_hpp */
