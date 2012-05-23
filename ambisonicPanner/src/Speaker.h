#ifndef _SPEAKERS_
#define _SPEAKERS_

/*
 *  Speaker.h
 *
 *  Created by Ken Willes and Michael Reynolds
 *  Copyright 2010 Southern Adventist University. All rights reserved.
 *
 *	The speaker is like the mixer--it checks to see which emitter is the
 *	closest and allows for some of that sound to come in and be returned
 *	to the main out.

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

#include "ofxMSAInteractiveObject.h"
#include "CompositeEmitters.h"
#include "Emitter.h"

class Speaker : public ofxMSAInteractiveObject {

	public:

		Speaker();
		void setup(int _speaker_id, int _x, int _y, CompositeEmitters * _emitters);

		void update();
		void draw();

		double getMix();

		int getSpeakerID();
		const double & getMaxEmitterDistance();
		double getSpeakerPercentageIntensity(const float & emitter_x, const float & emitter_y);

	float global_volume_adjustment;

	 private:

		double mix;

		int speaker_id;
		double max_emitter_distance;

		const int screen_height;
		const int screen_width;

		CompositeEmitters * emitters;
		SauColorModel speaker_color;

};

#endif
