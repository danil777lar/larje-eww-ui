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
    string result = "(" + _name + " ";

    result += _class.toString();
    result += _id.toString();
    result += _halign.toString();
    result += _valign.toString();
    result += _hexpand.toString();
    result += _vexpand.toString();
    result += _spaceEvenly.toString();
    result += _spacing.toString();
    result += _orientation.toString();
    result += _minHeight.toString();
    result += _minWidth.toString();
    result += _maxHeight.toString();
    result += _maxWidth.toString();
    result += _toolTip.toString();

    result += getContent();

    result += ")";
    return result;
}
