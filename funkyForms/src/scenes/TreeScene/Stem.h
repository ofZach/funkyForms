
#pragma once
#include "ofMain.h"
//#include "ofxVectorMath.h"
#include "TreeConstants.h"
#include "particle.h"

class Stem {

public:

	float		theta;
	bool		bALive;

	float		maxthickness;
	particle	head;
	ofVec2f	rootPos;
	int			stemLength, stemCount;

	ofPoint		pnts[MAX_STEMS_PNTS];

	// ------------------------------------------
	Stem() {

		stemCount	= 0;
		bALive		= false;
	}

	// ------------------------------------------ init stem
	void initStem(float x, float y) {

		maxthickness = ofRandom(1.0, 5.0);
		theta		 = ofRandomf();
		stemCount    = 0;
		bALive		 = true;
		stemLength   = (int)ofRandom(10, 50);
		rootPos.x    = x;
		rootPos.y    = y;

		for(int i=1; i<MAX_STEMS_PNTS; i++) {
			pnts[i] = 0;
		}
		head.setInitialCondition(x, y, ofRandom(-1.0, 1.0), ofRandom(-0.5, -1.0));
		head.damping = .01;//0.04678;
	}

	// ------------------------------------------ set the root
	void setRoot(float x, float y) {
		rootPos.x = x;
		rootPos.y = y;
	}

	// ------------------------------------------
	void update() {

		if(!bALive) return;

		if(stemCount < MAX_STEMS_PNTS) {

			theta += 0.1;

			// add a point as we grow
			pnts[stemCount].x = head.pos.x;
			pnts[stemCount].y = head.pos.y;

			head.addForce(((cos(theta) * ofRandomf())-head.frc.x) * 0.92, -0.1); // always grow up
			head.addDampingForce();
			head.update();

			head.resetForce();

			stemCount ++;
		}


	}

	// ------------------------------------------
	void draw() {

		if(!bALive) return;

		// the head
		ofFill();
		ofSetColor(255, 255, 255);
		head.draw();


		// the plant
		ofVec3f pos1, pos2;
		ofVec3f perp;
		ofVec3f scr;
		scr.set(0, 0, 1);


		ofNoFill();
		ofSetColor(255, 255, 255);
		glBegin(GL_QUAD_STRIP);
		for(int i=1; i<stemCount; i++) {

			pos1 = pnts[i];
			pos2 = pnts[i-1];
			perp.set(pos1 - pos2);
			perp.perpendicular(scr);

			float n = ofMap((float)i, 1.0, (float)stemCount, 0.0, 1.0);
			float thickness =  maxthickness - (n * maxthickness);

			float xOff        = perp.x * thickness;
			float yOff        = perp.y * thickness;

			glVertex3f(pos1.x - xOff, pos1.y - yOff, 0.0);
			glVertex3f(pos1.x + xOff, pos1.y + yOff, 0.0);

		}
		glEnd();

	}

};



