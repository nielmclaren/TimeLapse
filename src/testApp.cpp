#include "testApp.h"

void testApp::setup() {
	deviceId = 0;
	captureId = 0;
	
	// Increment by 1000 until we find a good filename.
	ofFile file;
	file.open(captureFilename(captureId));
	while (file.exists()) {
		captureId += 1000;
		file.open(captureFilename(captureId));
	}

	videoGrabber.setVerbose(true);
	videoGrabber.setDeviceID(deviceId);
	videoGrabber.initGrabber(640, 480);

	captureInterval = 60 * 1000;
	previousCaptureTime = ofGetSystemTime();
}

void testApp::update() {
	videoGrabber.update();
	if (videoGrabber.isFrameNew()) {
		if (ofGetSystemTime() - previousCaptureTime > captureInterval) {
			capture();
		}
	}
}

void testApp::draw() {
	ofBackground(0);
	videoGrabber.draw(0, 0);
}

void testApp::capture() {
	cout << "Capturing image " << captureId << "." << endl;
	captureImage.setFromPixels(videoGrabber.getPixels(), videoGrabber.width, videoGrabber.height, OF_IMAGE_COLOR);
	captureImage.saveImage(captureFilename(captureId++));
	previousCaptureTime = ofGetSystemTime();
}

string testApp::captureFilename(int id) {
	char str[16];
	sprintf(str, "capture%04i.jpg", captureId);
	return str;
}

void testApp::keyPressed(int key) {	
	switch (key) {
		case ' ':
			capture();
			break;
		case 'j':
			deviceId--;
			
			videoGrabber.setDeviceID(deviceId);
			videoGrabber.initGrabber(640, 480);
			break;
			
		case 'k':
			deviceId++;
			
			videoGrabber.setDeviceID(deviceId);
			videoGrabber.initGrabber(640, 480);
			break;
	}
}
