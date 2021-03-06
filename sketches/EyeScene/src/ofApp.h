#pragma once

#include "ofMain.h"
#include "EyeParticles.hpp"
#include "EyeLinker.hpp"
#include "ofxXmlSettings.h"
#include "Targets.hpp"
#include "EyePair.hpp"
#include "inputManager.h"


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    EyeParticles eyeParticles;
    EyeLinker eyeLinker;
    Targets targets;
    EyePair eyePair;
    
    inputManager IM;
    
    ofxXmlSettings settings;
    bool isRecord;
    int counter = 0;
    ofVec2f prevPos;
};

