/*
 *  main.cpp
 *
 *  Created by Ken Willes, Michael Reynolds, Ben Norskov
 *  Copyright 2010 Southern Adventist University. All rights reserved.
 *  This program mixes audio through 8 speakers. We used m-audio's hardware.

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
#include "SoundEngine.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main( ){

	// ViewSonic Max Display Size 1600 x 1200
	// Resize proportions of screen width and height to 1600 x 533

    ofAppGlutWindow window;
	ofSetupOpenGL(&window, 1600,533, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new SoundEngine());

}
