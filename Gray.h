#pragma once
#include "Pixel.h"
/**
 * @brief Gray пиксел наследник на Pixel.
 * @details Обектите от този клас изграждата матрицата на .pgm изображенията.
 */
class GPixel : public Pixel
{
private:
    short gray;
public:
    /**
     * @brief Конструктор на класа с параметри, приемащ стойността на пиксела и максимална стойност за всеки пиксел.
     */
    GPixel(short _gray,const short maxValue)
    {
        setGray(_gray, maxValue);
    }
    /**
     * @brief Сеттър с валидация за стойността на пиксела и максимална допустима стойност
     */
    void setGray(short _gray, const short maxValue)
    {
        if(0 > _gray || _gray > maxValue)
        {
            cout << "Ivalid value for a pixel!\nGray pixel has been set to ";
            _gray > maxValue ? gray = maxValue : gray = 0;
            cout << gray << "!"<< endl;
        }
        else
        {
            gray = _gray;
        }
    }
    /**
     * @brief Функция, която връща стойността на пиксела
     */
    short getGray() const
    {
        return gray;
    }
    /**
     * @brief Предефинирана виртуална функция от клас Pixel за принтиране на стойността в пиксела.
     */
    virtual void print() const override
    {
        cout << gray << '\t';
    }
    /**
     * @brief Предефинирана виртуална функция от клас Pixel за записване на стойността на пиксела в поток.
     */
    virtual void write(std::ofstream& file) const override
    {
        file << gray << " ";
    }
};