//
// Created by xxemokidxx on 7/16/25.
//

#include "EwwProperties.h"
#include "EwwUIObject.h"

using string = std::string;

EwwProperty::EwwProperty(const string &name) {
    _name = name;
}
string EwwProperty::toString() const {
    if (_name.empty() || _value.empty()) {
        return "";
    }

    return _name + ": " + _value + "\n";
}

Class::Class(const std::string &value) : EwwProperty("class") {
    _value = value;
}

Id::Id(const std::string &value) : EwwProperty("id") {
    _value = value;
}

const HAlign HAlign::Start("start");
const HAlign HAlign::Center("center");
const HAlign HAlign::End("end");
const HAlign HAlign::Fill("fill");
HAlign::HAlign(const std::string &value) : EwwProperty("halign") {
    _value = value;
}

const VAlign VAlign::Start("start");
const VAlign VAlign::Center("center");
const VAlign VAlign::End("end");
const VAlign VAlign::Fill("fill");
VAlign::VAlign(const std::string &value) : EwwProperty("valign") {
    _value = value;
}

const SpaceEvenly SpaceEvenly::False("false");
const SpaceEvenly SpaceEvenly::True("true");
SpaceEvenly::SpaceEvenly(const std::string &value) : EwwProperty("space-evenly") {
    _value = value;
}

Spacing::Spacing(const std::string &value) : EwwProperty("spacing") {
    _value = value;
}

const Orientation Orientation::Vertical("v");
const Orientation Orientation::Horizontal("h");
Orientation::Orientation(const std::string &value) : EwwProperty("orientation") {
    _value = value;
}

const Expand Expand::False("false");
const Expand Expand::True("true");
Expand::Expand(const std::string &value) : EwwProperty("expand") {
    _value = value;
}

MinHeight::MinHeight(const std::string &value) : EwwProperty("min-height") {
    _value = value;
}

MinWidth::MinWidth(const std::string &value) : EwwProperty("min-width") {
    _value = value;
}

MaxHeight::MaxHeight(const std::string &value) : EwwProperty("max-height") {
    _value = value;
}

MaxWidth::MaxWidth(const std::string &value) : EwwProperty("max-width") {
    _value = value;
}

ToolTip::ToolTip(const std::string &value) : EwwProperty("tooltip") {
    _value = value;
}