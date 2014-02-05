#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofBackground(0, 0, 0);

    img.loadImage("particle32.png");
}

//--------------------------------------------------------------
void testApp::update(){
    for(int i=0; i<particles.size(); ++i){
        particles[i].resetForce();
        //particles[i].addForce(0, 0.1);
        particles[i].addDampingForce();
        particles[i].update();
    }
    
    std::cout << particles.size() << std::endl;
    
    //enemyGroup.update();
    //enemyGroup.checkHit(p.pos.x, p.pos.y);
}

//--------------------------------------------------------------
void testApp::draw(){
    ofSetColor(255, 255, 255);

    string message = "Current particle num = " + ofToString(particles.size(), 0);
    ofDrawBitmapString(message, 20, 20);
    
    
//    ofNoFill();
//    ofBeginShape();
    for(int i=0; i<particles.size(); ++i){
        float posx = particles[i].pos.x - 16;
        float posy = particles[i].pos.y - 16;
        img.draw(posx, posy);
        
//        particles[i].draw();
//        ofCurveVertex(particles[i].pos.x, particles[i].pos.y);
    }
//    ofEndShape();
    
    
    //enemyGroup.draw();
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

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    Particle myParticle;
    myParticle.setInitialCondition(x, y, ofRandom(-3, 3), ofRandom(-3, 3));
    particles.push_back(myParticle);

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
