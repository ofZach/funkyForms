#pragma once

#include "ofMain.h"
#include "ofxSVG.h"
#include "FernStyle.h"

class Fern {
protected:
	vector<Fern> branches;
	int level;
	float length;
	ofPoint angle;
	bool side;

	const FernStyle* style;

	void setup(const FernStyle* style, int level, float length, ofPoint angle, bool side);
public:
	static bool svgEnable;

	Fern();
	void setup(const FernStyle& style, float baseLength);
	void draw(ofxSVG& svg);
	void draw(float age, ofxSVG& svg);
	void draw(float age, ofxSVG& svg, ofPoint translation, ofPoint rotation);
};
