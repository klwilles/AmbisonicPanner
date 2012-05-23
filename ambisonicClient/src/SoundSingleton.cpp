/*
 *  SoundSingleton.cpp
 *  wallofSpirituality
 *
 *  Created by Kenneth Willes on 6/20/10 -- cutting it real close
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

#include "SoundSingleton.h"

SoundSingleton::SoundSingleton(){
    id_counter = 0;
    retain_count = 1;
    loadSettings();
    setupOSC();
    sendTestMessage();

}

SoundSingleton::~SoundSingleton(){

}

SoundSingleton * SoundSingleton::_instance = 0;
int SoundSingleton::retain_count = 0;

SoundSingleton * SoundSingleton::getAndRetainInstance(){
    if(_instance==0){
        _instance = new SoundSingleton();
    } else {
        retain_count++;
    }
    return _instance;
}

void SoundSingleton::release(){
    retain_count--;
    if(retain_count==0){
        // must be at zero now, so self destruct.
        delete this;
    }
}

void SoundSingleton::loadSettings(){

    bool loaded = xml.load("sound_singleton.xml", "sound_singleton");
    xml.setPropertyFromXMLTag(port, "port");
    xml.setPropertyFromXMLTag(ip_address, "ip_address");
    xml.setPropertyFromXMLTag(osc_enabled, "osc_enabled");
    if(loaded==false){
        osc_enabled=false;
    }
}

///communication for sounds
int SoundSingleton::getNewSoundId(){
    // rest are ids
    id_counter++;
    //printf("id_counter %i\n", id_counter);
    return id_counter;
}
void SoundSingleton::startSoundType(int id, int type, float x, float y){
    //printf("startSoundType id: %i, type: %i\n", id, type);
    if(osc_enabled==true){

        ofxOscMessage m;

        m.setAddress("/newEmitter");
        m.addIntArg(id);
        m.addIntArg(type);
        m.addFloatArg(x);
        m.addFloatArg(y);

        sender.sendMessage(m);

    }
}
void SoundSingleton::updateSound(int id, float x, float y){
    if(osc_enabled==true){

        ofxOscMessage m;

        m.setAddress("/updateEmitter");
        m.addIntArg(id);
        m.addFloatArg(x);
        m.addFloatArg(y);

        sender.sendMessage(m);

    }
}
void SoundSingleton::stopSound(int id){
    if(osc_enabled==true){

        ofxOscMessage m;

        m.setAddress("/deleteEmitter"); // doesn't really delete, but stops
        m.addIntArg(id);

        sender.sendMessage(m);

    }
}

/// Setup OSC
void SoundSingleton::setupOSC(){
    if(osc_enabled==true){
        // must test
        sender.setup(ip_address, port);
    }
}
void SoundSingleton::sendTestMessage(){

    if(osc_enabled==true){

        ofxOscMessage m;

        m.setAddress("/test");
        m.addIntArg(1);
        m.addFloatArg(2.f);
        sound_bundle.addMessage(m);

        sender.sendBundle(sound_bundle);

    }

}
