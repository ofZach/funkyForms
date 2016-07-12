#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    icolor.setup(1, ofColor::lightBlue);
    cam.enableOrtho();
    light.setDiffuseColor(ofColor::green);
    light.setSpecularColor(ofColor::white);
    ofBackground(0);
//    light.setup();
//    int hMax = 10;
//    int wMax = 20;
    int row = 10;
    int column = 10;
    int stepX = ofGetWidth()/row;
    int stepY = ofGetHeight()/column;
    
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            int x = i*stepX;
            int y = j*stepY;
            Block block;
            float size = 100;
            block.maxDist = ofRandom(100,400);
            block.maxRadius = 200;
            float width = ofRandom(30,70);
            float height = ofRandom(30,70);
            
            block.setup(ofVec2f(x+ofRandom(5), y+ofRandom(5)), width, height);
//            block.direction = Block::TOPRIGHT ;
            j % 2 == 0 ? block.direction = Block::TOPRIGHT :  block.direction = Block::TOPLEFT;
 
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
    ofDrawBitmapString(ofToString(ofGetFrameRate()), 30, 30);
    icolor.update();
    
//    icolor.draw();
//    ofMesh mesh;
//    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
//    for (int i = 0; i < 50; i++) {
//        ofVec2f t(5*i, 0);
//        ofVec2f b(5*i, 20);
//        mesh.addVertex(t);
//        ofColor col(icolor.getColorAt(i));
//        mesh.addColor(col);
//        mesh.addVertex(b);
//        mesh.addColor(col);
//    }
//    mesh.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key == ' ') icolor.grow();
    if (key == 'c') icolor.colapse();
    if(key == '1'){
        for(auto &block: blocks){
            block.isCrazy ^= true;
        }
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
