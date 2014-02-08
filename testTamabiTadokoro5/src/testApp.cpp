#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    ofBackground(0, 0, 0);
    ofSetVerticalSync(true) ;
    ofSetFrameRate(60);
    //ofSetBackgroundAuto(false);
    pimg.loadImage("particle32.png");
    
    for(int i=0; i<200; ++i){
        particle myParticle;
        
        float x = 500 + 100 * cos((i/200.0) * TWO_PI);
        float y = 500 + 100 * sin((i/200.0) * TWO_PI);
        
        myParticle.setInitialCondition(x, y, 0, 0);
        particles.push_back(myParticle);
    }
    
    for(int i=0; i<particles.size(); ++i){
        spring mySpring;
        mySpring.distance = 4;
        mySpring.springiness = 0.2f;
        mySpring.particleA = &(particles[i]);
        mySpring.particleB = &(particles[(i+1)%particles.size()]);
        springs.push_back(mySpring);
    }
    
}

//--------------------------------------------------------------
void testApp::update(){
    for(int i=0; i<particles.size(); ++i){
        particles[i].resetForce();
    }

    for(int i=0; i<particles.size(); ++i){
        particles[i].addRepulsionForce(mouseX, mouseY, 200, 0.7f);
        
        for (int j = 0; j < i; j++){
			particles[i].addRepulsionForce(particles[j], 50, 0.1);
		}

        
    }
    
    
    for(int i=0; i<springs.size(); ++i){
        springs[i].update();
    }

    for(int i=0; i<particles.size(); ++i){
        particles[i].addDampingForce();
        particles[i].bounceOffWalls();
        particles[i].update();
    }
 
}

//--------------------------------------------------------------
void testApp::draw(){
    ofSetColor(127, 127, 127);
    for(int i=0; i<springs.size(); ++i){
        springs[i].draw();
    }
    
    ofSetColor(31, 127, 255);
    for(int i=0; i<particles.size(); ++i){
        particles[i].draw();
    }

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

    switch(key){
        case ' ':
        for(int i=0; i<particles.size(); ++i){
            particles[i].setInitialCondition(ofRandom(0, ofGetWidth()), ofGetWidth(), ofRandom(0, ofGetHeight()), 0);
        }
        break;
    }
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    particles[0].pos.set(mouseX, mouseY);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    particles[0].bFixed = true;
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    particles[0].bFixed = false;
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
