#pragma once
#include "Pixel.h"
/**
 * @brief RGB пиксел наследник на Pixel.
 * @details Обектите от този клас изграждата матрицата на .ppm изображенията.
 */
class RGBPixel : public Pixel
{
private:
    short red;
    short green;
    short blue;

public:
    /**
     * @brief Конструктор на класа с параметри, приемащ 3 стойности за червено, зелено и синьо и максимална допустима стойност за всеки пиксел.
     */
    RGBPixel(short r, short g, short b, const short maxValue)
    {
        setRed(r, maxValue);
        setGreen(g, maxValue);
        setBlue(b, maxValue);
    }
    /**
     * @brief Сеттър с валидация за червен цвят
     */
    void setRed(short _red, const short maxValue)
    {
        if(0 > _red || _red > maxValue)
        {
            cout << "Red value invalid!\nRed has been set to ";
            _red > maxValue ? red = maxValue : red = 0;
            cout << _red << "!"<< endl;
        }
        else
        {
            red = _red;
        }
    }
    /**
     * @brief Сеттър с валидация за зелен цвят
     */
    void setGreen(short _green, const short maxValue)
    {
        if(0 > _green || _green > maxValue)
        {
            cout << "Green value invalid!\nGreen has been set to ";
            _green > maxValue ? green = maxValue : green = 0;
            cout << green << "!"<< endl;
        }
        else
        {
            green = _green;
        }
    }
    /**
     * @brief Сеттър с валидация за син цвят
     */
    void setBlue(short _blue, const short maxValue)
    {
        if(0 > _blue || _blue > maxValue)
        {
            cout << "Blue value invalid!\nBlue has been set to ";
            _blue > maxValue ? blue = maxValue : blue = 0;
            cout << blue << "!"<< endl;
        }
        else
        {
            blue = _blue;
        }
    }

    /**
     * @brief Функцията връща Вектор с 3-те стойности на даден пиксел.
     */
    Vector<short> getRGB() const
    {
        Vector<short> rgb;
        rgb.push(red);
        rgb.push(green);
        rgb.push(blue);
        return rgb;
    }
    
    /**
     * @brief Предефинирана виртуална функция от клас Pixel за принтиране на стойностите в пиксела.
     */
    virtual void print() const override
    {
        cout << red << " " << green << " " << blue << "  ";
    }
    /**
     * @brief Предефинирана виртуална функция от клас Pixel за записване на стойностите на пиксела в поток.
     */
    virtual void write(std::ofstream& file) const override
    {
        file << red << " " << green << " " << blue << "  ";
    }
};