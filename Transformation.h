#pragma once
#include "Picture/Netpbm.h"
#include <cmath>

/**
 * @brief Клас за трансформации на изображения.
 * @details Всички в функции в класа са статични.
 */
class Transform
{
private:
    /**
     * @brief Функция, която получава вектора с трансформации на дадено изображение и спрямо типа му и премахва ненужните трансформации.
     */
    static void optimizeTransformations(Vector<String>& transform, const Type& picType)
    {
        cout << '1';
        for (int i = 0; i < transform.getSize();)
        {
            cout << '3';
            if(transform.getSize() >= 4)
            {   
                if((i+1) >= transform.getSize() || (i+2) >= transform.getSize() || (i+3) >= transform.getSize())
                {
                    break;
                }
                if (transform[i] == "left" && transform[i + 1] == "left" && transform[i + 2] == "left" && transform[i + 3] == "left")
                {
                    transform.pop(i);
                    transform.pop(i);
                    transform.pop(i);
                    transform.pop(i);
                    i = 0;
                    continue;
                }
                if (transform[i] == "right" && transform[i + 1] == "right" && transform[i + 2] == "right" && transform[i + 3] == "right")
                {
                    transform.pop(i);
                    transform.pop(i);
                    transform.pop(i);
                    transform.pop(i);
                    i = 0;
                    continue;
                }
            }

            if (transform.getSize() >= 2)
            {
                cout << '2';
                if((i+1) >= transform.getSize())
                {
                    break;
                }
                if (transform[i] == "vertical" && transform[i + 1] == "vertical")
                {
                    transform.pop(i);
                    transform.pop(i);
                    i = 0;
                    continue;
                }
                if (transform[i] == "horizontal" && transform[i + 1] == "horizontal")
                {
                    transform.pop(i);
                    transform.pop(i);
                    i = 0;
                    continue;
                }
                if (transform[i] == "left" && transform[i + 1] == "right")
                {
                    transform.pop(i);
                    transform.pop(i);
                    i = 0;
                    continue;
                }
                if (transform[i] == "right" && transform[i + 1] == "left")
                {
                    transform.pop(i);
                    transform.pop(i);
                    i = 0;
                }
            }
            i++;  
        }
        
        for(int i = 0; i < transform.getSize();)
        {
            if(picType == 1 && transform[i] == "monochrome")
            {
                transform.pop(i);
                i = 0;
                continue;
            }
            if((picType == 2 || picType == 1) && transform[i] == "grayscale")
            {
                transform.pop(i);
                i = 0;
                continue;
            }
            i++;
        }
        cout << '3';
        int countNegative = 0;
        for(int i = 0; i < transform.getSize(); i++)
        {
            if(transform[i] == "negative")
            {
                countNegative++;
            }
        }
        if(!(countNegative % 2))
        {
            for(int i = 0; i < transform.getSize();)
            {
                if(transform[i] == "negative")
                {
                    transform.pop(i);
                    i = 0;
                    continue;
                }
                i++;
            }
        }
        else
        {
            for(int i = 0; i < transform.getSize(); i++)
            {
                if(transform[i] == "negative")
                {
                    for(int j = i + 1; j < transform.getSize();)
                    {
                        if(transform[j] == "negative")
                        {
                            transform.pop(j);
                            j = i + 1;
                            continue;
                        }
                        j++;
                    }
                    break;
                }
            }
        }
        cout << '4';
        for(int i = 0; i < transform.getSize();)
        {
            if(transform[i] == "monochrome")
            {
                for(int j = i + 1; j < transform.getSize();)
                {
                    if(transform[j] == "monochrome" || transform[j] == "grayscale")
                    {
                        transform.pop(j);
                        j = i + 1;
                        continue;
                    }
                    j++;
                }
            }
            i++;
        }
        
        // transform.print();
    }

