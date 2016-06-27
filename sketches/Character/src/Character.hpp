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
#include "ofxGui.h"

class Character{
public:
    Skeleton skeleton;
    RectShape body;
    
    RectShape l_hand;
    RectShape l_hand2;
    
    RectShape r_hand;
    RectShape r_hand2;
    
    RectShape l_leg;
    TriangleShape l_leg2;
    
    RectShape r_leg;
    TriangleShape r_leg2;
    
    TriangleShape mouth;
    
    HeadEyeShape head;
    
    ClawShape l_claw;
    ClawShape r_claw;
    ClawShape headClaw;
    
    ofFloatColor colors[4] = {
        ofColor::lightGreen,
        ofColor::red,
        ofColor::mistyRose,
        ofColor::yellow
    };
    void setup(){

        
        skeleton.addLimb(ofVec2f(0, 0), 180, 2, 80, "torso", &skeleton.root); // torso 0
        ofNode *torso = skeleton.getLimb("torso")->getNodeAt(1);
        skeleton.getLimb("torso")->setPivot(0, ofVec2f(0, -10));
        skeleton.addLimb(ofVec2f(-60, 0), 120, 4, 120, "l_hand", torso);
        skeleton.getLimb("l_hand")->setPos(3, ofVec2f(0, 30));
        skeleton.addLimb(ofVec2f(60, 0), -120, 4, 120, "r_hand", torso);
        skeleton.getLimb("r_hand")->setPos(3, ofVec2f(0, 30));
        skeleton.addLimb(ofVec2f(0, 20), 0, 3, 80, "head", torso); // head 3
        skeleton.addLimb(ofVec2f(0, 20), 90, 2, 80, "mouth", skeleton.getLimb("head")->getNodeAt(0)); // head 3
        skeleton.addLimb(ofVec2f(-40, 0), 0, 3, 150, "l_leg", &skeleton.root); // left leg 4
        skeleton.addLimb(ofVec2f(40, 0), 0, 3, 150, "r_leg", &skeleton.root); // right leg 5

        body.setup(200, 30, skeleton.getLimb("torso"), 0);
        body.setColor(ofColor::lightGreen);
        l_hand.setup(40, 0, skeleton.getLimb("l_hand"), 0);
        l_hand.setColor(ofColor::lightGreen);
        l_hand2.setup(40, 0, skeleton.getLimb("l_hand"), 1);
        l_hand2.setColor(ofColor::khaki);
        r_hand.setup(40, 0, skeleton.getLimb("r_hand"), 0);
        r_hand.setColor(ofColor::lightGreen);
        r_hand2.setup(40, 0, skeleton.getLimb("r_hand"), 1);
        r_hand2.setColor(ofColor::khaki);
        r_claw.setup(40, 0, skeleton.getLimb("r_hand"), 2);
        r_claw.setColor(ofColor::white);
        l_claw.setup(40, 0, skeleton.getLimb("l_hand"), 2);
        l_claw.setColor(ofColor::white);
        headClaw.setup(40, 0, skeleton.getLimb("head"), 1);
        headClaw.setColor(ofColor::white);
        l_leg.setup(40, 0, skeleton.getLimb("l_leg"), 0);
        l_leg.setColor(ofColor::lightGreen);
        l_leg2.setup(40, 0, skeleton.getLimb("l_leg"), 1);
        l_leg2.setColor(ofColor::khaki);
        r_leg.setup(40, 0, skeleton.getLimb("r_leg"), 0);
        r_leg.setColor(ofColor::lightGreen);
        r_leg2.setup(40, 0, skeleton.getLimb("r_leg"), 1);
        r_leg2.setColor(ofColor::khaki);
        head.setup(200, 0, skeleton.getLimb("head"), 0);
        head.setColor(ofColor::lightGreen);
        mouth.setup(200, 0, skeleton.getLimb("mouth"), 0);
        mouth.setColor(ofColor::pink);
        
    }
    void update(){
        body.update();
        l_hand.update();
        l_hand2.update();
        r_hand.update();
        r_hand2.update();
        r_claw.update();
        l_claw.update();
        l_leg.update();
        l_leg2.update();
        r_leg.update();
        r_leg2.update();
        head.update();
        mouth.update();
        headClaw.update();
    }
    void draw(float velocity){
        skeleton.draw(velocity);
        body.draw();
        l_hand.draw();
        l_hand2.draw();
        r_hand.draw();
        r_hand2.draw();
        l_leg.draw();
        l_leg2.draw();
        r_leg.draw();
        r_leg2.draw();
        r_claw.draw();
        l_claw.draw();
        head.draw();
        mouth.draw();
        headClaw.draw();
    }
};
#endif /* Character_hpp */
