#ifndef LABEL_H
#define LABEL_H

#include "EwwProperties.h"
#include "EwwUIObject.h"

class Label : public EwwUIObject {
public:
    Text _text;
    Label();

    std::string getContent() const override;
};



#endif //LABEL_H
