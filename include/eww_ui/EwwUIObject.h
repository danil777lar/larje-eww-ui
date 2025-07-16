#ifndef EWWUIOBJECT_H
#define EWWUIOBJECT_H

#include <string>
#include <vector>

#include "EwwProperties.h"


class EwwUIObject {
protected:
        std::string _name;

        explicit EwwUIObject(const std::string &name);

        virtual std::string getContent() const;

public:
        Class _class;
        Id _id;
        HAlign _halign;
        VAlign _valign;
        SpaceEvenly _spaceEvenly;
        Spacing _spacing;
        Orientation _orientation;
        Expand _expand;
        MinHeight _minHeight;
        MaxHeight _maxHeight;
        MinWidth _minWidth;
        MaxWidth _maxWidth;
        ToolTip _toolTip;

        std::string serialize() const;
};


#endif
