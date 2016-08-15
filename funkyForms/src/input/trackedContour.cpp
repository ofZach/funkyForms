

#include "trackedContour.hpp"



trackedContour::trackedContour(){
    smoothingRate = 0.75;
    resampleInternal = 480;
    resampleTarget = 100;
    velSmoothingRate = 0.9;
    startTime = ofGetElapsedTimef();
    startThread();
}



  
trackedContour::~trackedContour(){
    // when the class is destroyed
    // close both channels and wait for
    // the thread to finish
    toAnalyze.close();
    analyzed.close();
    waitForThread(true);
}


void trackedContour::update(){
    // check if there's a new analyzed frame and upload
    // it to the texture. we use a while loop to drop any
    // extra frame in case the main thread is slower than
    // the analysis
    // tryReceive doesn't reallocate or make any copies
    newFrame = false;
    while(analyzed.tryReceive(data)){
        newFrame = true;
    }
    if(newFrame){
        // ;
    }
}

void trackedContour::analyze(ofPolyline line){
    toAnalyze.send(line);
}


void trackedContour::threadedFunction(){
    
    ofPolyline line;
    trackedData dataToSend;
    while(toAnalyze.receive(line)){

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
        // cout << tempT.size() << " " << dataToSend.resampleSmoothed.size() << endl;
        
        if (dataToSend.resampleSmoothed.size() == 0){
            dataToSend.resampleSmoothed = tempT;
            for (int i = 0; i < dataToSend.resampleSmoothed.size(); i++){
                
                dataToSend.velPts.push_back(ofPoint(0,0,0));
                
            }
        } else {
            for (int i = 0; i < resampleTarget; i++){
                ofPoint prev = dataToSend.resampleSmoothed[i] ;
                dataToSend.resampleSmoothed[i] = (smoothingRate) * dataToSend.resampleSmoothed[i] + (1-smoothingRate) * tempT[i];
                dataToSend.velPts[i] = (dataToSend.resampleSmoothed[i]  - prev) * ofMap(contourLength, 100, 1000, 1, 0.1, true);      // parametize?
            }
        }
        
        for (int i = 0; i < resampleTarget; i++){
            velAvg += dataToSend.velPts[i];
        }
        velAvg /= resampleTarget;
        velAvgSmooth = (velSmoothingRate) * velAvgSmooth + (1-velSmoothingRate) * velAvg;
        
        for (auto p : dataToSend.resampleSmoothed.getVertices()){
            
            unsigned int nearestIndex = 0;
            resampled.getClosestPoint(p, &nearestIndex);
       
        }
        

        
        prevFrame = resampled;
        
#if __cplusplus>=201103
        analyzed.send(std::move(dataToSend));
#else
        analyzed.send(dataToSend);
#endif
    }
    
}