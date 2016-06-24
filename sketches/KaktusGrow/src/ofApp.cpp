#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    plants.setup(ofVec3f(ofGetWidth()/2, ofGetHeight(), 0));
    ofSetFrameRate(60);
}

//--------------------------------------------------------------
void ofApp::update(){
    plants.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    plants.drawGui();
    plants.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == ' ') {
        plants.addKaktus(ofVec3f(ofRandom(ofGetWidth()), ofGetHeight(), 0));
    }
    if (key == 'a') {
        plants.fadeKaktus();
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
