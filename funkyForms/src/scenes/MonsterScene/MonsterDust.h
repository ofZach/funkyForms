
#pragma once
#include "ofMain.h"

class MonsterDust {

public:

	ofPoint			color, colorD;
	ofImage *		img;
	ofPoint			pos, vel, acc;
	bool			bHit, dead, bColor;
	float			r;
	float           rate, faderate;

	float alpha, alphaD;

	MonsterDust(float x, float y) {
		bColor = false;
		img = NULL;
		rate = ofRandom(0.3, 0.5);
		bHit = false;
		dead = false;
		pos.set(x, y);

		acc.x = ofRandom(-rate, rate);
		acc.y = ofRandom(-rate, rate);

		vel.x = ofRandom(-rate, rate);
		vel.y = ofRandom(-rate, rate);

		color.x = 255;
		color.y = 255;
		color.z = 255;
		alpha = 255;
		//alphaD = alpha;

		colorD = color;

		faderate = ofRandom(10, 20);
		r = ofRandom(3, 6.0);
	}

	void update() {
		if(dead) return;

		if(alpha <= 0) {
			dead = true;

		}

		alpha -= faderate;

		vel += acc;
		pos += vel;

		color += (colorD - color) / r;
		//alpha += (alphaD-alpha) / r;
	}

	void draw() {
		if(dead) return;
		ofSetColor(color.x, color.y, color.z, alpha);
		ofFill();
		if(img) {
			ofSetRectMode(OF_RECTMODE_CENTER);
			img->draw(pos.x, pos.y, r*5, r*5);
			ofSetRectMode(OF_RECTMODE_CORNER);
		}
		ofCircle(pos.x, pos.y, r);
	}

};
