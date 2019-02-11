#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    capture.init();
}

//--------------------------------------------------------------
void ofApp::update(){
    ofBackground(0, 0, 0);
    capture.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetHexColor(0xffffff);
    double timeFade = 1.0;
    while(!images.empty() && images.front()->getCaptureAgeSeconds() > timeFade)
    {
        delete images.front();
        images.pop_front();
    }

    ofEnableAlphaBlending();
    for(auto img : images) 
    {
        float alpha = 1.0 - img->getCaptureAgeSeconds()/timeFade;
        ofSetColor(255,255,255,alpha*255);
        img->draw(0,0,1280,720);
    }
    ofDisableAlphaBlending();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == ' ')
        images.push_back(capture.captureImage());
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

void ofApp::ofxAppPhaseWillBegin(ofxApp::Phase)
{
}

void ofApp::ofxAppContentIsReady(const std::string & contentID, vector<ContentObject*>)
{
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
