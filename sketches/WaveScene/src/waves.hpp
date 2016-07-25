//
//  waves.hpp
//  Wave
//
//  Created by Zerc on 6/21/16.
//
//

#ifndef waves_hpp
#define waves_hpp

#include "ofMain.h"
#include "wave.hpp"
class waves{
public:
    vector<wave> waves;
    void setup(){
        int pos = ofGetHeight()-150;
        ofFloatColor colors[4] = {
            ofColor::lightGreen,
            ofColor::red,
            ofColor::mistyRose,
            ofColor::yellow
        };
        for (int i = 0; i < 4; i++) {
            pos += 10*i;
            addWave(pos, colors[i]);
        }
    }
    void addWave( int ypos, ofFloatColor col){
        wave wave;
        wave.setup(ypos, col);
        waves.push_back(wave);
    }
    void update(int x, int y){
        for (int i = 0; i < waves.size(); i++) {
            waves[i].update(x, y);
        }
    }
    void draw(){
        
        ofPolyline *line = &waves[0].polyline;
        int index  = 5;
        while (index < waves[0].amount) {
            ofVec2f p = line->getPointAtIndexInterpolated(index);
            ofVec3f dir = line->getTangentAtIndex(index);
            float angle = atan2(dir.x, dir.y)*(180)/pi;
            ofSetColor(ofColor::white);
            ofSetLineWidth(ofNoise(index/20.0)*5);
            ofNode node;
            ofNode child;
            child.setParent(node);
            child.setPosition(-ofNoise(index/2.)*300, 0, 0);

            node.setPosition(p);
            ofQuaternion q = ofQuaternion(0, ofVec3f(1, 0, 0), 0, ofVec3f(0, 1, 0), angle, ofVec3f(0, 0, 1));
            node.setOrientation(q);

            ofDrawLine(node.getGlobalPosition(), child.getGlobalPosition());
            ofDrawCircle(child.getGlobalPosition(), ofNoise(index/20.0)*10);

            index += 5;
        }
//        for (int i = 0; i < line->getVertices().size(); i++) {
//            ofVec2f p = line->getVertices()[i];
//            int index  = 5;
//            while (index < waves[0].amount) {
//                if(i==index){
//                }
//                index += ofNoise(i/6.0)*4;
//            }
//        }
        for (int i = 0; i < waves.size(); i++) {
            waves[i].draw();
            int index  = 5;
            ofPolyline *line = &waves[i].polyline;
            
            while (index < waves[0].amount) {
                ofVec2f p = line->getPointAtIndexInterpolated(index);
                ofVec3f dir = line->getTangentAtIndex(index);
                float angle = atan2(dir.x, dir.y)*(180)/pi;
                ofNode node;
                ofNode child;
                child.setParent(node);
                child.setPosition(-ofNoise(index/2.)*300, 0, 0);
                
                node.setPosition(p);
                ofQuaternion q = ofQuaternion(0, ofVec3f(1, 0, 0), 0, ofVec3f(0, 1, 0), angle, ofVec3f(0, 0, 1));
                node.setOrientation(q);
                
                ofSetLineWidth(ofNoise(index/20.0)*5);
                ofSetColor(ofColor::gray);
                ofVec2f pos = node.getGlobalPosition()+ofVec2f(0, cos(ofGetElapsedTimef()*i)*40+100);
                float size = ofNoise(index/2.)*100;
                if(i!=waves.size()-1)
                    ofDrawCircle(pos, size);
                
                index += ofNoise((i*index)/20.01)*60;
            }
        }
        
        
    }
    void addPointsToMesh(ofMesh *m, ofNode l, ofNode r, int i){
        ofFloatColor col = ofColor::white;
        
        float mix = cos(i*3);
        ofFloatColor temp = ofColor::lightGreen;
        ofFloatColor temp2 = ofColor::darkMagenta;
        
        m->addVertex(l.getGlobalPosition());
        m->addColor(col);
        m->addVertex(r.getGlobalPosition());
        
        m->addColor(col);
    }
};

#endif /* waves_hpp */
