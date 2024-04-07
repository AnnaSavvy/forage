#pragma once

enum class EquipmentGrade : int
{
    NO_GRADE = 0,
    D_GRADE,
    C_GRADE,
    B_GRADE,
    A_GRADE
};

enum class WeaponType : int
{
    MELEE = 0,
    RANGED,
    FINESSE,
    MAGIC
};

struct Equipment
{
    int level = 0;

    EquipmentGrade getGrade()
    {
        if ( level >= 20 ) {
            return EquipmentGrade::A_GRADE;
        }
        else if ( level < 0 ) {
            return EquipmentGrade::NO_GRADE;
        }
        return static_cast<EquipmentGrade>( level / 5 );
    }
};

struct Weapon : public Equipment
{
    WeaponType type = WeaponType::MELEE;
    int power = 0;
};
