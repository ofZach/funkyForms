//
//  Spring.cpp
//  WaveScene
//
//  Created by Zerc on 7/25/16.
//
//

#include "Spring.hpp"

void Spring::setup(float _strength, float _restLength, float _invMass){
    
    restLength = _restLength;
    strength = _strength;
    invMass = _invMass;
    mamb = invMass * invMass;
}
void Spring::update(Point_ *prevPoint, Point_ *point){
    ofVec2f delta = ofVec2f(point->p.x, point->p.y) - ofVec2f(prevPoint->p.x, prevPoint->p.y) ;
    float dist = delta.length();
    float normDistStrength = (dist - restLength) / (dist * mamb) * strength;
    delta.y *= normDistStrength * invMass * 0.2;
    if(!prevPoint->isFixed){
        prevPoint->p.y += delta.y;
    }
    if(!point->isFixed){
        point->p.y -= delta.y;
    }
}