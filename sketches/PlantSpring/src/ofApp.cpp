#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    IM.setup();
    plantManager.setup();
    plantManager.setInputManager(&IM);
//    setupPlant();
}

void ofApp::setupPlant(){
    plant.setup();
    plant.setPos(ofVec2f(ofGetWidth()/2, ofGetHeight()), 0.5);
    plant.rig.dir = ofVec2f(0, -1);
    plant.rig.cbCount = ofRandom(3, 6) ;
    plant.rig.mbCount = ofRandom(5, 6) ;
    plant.rig.pos = ofVec2f(ofGetWidth()/2, ofGetHeight());
    plant.color = ofColor::red;
    plant.setup();
    plant.fadeIn();
}
//--------------------------------------------------------------
void ofApp::update(){
    IM.update();
    plantManager.update();
//    plant.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    plantManager.draw();
    IM.draw();
    ofSetColor(255);
//    plant.draw();
    ofDrawBitmapString(ofToString(ofGetFrameRate()), 20, 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
//    if(key == ' ')     randomizePlant();
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
