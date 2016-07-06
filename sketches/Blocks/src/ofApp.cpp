#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    int step = 200;
    for (int y = 0; y < ofGetHeight()+step; y+= step) {
        for (int x = 0; x < ofGetWidth()+step; x+=step) {
            
            Block block;
            
            y % 3 == 0 ? block.isLeft = true : block.isLeft = false;
            block.maxDist = ofRandom(300, 300);
            block.setup(ofVec2f(x, y), ofRandom(10, 200), ofRandom(10, 200));
            blocks.push_back(block);
        }
    }
    ofBackground(0);
    ofSetFrameRate(60);
}

//--------------------------------------------------------------
void ofApp::update(){
//    ofVec2f down(0, -1);
//    ofVec2f m(mouseX, mouseY);
//    ofLog() << m.dot(down);
    for(auto &block: blocks){
        block.update(mouseX, mouseY);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    for(auto &block: blocks){
        block.draw();
    }
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
