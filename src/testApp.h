#pragma once

#include "ofMain.h"

class testApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
	
		void keyPressed(int);
	
	void capture();
	string captureFilename(int);
	
	int deviceId;
	int captureId;
	ofVideoGrabber videoGrabber;
	ofImage captureImage;
	float previousCaptureTime;
	float captureInterval;
};
