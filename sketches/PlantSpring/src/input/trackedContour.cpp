

#include "trackedContour.hpp"



void trackedContour::update(ofPolyline line){
    
    
    float contourLength = line.getPerimeter();
    //cout << contourLength << endl;
    
    ofPolyline resampled = line.getResampledByCount( 480);
    
    while(resampled.size() < 480){
        resampled.getVertices().push_back(resampled[resampled.size()-1]);
    }
    
    //resampled.draw();
    
    
    
    if (prevFrame.size() > 0){
        
        
        int smallestStart = -1;
        float smallestAvgLen = 10000000;
        
        for (int i = 0; i < 480; i++){
            
            float avgLen = 0;
            for (int j = 0; j < 480; j++){
                avgLen += (resampled[ (j + i ) % 480] - prevFrame[j]).length() / 480.0;
            }
            if (avgLen < smallestAvgLen){
                smallestAvgLen = avgLen;
                smallestStart = i;
            }
            
        }
        
        ofPolyline temp;
        for (int i = 0; i < 480; i++){
            temp.addVertex( resampled[ (i + smallestStart) % 480]);
        }
        resampled = temp;

    
    }
    
    
    
    ofPolyline tempT = resampled.getResampledByCount(100);
    
    while(tempT.size() < 100){
        tempT.getVertices().push_back(tempT[tempT.size()-1]);
    }
    // cout << tempT.size() << " " << resampleSmoothed.size() << endl;
    
    if (resampleSmoothed.size() == 0){
        resampleSmoothed = tempT;
        for (int i = 0; i < resampleSmoothed.size(); i++){
            
            velPts.push_back(ofPoint(0,0,0));
            
        }
    } else {
        for (int i = 0; i < 100; i++){
            ofPoint prev = resampleSmoothed[i] ;
            resampleSmoothed[i] = 0.75f * resampleSmoothed[i] + 0.25f * tempT[i];
            velPts[i] = (resampleSmoothed[i]  - prev) * ofMap(contourLength, 100, 1000, 1, 0.1, true);
        }
    }
    
    for (int i = 0; i < 100; i++){
        velAvg += velPts[i];
    }
    velAvg /= 100;
    velAvgSmooth = 0.9* velAvgSmooth + 0.1 * velAvg;
    
    for (auto p : resampleSmoothed.getVertices()){
        
        unsigned int nearestIndex = 0;
        resampled.getClosestPoint(p, &nearestIndex);
   
    }
    

    
    prevFrame = resampled;
    
}