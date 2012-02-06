#include "testApp.h"
int w = 400;
int h = 300;

int x = 0;
int y = 0; 

int rw = 0;
int rh = 0;
int cx = 0;
int cy = 0;


int faceX = 0;
int faceY = 0;


extern "C" {
#include "macGlutfix.h"
}



//--------------------------------------------------------------
void testApp::setup(){

//	CGContextRef cgctx = NULL;
//	ofSetVerticalSync(true);
//    vidGrabber.setVerbose(true);
//    vidGrabber.initGrabber(w,h);
//    colorImg.allocate(w,h);
    
    
	ofSetFrameRate(30);
    
    
//    colorImgOf.allocate(w,h,OF_IMAGE_COLOR_ALPHA);
    
    tempFace.allocate(w,h,OF_IMAGE_COLOR);
    
    colorFace.allocate(w,h,OF_IMAGE_COLOR);
    
    
    fbo1.allocate(w, h, GL_RGBA);  
    fbo2.allocate(w, h, GL_RGBA);  
    
    
	bLearnBakground = true;

    haarFinder.setup("haarXML/haarcascade_frontalface_default.xml");


}




//--------------------------------------------------------------
void testApp::update(){
/*    
    bool bNewFrame = false;

    vidGrabber.grabFrame();
    bNewFrame = vidGrabber.isFrameNew();
	
	if (bNewFrame){
                colorImg.setFromPixels(vidGrabber.getPixels(), h,h);

    }
*/    

	
	unsigned char * data = pixelsBelowWindow(ofGetWindowPositionX(),ofGetWindowPositionY(),w,h);
	
    
    
    
	// now, let's get the R and B data swapped, so that it's all OK:
	for (int i = 0; i < w*h; i++){
        
		unsigned char r = data[i*4]; // mem A  
        
		data[i*4]   = data[i*4+1];   
		data[i*4+1] = data[i*4+2];   
		data[i*4+2] = data[i*4+3];   
		data[i*4+3] = r; 	
    }
    
        
    
    colorImgOf.setFromPixels(data, w, h, OF_IMAGE_COLOR_ALPHA);

    
////////remove alpha:
    
    
    unsigned char * rgba = colorImgOf.getPixels();   
    
    //total rgb pixels  
    int totalPixels = w * h * 3;  
    
    int counter = 0;  //for stepping through the the rgba image  
    
    for(int i = 0; i < totalPixels; i+= 3){  
        data[i]    = rgba[counter];  
        data[i+1] = rgba[counter+1];  
        data[i+2] = rgba[counter+2];  
        
        counter+=4; //go to the next pixel for the rgba array  
    }  
    

    
///////////    


        
    
    tempFace.setFromPixels(data, w, h, OF_IMAGE_COLOR);
    
    haarFinder.findHaarObjects(tempFace);
    
    int numFace = haarFinder.blobs.size();


	
	for(int i = 0; i < numFace; i++){
		 x = haarFinder.blobs[i].boundingRect.x;
		y = haarFinder.blobs[i].boundingRect.y;
		rw = haarFinder.blobs[i].boundingRect.width;
		 rh = haarFinder.blobs[i].boundingRect.height;

        
		 cx = haarFinder.blobs[i].centroid.x;
		 cy = haarFinder.blobs[i].centroid.y;
        
        
        
        colorFace.allocate(rw, rh, OF_IMAGE_COLOR);  
        leftFace.allocate(rw/2, rh, OF_IMAGE_COLOR);  
        rightFace.allocate(rw/2, rh, OF_IMAGE_COLOR);  

                   
        unsigned char face[ rw * rh * 3  ];  
        unsigned char  faceRight[ rw * rh * 3  ];  
        unsigned char  faceLeft[ rw * rh * 3  ];          
        for (int i = 0; i < rw/2-1; i++){  
            for (int j = 0; j < rh; j++){  

                
                int mainPixelPos = ((j + y) * w + (i + x)) * 3;  
                int subPixlPos = (j * (rw/2) + i) * 3;  
                
                faceLeft[subPixlPos] = data[mainPixelPos];   // R  
                faceLeft[subPixlPos + 1] = data[mainPixelPos + 1];  // G  
                faceLeft[subPixlPos + 2] = data[mainPixelPos + 2];  // B  
             

                    
                
            }
        }
    
        //colorFace.setFromPixels(faceLeft, rw, rh,  OF_IMAGE_COLOR);  
        leftFace.setFromPixels(faceLeft, rw/2, rh,  OF_IMAGE_COLOR);  
        
        
        
        for (int i = rw/2-1; i < rw; i++){  
            for (int j = 0; j < rh; j++){  
                
                
                int mainPixelPos = ((j + y) * w + (i + x)) * 3;  
                int subPixlPos = (j * round(rw/2)-1 + i) * 3;  
                
                faceRight[subPixlPos] = data[mainPixelPos];   // R  
                faceRight[subPixlPos + 1] = data[mainPixelPos + 1];  // G  
                faceRight[subPixlPos + 2] = data[mainPixelPos + 2];  // B  
                
                
                
                
                
            }
        }

        rightFace.setFromPixels(faceRight, rw/2, rh,  OF_IMAGE_COLOR);  

 
        
        for (int i = cx; i < rw; i++){  
            for (int j = cy; j < rh; j++){  
                
                
                int mainPixelPos = ((j + y) * w + (i + x)) * 3;  
                int subPixlPos = (j * rw + i) * 3;  
                
                face[subPixlPos] = data[mainPixelPos];   // R  
                face[subPixlPos + 1] = data[mainPixelPos + 1];  // G  
                face[subPixlPos + 2] = data[mainPixelPos + 2];  // B  
                
                
                
                
            }
        }

        colorFace.setFromPixels(face, rw, rh,  OF_IMAGE_COLOR);  

       
}
    
    
    
    
    
    
   }




//--------------------------------------------------------------
void testApp::draw(){
    
    
    ofSetHexColor(0xffffff);

    colorImgOf.draw(0,0);
    
    

        if (faceX > 10){
        colorFace.draw(x,y);
        }
//	ofSetColor(255,0,0);

    
//    ofSetColor(255,0,0);
//    ofSetColor(255,0,0);

    leftFace.draw(x-faceX,y+faceY);
//    ofSetColor(0,0,255);

        rightFace.draw(x+(rw/2-1)+faceX,y+faceY);

    
//    	ofSetColor(255,0,0);
	 /*  ofNoFill();
	ofSetColor(0x333333);
    for (int i = 0; i < haarFinder.blobs.size(); i++){
        haarFinder.blobs[i].draw(0,400);
    }
    */


	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    faceX+=1;
    //    faceY+=10;

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    faceX = 0;
    faceY = 0;
    
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}

