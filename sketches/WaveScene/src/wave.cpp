//
//  wave.cpp
//  Wave
//
//  Created by Zerc on 6/21/16.
//
//

#include "wave.hpp"
void wave::setup(int _ypos, ofFloatColor _color, int _width){
    width = _width;
    color = _color;
    ypos = _ypos;
    
    fbo.allocate(100, 100);
    fbo.begin();
    fbo.end();

//            restLength.addListener(this, &wave::reload);
//            strength.addListener(this, &wave::reload);
//            invMass.addListener(this, &wave::reload);
//            amount.addListener(this, &wave::reload);
//    
//            gui.loadFromFile("settings.xml");
    setupSpring();
    m.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    strokeMesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
}
void wave::setupSpring(){
    points.clear();
    springs.clear();
    for (int i = 0; i < amount; i++) {
        Spring spring;
        spring.setup( strength, restLength, invMass);
        springs.push_back( spring );
        
        Point_ point;
        
        float step = width/(amount*1.0-1.0);
        
        ofVec2f pos(i*step , ypos);
        
        point.p = pos;
        point.pp = pos;
        if(i == 0 || i == amount-1 ){
            point.isFixed = true;
        }else{
            point.isFixed = false;
        }
        points.push_back(point);
    }
}
void wave::update(vector<inputManager::Target> &targets){
    
    float force2 = 1 - friction * timeStep * timeStep;
    
    for (int i = 0; i < points.size(); i++) {
        for(auto &t: targets ){
            if(t.pos.distance(points[i].p)<30){
                if (!points[i].isFixed) {
                    points[i].p.y += t.vel.normalize().y*force;
                }
            }
        }
        float dy = (points[i].p.y - points[i].pp.y) * force2;
        points[i].pp = points[i].p;
        points[i].p.y = MAX(points[i].p.y + dy, 0);
    }
    for (int i = 0; i < springs.size(); i++) {
        if(i>0){
            springs[i].update(&points[i-1], &points[i]);
        }
    }
    updatePolyline();
    updateMesh();
}
void wave::updatePolyline(){
    polyline.clear();
    for (int i = 0; i < points.size(); i++) {
        polyline.addVertex(points[i].p);
    }
}
void wave::updateMesh(){
    m.clear();
    strokeMesh.clear();
    
    for (int i = 0; i < polyline.getVertices().size(); i++) {
        ofVec2f p = polyline.getVertices()[i];
        ofVec2f p2 = ofVec2f(p.x, ofGetHeight());
        ofVec3f dir = polyline.getTangentAtIndex(i);
        float angle = atan2(dir.x, dir.y)*(180)/pi;
        ofColor col = color;
        int a = angle/2+col.getHueAngle()/2;
        col.setHueAngle(a%360);
        ofColor cc = baseColor;
        
        float pct = ofMap(p.y, ypos-ofGetMouseX(), ypos, 1, 0, true);
        
        col.r = pct * cc.r + (1-pct) * col.r;
        col.g = pct * cc.g + (1-pct) * col.g;
        col.b = pct * cc.b + (1-pct) * col.b;
        
        m.addVertex(points[i].p);
        m.addColor(ofFloatColor(col, 1));
        m.addVertex(p2);
        m.addColor(ofFloatColor(col, 1));

//        ofNode node;
//        ofNode child;
//        child.setParent(node);
//        child.setPosition(ofVec3f(0, ofMap(pct, 0, 1, 0, 20), 0));
//        
//        node.setPosition(p);
//        ofQuaternion q = ofQuaternion(0, ofVec3f(1, 0, 0), 0, ofVec3f(0, 1, 0), angle, ofVec3f(0, 0, 1));
//        node.setOrientation(q);
//
//        strokeMesh.addVertex(node.getGlobalPosition());
//        strokeMesh.addVertex(child.getGlobalPosition());
    }

}
void wave::draw(){
    m.draw();
    strokeMesh.draw();
}