


#pragma once
#include "ofMain.h"
//#include "ofxVectorMath.h"
#include "TreeConstants.h"

class TreeLeaf {
	
public:
	
	ofPoint		pos;
	ofColor		color;
	bool		bDone;
	ofImage * img;
	float r, rd, rv;
	float alpha;
	
	float rate;
	TreeLeaf() {
		img = NULL;
		bDone = false;
		color.r = 255;
		color.g = 255;
		color.b = 255;
		color.a = 0;
		alpha = 0;
		r = 0;
		rv =0;
		rd = ofRandom(10, 20);
		rate= ofRandom(5, 10);
	}
	
	void update() {
		if(!bDone) alpha += rate;
		if(alpha >= 255) {
			alpha = 255;
			bDone = true;
		}
		
		rv = (rv*0.8) + (rd-r) / 19.0;
		r += rv;
		
	}
	
	void draw() {
		
		ofEnableAlphaBlending();
		ofSetColor(255,255,255, alpha);
		ofFill();
		if(img) {
			ofSetRectMode(OF_RECTMODE_CENTER);
			img->draw(pos.x, pos.y, r*2, r*2);
			ofSetRectMode(OF_RECTMODE_CORNER);
		}
		ofCircle(pos.x, pos.y, r);
		ofNoFill();
		ofSetColor(40, 100, 40);
		ofCircle(pos.x, pos.y, r);
		ofDisableAlphaBlending();
		
	}
	
	void drawTappered() {
		
		
	}
	
	
	
};
