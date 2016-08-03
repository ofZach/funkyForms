#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
//    plantrig.setup();
//    plant.setup();
    for (int i = 0; i < 1; i++) {
        Plant p;
        p.rig.mbCount = ofRandom(5, 6) ;
        p.rig.mbLengthMax = ofRandom(100, 300) ;
        p.rig.mbLengthMin = ofRandom(10, 100) ;
        p.rig.cbCount = ofRandom(3, 6) ;
        p.rig.cbLengthMax = ofRandom(50, 100) ;
        p.rig.cbLengthMin = ofRandom(10, 50) ;
        p.rig.pos = ofVec2f(ofRandomWidth(), ofGetHeight());
        if(i%2==0){
            p.color = ofColor::honeyDew;
        }else{
            p.color = ofColor::greenYellow;
        }
        p.setup();
        plants.push_back(p);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    for(auto &p: plants){
        p.update();
        p.rig.pos = ofVec2f(mouseX, mouseY);

    }
}

//--------------------------------------------------------------
void ofApp::draw(){
//    plantrig.draw();
//    plant.draw();
    for(auto &p: plants){
        p.draw();
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
