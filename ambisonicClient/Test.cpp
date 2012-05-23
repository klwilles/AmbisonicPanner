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

#include "Test.h"

Test::Test()
{
    //ctor
}

Test::~Test()
{
    //dtor
}

void Test::playSample(){
    thorn_sound.play(2,centroid_normalized.x,.9);
    //thorn_sound.stop();
}

void Test::stopAllSounds(){
    light_sound.stop();
    thorn_sound.stop();
}

void Test::update(){
    // before draw stuff
}
void Test::draw(){
    // draw whatever you want here
}
void Test::keyPressed(int key){

    // example
    if(key=='p'){
        playSample();
    } else if(key=='s'){
        stopAllSounds();
    }

}
