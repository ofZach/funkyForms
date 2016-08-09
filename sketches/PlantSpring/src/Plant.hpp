//
//  Plant.hpp
//  PlantSpring
//
//  Created by Zerc on 8/1/16.
//
//

#ifndef Plant_hpp
#define Plant_hpp

#include "ofMain.h"
#include "PlantRig.hpp"
#include "Animator.hpp"

class Plant{
public:
    // rig
    PlantRig rig;
    
    // Polylines
    ofPolyline mbLine, mbLine1, mbLine2;
    vector<ofPolyline> childLines1;
    vector<ofPolyline> childLines2;
    
    // meshes
    ofMesh mbMesh;
    vector<ofMesh> childMeshes;
    vector<ofMesh> childShadows;
    
    // fading
    Animator fadeAnimator;
    
    // settings
    struct StrokeSettings{
        float min;
        float max;
        ofPolyline *centerLine;
        ofPolyline *line1;
        ofPolyline *line2;
    };
    ofVec2f pos;
    float mbWidth;
    float cbWidth;
    float scale = 1.0;
    vector<float> cbWidths;
    
    // color
    ofColor color;
    
    // timing
    float timeOffset;
    int age = 0;
    int ageMax;
    bool isDead = false;
    
    // set
    void setup();
    void setupChildBranches();
    void setPos(ofVec2f _pos, float smooth){ rig.pos = rig.pos*smooth+ (1-smooth)*_pos;}
   
    // get
    ofVec2f getPos(){ return rig.pos; }
    
    bool isFadeOutFinished(){
        return fadeAnimator.isFinished;
    }
    
    // update
    void update();
    void updateAge();
    void updatePolylines();
    void updateMesh();
    void makeCorner(ofPolyline *line, ofPolyline &l, int i, float angle, float lenght);
    void makeStroke(int i, 
                    float min,
                    float max,
                    ofPolyline &centerLine,
                    ofPolyline *line1,
                    ofPolyline *line2
                    );
    
    void fadeIn(){fadeAnimator.in();};
    void fadeOut(){fadeAnimator.out();};
    void updateFade(){fadeAnimator.update();}
    bool isFadeFinished() { return fadeAnimator.isFinished; }
    
    // draw
    void draw();
    void drawPolylines();
    void drawMeshes();
};

#endif /* Plant_hpp */
