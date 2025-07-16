#ifndef EWWPROPERTIES_H
#define EWWPROPERTIES_H
#include <string>

class EwwProperty {
public:
    virtual std::string toString() const;
protected:
    std::string _name;
    std::string _value;
    EwwProperty(const std::string &name);
    virtual ~EwwProperty() = default;
};

class Class : EwwProperty {
public:
    explicit Class(const std::string &value);
};

class Id : EwwProperty {
public:
    explicit Id(const std::string &value);
};

class HAlign : EwwProperty {
public:
    static const HAlign Start;
    static const HAlign Center;
    static const HAlign End;
    static const HAlign Fill;
private:
    explicit HAlign(const std::string &value);
};

class VAlign : EwwProperty {
public:
    static const VAlign Start;
    static const VAlign Center;
    static const VAlign End;
    static const VAlign Fill;
private:
    explicit VAlign(const std::string &value);
};

class SpaceEvenly : EwwProperty {
public:
    static const SpaceEvenly True;
    static const SpaceEvenly False;
private:
    explicit SpaceEvenly(const std::string &value);
};

class Spacing : EwwProperty {
public:
    explicit Spacing(const std::string &value);
};

class Orientation : EwwProperty {
public:
    static const Orientation Vertical;
    static const Orientation Horizontal;
private:
    explicit Orientation(const std::string &value);
};

class Expand : EwwProperty {
public:
    static const Expand True;
    static const Expand False;
private:
    explicit Expand(const std::string &value);
};

class MinHeight : EwwProperty {
public:
    explicit MinHeight(const std::string &value);
};

class MinWidth : EwwProperty {
public:
    explicit MinWidth(const std::string &value);
};

class MaxHeight : EwwProperty {
public:
    explicit MaxHeight(const std::string &value);
};

class MaxWidth : EwwProperty {
public:
    explicit MaxWidth(const std::string &value);
};

class ToolTip : EwwProperty {
public:
    explicit ToolTip(const std::string &value);
};

#endif
