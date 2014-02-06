#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    ofBackground(0, 0, 0);
    
    ofSetVerticalSync(true) ;
    ofSetFrameRate(60);
    
    particle_a.setInitialCondition(400, 400, 0, 0);
    particle_b.setInitialCondition(500, 500, 0, 0);
    
    mySpring.distance = 100;
    mySpring.springiness = 0.1f;
    mySpring.particleA = &particle_a;
    mySpring.particleB = &particle_b;
}

//--------------------------------------------------------------
void testApp::update(){
    particle_a.resetForce();
    particle_b.resetForce();
    
    mySpring.update();
    
    particle_a.bounceOffWalls();
    particle_a.update();
    
    particle_b.bounceOffWalls();
    particle_b.update();
}

//--------------------------------------------------------------
void testApp::draw(){
    ofSetColor(255, 255, 255);
    
    mySpring.draw();
    
    particle_a.draw();
    particle_b.draw();

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
    particle_a.pos.set(mouseX, mouseY);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    particle_a.bFixed = true;
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    particle_a.bFixed = false;
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
