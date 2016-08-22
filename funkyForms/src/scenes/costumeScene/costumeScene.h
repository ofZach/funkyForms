
#pragma once

#include "ofMain.h"
#include "baseScene.h"
#include "particle.h"
#include "trackedContour.hpp"
#include "spring3f.h"
#include "particle3f.h"



// I hold contour trackers for this scene
// and track them so we have stable points...


class springline {
    
public:
    
    vector < spring3f > springs;
    vector < particle3f * > particles;
    
    void setup( int count, ofPoint pos){
        
        
        
        for (int j = 0; j < count; j ++){
            
            
            
            particle3f * p = new particle3f();
            p->setInitialCondition(pos.x + ofRandom(-10,10), pos.y + ofRandom(-10,10), 0+ ofRandom(-10,10), 0,0,0);
            particles.push_back(p);
            if (j != 0){
                spring3f s;
                s.springiness = 0.50;
                s.distance = 1;
                s.particleA = particles[particles.size()-2];
                s.particleB = particles[particles.size()-1];
                springs.push_back(s);
            }
        }
    }
};

//bool comparisonFunction(  particle3f * a, particle3f * b ) {
//    return a->pos.x < b->pos.x;
//}


class trackedContourObj {

    public:
    
    int id;
    int packetId;
    trackedContour * TC;            // I need to be more manual about this since the copy contstructor of ofThread is smartly deleted :) 
    
    
    //------------------------ phsyics!
    vector < springline > springLines;
    vector < particle3f * > allParticles;
    
    void setup( ofPoint target){
        for (int i = 0; i < 100; i++){
            springline temp;
            temp.setup( ofRandom(10,18), target);
            springLines.push_back(temp);
            
            for (auto a : temp.particles){
                allParticles.push_back(a);
            }
            
        }
    }
    
    void update( ofPolyline & resampleSmoothed){
        
        
        
        //sort( allParticles.begin(), allParticles.end(), comparisonFunction );
        
        sort(allParticles.begin(), allParticles.end(),
             [](const particle3f * a, const particle3f * b) -> bool
             {
                 return a->pos.x < b->pos.x;
             });
        
        
        
        
        for (int i = 0; i < allParticles.size(); i++){
            allParticles[i]->resetForce();
            //allParticles[i]->addForce(0, 1.5 * sin(ofGetElapsedTimef()), 0);
        }
        
        
        ofPoint pt = resampleSmoothed.getCentroid2D();
        
        float mouseX = ofGetMouseX();
        float mouseY = ofGetMouseY();
        
//        for (int i = 0; i < allParticles.size(); i++){
//            
//            
//            for (int j = 0; j < i; j++){
//                allParticles[i]->addRepulsionForce(*allParticles[j], 0.4, 1.4);
//            }
//        }
//
        
        float ff = ofGetElapsedTimef();
        
        for (int i = 0; i < allParticles.size(); i++){
            for (int j = i-1; j >= 0; j--){
                if ( fabs(allParticles[j]->pos.x - allParticles[i]->pos.x) >	15) break;
                allParticles[i]->addRepulsionForce( *allParticles[j],15,1.1f);
            }
        }
        
        
        for (int i = 0; i < allParticles.size(); i++){
            if (resampleSmoothed.size() == 100){
                for (int j = 0; j < 100; j++){
                    //allParticles[i]->addRepulsionForce(resampleSmoothed[j].x, resampleSmoothed[j].y,0,20,1.1);
                }
            }
            allParticles[i]->addRepulsionForce(pt.x, pt.y,0,1000, 1 + 2 * sin(ff));
        }
        
        for (int i = 0; i < springLines.size(); i++){
            
            if (resampleSmoothed.size() == 100){
                springLines[i].particles[0]->bFixed = true;
                springLines[i].particles[0]->pos.set(resampleSmoothed[i].x, resampleSmoothed[i].y);
                
                springLines[i].particles[ springLines[i].particles.size()-1]->bFixed = true;
                springLines[i].particles[springLines[i].particles.size()-1]->pos.set(resampleSmoothed[ ((i + 1)) % 100 ].x, resampleSmoothed[((i + 1)) % 100].y);
                
            }
            
            for (auto a: springLines[i].springs){
                a.update();
            }
        }
        
        for (int i = 0; i < allParticles.size(); i++){
            allParticles[i]->addDampingForce();
            //allParticles[i]->pos.z = 0;
            allParticles[i]->update();
        }
    }
    
    void draw(float alpha){
        
        for (int i = 0; i < springLines.size(); i++){
            
            
            ofSetColor( 150 + 80 * sin(i), 150 + 80 * sin(i), 150 + 80 * sin(i), alpha*255);
            //ofMesh m;
            //m.setMode(OF_PRIMITIVE_LINE_STRIP);
            ofFill();
            ofBeginShape();
            for (int j = 0; j < springLines[i].springs.size(); j++){
                float pct = ofMap(j, 0, springLines[i].springs.size(), 255, 100);
                //cout << springLines[i].springs[j].particleA->pos << endl;
                //m.addVertex(springLines[i].springs[j].particleA->pos);
                //m.addColor( ofColor(255, 255, 255, pct));
                ofVertex(springLines[i].springs[j].particleA->pos.x, springLines[i].springs[j].particleA->pos.y);
                if (j == springLines[i].springs.size()-1){
                    ofVertex(springLines[i].springs[j].particleB->pos.x, springLines[i].springs[j].particleB->pos.y);
                }
            }
            
            ofEndShape();
            
            //m.draw();
            
            //        for (auto a: springLines[i].springs){
            //            
            //            a.draw();
            //        }
            
            
        }
        
        
    }
    
};

class costumeScene : public baseScene {
    
public:
    
    void setup();
    void update();
    void draw();
    
    void start();
    void stop();
    
    void blobBorn(int packetId, int id);
    void blobDied(int packetId, int id);
    
    vector < trackedContourObj > trackedObjects;
    
    
};


