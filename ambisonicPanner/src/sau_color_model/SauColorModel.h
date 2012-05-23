#ifndef _SAU_COLOR_MODEL
#define _SAU_COLOR_MODEL

/*
 *  SauColorModel.h
 *  wallSoundPanner
 *
 *  Created by Kenneth Willes on 6/7/10.
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

class SauColorModel {

	public:

		SauColorModel(string color_name="southern evergreen");
		SauColorModel(const SauColorModel & orig);
		SauColorModel & operator=(const SauColorModel & orig);

		void setColor(string color_name);
		void setAlpha(int alpha);
		int getR();
		int getG();
		int getB();
		int getA();

	private:

		int r, g, b, a;

};

#endif
