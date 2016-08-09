//
//  eyeParticle.hpp
//  funkyForms
//
//  Created by Gordey on 8/9/16.
//
//

#ifndef eyeParticle_hpp
#define eyeParticle_hpp

#include "ofMain.h"
#include "particle.h"

class flockingForce {
public:
    
    int			count;
    ofVec2f	sum;
    float		distance;
    float		strength;
    
};

class eyeParticle : public particle{
public:
    flockingForce cohesion;
    flockingForce seperation;
    flockingForce alignment;
    
    float angle;
    
    ofVec2f getPos(){ return pos; }
    float getAngle();
    
    void addForFlocking(eyeParticle &p);
    void addFlockingForce();
};

#endif /* eyeParticle_hpp */
