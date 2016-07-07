#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    cam.enableOrtho();
    light.setDiffuseColor(ofColor::green);
    light.setSpecularColor(ofColor::white);
    ofBackground(0);
//    light.setup();
//    int hMax = 10;
//    int wMax = 20;
    int row = 20;
    int column = 20;
    int stepX = ofGetWidth()/row;
    int stepY = ofGetHeight()/column;
    
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            int x = i*stepX;
            int y = j*stepY;
            Block block;
            float size = 100;
            block.maxDist = ofRandom(20,100);
            block.maxRadius = 300;
//            block.lightRadius = ofRandom(100, 600);
            block.setup(ofVec2f(x, y), ofRandom(0.3, 0.8) * stepX, ofRandom(0.3, 0.8) * stepY);
            
            if(j%(int)ofRandom(1, 5) == 0){
                block.direction = Block::RIGHT;
            }
            if(j%(int)ofRandom(1, 5) == 0){
                block.direction = Block::TOPRIGHT;
            }
            if(j%(int)ofRandom(1, 5) == 0){
                block.direction = Block::LEFT;
            }
            if(j%(int)ofRandom(1, 5) == 0){
                block.direction = Block::TOPLEFT;
            }
            blocks.push_back(block);
        }
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    cam.setPosition(ofGetWidth()/2, ofGetHeight()/2, 2000);
    for(auto &block: blocks){
        block.update(mouseX, ofGetHeight()-mouseY);
    }
    light.setPosition(mouseX, ofGetHeight()-mouseY, 300);
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();
    ofEnableDepthTest();
    for(auto &block: blocks){
        block.draw();
    }
    ofDisableDepthTest();
    cam.end();
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
