#include "ofApp.h"
using namespace ofxCv;

ofxFaceTracker::Gesture gestureIds[] = {
    ofxFaceTracker::MOUTH_WIDTH,
    ofxFaceTracker::MOUTH_HEIGHT,
    ofxFaceTracker::LEFT_EYEBROW_HEIGHT,
    ofxFaceTracker::RIGHT_EYEBROW_HEIGHT,
    ofxFaceTracker::LEFT_EYE_OPENNESS,
    ofxFaceTracker::RIGHT_EYE_OPENNESS,
    ofxFaceTracker::JAW_OPENNESS,
    ofxFaceTracker::NOSTRIL_FLARE
};

string gestureNames[] = {
    "mouthWidth",
    "mouthHeight",
    "leftEyebrowHeight",
    "rightEyebrowHeight",
    "leftEyeOpenness",
    "rightEyeOpenness",
    "jawOpenness",
    "nostrilFlare"
};

int gestureCount = 8;
//--------------------------------------------------------------
void ofApp::setup(){

    video.load("sampleMovie.mov");
//    video.play();
    tracker.setup();
    tracker.setRescale(.25);
    tracker.setIterations(100);
    tracker.setClamp(10);
    tracker.setTolerance(.5);
    tracker.setAttempts(4);
}

//--------------------------------------------------------------
void ofApp::update(){
    video.update();
    if(video.isFrameNew()) {
        tracker.update(toCv(video));
        trackedFrames.push_back(tracker.getImageMesh());
        vector<float> curGesture;
        for(int i = 0; i < gestureCount; i++) {
            curGesture.push_back(tracker.getGesture(gestureIds[i]));
        }
        trackedGestures.push_back(curGesture);
        video.nextFrame();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    float scale = ofGetWidth() / video.getWidth();
    ofScale(scale, scale);
    video.draw(0, 0);
    ofSetLineWidth(2);
    tracker.draw();
    ofDrawBitmapString(ofToString((int) ofGetFrameRate()), 10, 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == ' ') {
        ofFile out("data.json", ofFile::WriteOnly);
        out << "[";
        for(int i = 0; i < trackedFrames.size(); i++) {
            out << "{";
            for(int j = 0; j < gestureCount; j++) {
                out << gestureNames[j] << ":" << trackedGestures[i][j] << "," << endl;
            }
            out << "vertices: [";
            for(int j = 0; j < trackedFrames[i].getNumVertices(); j++) {
                out << "[" << ofVec2f(trackedFrames[i].getVertex(j)) << "]," << endl;
            }
            out << "]";
            out << "},";
        }
        out << "]";
    }
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

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
