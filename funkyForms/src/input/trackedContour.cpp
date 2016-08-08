

#include "trackedContour.hpp"



trackedContour::trackedContour(){
    
    
    smoothingRate = 0.75;
    resampleInternal = 480;
    resampleTarget = 100;
    velSmoothingRate = 0.9;
    startTime = ofGetElapsedTimef();
}


void trackedContour::update(ofPolyline line){
    
    
    float contourLength = line.getPerimeter();
    //cout << contourLength << endl;
    
    ofPolyline resampled = line.getResampledByCount( resampleInternal);
    
    while(resampled.size() < resampleInternal){
        resampled.getVertices().push_back(resampled[resampled.size()-1]);
    }
    
    //resampled.draw();
    
    
    
    if (prevFrame.size() > 0){
        
        
        int smallestStart = -1;
        float smallestAvgLen = 100000000.0;
        
        for (int i = 0; i < resampleInternal; i++){
            
            float avgLen = 0;
            for (int j = 0; j < resampleInternal; j++){
                avgLen += (resampled[ (j + i ) % resampleInternal] - prevFrame[j]).length() / (float)resampleInternal;
            }
            if (avgLen < smallestAvgLen){
                smallestAvgLen = avgLen;
                smallestStart = i;
            }
            
        }
        
        ofPolyline temp;
        for (int i = 0; i < resampleInternal; i++){
            temp.addVertex( resampled[ (i + smallestStart) % resampleInternal]);
        }
        resampled = temp;

    
    }
    
    
    
    ofPolyline tempT = resampled.getResampledByCount(resampleTarget);
    
    while(tempT.size() < resampleTarget){
        tempT.getVertices().push_back(tempT[tempT.size()-1]);
    }
    // cout << tempT.size() << " " << resampleSmoothed.size() << endl;
    
    if (resampleSmoothed.size() == 0){
        resampleSmoothed = tempT;
        for (int i = 0; i < resampleSmoothed.size(); i++){
            
            velPts.push_back(ofPoint(0,0,0));
            
        }
    } else {
        for (int i = 0; i < resampleTarget; i++){
            ofPoint prev = resampleSmoothed[i] ;
            resampleSmoothed[i] = (smoothingRate) * resampleSmoothed[i] + (1-smoothingRate) * tempT[i];
            velPts[i] = (resampleSmoothed[i]  - prev) * ofMap(contourLength, 100, 1000, 1, 0.1, true);      // parametize?
        }
    }
    
    for (int i = 0; i < resampleTarget; i++){
        velAvg += velPts[i];
    }
    velAvg /= resampleTarget;
    velAvgSmooth = (velSmoothingRate) * velAvgSmooth + (1-velSmoothingRate) * velAvg;
    
    for (auto p : resampleSmoothed.getVertices()){
        
        unsigned int nearestIndex = 0;
        resampled.getClosestPoint(p, &nearestIndex);
   
    }
    

    
    prevFrame = resampled;
    
}