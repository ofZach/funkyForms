#pragma once

#include "Fern.h"
#include "ofxSVG.h"

class RandomFern {
public:
	static vector<ofxSVG> leaves;

	ofPoint pos;
	FernStyle style;
	Fern fern;
	ofxSVG * leaf;

	//ofxDisplayList mature;

	RandomFern() {
		leaf = NULL;
		randomize();
	}
	void addLeaf(string filename) {
		leaves.push_back(ofxSVG());
		leaves.back().load(filename);
	}
	void randomize() {
		style.trunkScaling = ofRandom(.91, .96);
		style.trunkAngle.set(
			ofRandom(1, 5),
			ofRandom(1, 3));
		style.trunkVariation.set(
			ofRandom(1, 3),
			ofRandom(1, 2));

		style.branchScaling = ofRandom(.3, .6);
		style.branchAngle.set(
			ofRandom(50, 120),
			ofRandom(-30, 30));
		style.branchVariation.set(
			ofRandom(3, 20),
			ofRandom(3, 5));

		style.minLength = ofRandom(3, 10);
		style.branchWidth = ofRandom(.2, .4);

		style.leafScale = ofRandom(3, 10);

		style.leftBranchAngle.set(1, 1);
		style.rightBranchAngle.set(-1, 1);
		style.leftTrunkAngle.set(1, 1);
		style.rightTrunkAngle.set(-1, 1);

		style.leafGrowth = 3;
		style.overallGrowth = .3;

		style.leafVariation.set(10, 10);

		fern.setup(style, ofRandom(20, 40));

		//mature.update();
	}
	void draw(float age) {
		if(leaf == NULL) {
			if(leaves.size() > 0)
				leaf = &(leaves[(int) ofRandom(0, leaves.size())]);
		} else {
//			if(age >= 1) {
//				if(!mature.draw()) {
//					mature.begin();
//					fern.draw(*leaf);
//					mature.end();
//				}
//			} else {
				fern.draw(age, *leaf);
//			}
		}
	}
};
