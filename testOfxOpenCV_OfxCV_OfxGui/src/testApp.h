#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxGui.h"

class testApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    void resetBackgroundPressed();
    
    ofVideoGrabber cam;
    ofxCv::ContourFinder contourFinder;
    ofxCv::RunningBackground background;
    ofImage thresholded;
    
    ofxPanel gui;
    ofxFloatSlider bgThresh;    //背景差分のしきい値
    ofxFloatSlider contourThresh;   //輪郭抽出の閾値
    ofxButton resetBackgroundButton;    //背景リセットボタン
    
};