    /**
     * @brief Функция, която завърта матрицата на изображението наляво
     */
    static void left(Matrix<Pixel*>& pixels)
    {
        pixels.rotateLeft();
        // Prints the picture
        // for(int i = 0; i < pixels.getRows(); i++)
        // {
        //     for(int j = 0; j < pixels.getCols(); j++)
        //     {
        //         pixels.get(i, j)->print();
        //     }
        //     cout << endl;
        // }
    }
    /**
     * @brief Функция, която завърта матрицата на изображението надясно
     */
    static void right(Matrix<Pixel*>& pixels)
    {
        pixels.rotateRight();
        // Prints the picture
        // for(int i = 0; i < pixels.getRows(); i++)
        // {
        //     for(int j = 0; j < pixels.getCols(); j++)
        //     {
        //         pixels.get(i, j)->print();
        //     }
        //     cout << endl;
        // }
    }
    /**
     * @brief Функция, която завърта матрицата на изображението вертикално
     */
    static void vertical(Matrix<Pixel*>& pixels)
    {
        pixels.flipVertical();
        // Prints the picture
        // for(int i = 0; i < pixels.getRows(); i++)
        // {
        //     for(int j = 0; j < pixels.getCols(); j++)
        //     {
        //         pixels.get(i, j)->print();
        //     }
        //     cout << endl;
        // }
    }
    /**
     * @brief Функция, която завърта матрицата на изображението хоризонтално
     */
    static void horizontal(Matrix<Pixel*>& pixels)
    {
        pixels.flipHorizontal();
        // Prints the picture
        // for(int i = 0; i < pixels.getRows(); i++)
        // {
        //     for(int j = 0; j < pixels.getCols(); j++)
        //     {
        //         pixels.get(i, j)->print();
        //     }
        //     cout << endl;
        // }
    }

