#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxCvHaarFinder.h"


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
        unsigned char * grab(int x, int y, int w, int h);
    
    
    
    ofVideoGrabber 		vidGrabber;
    
    ofxCvColorImage colorImg;
    ofImage			colorImgOf;

    ofImage			colorFace;
    ofImage			tempFace;
    ofImage			rectFace;

    ofFbo fbo1, fbo2;
    
    
    
    
    ofImage			leftFace;
    ofImage			rightFace;
    
    ofxCvGrayscaleImage 	grayImage;
    ofxCvGrayscaleImage 	grayBg;
    ofxCvGrayscaleImage 	grayDiff;
    
    ofxCvContourFinder 	contourFinder;
    ofxCvHaarFinder			haarFinder;

    
    int 				threshold;
    bool				bLearnBakground;

    
    unsigned int 	*pix;
    unsigned int 	*pixelz;

    unsigned char 	* colorPixelsLeft;
    
    unsigned char 	* colorPixelsRight;
    
    

};

#endif
