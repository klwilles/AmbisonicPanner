/*
 *  Speaker.cpp
 *
 *  Created by Ken Willes and Michael Reynolds
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

#include "Speaker.h"

//--------------------------------------------------------------
Speaker::Speaker():mix(0.0), screen_height(ofGetHeight()), screen_width(ofGetWidth()) {

	setSize(30, 30); // set width, height
	enableMouseEvents();
	speaker_color.setColor("black");

	max_emitter_distance = (double) screen_height;

	global_volume_adjustment = 1.0; //0 - 1
	//this is used to globally adjust the volume of all speakers.

}

//--------------------------------------------------------------
void Speaker::setup(int _speaker_id, int _x, int _y, CompositeEmitters * _emitters){
	emitters = _emitters;
	speaker_id = _speaker_id;
	x = _x;
	y = _y;
}

//--------------------------------------------------------------
void Speaker::update(){

	if(isMouseDown()){
		x = getMouseX()-width/2;  //move speaker with mouse position
		y = getMouseY()-height/2; //move speaker with mouse position
	}

}
//--------------------------------------------------------------
void Speaker::draw(){

	// draw box
	ofSetColor(speaker_color.getR(), speaker_color.getG(), speaker_color.getB());
	ofRect(x, y, width, height);

	// draw speaker number
	ofSetColor(0xFFFFFF);
	ofDrawBitmapString(ofToString(speaker_id, 0), x+10, y+20);

}
//--------------------------------------------------------------
int Speaker::getSpeakerID(){
	return speaker_id;
}

const double & Speaker::getMaxEmitterDistance(){
	return max_emitter_distance;
}

// as sound emitter gets closer to speaker, the volume goes up.
double Speaker::getSpeakerPercentageIntensity(const float & emitter_x, const float & emitter_y) {

	double emitter_distance_to_speaker = (double) ofDist(x,y, emitter_x, emitter_y);
	double intensity = (double) (1-ofClamp((emitter_distance_to_speaker/getMaxEmitterDistance()), 0.0, 1.0));
	//printf("intensity: %f\n", intensity);
	return intensity;

}

//--------------------------------------------------------------
double Speaker::getMix(){

	mix=0.0;
	if(!emitters->getEmitters().empty()){
		vector<Emitter *>::iterator iter = emitters->getEmitters().begin();
		for(iter; iter!=emitters->getEmitters().end(); ++iter){
			double percent = getSpeakerPercentageIntensity((*iter)->getX(), (*iter)->getY());
			mix =  mix + (percent * (*iter)->getSoundBuffer()) * global_volume_adjustment;
			//printf("speaker_id:%i, mix: %f + percent: %f * emitter[i]getSoundStream \n", speaker_id, mix, percent);
		}
	}

	return mix;

}
