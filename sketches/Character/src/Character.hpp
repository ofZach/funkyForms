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
    void setup(){
        skeleton.addLimb(ofVec2f(-100, 0), 45, 4, 120,  &skeleton.torso);
        skeleton.addLimb(ofVec2f(100, 0), -90, 4, 120, &skeleton.torso);
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
    }
};
#endif /* Character_hpp */
