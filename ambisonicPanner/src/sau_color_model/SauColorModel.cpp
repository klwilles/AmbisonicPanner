/*
 *  SauColorModel.cpp
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

#include "SauColorModel.h"

SauColorModel::SauColorModel(string color_name){
	setColor(color_name);
	setAlpha(255);
}

SauColorModel::SauColorModel(const SauColorModel & orig){

	r = orig.r;
	g = orig.g;
	b = orig.b;
	a = orig.a;

}

SauColorModel & SauColorModel::operator=(const SauColorModel & orig){

	r = orig.r;
	g = orig.g;
	b = orig.b;
	a = orig.a;

	return *this;

}

void SauColorModel::setColor(string color_name){

	// primary
	if(color_name=="southern evergreen"){
		r = 24;
		g = 79;
		b = 44;
	}

	// secondary
	else if (color_name=="southern lime") {
		r = 206;
		g = 213;
		b = 74;
	} else if (color_name=="southern lime-light") {
		r = 227;
		g = 230;
		b = 150;
	}

	// tertiary - bright
	else if (color_name=="ruby") {
		r = 150;
		g = 23;
		b = 46;
	} else if (color_name=="tangerine") {
		r = 255;
		g = 136;
		b = 73;
	} else if (color_name=="dandelion") {
		r = 250;
		g = 218;
		b = 99;
	} else if (color_name=="cool gray") {
		r = 188;
		g = 189;
		b = 188;
	} else if (color_name=="black") {
		r = 17;
		g = 28;
		b = 36;
	} else if (color_name=="lavender") {
		r = 220;
		g = 199;
		b = 223;
	} else if (color_name=="burgundy") {
		r = 125;
		g = 0;
		b = 99;
	} else if (color_name=="violet") {
		r = 79;
		g = 45;
		b = 127;
	} else if (color_name=="royal") {
		r = 0;
		g = 82;
		b = 147;
	} else if (color_name=="robin") {
		r = 187;
		g = 231;
		b = 230;
	}

	// tertiary - muted
	else if (color_name=="rust") {
		r = 189;
		g = 79;
		b = 25;
	} else if (color_name=="soft orange") {
		r = 225;
		g = 163;
		b = 88;
	} else if (color_name=="sand") {
		r = 225;
		g = 16;
		b = 183;
	} else if (color_name=="tan") {
		r = 211;
		g = 191;
		b = 150;
	} else if (color_name=="brown") {
		r = 74;
		g = 60;
		b = 49;
	} else if (color_name=="lilac") {
		r = 196;
		g = 175;
		b = 185;
	} else if (color_name=="rasberry") {
		r = 111;
		g = 44;
		b = 62;
	} else if (color_name=="plum") {
		r = 100;
		g = 68;
		b = 89;
	} else if (color_name=="midnight") {
		r = 38;
		g = 63;
		b = 106;
	} else if (color_name=="sky") {
		r = 186;
		g = 199;
		b = 195;
	} else {
		// default
		// primary southern evergreen
		r = 24;
		g = 79;
		b = 44;

	}

}

void SauColorModel::setAlpha(int alpha){
	if(alpha<256){
		a = alpha;
	} else {
		a = 255;
	}
}

int SauColorModel::getR(){
	return r;
}

int SauColorModel::getG(){
	return g;
}

int SauColorModel::getB(){
	return b;
}

int SauColorModel::getA(){
	return a;
}
