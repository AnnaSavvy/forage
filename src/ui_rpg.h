#pragma once
#include "ui.h"

class CenteringLabel : public Label
{
    int _expectedWidth;

public:
    CenteringLabel( const Point & position, const std::string & text, int width );
    virtual void render() override;
};

class SkillCounter : public UIContainer
{
public:
    ValueComponent _binding;

    SkillCounter( Point position, int width, std::string description, ValueBinding binding );

    void handleClickEvent( const Point & click, int modes ) override;
};

class AttributeCounter : public UIContainer
{
    CenteringLabel * _display;

public:
    ValueComponent _binding;

    AttributeCounter( Point position, std::string description, ValueBinding binding );

    void handleClickEvent( const Point & click, int modes ) override;
};
