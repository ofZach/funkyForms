#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    svg1.load("gordon.svg");
    svg2.load("monkey.svg");
    ofEnableSmoothing();
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    svg1.draw();
    svg2.draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

    if(key=='s'){
        svg1.save("svg1_"+ofToString(ofGetTimestampString())+".svg");
        svg2.save("svg2_"+ofToString(ofGetTimestampString())+".svg");

    }
    
    if(key=='m'){
    
    /*
     Group all svgs together and save out without modifying originals
     */
    ofxSVGRef totSVG(new ofxSVG());
    
    
    
    totSVG->merge(svg1);
    totSVG->merge(svg2);
    
    // totSVG->setViewbox(0,0,camWidth, camHeight);
    // totSVG->setSize(camWidth, camHeight);
    totSVG->setViewbox(0,0,400,300);
    
    totSVG->save("Merged_"+ofToString(ofGetTimestampString())+".svg");
    totSVG.reset();

    
    }
    
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    float sx = (float)x/(float)ofGetWidth();
    float sy = (float)y/(float)ofGetHeight();
    
    ofColor col;
    col.set(sx*255,255-sx*255,255*sy);
    svg1.setFillColor(col,2);
    
    col.invert();
    svg2.setStrokeColor(col);
    
    svg2.setStrokeWidth(sy*5);
}
//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}