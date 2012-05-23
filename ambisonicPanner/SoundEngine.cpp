/*
 *  SoundEngine.cpp
 *
 *  Created by Ken Willes, Michael Reynolds, Ben Norskov
 *  Copyright 2010 Southern Adventist University. All rights reserved.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

 *
 */

#include "SoundEngine.h"

SoundEngine::SoundEngine(){

	// setup background color
	color.setColor("cool gray");
	ofBackground(color.getR(), color.getG(), color.getB());
	ofSetFrameRate(20);

	// emitters
	ofSetDataPathRoot("./data/");
	composite_emitters = new CompositeEmitters(MAX_EMITTERS);
	selected_emitter_id = 0;

	// load xml settings for speakers
	speakers = new Speaker[SPEAKER_COUNT];
	loadXml(speakers);

	// setup osc communication -- 5010 is a port number. has to match pc port number sender(ip, port)
	osc_from_pc.setup(5010);

	///////////////////////////////////////////////////////////////
	// Sound setup

	int outputs		= 8;
	int inputs		= 0;
	int sample_rate = 44100;
	int buffer_size = 256;
	int num_buffers = 4;

	ofSoundStreamSetup(outputs,inputs,this,sample_rate,buffer_size, num_buffers);
	pause_enabled = false;

	ofSetWindowTitle("Interactive Wall Sound Panner");
	global_volume = .3;
	setGlobalVolume(.3);


}

SoundEngine::~SoundEngine(){

	composite_emitters->stopAllEmitters();

	ofSleepMillis(1000);
	ofSoundStreamClose(); // does same thing as ofSoundStreamStop?

	ofSleepMillis(1000);
	saveXml(speakers);

	ofSleepMillis(1000);

	///////////////////////////////////
	delete [] speakers;
	speakers = 0;

	delete composite_emitters;
	composite_emitters = 0;

}

void SoundEngine::audioRequested(float * output, int bufferSize, int nChannels){

	for(int i=0; i<bufferSize; i++){
		output[i*nChannels	  ] = speakers[0].getMix();
		output[i*nChannels + 1] = speakers[1].getMix();
		output[i*nChannels + 2] = speakers[2].getMix();
		output[i*nChannels + 3] = speakers[3].getMix();
		output[i*nChannels + 4] = speakers[4].getMix();
		output[i*nChannels + 5] = speakers[5].getMix();
		output[i*nChannels + 6] = speakers[6].getMix();
		output[i*nChannels + 7] = speakers[7].getMix();
	}

}

void SoundEngine::update(){

	 while (osc_from_pc.hasWaitingMessages()) {
		 ofxOscMessage m;
		 osc_from_pc.getNextMessage(&m);
		 string current_address = m.getAddress();
		 if (current_address == "/newEmitter") {
			 printf("new emitter id %i type %i x %f y %f\n", m.getArgAsInt32(0), m.getArgAsInt32(1), m.getArgAsFloat(2), m.getArgAsFloat(3));
			 // ----------------------------------------------------------------   add new sound to array
			 composite_emitters->turnOnSound(m.getArgAsInt32(0), m.getArgAsInt32(1), m.getArgAsFloat(2), m.getArgAsFloat(3));
			 selected_emitter_id = m.getArgAsInt32(0);
		} else if (current_address == "/deleteEmitter") {
			 printf("delete emitter id\n", m.getArgAsInt32(0));
			 //----------------------------------------------------------------   remove a sound
			 composite_emitters->turnOffSound(m.getArgAsInt32(0));
		 } else if (current_address == "/updateEmitter") {
			 printf("update Emitter at id %i x %f y %f", m.getArgAsInt32(0), m.getArgAsFloat(1), m.getArgAsFloat(2));
			 //-------------------------------------------   update current sounds based on id passed in current_address
			 composite_emitters->moveEmitter(m.getArgAsInt32(0), m.getArgAsFloat(1), m.getArgAsFloat(2));
		 } else {
			 cout << "from pc: " << current_address << endl;
		 }
	 }
	if (composite_emitters->totalEmitters() > 0) {
		// checking for "deletion", more like checking to stop sounds
		composite_emitters->update();
	}

}

void SoundEngine::draw(){

	composite_emitters->draw();
	// speakers have their own draw and update events
	ofDrawBitmapString(ofToString(global_volume) + " global Volume", 40, ofGetHeight() - 30);

}

