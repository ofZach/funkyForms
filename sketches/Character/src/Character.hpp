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
    EllipseShape elShape;
    EllipseShape torso;
    
    void setup(){
        skeleton.addLimb(ofVec2f(-100, 0), 45, 2, 120,  &skeleton.torso);
        skeleton.setPivot(0, 0, ofVec2f(100, 0));
        skeleton.addLimb(ofVec2f(100, 0), -90, 2, 120, &skeleton.torso);
        skeleton.addLimb(ofVec2f(-70, 0), 0, 3, 150, &skeleton.root);
        skeleton.addLimb(ofVec2f(70, 0), 0, 3, 150, &skeleton.root);
        trShape.setup(50, skeleton.getLimb(0), 0);
        elShape.setup(70, skeleton.getLimb(0), 2);
    }
    void update(){
        trShape.update();
        elShape.update();
    }
    void draw(){
        skeleton.draw();
        trShape.draw();
        elShape.draw();
//        torso.draw();
    }
};
#endif /* Character_hpp */
