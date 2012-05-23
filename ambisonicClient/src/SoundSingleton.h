#ifndef SOUNDSINGLETON_H
#define SOUNDSINGLETON_H

/*
 *  SoundSingleton.h
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

#include "ofMain.h"
#include "ProgramStatusLogger.h"
#include "XmlManager.h"
#include "ofxOsc.h"

class SoundSingleton {

    public:
        static SoundSingleton * getAndRetainInstance();
        void release();
        ~SoundSingleton();

        // id,
        // type needs to get set once
        int getNewSoundId(); // class need to keep track of sound id so it can start, update and stop it.
        void startSoundType(int id, int type, float x, float y); // always balance out start sound type
        void updateSound(int id, float x, float y);
        void stopSound(int id);
        void sendTestMessage();

    protected:
        SoundSingleton();

    private:

        static SoundSingleton * _instance;
        static int retain_count;

        //OSC
        void setupOSC();
        string ip_address; // = "169.254.253.12";
        int port; // = 5010;
        bool osc_enabled;
        ofxOscSender sender;
        ofxOscBundle sound_bundle;

        // Xml
        XmlManager xml;
        void loadSettings();
        void saveMenuSettings();

        unsigned int id_counter;

};

#endif // SOUNDSINGLETON_H
