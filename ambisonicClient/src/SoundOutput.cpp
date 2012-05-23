/*
 *  SoundOutput.cpp
 *  wallofSpirituality
 *
 *  Created by Kenneth Willes on 6/20/10.
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

#include "SoundOutput.h"

SoundOutput::SoundOutput(){

    sound_transmitter = SoundSingleton::getAndRetainInstance();

    id = 0;
    x = 0; y = 0;

    distance_threshold_to_update = .08;
    sound_type = 0;

    is_playing = false;

}

SoundOutput::~SoundOutput(){
    sound_transmitter->release();
}

void SoundOutput::play(int _sound_type, float _x, float _y){

    if(is_playing==true && sound_type!=_sound_type){
        // stop sound before you play a different type of sound
        stop();
    } else if(is_playing==true && sound_type==_sound_type){
        updateSoundLocation(_x,_y);
    }

    if(is_playing==false) {
        // must be playing for first time
        id = sound_transmitter->getNewSoundId();
        x = _x;
        y = _y;
        sound_type = _sound_type;
        is_playing = true;
        // package sound for wallSoundPanner
        sound_transmitter->startSoundType(id, sound_type, x, y);
        printf("play id %i, sound_type %i\n", id, sound_type);
    }

}
void SoundOutput::updateSoundLocation(float _x, float _y){
    float distance = ofDist(_x, _y, x, y);
    if(distance>distance_threshold_to_update){
        x = _x;
        y = _y;
        sound_transmitter->updateSound(id, x, y);
        printf("update id %i, x %f, y %f\n", id, x, y);
    }
}
void SoundOutput::stop(){
    if(is_playing==true){
        is_playing = false;
        sound_transmitter->stopSound(id);
        printf("stop id %i\n", id);
    }
}
