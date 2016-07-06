//
//  Block.cpp
//  Blocks
//
//  Created by Zerc on 7/6/16.
//
//

#include "Block.hpp"
void Block::setup(ofVec2f _pos){
    pos = _pos;
    for (int i = 0; i < 4; i++) {
        ofPolyline line;
        Face p;
        ofMesh m;
        p.line = line;
        p.mesh = m;
        p.color = colors[(int)ofRandom(10)];
        faces.push_back(p);
    }
    rectBackColor = colors[(int)ofRandom(10)];
    rectFrontColor = colors[(int)ofRandom(10)];
}
void Block::update(int x, int y){
    // calculate size
    ofVec2f pointer(x, y);
    float smooth = 0.9;
    float dist = pointer.distance(pos);
    if ( dist < 300 ) {
        rectDistance = smooth*rectDistance + (1-smooth)*dist;
    }else{
        rectDistance = smooth*rectDistance + (1-smooth)*300;
    }
    
    // setup rectangles
    rectFront.setPosition((pos-rectDistance));
    rectBack.setPosition(pos);
    
    rectFront.setWidth(rectFrontW);
    rectFront.setHeight(rectFrontH);
    rectBack.setWidth(rectFrontW);
    rectBack.setHeight(rectFrontH);
    
    // setup polylines
    for (int i = 0; i < faces.size(); i++) {
        faces[i].line.clear();
    }
    
    faces[0].line.lineTo(rectBack.getTopLeft());
    faces[0].line.lineTo(rectBack.getBottomLeft());
    faces[0].line.lineTo(rectFront.getBottomLeft());
    faces[0].line.lineTo(rectFront.getTopLeft());
    faces[0].line.close();
    faces[0].dir = ofVec2f(-1, 0);
    
    faces[1].line.lineTo(rectBack.getBottomLeft());
    faces[1].line.lineTo(rectBack.getBottomRight());
    faces[1].line.lineTo(rectFront.getBottomRight());
    faces[1].line.lineTo(rectFront.getBottomLeft());
    faces[1].line.close();
    faces[1].dir = ofVec2f(0, 1);

    faces[2].line.lineTo(rectBack.getTopLeft());
    faces[2].line.lineTo(rectBack.getTopRight());
    faces[2].line.lineTo(rectFront.getTopRight());
    faces[2].line.lineTo(rectFront.getTopLeft());
    faces[2].line.close();
    faces[2].dir = ofVec2f(0, -1);

    faces[3].line.lineTo(rectBack.getTopRight());
    faces[3].line.lineTo(rectBack.getBottomRight());
    faces[3].line.lineTo(rectFront.getBottomRight());
    faces[3].line.lineTo(rectFront.getTopRight());
    faces[3].line.close();
    faces[3].dir = ofVec2f(1, 0);
    
    // build mesh
    for(auto &face: faces){
        face.mesh.clear();
        face.mesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
        int i = 0;
        for (auto &point: face.line.getVertices()) {
            ofColor col = face.color;
            face.mesh.addVertex(point);
            if(i<2){
                col.setBrightness(255.0/(distance/5.0));
            }
            face.mesh.addColor(col);
            i++;
        }
    }
    
    // calculate distance
    distance = rectFront.getCenter().distance(rectBack.getCenter());
    ofLog() << distance;
}
void Block::draw(){
    ofVec2f curDir = rectFront.getCenter() - rectBack.getCenter();
    int i = 0;
    for(auto &face: faces){
        ofSetColor(colors[i]);
        float dot = curDir.dot(face.dir);
        if (dot < 0) {
            face.mesh.draw();
        }
        i++;
    }
    ofSetColor(colors[4]);
    ofDrawRectangle(rectFront);
    ofSetColor(colors[5]);
    ofDrawCircle(curDir, 20);
//    ofDrawRectangle(rectBack);
}