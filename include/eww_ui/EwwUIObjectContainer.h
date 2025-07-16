#ifndef EWWUIOBJECTCONTAINER_H
#define EWWUIOBJECTCONTAINER_H


#include "EwwUIObject.h"


class EwwUIObjectContainer : public EwwUIObject {

protected:
    std::vector<EwwUIObject*> _children;

    EwwUIObjectContainer(const std::string &name);

    std::string getContent() const override;

public:
    void addChild(EwwUIObject* child);

};



#endif
