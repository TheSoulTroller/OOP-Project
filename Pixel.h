#pragma once
#include <fstream>
/**
 * @brief Абстрактен клас пиксел.
 * @details Класът се използва в матрицата на всяко изображение.
 */
class Pixel
{
public:
    /**
     * @brief Виртуален деструктор.
     */
    virtual ~Pixel(){};
    /**
     * @brief Чисто виртуална фунцкия, която изписва стойнността в пискела.
     */
    virtual void print() const = 0;
    /**
     * @brief Чисто виртуална фунцкия, която приема поток и записва в него стойнноста на пиксела.
     */
    virtual void write(std::ofstream& file) const = 0;
};
