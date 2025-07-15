//
// Created by xxemokidxx on 7/15/25.
//

#include "EwwUIObject.h"
#include "eww_ui/EwwUIObject.h"

using string = std::string;

EwwUIObject::EwwUIObject(const std::string &name) {
    _name = name;
}


void EwwUIObject::addChild(EwwUIObject* child) {
    _children.push_back(child);
}

string EwwUIObject::serialize() const {
    string result = "(" + _name + ": ";
    result += ":class \"" + _class + "\" ";
    result += ")";
    return result;
}
