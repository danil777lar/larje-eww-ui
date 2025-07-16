#include "EwwUIObjectContainer.h"
using string = std::string;


EwwUIObjectContainer::EwwUIObjectContainer(const string &name) : EwwUIObject(name) {

}

void EwwUIObjectContainer::addChild(EwwUIObject *child) {
    _children.push_back(child);
}

string EwwUIObjectContainer::getContent() const override{
    string result = "";
    for (EwwUIObject *child : _children) {
        result += child->serialize();
    }

    return result;
}

