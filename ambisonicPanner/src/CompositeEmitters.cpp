/*
 *  CompositeEmitters.cpp
 *  wallSoundPanner
 *
 *  Created by Michael Reynolds, Kenneth Willes on 5/20/10.
 *  Copyright 2010 Southern Adventist University.

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

#include "CompositeEmitters.h"

CompositeEmitters::CompositeEmitters(int count){

	// make the collection
	for (int i=0; i<count; i++) {
		//					   Emitter(int _id, float _x,float _y,int _sound_type);
		emitters.push_back(new Emitter(i, 0, 0));
//		emitters.push_back(new Emitter(i, ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()), 0, 30));
		printf("Composite pushed %i\n", i);
	}
}

CompositeEmitters::~CompositeEmitters(){
	deleteAllEmitters();
}


// this is called by osc
void CompositeEmitters::turnOnSound(int _id, int _type, float _x, float _y){
	iter = emitters.begin();
	for (iter; iter!=emitters.end(); ++iter){
		if ((*iter)->buffer_is_stopped) {
			//if emitter is not playing
			(*iter)->setSoundType(_id, _type);
			(*iter)->updateSoundPosition(_x, _y);
			(*iter)->play();
			printf("emitter %id turned on.\n", _id);
			normalizeSounds();
			break;
		}
	}
}
void CompositeEmitters::turnOffSound(int _id) {
	if(_id>=0){
		Emitter * e = getEmitterFromId(_id);
		if (e!=0) {
			e->stop();
			printf("Emitter %i turned off \n", _id);
			normalizeSounds();
			e->should_delete = false;
		} else {
			printf("*** *** *** *** Warning *** *** *** ***, CompositeEmitters::turnOffSound - getEmitterFromId returned 0");
		}

	} else {
		printf("remove emitter out of range \n");
	}
}

void CompositeEmitters::pauseAllEmitters(){
	iter = emitters.begin();
	for (iter; iter != emitters.end(); ++iter){
		(*iter)->pause();
	}
}
void CompositeEmitters::playAllEmitters(){
	iter = emitters.begin();
	for (iter; iter != emitters.end(); ++iter){
		(*iter)->play();
	}
}

void CompositeEmitters::stopAllEmitters(){
	iter = emitters.begin();
	for (iter; iter != emitters.end(); ++iter){
		(*iter)->stop();
	}
}

void CompositeEmitters::moveEmitter(int _id, float _x, float _y){
	if(_id>=0){
		Emitter * e = getEmitterFromId(_id);
		if (e!=0) {
			e->updateSoundPosition(_x, _y);
		} else {
			printf("Warning, CompositeEmitters::moveEmitter - getEmitterFromId returned 0\n");
		}


	} else {
		printf("move emitter id out of range \n");
	}
}

void CompositeEmitters::update(){
	iter = emitters.begin();
	for (iter; iter != emitters.end(); ++iter){
		//check to see if the sound is done playing
		(*iter)->checkProgress();
	}
	iter = emitters.begin();
	if ((*iter)->should_delete) {
		int f = (*iter)->sound_id;
		cout << f << " from compositeEmitters update" << endl;
		turnOffSound(f);
	}
}

void CompositeEmitters::draw(){
	iter = emitters.begin();
	for (iter; iter!=emitters.end(); ++iter) {
		(*iter)->draw();
	}
}

vector<Emitter *> & CompositeEmitters::getEmitters(){
	return emitters;
}

int CompositeEmitters::totalEmitters(){
	return emitters.size();
}

float CompositeEmitters::getVolume(int _id){

	if(_id>=0){
		Emitter * e = getEmitterFromId(_id);
		if (e!=0) {
			return e->getVolume();
		} else {
			printf("Warning, CompositeEmitters::getVolume - getEmitterFromId returned 0\n");
		}


	}
	printf("move emitter id out of range \n");
	return 0.f;

}
float CompositeEmitters::getX(int _id){
	if(_id>=0){
		Emitter * e = getEmitterFromId(_id);
		if (e!=0) {
			return e->getX();
		} else {
			printf("Warning, CompositeEmitters::getX - getEmitterFromId returned 0\n");
		}


	}
	printf("move emitter id out of range \n");
	return 0.f;

}
float CompositeEmitters::getY(int _id){
	if(_id>=0){
		Emitter * e = getEmitterFromId(_id);
		if (e!=0) {
			return e->getY();
		} else {
			printf("Warning, CompositeEmitters::getY - getEmitterFromId returned 0\n");
		}


	}
	printf("move emitter id out of range \n");
	return 0.f;

}

void CompositeEmitters::deleteAllEmitters(){

	iter = emitters.begin();
	for (iter; iter!=emitters.end(); ++iter){
		delete *iter;
	}
	emitters.clear();

}

void CompositeEmitters::normalizeSounds() {
	iter = emitters.begin();
	int count = 0;
	for (iter; iter!=emitters.end(); ++iter) {
		if (!(*iter)->buffer_is_stopped) {
			count ++;
		}
	}
	if (count > 0) {
		float normalized_volume = 100.0 / (float)count;
		iter = emitters.begin();
		for (iter; iter!=emitters.end(); ++iter) {
			if (!(*iter)->buffer_is_stopped) {
				(*iter)->setVolume(normalized_volume);
				(*iter)->setFadeAmount(normalized_volume);
			}
		}
	}
}

Emitter * CompositeEmitters::getEmitterFromId(int _id) {

	iter = emitters.begin();
	for (iter; iter!=emitters.end(); ++iter) {
		if ((*iter)->sound_id == _id) {
			return *iter;
		}
	}

	return 0;

}

