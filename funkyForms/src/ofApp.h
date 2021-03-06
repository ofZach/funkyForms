#pragma once

#include "ofMain.h"
#include "appSettings.h"
#include "inputManager.h"
#include "sceneManager.h"
//#include "simpleScene.h"
#include "plantsScene.hpp"
#include "treeScene.h"
#include "TreeScene.h"
#include "MonsterScene.h"
#include "ofxSVG.h"
#include "renderManager.h"
#include "eyesScene.hpp"
#include "wavesScene.hpp"
//#include "simpleScene2.h"
//#include "costumeScene.h"
//#include "costumeScene2.h"
#include "paintScene.h"
//#include "buildingScene.h"
#include "ofxSyphon.h"
#include "light2dScene.h"
#include "particleScene.h"
//#include "box2dScene.h"
#include "tableScene.h"
#include "tableScene2.h"
#include "ofxDmx.h"
#include "tableScene3.h"

enum view {
    VIEW_DEBUG,
    VIEW_OVERVIEW,
    VIEW_LEFT,
    VIEW_RIGHT,
    VIEW_CENTER,
    VIEW_TOP
};




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
    void changeScene(int i);
    
        inputManager IM;
        sceneManager SM;
        renderManager RM;
    
    bool bDrawSmall;
    
        vector < string > viewNames;
        int currentView;
    
#ifdef USE_SYPHON
    ofxSyphonServer individualTextureSyphonServer;
#endif
    
    
        float sceneChangeTime;
        bool bInSceneChange;
        float startSceneChangeTime;
        bool bChanged;
        bool bNext;
        int whoToGoTo;
    
    
#ifdef USE_DMX
    float stageBrightness;
    float tableBrightness;
    ofxDmx dmx;
#endif
    
};
