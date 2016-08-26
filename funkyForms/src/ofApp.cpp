#include "ofApp.h"

#ifdef OVER_MAD_MAPPER
#include <Cocoa/Cocoa.h>
#endif

//--------------------------------------------------------------
void ofApp::setup(){

    
    RM.setup();
    
    bDrawSmall = false;
    
//    cout << "OpenCV version : " << CV_VERSION << endl;
//    cout << "Major version : " << CV_MAJOR_VERSION << endl;
//    cout << "Minor version : " << CV_MINOR_VERSION << endl;
//    cout << "Subminor version : " << CV_SUBMINOR_VERSION << endl;
//    
//    std::exit(0);
    
    
    viewNames = { "debug", "overview", "left", "right", "center", "top" };
    
    ofRectangle bounds;

    SM.scenes.push_back(new paintScene());
    SM.scenes.push_back(new particleScene());
    SM.scenes.push_back(new light2dScene());
    SM.scenes.push_back(new box2dScene());

    SM.scenes.push_back(new buildingScene());
    SM.scenes.push_back(new costumeScene2());
    SM.scenes.push_back(new TreeScene());
    SM.scenes.push_back(new plantsScene());
    SM.scenes.push_back(new simpleScene());
    SM.scenes.push_back(new simpleScene2());
    
    SM.scenes.push_back(new MonsterScene());
    SM.scenes.push_back(new eyesScene());
    SM.scenes.push_back(new wavesScene());

    IM.setup();
    
    IM.CVM[0].packet.RM = &RM;
    IM.CVM[1].packet.RM = &RM;

    for (int i = 0; i < SM.scenes.size(); i++){
        SM.scenes[i]->cvData[0] = &IM.CVM[0].packet;
        SM.scenes[i]->cvData[1] = &IM.CVM[1].packet;
        //SM.scenes[i]->cvData[0]
        SM.scenes[i]->RM = &RM;
    }
    
    SM.setup();
//    SM.currentScene = 2;
    
    currentView = VIEW_OVERVIEW;
    
    
    
    IM.CVM[0].RM = &RM;
    IM.CVM[1].RM = &RM;
    IM.CVM[0].packet.cacheRects();
    IM.CVM[1].packet.cacheRects();
    

    
#ifdef USE_SYPHON
    individualTextureSyphonServer.setName("funkyForms");
#endif

    
    
}

