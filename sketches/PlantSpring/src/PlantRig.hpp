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
    // pos, vel
    ofVec2f pos;
    
    // polylines
    ofPolyline mainBranchLine;
    vector<ofPolyline> childBranchLines;

    // points
    vector<ofVec2f> mainBranchPoints;
    vector<ofVec2f> mainBranchInitPoints;
    
    vector<vector<ofVec2f>> childBranchesPoints;
    vector<vector<ofVec2f>> childBranchesInitPoints;
    
    vector<vector<ofVec2f>> child2pts;
    vector<vector<ofVec2f>> child2Initpts;
    vector<int> child2links;
    
    // randoms
    vector<int> randomBools;
    vector<float> randomFloats;
    
    // settings
    struct BranchSettings{
        vector<ofVec2f> *points;
        ofVec2f pos;
        ofVec2f dir;
        float lengthMin;
        float lengthMax;
        int branchCount;
    };
    
    // mainbranch
    float mbLengthMin;
    float mbLengthMax;
    int mbCount;
    
    // childbranch
    float cbLengthMin;
    float cbLengthMax;
    int cbCount;
    
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
