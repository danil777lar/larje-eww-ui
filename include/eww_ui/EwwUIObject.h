#ifndef EWWUIOBJECT_H
#define EWWUIOBJECT_H

#include <string>
#include <vector>


class EwwUIObject {
protected:
        std::string _name;

        std::string _class = "back";
        std::string _id;
        std::string _halign;
        std::string _valign;
        std::string _spaceEvenly;
        std::string _spacing;
        std::string _orientation;
        std::string _expand;
        std::string _minWidth;
        std::string _minHeight;
        std::string _maxWidth;
        std::string _maxHeight;
        std::string _toolTip;

        std::vector<EwwUIObject*> _children;

        EwwUIObject(const std::string &name);

public:
        void addChild(EwwUIObject* child);
        std::string serialize() const;
};


#endif
