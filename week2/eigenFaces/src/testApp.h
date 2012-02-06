//////////////////////////////////////////////////////////////////////////////////////
// OnlineFaceRec.cpp, by Shervin Emami (www.shervinemami.info) on 30th Dec 2011.
// Online Face Recognition from a camera using Eigenfaces.
//////////////////////////////////////////////////////////////////////////////////////
//
// Some parts are based on the code example by Robin Hewitt (2007) at:
// "http://www.cognotics.com/opencv/servo_2007_series/part_5/index.html"
//
// Command-line Usage (for offline mode, without a webcam):
//
// First, you need some face images. I used the ORL face database.
// You can download it for free at
//    www.cl.cam.ac.uk/research/dtg/attarchive/facedatabase.html
//
// List the training and test face images you want to use in the
// input files train.txt and test.txt. (Example input files are provided
// in the download.) To use these input files exactly as provided, unzip
// the ORL face database, and place train.txt, test.txt, and eigenface.exe
// at the root of the unzipped database.
//
// To run the learning phase of eigenface, enter in the command prompt:
//    OnlineFaceRec train <train_file>
// To run the recognition phase, enter:
//    OnlineFaceRec test <test_file>
// To run online recognition from a camera, enter:
//    OnlineFaceRec
//
//////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>

#include <stdio.h>		// For getchar() on Linux
#include <termios.h>	// For kbhit() on Linux
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>	// For mkdir(path, options) on Linux

#include <vector>
#include <string>

// #include "cvaux.h"
#include "highgui.h"

#ifndef BOOL
#define BOOL bool
#endif


#include "ofMain.h"
#include "ofxOpenCv.h"
#include "eigenObjects.h"


#pragma once

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
        int captureWidth;
        int captureHeight;
    
    ofxCvGrayscaleImage grayImg;
    ofxCvColorImage colorImg;
    ofVideoGrabber 		vidGrabber;
    
    ofxCvColorImage colorImg2;

    IplImage *camImg;

    
    ofTrueTypeFont	myFont;
    
    
    char eventString[255];

    
    int w ;
    int h ;
    
    
    
    
    
    

};
