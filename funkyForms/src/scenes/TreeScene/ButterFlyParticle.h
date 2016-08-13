

#pragma once
#include "ofMain.h"
#include "particle.h"
#include "ButterflyAnimation.h"

class ButterFlyParticle : public particle {
	
	
public:
	
	float				scale;
	int					color;
	float				alpha, alphaD;
	ofImage *			img;
	ButterflyAnimation	butterfly;
	float				radius;
	
	ButterFlyParticle() {
		img = NULL;
		
	}
	
	void setupButterfly() {
		
		radius = 20;
		seperation.distance		= radius * 3;
		alignment.distance		= 80;
		cohesion.distance		= 90;
		damping = 0.020;//0.07;
		
		
		seperation.strength		= .983;
		alignment.strength		= .15;
		cohesion.strength		= .15;
		
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
			ofSetColor(255, 255, 255, alpha);
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