#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    block.setup(ofVec2f(500, 500));
    ofBackground(0);
    ofSetFrameRate(60);
}

//--------------------------------------------------------------
void ofApp::update(){
//    ofVec2f down(0, -1);
//    ofVec2f m(mouseX, mouseY);
//    ofLog() << m.dot(down);
    block.update(mouseX, mouseY);
}

//--------------------------------------------------------------
void ofApp::draw(){
    block.draw();
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
