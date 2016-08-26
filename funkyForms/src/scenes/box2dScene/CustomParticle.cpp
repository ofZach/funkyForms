//
//  CustomParticle.cpp
//  funkyForms
//
//  Created by Qinzi Tan on 8/25/16.
//
//

#include "CustomParticle.hpp"
CustomParticle::CustomParticle() {
    
}


void CustomParticle::update(){
    
}


void CustomParticle::draw(float _scale, int _length){
    float radius = getRadius();
    
    glPushMatrix();
    glTranslatef(getPosition().x, getPosition().y, 0);
    
    ofSetColor(color.r, color.g, color.b);
    ofFill();
    
    ofPushStyle();
    ofScale(_scale,_scale,_scale);
    //    ofDrawBitmapString(myString, 0, 0);
    
    ofDrawCircle(0,0,_scale);
    ofPopStyle();
    glPopMatrix();
    
    drawTrail(_length);
    
}


void CustomParticle::drawTrail(int _length){
    
    trail.addVertex(getPosition());
    
    if (trail.getVertices().size() > _length) {
        for (int i = 0; i<trail.getVertices().size() - _length; i++) {
            trail.getVertices().erase(trail.getVertices().begin()+i);
        }
        
    }
    
    ofMesh mesh;
    mesh.setMode(OF_PRIMITIVE_LINES);
    
    for (int i = 0; i< trail.getVertices().size();i++) {
        mesh.addVertex(ofVec2f(trail.getVertices()[i].x,trail.getVertices()[i].y));
    }
    
    mesh.draw();
    
}

