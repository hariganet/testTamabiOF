#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetFrameRate(60);
    ofSetBackgroundAuto(false);
    
    quality = OF_IMAGE_QUALITY_WORST;
    
    reset();
    
}

void testApp::reset(){
    img.loadImage("neputa.jpg");
    img.resize(img.getWidth()/10, img.getHeight()/10);
    
}

//--------------------------------------------------------------
void testApp::update(){
    string compressedFilename = "compressed.jpg";
    
    img.saveImage(compressedFilename, quality);
    ofBuffer file = ofBufferFromFile(compressedFilename);
    int fileSize = file.size();
    
    char* buffer = file.getBinaryBuffer();
    int whichByte = static_cast<int>(ofRandom(fileSize));
    int whichBit = ofRandom(8);

    char bitMask = 1 << whichBit;
    buffer[whichByte] |= bitMask    ;
    
    ofBufferToFile(compressedFilename, file);
    img.loadImage(compressedFilename);
}

//--------------------------------------------------------------
void testApp::draw(){
    ofSetColor(255, 255, 255);
    
    img.draw(0, 0, ofGetWidth(), ofGetHeight());
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    reset();
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    
    if(x < 0 || x >= img.getWidth() || y < 0 || y >= img.getHeight()){
        return;
    }
    
    unsigned char* imgPixel = img.getPixels();
    int step = img.getWidth()*3;
    
    std::cout << "RGB(" << (int)imgPixel[y * step + x * 3 + 0]
    << "," << (int)imgPixel[y * step + x * 3 + 1]
    << "," << (int)imgPixel[y * step + x * 3 + 2] << ")" << std::endl;
    
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
