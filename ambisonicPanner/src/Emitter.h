#ifndef _EMITTER_
#define _EMITTER_

/*
 *  Emitter.h
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

#include "ofMain.h"
#include "SauColorModel.h"
#include "Sample.h"

class Emitter : public ofRectangle {

	public:

		Emitter(int _id, float _x, float _y);
		~Emitter();

		void updateSoundPosition(float _x, float _y); // update factors for sound
		void draw(); // for visual feedback
		double getSoundBuffer(); // the sound

		int getEmitterID();

		const double & getVolume();
		double getVolumeWeight();
		void setVolume(double _volume);

		void setX(float _x);
		void setY(float _y);
		const float & getX();
		const float & getY();

		int getSoundType();
		void setSoundType(int _id, int _type);
		const double & getMaxEmitterInfluence();

		void pause();
		void stop();
		void play();
		void checkProgress();
	void setFadeAmount(float _norm_vol);

		void initLoadSounds();

		bool buffer_is_stopped;

		int sound_id;
		bool should_delete;

		//---------------------------------- fade shound stuff
	bool fade_sound;
	float fade_amount;

	private:
		int emitter_id;

		double volume;
		double max_emitter_influence;

		int sound_type;
		//Sample sampler;

		Sample thorn_connect;
		Sample thorn_disconnect;
		Sample thorn_group;
		Sample funnel_down;
		Sample light_swirl;

		vector<Sample *>::iterator iter;
		vector<Sample *> sample_holder;

		double noise;

		int screen_width;
		int screen_height;
		string file;
		SauColorModel color;

};

#endif
