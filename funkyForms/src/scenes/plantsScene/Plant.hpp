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
#include "iColor.hpp"

class Plant{
public:
    
    // zach added
    bool bLeftSide;     // am I left side plant or a right side one
    bool bGrewUp;
    
    
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
    bool isFading = false;
    Animator fadeAnimator;
    Animator mbGrowAnimator;
    Animator cbGrowAnimator;
    Animator cb2GrowAnimator;
    vector<Animator> cbGrowAnimators;
    iColor icolor;
    
    // settings
    struct StrokeSettings{
        float min;
        float max;
        ofPolyline *centerLine;
        ofPolyline *line1;
        ofPolyline *line2;
    };
    ofVec2f pos;
    float mbWidth = 20;
    float cbWidth = 10;
    float scale = 1.0;
    vector<float> cbWidths;
    
    // color
    ofColor color;
    
    // timing, id 
    int id;
    int packetId;
    int pointLinkId;
    float timeOffset;
    int age = 0;
    int ageMax;
    bool isDead = false;
    int fadingCounter = 0;
    int fadingDelay = 200;
    
    // shadow
    ofImage shadow;
    float shadowRadius = 10;
    float shadowOpacity = 120;
    
    // set
    void setup();
    void setupChildBranches();
    void setupMeshRes();
    void setupAnimators();
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
    
    void fadeIn(){mbGrowAnimator.in();  bGrewUp = true;};
    void fadeOut(){isFading = true;};
    void updateAnimators();
    bool isFadeFinished() { return fadeAnimator.isFinished; }
    
    // draw
    void draw();
    void drawPolylines();
    void drawMeshes();
    void drawShadow();
};

#endif /* Plant_hpp */
