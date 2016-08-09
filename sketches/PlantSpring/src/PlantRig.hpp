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
    
    // randoms
    vector<int> randomBools;
    vector<float> randomFloats;
    float timeOffset;
    
    // settings
    struct BranchSettings{
        vector<ofVec2f> *points;
        ofVec2f pos;
        ofVec2f dir;
        float lengthMin;
        float lengthMax;
        int branchCount;
    };
    float timeSpeed = 0.93;
    
    // mainbranch
    float mbLengthMin = 70;
    float mbLengthMax = 100;
    int mbCount = 6;
    
    // childbranch
    float cbLengthMin = 30;
    float cbLengthMax = 50;
    int cbCount = 3;
    
    void setup();
    void setupRandom();
    void makeMainBranch();
    void makeChildBranches();
    void makeChild2();
    void makeBranch(BranchSettings s);
    
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
