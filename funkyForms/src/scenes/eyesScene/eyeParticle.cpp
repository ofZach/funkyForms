//
//  eyeParticle.cpp
//  funkyForms
//
//  Created by Gordey on 8/9/16.
//
//

#include "eyeParticle.hpp"
float eyeParticle::getAngle(){
    ofVec2f zero(1, 0);
    float diffX = zero.x - vel.x;
    float diffY = zero.y - vel.y;
    
    float angleTo = atan2(diffY, diffX);
    
    float diffAngle = (angleTo - angle);
    if (diffAngle < -PI) diffAngle += TWO_PI;
    if (diffAngle > PI) diffAngle -= TWO_PI;
    
    angle  += 0.03 * diffAngle;
    
    return angle;
}
void eyeParticle::addFlockingForce(){
    // seperation
    if(seperation.count > 0){							// let's add seperation :)
        seperation.sum /= (float)seperation.count;
        float sepFrc 	= seperation.strength;
        frc -= (seperation.sum.normalized()		    * sepFrc);
    }
    
    // alignment
    if(alignment.count > 0){
        alignment.sum /= (float)alignment.count;
        float alignFrc 	= alignment.strength;
        frc += (alignment.sum		* alignFrc);		// don't normalize the allignment, just use the average
    }
    
    // cohesion
    if(cohesion.count > 0){
        cohesion.sum /= (float)cohesion.count;
        cohesion.sum -= pos;
        float cohFrc 	= cohesion.strength;
        frc += (cohesion.sum.normalized()			* cohFrc);
    }
    
}
void eyeParticle::addForFlocking(eyeParticle &p){
    
    ofVec3f diff, diffNormalized;
    float distance;
    
    diff			= p.pos - pos;
    distance		= diff.length();
    diffNormalized	= diff;
    diffNormalized.normalize();
    
    if( distance > 0 && distance < seperation.distance ){
        seperation.sum += diffNormalized;
        seperation.count++;
    }
    
    if( distance > 0 && distance < alignment.distance ){
        alignment.sum += p.vel.getNormalized();
        alignment.count++;
    }
    
    if( distance > 0 && distance < cohesion.distance ){
        cohesion.sum += p.pos;
        cohesion.count++;
    }
}