void SoundEngine::keyPressed(int key){

	switch (key) {

		case ' ':
			// spacebar
			if (pause_enabled==true) {
				composite_emitters->pauseAllEmitters();
				pause_enabled=false;
			} else {
				composite_emitters->playAllEmitters();
				pause_enabled=true;
			}
			break;

		/** for testing */
		case 'A':{
			//A for "AAAAAH! TOO LOUD!"
			float _gl;
			if (speakers[0].global_volume_adjustment == 0.0) {
				_gl=0.3;
			} else {
				_gl = 0.0;
			}
			setGlobalVolume(_gl);
			break;
		}
		case 'n':
			// n button
			composite_emitters->turnOnSound(10, 0, .1, .1);
			selected_emitter_id = 10;
			//
			break;
		case 'N':
			// n button
			composite_emitters->turnOnSound(36, 1, .1, .2);
			selected_emitter_id = 36;
			//
			break;
		case 'm':
			composite_emitters->turnOnSound(12003, 2, .003, .7);
			selected_emitter_id = 12003;
			break;
		case 'M':
			selected_emitter_id = 3;
			composite_emitters->turnOnSound(3, 4, .4, .4);
			break;
		case 'd':
			// d button
			composite_emitters->turnOffSound(selected_emitter_id);
			//
			break;
		case 'l':
			// list devices
			ofSoundStreamListDevices();
			break;
		case OF_KEY_LEFT: {
			float x = composite_emitters->getX(selected_emitter_id)/ofGetWidth() - .01;
			float y = composite_emitters->getY(selected_emitter_id)/ofGetHeight();
			composite_emitters->moveEmitter(selected_emitter_id, x, y);
			break;
		}
		case OF_KEY_RIGHT: {
			float x = composite_emitters->getX(selected_emitter_id)/ofGetWidth() + .01;
			float y = composite_emitters->getY(selected_emitter_id)/ofGetHeight();
			composite_emitters->moveEmitter(selected_emitter_id, x, y);
			break;
		}
		case OF_KEY_DOWN: {
			float x = composite_emitters->getX(selected_emitter_id)/ofGetWidth();
			float y = composite_emitters->getY(selected_emitter_id)/ofGetHeight() + .03;
			composite_emitters->moveEmitter(selected_emitter_id, x, y);
			break;
		}
		case OF_KEY_UP: {
			float x = composite_emitters->getX(selected_emitter_id)/ofGetWidth();
			float y = composite_emitters->getY(selected_emitter_id)/ofGetHeight() - .03;
			composite_emitters->moveEmitter(selected_emitter_id, x, y);
			break;
		}
		case '1':
			selected_emitter_id = 10;
			break;
		case '2':
			selected_emitter_id = 36;
			break;
		case '3':
			selected_emitter_id = 12003;
			break;
		case '4':
			selected_emitter_id = 3;
			break;
		case '+':{
			//make louder
			float gl = speakers[0].global_volume_adjustment += .05;
			if (gl > 1.0) gl = 1;
			setGlobalVolume(gl);
			break;
		}
		case '-':{
			//make softer
			float gl = speakers[0].global_volume_adjustment -= .05;
			if (gl < 0.0) gl = 0;
			setGlobalVolume(gl);
			break;
		}
		/****************/

		default:
			printf("keypress: %i\n", key);
			break;

	}
}

void SoundEngine::loadXml(Speaker * _speakers){

	ofSetDataPathRoot("./data/");
	if( xml.loadFile("sound_engine_settings.xml") ){
		ProgramStatusLogger::record("sound_engine_settings.xml loaded successfully");
		for (int i=0; i<SPEAKER_COUNT; i++) {
			if(xml.pushTag("speaker", i)){
				// getValue("TAG", item num, default value);
				int x = xml.getValue("x", 0, 0);
				int y = xml.getValue("y", 0, 0);
				_speakers[i].setup(i, x, y, composite_emitters);
				xml.popTag();//go back down to the root
			} else {
				ProgramStatusLogger::record("one of the speaker tags did not load", OF_LOG_FATAL_ERROR);
			}
		}
	} else {
		ProgramStatusLogger::record("unable to load the xml file, sound_engine_settings.xml--check the bin/data folder", OF_LOG_FATAL_ERROR);
	}

}

void SoundEngine::saveXml(Speaker * _speakers){
	//can be enabled for save speaker loction on on exit
	for (int i=0; i <SPEAKER_COUNT; i++) {
		xml.pushTag("speaker", _speakers[i].getSpeakerID());
		xml.setValue("x", _speakers[i].x, 0);
		xml.setValue("y", _speakers[i].y, 0);
		xml.popTag();
	}
	xml.saveFile("sound_engine_settings.xml");
}

void SoundEngine::setGlobalVolume(float _gl) {
	speakers[0].global_volume_adjustment = _gl;
	speakers[1].global_volume_adjustment = _gl;
	speakers[2].global_volume_adjustment = _gl;
	speakers[3].global_volume_adjustment = _gl;
	speakers[4].global_volume_adjustment = _gl;
	speakers[5].global_volume_adjustment = _gl;
	speakers[6].global_volume_adjustment = _gl;
	speakers[7].global_volume_adjustment = _gl;
	global_volume = _gl;
}
