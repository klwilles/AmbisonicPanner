#ifndef SOUNDOUTPUT_H
#define SOUNDOUTPUT_H

/*
 *  SoundOutput.h
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

#include "ofMain.h"
#include "SoundSingleton.h"

class SoundOutput
{
    public:
        SoundOutput();
        ~SoundOutput();
        void play(int _sound_type, float _x, float _y);
        void updateSoundLocation(float _x, float _y);
        void stop();

    private:
        SoundSingleton * sound_transmitter;
        int id;
        float x, y;
        float distance_threshold_to_update;
        int sound_type;
        bool is_playing;
};

#endif // SOUNDOUTPUT_H
