#ifndef _COMPOSITE_EMITTERS
#define _COMPOSITE_EMITTERS

/*
 *  CompositeEmitters.h
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

#include "ofMain.h"
#include "Emitter.h"

class CompositeEmitters {

	public:

		CompositeEmitters(int count);
	    ~CompositeEmitters();

		void turnOnSound(int _id, int _type, float _x, float _y);
		void turnOffSound(int _id);
		//void deleteMarkedEmitters();

		void moveEmitter(int _id, float _x, float _y);
		void stopAllEmitters();
		void pauseAllEmitters();
		void playAllEmitters();

		void update();
		void draw();

		vector<Emitter *> & getEmitters();

		int totalEmitters();
		float getVolume(int _id);
		float getX(int _id);
		float getY(int _id);

		void normalizeSounds();

	private:
		void deleteAllEmitters();
		vector<Emitter *>::iterator iter;
		vector<Emitter *> emitters;

		Emitter * getEmitterFromId(int _id);

};

#endif
