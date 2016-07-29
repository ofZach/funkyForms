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
    
    ofPoint midPt;
    ofPolyline prevFrame;
    ofPolyline resampleSmoothed;
    
    
    vector < ofPoint > velPts;
    
    void update( ofPolyline line);
    
    ofPoint velAvg;
    ofPoint velAvgSmooth;
    
};