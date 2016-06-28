#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofBackground(0);
    character.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
    float smooth = 0.9;
    ofVec2f m(mouseX, mouseY);
    ofVec2f dir = m - pMouse;
    
    velocity = smooth*velocity + (smooth-1)*dir.x;
    
    character.update();
    
    pMouse.set(mouseX, mouseY);
}

//--------------------------------------------------------------
void ofApp::draw(){
    character.draw(-velocity);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == ' '){
        character.attachShapes();
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
