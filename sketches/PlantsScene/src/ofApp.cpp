#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofBackground(0);
    inputManager.setup();
    plantManager.setup(&inputManager);
//    plant.setup();
    plant.setPosition(ofVec2f(300, ofGetHeight()));
}

//--------------------------------------------------------------
void ofApp::update(){
    inputManager.update();
    plantManager.update();
    plant.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    inputManager.draw();
    plantManager.draw();
    plant.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    plant.impulse(0);
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
