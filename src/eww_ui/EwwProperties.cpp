//
// Created by xxemokidxx on 7/16/25.
//

#include "EwwProperties.h"
#include "eww_ui/EwwProperties.h"
#include "EwwUIObject.h"

using string = std::string;

EwwProperty::EwwProperty(const string &name, const bool &addQuotes) {
    _name = name;
    _addQuotes = addQuotes;
}
string EwwProperty::toString() const {
    if (_name.empty() || _value.empty()) {
        return "";
    }

    string n = ":" + _name + " ";
    string v = _value;
    if (_addQuotes) {
        v = "\'" + v + "\'";
    }

    return n + v + " ";
}

Class::Class() : EwwProperty("class", true){}
Class::Class(const std::string &value) : EwwProperty("class", true) {
    _value = value;
}

Id::Id() : EwwProperty("id", true) {}
Id::Id(const std::string &value) : EwwProperty("id", true) {
    _value = value;
}

const HAlign HAlign::Start("start");
const HAlign HAlign::Center("center");
const HAlign HAlign::End("end");
const HAlign HAlign::Fill("fill");
HAlign::HAlign() : EwwProperty("halign", true) {}
HAlign::HAlign(const std::string &value) : EwwProperty("halign", true) {
    _value = value;
}

const VAlign VAlign::Start("start");
const VAlign VAlign::Center("center");
const VAlign VAlign::End("end");
const VAlign VAlign::Fill("fill");
VAlign::VAlign() : EwwProperty("valign", true) {}
VAlign::VAlign(const std::string &value) : EwwProperty("valign", true) {
    _value = value;
}

const VExpand VExpand::False("false");
const VExpand VExpand::True("true");
VExpand::VExpand() : EwwProperty("vexpand", false) {}
VExpand::VExpand(const std::string &value) : EwwProperty("vexpand", false) {
    _value = value;
}

const HExpand HExpand::False("false");
const HExpand HExpand::True("true");
HExpand::HExpand() : EwwProperty("hexpand", false) {}
HExpand::HExpand(const std::string &value) : EwwProperty("hexpand", false) {
    _value = value;
}

const SpaceEvenly SpaceEvenly::False("false");
const SpaceEvenly SpaceEvenly::True("true");
SpaceEvenly::SpaceEvenly() : EwwProperty("space-evenly", false) {}
SpaceEvenly::SpaceEvenly(const std::string &value) : EwwProperty("space-evenly", false) {
    _value = value;
}

Spacing::Spacing() : EwwProperty("spacing", false) {}
Spacing::Spacing(const std::string &value) : EwwProperty("spacing", false) {
    _value = value;
}

const Orientation Orientation::Vertical("v");
const Orientation Orientation::Horizontal("h");
Orientation::Orientation() : EwwProperty("orientation", true) {}
Orientation::Orientation(const std::string &value) : EwwProperty("orientation", true) {
    _value = value;
}

MinHeight::MinHeight() : EwwProperty("min-height", true) {}
MinHeight::MinHeight(const std::string &value) : EwwProperty("min-height", true) {
    _value = value;
}

MinWidth::MinWidth() : EwwProperty("min-width", true) {}
MinWidth::MinWidth(const std::string &value) : EwwProperty("min-width", true) {
    _value = value;
}

MaxHeight::MaxHeight() : EwwProperty("max-height", true) {}
MaxHeight::MaxHeight(const std::string &value) : EwwProperty("max-height", true) {
    _value = value;
}

MaxWidth::MaxWidth() : EwwProperty("max-width", true) {}
MaxWidth::MaxWidth(const std::string &value) : EwwProperty("max-width", true) {
    _value = value;
}

ToolTip::ToolTip() : EwwProperty("tooltip", true) {}
ToolTip::ToolTip(const std::string &value) : EwwProperty("tooltip", true) {
    _value = value;
}

Text::Text() : EwwProperty("text", true) {}
Text::Text(const std::string &value) : EwwProperty("text", true) {
    _value = value;
}
