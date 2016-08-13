#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    
    
    ofRectangle bounds;
    

    
    SM.scenes.push_back(new simpleScene());
    SM.scenes.push_back(new plantsScene());
    SM.scenes.push_back(new TreeScene());
    SM.scenes.push_back(new MonsterScene());
    
    IM.setup();

    
    for (int i = 0; i < SM.scenes.size(); i++){
        SM.scenes[i]->cvData = &IM.CVM.packet;
        SM.scenes[i]->tracker = &IM.CVM.tracker;
        SM.scenes[i]->RM = &RM;
    }
    
    SM.setup();
    
    currentView = VIEW_DEBUG;
    
    RM.setup();
    
    IM.CVM.RM = &RM;
}

//--------------------------------------------------------------
void ofApp::update(){

    IM.update();
    
    //-----------------------------------------------------------
    // check for new or dead blobs;
        for (auto a : IM.CVM.bornThisFrame){
            SM.blobBorn(a);
        }
        
        for (auto a : IM.CVM.diedThisFrame){
            SM.blobDied(a);
        }
        IM.CVM.diedThisFrame.clear();
        IM.CVM.bornThisFrame.clear();
    
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
    ofClearAlpha();
    RM.fbo.end();

    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(0);
    
    if (currentView == VIEW_DEBUG){
        IM.draw();
    } else if (currentView == VIEW_OVERVIEW) {
        ofRectangle target(0,0,ofGetWidth(), ofGetHeight());
        ofRectangle src(0,0, RM.fbo.getWidth(), RM.fbo.getHeight());
        src.scaleTo(target);
        ofSetColor(255);
        RM.fbo.draw(src);
        ofNoFill();
        ofDrawRectangle(src);
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
    
    SM.drawGui();       // draw the gui outside of the RM
    
    
    ofDrawBitmapStringHighlight("current view " + ofToString(currentView) +  " : " + ofToString(ofGetFrameRate(),3), ofGetWidth()-400, 20);
    
      ofDrawBitmapStringHighlight("current scene " + SM.scenes[SM.currentScene]->sceneName, ofGetWidth()-400, 40);
    ofDrawBitmapStringHighlight("pressed right / left arrow to advance scene\ntop / bottom arrow to advance view", ofGetWidth()-400, 60);
    
    //RM.draw();
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