    /**
     * @brief Функция, която обръща стойностите на пикселите в матрицата на изображението
     * @param pixels матрицата на изображението
     * @param picType типа на изображението
     * @param maxValue максималната допустима стойност на пикселите в това изображение
     */
    static void negative(Matrix<Pixel*>& pixels, const short maxValue, const Type& picType)
    {
        const int type = picType == 1 ? 1 : picType == 2 ? 2 : 3;
        for(int i = 0; i < pixels.getRows(); i++)
        {
            for(int j = 0; j < pixels.getCols(); j++)
            {
                if(type == 1)
                {
                    BWPixel* pixel = dynamic_cast<BWPixel*>(pixels.get(i, j));
                    pixel->setBlack(abs(pixel->getBlack() - 1));
                }
                if(type == 2)
                {
                    GPixel* pixel = dynamic_cast<GPixel*>(pixels.get(i, j));
                    pixel->setGray(abs(pixel->getGray() - maxValue), maxValue);
                }
                if(type == 3)
                {
                    RGBPixel* pixel = dynamic_cast<RGBPixel*>(pixels.get(i, j));
                    Vector<short> rgb = pixel->getRGB();
                    pixel->setRed(abs(rgb[0] - maxValue), maxValue);
                    pixel->setGreen(abs(rgb[1] - maxValue), maxValue);
                    pixel->setBlue(abs(rgb[2] - maxValue), maxValue);
                }
            }
        }

        // Prints the picture
        // for(int i = 0; i < pixels.getRows(); i++)
        // {
        //     for(int j = 0; j < pixels.getCols(); j++)
        //     {
        //         pixels.get(i, j)->print();
        //     }
        //     cout << endl;
        // }
    }
    /**
     * @brief Функция, която прави изображението черно бяло
     * @param pixels матрицата на изображението
     * @param picType типа на изображението
     * @param maxValue максималната допустима стойност на пикселите в това изображение
     */
    static void monochrome(Matrix<Pixel*>& pixels, const short maxValue, const Type& picType)
    {
        if(picType == 1)
        {
            cout << "Already in monochrome" << endl;
            return;
        }
        const int type = picType == 2 ? 2 : 3;
        for(int i = 0; i < pixels.getRows(); i++)
        {
            for(int j = 0; j < pixels.getCols(); j++)
            {
                if(type == 2)
                {
                    GPixel* pixel = dynamic_cast<GPixel*>(pixels.get(i, j));
                    if(pixel->getGray() > maxValue / 2)
                    {
                        pixel->setGray(maxValue, maxValue);
                    }
                    else
                    {
                        pixel->setGray(0, maxValue);
                    }
                }
                else
                {
                    RGBPixel* pixel = dynamic_cast<RGBPixel*>(pixels.get(i, j));
                    Vector<short> rgb = pixel->getRGB();
                    short specialValue = round (0.299 * rgb[0] + 0.587 * rgb[1] + 0.114 * rgb[2]);
                    if(specialValue > maxValue / 2)
                    {
                        pixel->setRed(maxValue, maxValue);
                        pixel->setGreen(maxValue, maxValue);
                        pixel->setBlue(maxValue, maxValue);
                    }
                    else
                    {
                        pixel->setRed(0, maxValue);
                        pixel->setGreen(0, maxValue);
                        pixel->setBlue(0, maxValue);
                    }

                }
            }
        }
    }
    /**
     * @brief Функция, която прави изображението сиво
     * @param pixels матрицата на изображението
     * @param picType типа на изображението
     * @param maxValue максималната допустима стойност на пикселите в това изображение
     */
    static void grayscale(Matrix<Pixel*>& pixels, const short maxValue, const Type& picType)
    {
        if(picType == 2 || picType == 1)
        {
            cout << "Already in grayscale" << endl;
            return;
        }
        for(int i = 0; i < pixels.getRows(); i++)
        {
            for(int j = 0; j < pixels.getCols(); j++)
            {
                RGBPixel* pixel = dynamic_cast<RGBPixel*>(pixels.get(i, j));
                Vector<short> rgb = pixel->getRGB();
                short specialValue = round (0.299 * rgb[0] + 0.587 * rgb[1] + 0.114 * rgb[2]);
                pixel->setRed(specialValue, maxValue);
                pixel->setGreen(specialValue, maxValue);
                pixel->setBlue(specialValue, maxValue);
            }
        }
    }

public:
    /**
     * @brief Функция, която извършва нужните операциите по изображението след като трансформациите се оптимизират с помощта на optimizeTransformation().
     * @param transform вектор от трансформации на изображението
     * @param pixels матрицата на изображението
     * @param picType типа на изображението
     * @param maxValue максималната допустима стойност на пикселите в това изображение
     */
    static bool transform(Vector<String>& transform, Matrix<Pixel*>& pixels, const Type& picType, const short maxValue)
    {
        cout << "Enter transform!" << endl;
        if(transform.getSize() > 1)
        {
            optimizeTransformations(transform, picType);
        }
        cout << "Optimized transform!" << endl;
        if(transform.getSize() == 0)
        {
            cout << "After optimization there is no need to change the picture!" << endl;
            return false;
        }

        for(int i = 0; i < transform.getSize(); i++)
        {
            if(transform[i] == "left")
            {
                Transform::left(pixels);
                continue;
            }
            if(transform[i] == "right")
            {
                Transform::right(pixels);
                continue;
            }
            if(transform[i] == "vertical")
            {
                Transform::vertical(pixels);
                continue;
            }
            if(transform[i] == "horizontal")
            {
                Transform::horizontal(pixels);
                continue;
            }
            if(transform[i] == "negative")
            {
                cout << "Entering negative" << endl;
                Transform::negative(pixels, maxValue, picType);
                continue;
            }
            if(transform[i] == "monochrome")
            {
                Transform::monochrome(pixels, maxValue, picType);
                continue;
            }
            if(transform[i] == "grayscale")
            {
                Transform::grayscale(pixels, maxValue, picType);
                continue;
            }
        }
        return true;
    }

};