#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "trackedContour.hpp"


// testing the original blob tracker
#define USE_OLDER_BLOB_TRACKER


#ifdef USE_OLDER_BLOB_TRACKER
    #include "ofxOpenCv.h"
    #include "ofCvBlobTracker.h"
    #include "ofCvBlobListener.h"

#endif 


// todo:

// remap contours to target size
// (x) check another contour tracker (from original app)
// add new blob / end blob events
// gui
// (x) try watershed
// http://stackoverflow.com/questions/24798660/how-get-contours-between-objects-with-opencv-watershed


class cvBlob {
    
public:
    
    ofPolyline blob;
    int id;
    float age;

};

class cvPacket {
    
public:
    
    map < int, trackedContour > * trackedContours;      // access tracked contours by ID
    vector < int > idsThisFrame;                        // list of IDs
    map < int, int > idToBlobPos;                       // from ID, get position in this blob array
    vector < cvBlob > blobs;
    
    // todo:
    // vectors that sort horizontally, by age, by size, etc....
    
};




#ifdef USE_OLDER_BLOB_TRACKER
class cvManager : public ofCvBlobListener {
#else 
class cvManager {
#endif

public:
  
    void setup();
    void update(ofPixels & pixels);
    void draw();
    
    map < int, trackedContour > trackedContours;
    
    ofParameterGroup cvParams;

#ifdef USE_OLDER_BLOB_TRACKER
    
    ofxCvColorImage imgColor;
    ofxCvGrayscaleImage imgGray;
    ofxCvContourFinder finder;
    ofCvBlobTracker tracker;
    
    ofParameter <int> rejectDistanceThreshold;
    ofParameter <int> ghostFrames;
    ofParameter <float> minimumDisplacementThreshold;
    
    
    void blobOn( int x, int y, int bid, int order );
    void blobMoved( int x, int y, int bid, int order );
    void blobOff( int x, int y, int bid, int order );
    
#else 
    
    ofxCv::ContourFinder contourFinder;
    ofParameter <int> persistance;
    ofParameter <int> maximumDistance;
    
#endif
    
    // per frame, what happened with IDs.
    vector < int > bornThisFrame;
    vector < int > diedThisFrame;
    vector < int > existThisFrame;
    
    cvPacket packet;
    
};