#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofBackground(0, 0, 0);
    ofEnableBlendMode(OF_BLENDMODE_ADD);

    img.loadImage("particle32.png");
}

//--------------------------------------------------------------
void testApp::update(){
    for(int i=0; i<particles.size(); ++i){
        particles[i].resetForce();
        particles[i].addForce(0, 0.28);
        particles[i].addDampingForce();
		particles[i].bounceOffWalls();
        particles[i].update();
    }
    
    std::cout << particles.size() << std::endl;
}

//--------------------------------------------------------------
void testApp::draw(){

//    string message = "Current particle num = " + ofToString(particles.size(), 0);
//    ofDrawBitmapString(message, 20, 20);
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	ofSetColor(0, 0, 0, 31);
	ofRect(0, 0, ofGetWidth(), ofGetHeight());
	
	ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofSetColor(255, 255, 255);
    for(int i=0; i<particles.size(); ++i){
        img.draw(particles[i].pos.x - 16, particles[i].pos.y - 16);
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if(key == 'c'){
        particles.clear();
    }
    
    if(key == 'f'){
        ofToggleFullscreen();
    }
    

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    preMouse.x = x;
    preMouse.y = y;
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

    float dx = x - preMouse.x;
    float dy = y - preMouse.y;
    
    Particle myParticle;
    myParticle.setInitialCondition(x, y, dx*0.5, dy*0.5);
    particles.push_back(myParticle);

    preMouse.x = x;
    preMouse.y = y;
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    particles.clear();
    preMouse.x = x;
    preMouse.y = y;
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
