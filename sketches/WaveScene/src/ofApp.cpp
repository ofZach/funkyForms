#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofSetFrameRate(60);
    waveManager.setup();
    inputManager.setup();

    stencilWaves.setup();
    stencilWaves.setInputManager(&inputManager);
//    inputManager.setInputToMouse();
    waveManager.setInputManager(&inputManager);
}

//--------------------------------------------------------------
void ofApp::update(){
    inputManager.update();
//    stencilWaves.update();
    waveManager.update(mouseX, mouseY);

    ofVec2f mPos(mouseX, mouseY);
    ofVec2f vel = mPos - mPosPrev;
//    inputManager.setMouse(mPos, vel.normalize());
    mPosPrev.set(mouseX, mouseY);
}

//--------------------------------------------------------------
void ofApp::draw(){
//    waveManager.draw();
//    inputManager.draw();
//    stencilWaves.draw();
    
    waveManager.drawSpikes();
    ofDrawBitmapString(ofToString(ofGetFrameRate()), ofGetWidth()-50, 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
