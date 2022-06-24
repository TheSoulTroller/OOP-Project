#pragma once
#include "Pixel.h"

/**
 * @brief Black/White пиксел наследник на Pixel.
 * @details Обектите от този клас изграждата матрицата на .pbm изображенията.
 */
class BWPixel : public Pixel
{
private:
    short black;

public:
    /**
     * @brief Конструктор на класа с параметри, приемащ стойността на пиксела.
     */
    BWPixel(short _black)
    {
        setBlack(_black);
    }
    /**
     * @brief Сеттър с валидация за стойността на пиксела
     */
    void setBlack(short _black)
    {
        if(_black != 0 && _black != 1)
        {
            cout << "Black value exceeded the range!\nBlack has been set to ";
            _black > 1 ? black = 1 : black = 0;
            cout << black << "!"<< endl;
        }
        else
        {
            black = _black;
        }
    }
    /**
     * @brief Функция, която връща стойността на пиксела
     */
    short getBlack() const
    {
        return black;
    }
    /**
     * @brief Предефинирана виртуална функция от клас Pixel за принтиране на стойността в пиксела.
     */
    virtual void print() const override
    {
        cout << black << " ";
    }
    /**
     * @brief Предефинирана виртуална функция от клас Pixel за записване на стойността на пиксела в поток.
     */
    virtual void write(std::ofstream& file) const override
    {
        file << black << " ";
    }
};