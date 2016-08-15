

#pragma once
#include "ofMain.h"
//#include "ofxVectorMath.h"
#include "appSettings.h"    //2016
class MonsterHair {


public:

	ofVec2f pos1, pos2, p, v, a;

	MonsterHair() {
		p.set(0,0);
		v.set(0,0);
		a.set(0,0);
		pos1.set(0,0);
		pos2.set(0,0);
	}


	void update() {
		// Spring
		float M = 0.8;   // Mass
		float K = 1.2;   // Spring constant
		float D = 0.92;  // Damping

		ofVec2f force = -K * (p - pos2);    // f=-ky
		a = force / M;
		v = D * (v + a);
		p = p + v;

	}

	void draw() {
		ofPushStyle();
		ofSetColor(255, 0, 0);
		glLineWidth(4.09 * OFFSCREEN_SCALE);
		ofLine(pos1.x, pos1.y, p.x, p.y);
		ofPopStyle();
	}
};
