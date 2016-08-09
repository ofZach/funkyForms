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
    
    trackedContour();
    
    ofPoint midPt;
    ofPolyline prevFrame;
    ofPolyline resampleSmoothed;

    vector < ofPoint > velPts;
    
    void update( ofPolyline line);
    
    ofPoint velAvg;
    ofPoint velAvgSmooth;
    
    float smoothingRate;
    int resampleInternal;
    int resampleTarget;
    float velSmoothingRate;
    
    float startTime;
    
};