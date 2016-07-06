#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofBackground(0);
    plant.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
    ofVec2f mouse;
    mouse.set(mouseX, mouseY);
    static ofVec2f pMouse;
    velocity = mouse-pMouse;
    pMouse = mouse;
    plant.update(velocity);
//    ofLog() << velocity;
}

//--------------------------------------------------------------
void ofApp::draw(){
    plant.draw(mouseX, mouseY);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == ' ')  plant.randomize();
    if(key == '1')  plant.impulse(0);
    if(key == '2')  plant.impulse(1);
    if(key == '3')  plant.impulse(2);
    if(key == '4')  plant.impulse(3);
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
