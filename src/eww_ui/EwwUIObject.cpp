#include "EwwUIObject.h"
#include "eww_ui/EwwUIObject.h"

using string = std::string;

EwwUIObject::EwwUIObject(const std::string &name) {
    _name = name;
}

string EwwUIObject::getContent() const {
    return "";
}

string EwwUIObject::serialize() const {
    string result = "(" + _name + ": ";
    result += ":class \"" + _class + "\" ";
    result += getContent();
    result += ")";
    return result;
}
