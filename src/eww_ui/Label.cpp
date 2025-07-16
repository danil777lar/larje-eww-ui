//
// Created by xxemokidxx on 7/16/25.
//

#include "Label.h"
#include "EwwUIObject.h"

using string = std::string;

Label::Label() : EwwUIObject("label") {}

string Label::getContent() const {
    string content = "";

    content += _text.toString();

    return content;
}
