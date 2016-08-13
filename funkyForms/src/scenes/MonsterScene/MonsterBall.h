
#pragma once
#include "ofMain.h"
#include "ofxBox2d.h"


class MonsterBall : public ofxBox2dCircle {

public:
	
	float		initTime;
	float		age;
	
	ofImage *	img;
	ofColor		color;
	float		alphaPct;
	float		sizePct;
	
	MonsterBall() {
		sizePct = 1.0;
		alphaPct = 1.0;
		img = NULL;
		age = 0.0;
		initTime;
		color.a = 255;
	}

	void draw() {
		ofEnableAlphaBlending();
		ofPoint pos = getPosition();
		float	r   = getRadius() * sizePct;

		if(img) {
			ofFill();
			ofSetColor(color.r, color.g, color.b, color.a*alphaPct);
			ofSetRectMode(OF_RECTMODE_CENTER);
			img->draw(pos.x, pos.y, r*5, r*5);
			ofSetRectMode(OF_RECTMODE_CORNER);
		}
		ofSetColor(color.r, color.g, color.b, color.a);
		ofFill();
		ofCircle(pos.x, pos.y, r);
		ofNoFill();
		ofSetColor(40, 40, 40, color.a);
		ofCircle(pos.x, pos.y, r);
		ofDisableAlphaBlending();
	}

};





