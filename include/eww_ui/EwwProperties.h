#ifndef EWWPROPERTIES_H
#define EWWPROPERTIES_H
#include <string>

class EwwProperty {
public:
    virtual std::string toString() const;
protected:
    bool _addQuotes;
    std::string _name;
    std::string _value;
    EwwProperty(const std::string &name, const bool &addQuotes);
    virtual ~EwwProperty() = default;
};

// ----------------- GENERAL ----------------------------

class Class : public EwwProperty {
public:
    Class();
    explicit Class(const std::string &value);
};

class Id : public EwwProperty {
public:
    Id();
    explicit Id(const std::string &value);
};

class HAlign : public EwwProperty {
public:
    static const HAlign Start;
    static const HAlign Center;
    static const HAlign End;
    static const HAlign Fill;
    HAlign();
private:
    explicit HAlign(const std::string &value);
};

class VAlign : public EwwProperty {
public:
    static const VAlign Start;
    static const VAlign Center;
    static const VAlign End;
    static const VAlign Fill;
    VAlign();
private:
    explicit VAlign(const std::string &value);
};

class VExpand : public EwwProperty {
public:
    static const VExpand True;
    static const VExpand False;
    VExpand();
private:
    explicit VExpand(const std::string &value);
};

class HExpand : public EwwProperty {
public:
    static const HExpand True;
    static const HExpand False;
    HExpand();
private:
    explicit HExpand(const std::string &value);
};

class SpaceEvenly : public EwwProperty {
public:
    static const SpaceEvenly True;
    static const SpaceEvenly False;
    SpaceEvenly();
private:
    explicit SpaceEvenly(const std::string &value);
};

class Spacing : public EwwProperty {
public:
    Spacing();
    explicit Spacing(const std::string &value);
};

class Orientation : public EwwProperty {
public:
    static const Orientation Vertical;
    static const Orientation Horizontal;
    Orientation();
private:
    explicit Orientation(const std::string &value);
};

class MinHeight : public EwwProperty {
public:
    MinHeight();
    explicit MinHeight(const std::string &value);
};

class MinWidth : public EwwProperty {
public:
    MinWidth();
    explicit MinWidth(const std::string &value);
};

class MaxHeight : public EwwProperty {
public:
    MaxHeight();
    explicit MaxHeight(const std::string &value);
};

class MaxWidth : public EwwProperty {
public:
    MaxWidth();
    explicit MaxWidth(const std::string &value);
};

class ToolTip : public EwwProperty {
public:
    ToolTip();
    explicit ToolTip(const std::string &value);
};

// ------------------------------------------------------


// --------------------  LABEL  -----------------------

class Text : public EwwProperty {
public:
    Text();
    explicit Text(const std::string &value);
};

// ------------------------------------------------------

#endif
