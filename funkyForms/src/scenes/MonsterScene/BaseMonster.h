

#pragma once
#include "ofMain.h"
//#include "ofxVectorMath.h"

class BaseMonster {
	
	
public:
	
	//int			id;
	ofVec2f	pos, vel, prePos;
	ofRectangle rect;
	
	BaseMonster() {
	}
	
	virtual void update() {
	}
	virtual void draw() {
		
		ofEnableAlphaBlending();
		ofFill();
		ofSetColor(255, 25, 0, 100);
		
		ofCircle(pos.x, pos.y, 30);
		
		ofSetColor(255, 255, 250);
		ofDrawBitmapString(ofToString(-999), pos.x, pos.y);
		ofDisableAlphaBlending();
	}
	
};