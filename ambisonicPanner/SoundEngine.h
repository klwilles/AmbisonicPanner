#ifndef _SOUND_ENGINE
#define _SOUND_ENGINE

/*
 *  SoundEngine.h
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

#include "ofMain.h"

#include "Speaker.h"
#include "CompositeEmitters.h"

#include "ofxXmlSettings.h"
#include "ofxOsc.h"

#include "SauColorModel.h"
#include "ProgramStatusLogger.h"

//#include "ofEventUtils.h"

#define SPEAKER_COUNT 8
#define MAX_EMITTERS 14

class SoundEngine : public ofBaseApp {

	public:

		SoundEngine();
		~SoundEngine();

		void audioRequested(float * output, int bufferSize, int nChannels);

		void update();
		void draw();
		void keyPressed(int key);

		CompositeEmitters * composite_emitters;
		Speaker * speakers;

		// local testing
		int selected_emitter_id;

		//ofxXmlSettings
		ofxXmlSettings xml;

		//color
		SauColorModel color;

		//osc
		ofxOscReceiver osc_from_pc;
		int getSoundId(string _current_address);

		void loadXml(Speaker * _speakers);
		void saveXml(Speaker * _speakers);

	void setGlobalVolume(float _gl);

		bool pause_enabled;

private:
	float global_volume;

};

#endif
