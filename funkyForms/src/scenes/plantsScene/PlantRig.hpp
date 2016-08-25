//
//  PlantRig.hpp
//  PlantSpring
//
//  Created by Zerc on 8/1/16.
//
//

#ifndef PlantRig_hpp
#define PlantRig_hpp

#include "ofMain.h"
class PlantRig{
public:
    // pos, vel, direction
    ofVec2f pos;
    ofVec2f dir;
    int indexOffset = 1;
    
    // polylines
    ofPolyline mainBranchLine;
    vector<ofPolyline> childBranchLines;

    // points
    vector<ofVec2f> mainBranchPoints;
    vector<float> mainBranchPcts;
    vector<ofVec2f> mainBranchInitPoints;
    
    vector<vector<ofVec2f>> childBranchesPoints;
    vector<vector<ofVec2f>> childBranchesInitPoints;
    
    vector<vector<ofVec2f>> child2pts;
    vector<vector<ofVec2f>> child2Initpts;
    vector<int> child2links;
    
    float horizOffset = 1;
    float vertOffset = 1;
    float horizOffsetMain = 1;
    float vertOffsetMain = 1;
    
    // randoms
    vector<int> randomBools;
    vector<float> randomFloats;
    float timeOffset;
    
    // settings
    struct BranchSettings{
        vector<ofVec2f> *points;
        ofVec2f pos;
        ofVec2f dir;
        float width;
        float height;
        float lengthVariation;
        int branchCount;
    };
    float timeSpeed = 0.93;
    
    // mainbranch
    float mbWidth = 70;
    float mbHeight = 100;
    int mbCount = 6;
    
    // childbranch
    float cbWidth = 30;
    float cbHeight = 50;
    int cbCount = 3;
    
    float lengthVariation = 10;
    
    void setup();
    void setupRandom();
    void makeMainBranch();
    void makeChildBranches();
    void makeChild2();
    void makeBranch(BranchSettings s);
    
    // expand children length. val is multiply : length * horizOffset
    void expandHoriz(float val){ horizOffset = horizOffset * 0.9 + 0.1 * val;};
    void expandVert(float val){ vertOffset = vertOffset * 0.9 + 0.1 * val;};
    // expand main branch
    void expandHorizMain(float val){ horizOffsetMain = horizOffsetMain * 0.9 + 0.1 * val;};
    void expandVertMain(float val){ vertOffsetMain = vertOffsetMain * 0.9 + 0.1 * val;};
    
    void update();
    void updateMainBranch();
    void updateChildBranches();
    void updateChild2();
    void updateMBPolyline();
    void updateCBPolyline();
    void updateC2Polyline();

    
    void draw();
    void drawChildBranches();
    void drawMainBranch();
    void drawChild2();
};

#endif /* PlantRig_hpp */
