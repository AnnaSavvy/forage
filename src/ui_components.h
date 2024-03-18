#pragma once
#include "ui_base.h"
#include "binding.h"

class ProgressBar : public UIComponent
{
    Style _style;

public:
    ValueComponent _binding;

    ProgressBar( const Rect & dimensions, ValueBinding binding );
    ProgressBar( const Rect & dimensions, ValueBinding binding, const Style & style );

    void setStyle( const Style & style );
    virtual void update( float deltaTime ) override {}
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
    virtual void render() override;
};
