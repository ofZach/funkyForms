

#include "trackedContour.hpp"



void trackedContour::update(ofPolyline line){
    
    
    float contourLength = line.getPerimeter();
    //cout << contourLength << endl;
    
    ofPolyline resampled = line.getResampledByCount( sampleCount);
    
    while(resampled.size() < sampleCount){
        resampled.getVertices().push_back(resampled[resampled.size()-1]);
    }
    
    //resampled.draw();
    
    
    
    if (prevFrame.size() > 0){
        
        
        int smallestStart = -1;
        float smallestAvgLen = 10000000;
        
        for (int i = 0; i < sampleCount; i++){
            
            float avgLen = 0;
            for (int j = 0; j < sampleCount; j++){
                avgLen += (resampled[ (j + i ) % sampleCount] - prevFrame[j]).length() / sampleCount*1.0;
            }
            if (avgLen < smallestAvgLen){
                smallestAvgLen = avgLen;
                smallestStart = i;
            }
            
        }
        
        ofPolyline temp;
        for (int i = 0; i < sampleCount; i++){
            temp.addVertex( resampled[ (i + smallestStart) % sampleCount]);
        }
        resampled = temp;

    
    }
    
    
    
    ofPolyline tempT = resampled.getResampledByCount(resampleCount);
    
    while(tempT.size() < resampleCount){
        tempT.getVertices().push_back(tempT[tempT.size()-1]);
    }
    // cout << tempT.size() << " " << resampleSmoothed.size() << endl;
    
    if (resampleSmoothed.size() == 0){
        resampleSmoothed = tempT;
        for (int i = 0; i < resampleSmoothed.size(); i++){
            
            velPts.push_back(ofPoint(0,0,0));
            
        }
    } else {
        for (int i = 0; i < resampleCount; i++){
            ofPoint prev = resampleSmoothed[i] ;
            resampleSmoothed[i] = 0.75f * resampleSmoothed[i] + 0.25f * tempT[i];
            velPts[i] = (resampleSmoothed[i]  - prev) * ofMap(contourLength, resampleCount, 1000, 1, 0.1, true);
        }
    }
    
    for (int i = 0; i < resampleCount; i++){
        velAvg += velPts[i];
    }
    velAvg /= resampleCount;
    velAvgSmooth = 0.9* velAvgSmooth + 0.1 * velAvg;
    
    for (auto p : resampleSmoothed.getVertices()){
        
        unsigned int nearestIndex = 0;
        resampled.getClosestPoint(p, &nearestIndex);
   
    }
    

    
    prevFrame = resampled;
    
}