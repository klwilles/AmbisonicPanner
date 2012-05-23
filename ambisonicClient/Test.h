#ifndef TEST_H
#define TEST_H

/*
 *  Test.h
 *  wallSoundPanner
 *
 *  Created by Michael Reynolds, Kenneth Willes on 5/20/10.
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

class Test
{
    public:
        Test();
        virtual ~Test();

        void update();
		void draw();
		void keyPressed(int key);

        void playSample();
        void stopAllSounds();

    protected:

        // sound
        SoundOutput light_sound;
        SoundOutput thorn_sound;

};

#endif // TEST_H
