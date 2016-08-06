//
//  trackedContour.hpp
//  funkyForms
//
//  Created by zach on 7/29/16.
//
//

#pragma once

#include "ofMain.h"


class trackedContour {
    
public: 
    int sampleCount = 50;
    int resampleCount = 4;

    ofPoint midPt;
    ofPolyline prevFrame;
    ofPolyline resampleSmoothed;
    
    
    vector < ofPoint > velPts;
    
    void update( ofPolyline line);
    
    ofPoint velAvg;
    ofPoint velAvgSmooth;
    
};