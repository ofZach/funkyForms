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
    RectShape torsoShape;
    RectShape l_hand, l_hand2, r_hand2, r_hand, l_leg, l_leg2, r_leg, r_leg2;
    ofFloatColor colors[4] = {
        ofColor::lightGreen,
        ofColor::red,
        ofColor::mistyRose,
        ofColor::yellow
    };
    void setup(){
        skeleton.addLimb(ofVec2f(0, 0), 90, 2, 80, "torso", &skeleton.root); // torso 0
        ofNode *torso = skeleton.getLimb("torso")->getNodeAt(1);
        skeleton.getLimb("torso")->setAngleRange(0, 20);
        skeleton.getLimb("torso")->setAngleRange(1, 5);
        skeleton.getLimb("torso")->setAngleRange(2, 5);
        skeleton.addLimb(ofVec2f(-100, 0), 70, 3, 120, "l_hand", torso);
        skeleton.getLimb("l_hand")->setAngleRange(0, 45);
        skeleton.getLimb("l_hand")->setInitAngle(1, 25);
        skeleton.getLimb("l_hand")->setAngleRange(1, 20);
        skeleton.addLimb(ofVec2f(100, 0), -70, 3, 120, "r_hand", torso);
        skeleton.getLimb("r_hand")->setAngleRange(0, 45);
        skeleton.getLimb("r_hand")->setAngleRange(1, 20);
        skeleton.addLimb(ofVec2f(0, 20), 0, 2, 80, "head", torso); // head 3
        skeleton.addLimb(ofVec2f(-70, 0), 0, 3, 150, "l_leg", &skeleton.root); // left leg 4
        skeleton.getLimb("l_leg")->setAngleRange(0, 10);

        skeleton.addLimb(ofVec2f(70, 0), 10, 3, 150, "r_leg", &skeleton.root); // right leg 5
        skeleton.initAngles();
        
        torsoShape.setup(200, skeleton.getLimb("torso"), 0);
        torsoShape.setColor(ofColor::lightGreen);
        
        l_hand.setup(100, skeleton.getLimb("r_hand"), 1);
        l_hand.setColor(ofColor::lightGreen);

//        l_hand2.setup(100, skeleton.getLimb("l_hand"), 1);
//        l_hand2.setColor(ofColor::lightGreen);
//        
//        r_hand.setup(100, skeleton.getLimb("r_hand"), 0);
//        r_hand.setColor(ofColor::lightGreen);
//
//        r_hand2.setup(100, skeleton.getLimb("r_hand"), 1);
//        r_hand2.setColor(ofColor::lightGreen);
//
//        r_leg.setup(100, skeleton.getLimb("r_leg"), 0);
//        r_leg.setColor(ofColor::lightGreen);
//
//        r_leg2.setup(100, skeleton.getLimb("r_leg"), 1);
//        r_leg2.setColor(ofColor::lightGreen);

    }
    void update(){
        torsoShape.update();
        l_hand.update();
//        l_hand2.update();
//        r_hand.update();
//        r_hand2.update();
//        l_leg.update();
//        l_leg2.update();
//        r_leg.update();
//        r_leg2.update();
    }
    void draw(float velocity){
        l_hand.draw();
//        l_hand2.draw();
//        r_hand.draw();
//        r_hand2.draw();
//        r_leg.draw();
//        r_leg2.draw();
//        l_leg.draw();
//        l_leg2.draw();
        torsoShape.draw();
        skeleton.draw(velocity);
    }
};
#endif /* Character_hpp */
