#pragma once
#include "ui.h"

class SkillCounter : public UIContainer
{
public:
    ValueComponent _binding;

    SkillCounter( Point position, int width, std::string description, ValueBinding binding );

    void handleClickEvent( const Point & click, int modes ) override;
};


