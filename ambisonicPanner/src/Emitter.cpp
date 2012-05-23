/*
 *  Emitter.cpp
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

#include "Emitter.h"

Emitter::Emitter(int _id, float _x, float _y):
	ofRectangle(_x, _y, 10.f, 10.f),
	emitter_id(_id)
{

	// for visual feedback of sounds moving around on screen

	screen_width = ofGetWidth();
	screen_height = ofGetHeight();

	max_emitter_influence = (double) screen_height;
	buffer_is_stopped = true;

	sound_type=0;
	setVolume(0);
	//volume should get set when the sound plays
	initLoadSounds();
	//printf("Emitter %i constructed \n", _id);
	should_delete = false;

	fade_sound = false;
	setFadeAmount(100);
}

Emitter::~Emitter() {
	printf("~Emitter %i destroyed \n", emitter_id);
}

void Emitter::setSoundType(int _id, int _type){

	printf("trying to set sound type %i id %i\n", _type, _id);
	if (_type>=0 && _type<sample_holder.size()) {
		sound_type = _type;
		sound_id = _id;
	} else {
		printf("out of range\n");
		sound_type = 0;
		sound_id = _id;
	}
}

void Emitter::updateSoundPosition(float _x, float _y) {
	_x *= ofGetWidth();
	_y *= ofGetHeight();
	printf("Emitter::updateSoundPosition x %f y %f", _x, _y);
	x=_x; //x postion of emitter
	y=_y; //y postion of emitter
}

void Emitter::draw() {

	// visibility is based on volume

	ofEnableAlphaBlending();
		ofSetColor(color.getR(), color.getG(), color.getB(), (int) (255*getVolumeWeight()) );
		ofCircle(x, y, width);

		ofNoFill();
		ofSetColor(255, 255, 255, (int) (255*getVolumeWeight()));
		ofCircle(x, y, getMaxEmitterInfluence());
		ofFill();
	ofDisableAlphaBlending();

	// draw emitter number
	ofSetColor(0,0,0, (int) (255*getVolumeWeight()) );
	ofDrawBitmapString("i:"+ofToString(emitter_id, 0), x-5,y+5); //emitter number drawn inside of emitter
	ofDrawBitmapString("v:"+ofToString(volume,0), x-5, y+15); // volume

}

double Emitter::getSoundBuffer(){
	if (buffer_is_stopped==false) {
		//return (double) (sampler.update()*getVolumeWeight());
		double d = (sample_holder[sound_type]->update()*getVolumeWeight());
		//	cout << d << " from get sound bufffer " << sample_holder[sound_type]->getIsPlaying() << endl;
		return d;
	} else {
		return 0;
	}

	/* noise left in for debug
		if (buffer_is_stopped==false) {
			noise = (double) (ofRandomf()*getVolumeWeight());
			return noise;
		}
	*/
}

int Emitter::getEmitterID(){
	return emitter_id;
}

const double & Emitter::getVolume(){
	return volume;
}
double Emitter::getVolumeWeight(){
	double volume_limit = 100;
	double percentage_weight = (double) (getVolume()/volume_limit);
	return percentage_weight; // returns pixel radius
}
void Emitter::setVolume(double _volume){
	volume = ofClamp(_volume, 0.0, 100.0);
}

void Emitter::pause(){
	buffer_is_stopped=true;
	if (sample_holder[sound_type]->getIsPaused()) {
		sample_holder[sound_type]->setPaused(true);
	}

}
void Emitter::stop(){
	fade_sound = true;
}
void Emitter::play(){
	buffer_is_stopped=false;
	iter = sample_holder.begin() + sound_type;
	(*iter)->setPaused(false);
	(*iter)->play();
}

void Emitter::setX(float _x){
	x = _x;
}
void Emitter::setY(float _y){
	y = _y;
}
const float & Emitter::getX(){
	return x;
}
const float & Emitter::getY(){
	return y;
}

int Emitter::getSoundType(){
	return sound_type;
}

const double & Emitter::getMaxEmitterInfluence(){
	return max_emitter_influence;
}

void Emitter::initLoadSounds() {
	printf("loaded sounds\n");
	//Sound Type 0
	thorn_connect.load("finalsounds/thorn1Connect.wav");
	thorn_connect.setLooping(false);
	thorn_connect.stop();
	thorn_connect.setSpeed(.1);
	sample_holder.push_back(&thorn_connect);

	//Sound Type 1
	thorn_disconnect.load("finalsounds/thorn1Disconnect.wav");
	thorn_disconnect.setLooping(false);
	thorn_disconnect.stop();
	thorn_disconnect.setSpeed(.1);
	sample_holder.push_back(&thorn_disconnect);

	//Sound Type 2 USED
	thorn_group.load("finalsounds/thornSound.wav");
	thorn_group.setLooping(true);
	thorn_group.stop();
	thorn_group.setSpeed(.1);
	sample_holder.push_back(&thorn_group);

	//Sound Type 3
	funnel_down.load("finalsounds/funnelDown.wav");
	funnel_down.setLooping(true);
	funnel_down.stop();
	funnel_down.setSpeed(.1);
	sample_holder.push_back(&funnel_down);

	//Sound Type 4 USED
	light_swirl.load("finalsounds/lightSound.wav");
	light_swirl.setLooping(true);
	light_swirl.stop();
	light_swirl.setSpeed(.1);
	sample_holder.push_back(&light_swirl);
}
//------------------------------------------------------------------------------ CHECK PROGRESS
void Emitter::checkProgress() {
	bool b = sample_holder[sound_type]->getIsLooping();
	if (!b && (sample_holder[sound_type]->getPosition() >= 1.0) && !buffer_is_stopped) {
		should_delete = true;
	}
	if (fade_sound == true) {
		if (volume <= 0) {
			fade_sound = false;
			buffer_is_stopped=true;
			iter = sample_holder.begin() + sound_type;
			if ((*iter)->getIsPlaying()) {
				(*iter)->stop();
			}
		} else {
			volume -= fade_amount;
			if (volume < 0) volume = 0;
		}
	}
}
//------------------------------------------------------------------------------ CHECK PROGRESS
void Emitter::setFadeAmount(float _norm_vol) {
	fade_amount = _norm_vol * .2;
	//whatever the normalized volume for sounds is, make the fade amount 15% of that.
	//.15 would make a sound fade out in about 9 frames @ 60fps
	//.2 would take 5 frames
}
