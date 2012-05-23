/*
 *  XmlManager.cpp
 *  wallofSpirituality
 *
 *  Created by Kenneth Willes on 5/21/10.
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

#include "XmlManager.h"

XmlManager::XmlManager(){
    //ofSetDataPathRoot("./data/");
    loaded = false;
}
bool XmlManager::load(string _filename, string _root){

    filename = _filename;
    loaded = xml.loadFile(filename);
    if(loaded==false) {
        loadXMLError("Bad news, "+filename+" did not load successfully.");
        return false;
    }
    loaded = setRootLevel(_root);
    if(loaded==false) {
        loadXMLError("setRootLevel at "+_root+" was not successful.");
        return false;
    }

    return true;

}
void XmlManager::save(){
    // save the xml object to xml file
   if(loaded){
        xml.saveFile(filename);
   }else {
        loadXMLError("Cannot save because xml is not loaded");
   }
}
bool XmlManager::setRootLevel(string _root){
    root = _root;
    bool status = xml.pushTag(root);
    if(status==false){
        pushXMLError(root);
    }
}
// set root node in constructor before using these
// getting xml tags and assigning them to pointer, properties
//void XmlManager::setPointerFromXMLTag(int * pointer, const string & tag){
//    if(loaded==true){
//        if(xml.pushTag(tag)){
//            pointer[0] = xml.getValue("min", 1);
//            pointer[1] = xml.getValue("val", 2);
//            pointer[2] = xml.getValue("max", 3);
//            xml.popTag();
//        } else {
//            pushXMLError(tag);
//        }
//    }
//}
//void XmlManager::setPointerFromXMLTag(float * pointer, const string & tag){
//    if(loaded==true){
//        if(xml.pushTag(tag)){
//            pointer[0] = xml.getValue("min", 1.0);
//            pointer[1] = xml.getValue("val", 2.0);
//            pointer[2] = xml.getValue("max", 3.0);
//            xml.popTag();
//        } else {
//            pushXMLError(tag);
//        }
//    }
//}
void XmlManager::setPropertyFromXMLTag(bool & property, const string & tag){
    if(loaded==true){
        if(xml.pushTag(tag)){
            property = (bool) xml.getValue("val", 0);
            xml.popTag();
        } else {
            pushXMLError(tag);
        }
    }
}
void XmlManager::setPropertyFromXMLTag(string & property, const string & tag){
    if(loaded==true){
        if(xml.pushTag(tag)){
            property = xml.getValue("val", "null");
            xml.popTag();
        } else {
            pushXMLError(tag);
        }
    }
}
void XmlManager::setPropertyFromXMLTag(int & property, const string & tag){
    if(loaded==true){
        if(xml.pushTag(tag)){
            property = xml.getValue("val", 0);
            xml.popTag();
        } else {
            pushXMLError(tag);
        }
    }
}
void XmlManager::setPropertyFromXMLTag(float & property, const string & tag){
    if(loaded==true){
        if(xml.pushTag(tag)){
            property = xml.getValue("val", 0.0);
            xml.popTag();
        } else {
            pushXMLError(tag);
        }
    }
}
void XmlManager::setPropertyFromXMLTag(ofRectangle & property, const string & tag){
    if(loaded==true){
        if(xml.pushTag(tag)){
            property.x = xml.getValue("x", 0);
            property.y = xml.getValue("y", 0);
            property.width = xml.getValue("width", 0);
            property.height = xml.getValue("height", 0);
            xml.popTag();
        } else {
            pushXMLError(tag);
        }
    }
}
void XmlManager::setPropertyFromXMLTag(SliderInt & property, const string & tag){
    if(loaded==true){
        if(xml.pushTag(tag)){
            property.min = xml.getValue("min", 1);
            property.val = xml.getValue("val", 2);
            property.max = xml.getValue("max", 3);
            xml.popTag();
        } else {
            pushXMLError(tag);
        }
    }
}
void XmlManager::setPropertyFromXMLTag(SliderFloat & property, const string & tag){
    if(loaded==true){
        if(xml.pushTag(tag)){
            property.min = xml.getValue("min", 1.0);
            property.val = xml.getValue("val", 2.0);
            property.max = xml.getValue("max", 3.0);
            xml.popTag();
        } else {
            pushXMLError(tag);
        }
    }
}
// setting xml tags from pointers, properties
//void XmlManager::setXMLTagFromPointer(const string & tag, int * pointer){
//    if(loaded==true){
//        if(xml.pushTag(tag)){
//            xml.setValue("min", pointer[0]);
//            xml.setValue("val", pointer[1]);
//            xml.setValue("max", pointer[2]);
//            xml.popTag();
//        } else {
//            pushXMLError(tag);
//        }
//    }
//}
//void XmlManager::setXMLTagFromPointer(const string & tag, float * pointer){
//    if(loaded==true){
//        if(xml.pushTag(tag)){
//            xml.setValue("min", pointer[0]);
//            xml.setValue("val", pointer[1]);
//            xml.setValue("max", pointer[2]);
//            xml.popTag();
//        } else {
//            pushXMLError(tag);
//        }
//    }
//}
void XmlManager::setXMLTagFromProperty(const string & tag, bool & property){
    if(loaded==true){

        if(xml.pushTag(tag)){
            xml.setValue("val", (int) property);
            xml.popTag();
        } else {
            pushXMLError(tag);
        }

    }
}
void XmlManager::setXMLTagFromProperty(const string & tag, string & property){
    if(loaded==true){

        if(xml.pushTag(tag)){
            xml.setValue("val", property);
            xml.popTag();
        } else {
            pushXMLError(tag);
        }

    }
}
void XmlManager::setXMLTagFromProperty(const string & tag, int & property){
    if(loaded==true){

        if(xml.pushTag(tag)){
            xml.setValue("val", property);
            xml.popTag();
        } else {
            pushXMLError(tag);
        }

    }
}
void XmlManager::setXMLTagFromProperty(const string & tag, float & property){
    if(loaded==true){

        if(xml.pushTag(tag)){
            xml.setValue("val", property);
            xml.popTag();
        } else {
            pushXMLError(tag);
        }

    }
}
void XmlManager::setXMLTagFromProperty(const string & tag, ofRectangle & property){
    if(loaded==true){

        if(xml.pushTag(tag)){
            xml.setValue("x", property.x);
            xml.setValue("y", property.y);
            xml.setValue("width", property.width);
            xml.setValue("height", property.height);
            xml.popTag();
        } else {
            pushXMLError(tag);
        }

    }
}
void XmlManager::setXMLTagFromProperty(const string & tag, SliderInt & property){
    if(loaded==true){

        if(xml.pushTag(tag)){
            xml.setValue("min", property.min);
            xml.setValue("val", property.val);
            xml.setValue("max", property.max);
            xml.popTag();
        } else {
            pushXMLError(tag);
        }

    }
}
void XmlManager::setXMLTagFromProperty(const string & tag, SliderFloat & property){
    if(loaded==true){

        if(xml.pushTag(tag)){
            xml.setValue("min", property.min);
            xml.setValue("val", property.val);
            xml.setValue("max", property.max);
            xml.popTag();
        } else {
            pushXMLError(tag);
        }

    }
}

void XmlManager::pushXMLError(const string & tag){
    ProgramStatusLogger::record("Unable to push into "+tag+" of "+filename, OF_LOG_ERROR);
}
void XmlManager::loadXMLError(const string & message){
    ProgramStatusLogger::record(message, OF_LOG_ERROR);
}
