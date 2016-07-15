#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    eyeManager.setup();
    eyeLinker.setup();
    eyeManager.setTargets(&targets.targets);
    targets.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
    ofVec2f m(mouseX, mouseY);
    ofVec2f vel = m - prevPos;
    prevPos = m;
    
    targets.update();
    eyeLinker.setVel(vel);
    
    eyeLinker.update(ofVec2f(mouseX, mouseY));
    eyeManager.update(mouseX, mouseY);
}

//--------------------------------------------------------------
void ofApp::draw(){
//    targets.draw();
//    eyeManager.draw();
    eyeLinker.draw();
    
    ofSetColor(255);
    ofDrawBitmapString(ofToString(ofGetFrameRate()), ofGetWidth()-50, 20);

    if(isRecord){
        settings.addTag("pos");
        settings.pushTag("pos", counter);
        settings.addValue("x", mouseX);
        settings.addValue("y", mouseY);
        settings.popTag();
        counter++;
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == '1'){
        settings.addTag("data");
        settings.pushTag("data");
        isRecord = true;
    }
    if(key == '2'){
        settings.popTag();
        settings.saveFile("data.xml");
        isRecord = false;
    }
    if(key == 'w'){
        eyeManager.setBehavior(EyeManager::B_WAIT);
    }
    if(key == 'a'){
        eyeManager.setBehavior(EyeManager::B_ATTACK);
    }
    if(key == 'r'){
        eyeManager.setBehavior(EyeManager::B_RANDOM);
    }
    if(key == 'o'){
        eyeManager.open();
    }
    if(key == 'c'){
        eyeManager.close();
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
