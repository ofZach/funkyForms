

#pragma once
#include "ofMain.h"
#include "particle.h"
#include "ButterflyAnimation.h"
#include "flockingForce.h"


class ButterFlyParticle : public particle {
	
	
public:
	
	float				scale;
	int					color;
	float				alpha, alphaD;
	ofImage *			img;
	ButterflyAnimation	butterfly;
	float				radius;
    float               glowAlpha;
    //------------------------------------------------------------
    void addForFlocking(particle &p){
        
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
            alignment.sum += p.vel;
            alignment.count++;
        }
        
        if( distance > 0 && distance < cohesion.distance ){
            cohesion.sum += p.pos;
            cohesion.count++;
        }
    }
    
    //------------------------------------------------------------
    void addFlockingForce(){
        
        
        // seperation
        if(seperation.count > 0){
            seperation.sum /= (float)seperation.count;
        }
        
        // alignment
        if(alignment.count > 0){
            alignment.sum /= (float)alignment.count;
        }
        
        // cohesion
        if(cohesion.count > 0){
            cohesion.sum /= (float)cohesion.count;
            cohesion.sum -= pos;
        }
        
        float sepFrc 	= seperation.strength;
        float cohFrc 	= cohesion.strength;
        float alignFrc 	= alignment.strength;
        
        frc -= (seperation.sum.normalized()		    * sepFrc);
        frc += (alignment.sum			* alignFrc);
        frc += (cohesion.sum.normalized()			* cohFrc);
    }
    

    
    flockingForce cohesion;
    flockingForce seperation;
    flockingForce alignment;
    
    
	ButterFlyParticle() {
		img = NULL;
		
	}
	
	void setupButterfly() {
		
		radius = 20;
		seperation.distance		= radius * 2;
		alignment.distance		= 130;
		cohesion.distance		= 90;
		damping = 0.020;//0.07;
		
		
		seperation.strength		= .983;
		alignment.strength		= .19;
		cohesion.strength		= .019;
		
		alpha = 0;
		alphaD = 100;
		
		scale					= ofRandom(0.06, 0.1);
	}
	
	float getHeading2D() {	
		float a = (float)atan2(-vel.y, vel.x);
		return ofRadToDeg(-1*a);
	}
	
	
	void draw() {
		
		ofFill();
		alpha += (alphaD - alpha) / 20.0;
		
		ofEnableAlphaBlending();
		
		ofVec2f velNormal = vel;
		velNormal.normalize();
		ofVec2f velPerp;
		velPerp.x = -velNormal.y;
		velPerp.y = velNormal.x;
		
		float rot = getHeading2D();
		
		if(img != NULL) {
			ofSetColor(255, 255, 255, alpha * glowAlpha);
			ofSetRectMode(OF_RECTMODE_CENTER);
			img->draw(pos.x, pos.y, radius*6, radius*6);
			ofSetRectMode(OF_RECTMODE_CORNER);
		}
		
		ofSetHexColor(color);
		glPushMatrix();
		butterfly.rot = 90 + rot;
		butterfly.position.x = pos.x;
		butterfly.position.y = pos.y;
		butterfly.scale = scale;
		butterfly.draw(ofGetElapsedTimef());
		glPopMatrix();
		ofDisableAlphaBlending();
		
		
		
		
		
		
		
	}
	
	
};