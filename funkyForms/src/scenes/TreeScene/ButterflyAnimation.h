#pragma once

#include "ofxSvg.h"
#include "ofxColor.h"       // old color thing

class ButterflyAnimation {
protected:
	static vector<ofxSVG> shapes;

	ofxSVG* shape;

	float lowerTheta, upperTheta;
	float pausingIntentionality, flappingIntentionality;

	float pausingRate, flappingRate;
	
	ofxColor color;
public:
	ofPoint position;
	float scale;
	float rot;
	
	static void addFile(string filename) {
		ofxSVG svg;
		svg.load(filename);
		shapes.push_back(svg);
	}

	ButterflyAnimation() {
		int i = (int) (ofRandom(0, shapes.size()));
		shape = &(shapes[i]);

		pausingRate = ofRandom(1, 2);
		flappingRate = ofRandom(5, 15);
		lowerTheta = -30;
		upperTheta = 60;
		pausingIntentionality = 3;
		flappingIntentionality = 1.5;
		scale = ofRandom(.1, .5);

		position.set(0, 0, 0);

		color = ofxColor(
			ofRandom(0, 255),
			255,
			255,
			128,
			OF_COLOR_HSV);
		rot = 90;
	}
	ButterflyAnimation(const ButterflyAnimation& from) {
		shape = from.shape;
		pausingRate = from.pausingRate;
		flappingRate = from.flappingRate;
		lowerTheta = from.lowerTheta;
		upperTheta = from.upperTheta;
		pausingIntentionality = from.pausingIntentionality;
		flappingIntentionality = from.flappingIntentionality;
		position = from.position;
		scale = from.scale;
		color = from.color;
	}
	void draw(float time) {
		float pausingState = tanh(sin(pausingRate * time * PI) * pausingIntentionality);
		float flappingState = tanh(sin(flappingRate * time * PI) * flappingIntentionality);
		float overallState = ofLerp(flappingState, 1, ofMap(pausingState, -1, 1, 0, 1));
		float theta = ofMap(overallState, -1, 1, lowerTheta, upperTheta);
		
		
		float sw = (shape->getWidth()*scale);
		float sh = -10;//((shape->getHeight()*scale));
		
        float w2 = shape->getWidth() / 2;
        float h2 = shape->getHeight() / 2;
        
		//shape->setAnchor(OF_ANCHOR_CENTER);
		ofPushMatrix();
		ofTranslate(position.x, position.y, 0);
		ofRotate(rot, 0, 0, 1);
		
		// 1
		ofPushMatrix();
		ofRotate(theta, 0, -1, 0);
		ofTranslate((sw/2), sh, 0);
        ofScale(scale, scale);
        ofTranslate(-w2, -h2);
        shape->draw();
        
        //shape->drawPlain(scale);
		ofPopMatrix();
		
		// 2
		ofPushMatrix();
		ofScale(-1, 1);
		ofRotate(theta, 0, -1, 0);
		ofTranslate((sw/2), sh, 0);
        ofScale(scale, scale);
        ofTranslate(-w2, -h2);
         shape->draw();
		//shape->drawPlain(scale);
		ofPopMatrix();
		
		
		ofPopMatrix();
		//shape->setAnchor(OF_ANCHOR_CORNER);

		return;
	
		
		
		
		//shape->setAnchor(OF_ANCHOR_CENTER);
		ofPushMatrix();
		ofTranslate(position.x+(sw/2), position.y, 0);
		ofRotate(rot, 0, 0, 1);
		ofPushStyle();
		ofEnableAlphaBlending();
		ofSetColor(color);
		ofFill();

		ofPushMatrix();
		ofScale(-1, 1);
		ofRotate(theta, 0, -1, 0);
        
        ofScale(scale, scale);
        
        shape->draw();
		ofPopMatrix();

		ofPushMatrix();
		ofRotate(theta, 0, -1, 0);
        ofScale(scale, scale);
        shape->draw(); //Plain(scale);
		ofPopMatrix();

		ofDisableAlphaBlending();
		ofPopStyle();

		ofPopMatrix();
		//shape->setAnchor(OF_ANCHOR_CORNER);
	}
};