//--------------------------------------------------------------
void ofApp::update(){

    // this helps get us "ABOVE" mad mapper....
    // https://developer.apple.com/library/mac/documentation/Cocoa/Conceptual/WinPanel/Concepts/WindowLevel.html
    // maybe we can go small in the corner of the tower projection and have a
    // way to move back to a good monitor for adjusting preferences...
    
    
    #ifdef OVER_MAD_MAPPER
    if (ofGetFrameNum() % 100 == 0){
        NSWindow * window = (NSWindow *)ofGetCocoaWindow();
        if(window) {
            // make your obj-c calls here
            //[window setLevel:NSScreenSaverWindowLevel];
            [window setLevel:NSScreenSaverWindowLevel + ofGetFrameNum()];
        }
    }
    #endif
    
    
    IM.update();
    
    //-----------------------------------------------------------
    // check for new or dead blobs;
    for (int i = 0; i < 2; i++){
        for (auto a : IM.CVM[i].bornThisFrame){
            SM.blobBorn(i, a);
        }
        
        for (auto a : IM.CVM[i].diedThisFrame){
            SM.blobDied(i, a);
        }
    
        for (auto a : IM.CVM[i].movedThisFrame){
            SM.blobMoved(i, a);
        }
    
        IM.CVM[i].diedThisFrame.clear();
        IM.CVM[i].bornThisFrame.clear();
        IM.CVM[i].movedThisFrame.clear();
    }
    
    //-----------------------------------------------------------
    
    SM.update();
    
    // draw the current scene into the fbo
    // for now, draw boxes to help us see what's going on

    RM.fbo.begin();
    ofClear(0,0,0,255);
    SM.draw();
    ofNoFill();
    ofSetColor(255);
    ofDrawRectangle(RM.getRectForScreen(SCREEN_LEFT));
    ofDrawRectangle(RM.getRectForScreen(SCREEN_CENTER));
    ofDrawRectangle(RM.getRectForScreen(SCREEN_RIGHT));
    ofDrawRectangle(RM.getRectForScreen(SCREEN_TOP));
    
    float scale = RM.getWidth() / 2100.0; //(float)RM.windows.getWidth();
    
    ofPushMatrix();
    
    ofScale(scale, scale, 1.0);
    //RM.blocks.draw();
    RM.drawBuidling();
    
    ofPopMatrix();
    
    ofClearAlpha();
    RM.fbo.end();
    
    
#ifdef USE_SYPHON
    individualTextureSyphonServer.publishTexture(&(RM.fbo.getTexture()));
#endif
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(0);

    ofSetColor(255);
    ofDrawBitmapString(ofToString(ofGetFrameRate()), 20, 20);
    
    if (!bDrawSmall){
    if (currentView == VIEW_DEBUG){
        IM.draw();
    } else if (currentView == VIEW_OVERVIEW) {
        
      //  RM.fbo.draw(0,0);
        
        ofRectangle target(0,0,ofGetWidth(), ofGetHeight());
        ofRectangle src(0,0, RM.fbo.getWidth(), RM.fbo.getHeight());
        src.scaleTo(target);
        ofSetColor(255);
        RM.fbo.draw(src);
//        ofNoFill();
//        ofDrawRectangle(src);
    } else {
        ofRectangle target(0,0,ofGetWidth(), ofGetHeight());
        
        ofRectangle orig, dest;
        
        switch (currentView){
            case VIEW_LEFT:
                orig = RM.getRectForScreen(SCREEN_LEFT);
                dest = RM.getRectForScreen(SCREEN_LEFT);
                break;
            case VIEW_CENTER:
                orig = RM.getRectForScreen(SCREEN_CENTER);
                dest = RM.getRectForScreen(SCREEN_CENTER);
                break;
            case VIEW_RIGHT:
                orig = RM.getRectForScreen(SCREEN_RIGHT);
                dest = RM.getRectForScreen(SCREEN_RIGHT);
                break;
            case VIEW_TOP:
                orig = RM.getRectForScreen(SCREEN_TOP);
                dest = RM.getRectForScreen(SCREEN_TOP);
                break;
        }
       
        dest.scaleTo(target);
        dest.scaleFromCenter(0.9);
        float scale = dest.getWidth() / orig.getWidth();
        ofPoint offset = orig.getPosition();
        ofPoint push = ofPoint(target.width - dest.getWidth(), target.height-dest.getHeight())*0.5;
        
        ofSetColor(255);
        
        ofPushMatrix();
        ofTranslate(push.x, push.y);
        ofScale(scale, scale);
        RM.fbo.draw(-orig.x, -orig.y);
        ofPopMatrix();
        ofNoFill();
    } 
    }
    SM.drawGui();       // draw the gui outside of the RM
    
    
    
    ofDrawBitmapStringHighlight("current view " + viewNames[currentView] +  " : " + ofToString(ofGetFrameRate(),3), ofGetWidth()-400, 20);
    
      ofDrawBitmapStringHighlight("current scene " + SM.scenes[SM.currentScene]->sceneName, ofGetWidth()-400, 40);
    ofDrawBitmapStringHighlight("press right / left arrow to advance scene\ntop / bottom arrow to advance view", ofGetWidth()-400, 60);

    ofSetColor(255);
    ofDrawBitmapString(ofToString(ofGetFrameRate()), ofGetWidth()-50, 20);
    
   
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    
    if (key == OF_KEY_UP){
        currentView = currentView + 1;
        currentView %= (VIEW_TOP+1);
    } else if (key == OF_KEY_DOWN){
        currentView--;
        if (currentView < 0){
            currentView += (VIEW_TOP+1);
        }
    }
    
    if (key  == OF_KEY_RIGHT){
        SM.advanceScene();
    } else if (key == OF_KEY_LEFT){
        SM.reverseScene();
    }
    
    if (key == 'w'){
        ofSetWindowShape(200,200);
        bDrawSmall = true;
    } else if (key == 'W') {
        ofSetWindowShape(1920,1980);
        bDrawSmall = false;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
