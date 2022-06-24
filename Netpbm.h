#pragma once
#include "../Helpers/String.h"
#include "../Helpers/Vector.h"
#include "../Helpers/Matrix.h"
#include "../Helpers/Time.h"
#include "Pixel.h"
#include "RGB.h"
#include "Gray.h"
#include "BlackWhite.h"
#include <fstream>

/**
 * @brief Тип на изображението спрямо магическото число във файла.
 * @details P1 - .pbm, P2 - .pgm, P3 - .ppm;
 */
enum Type{
    invalid,
    P1,
    P2,
    P3,
};
/**
 * @brief Клас изображение има име, тип, матрица на изображението, максимална допустима стойност на пикселите и вектор с трансформации.
 * @details Помощните класове String, Matrix и Vector улесняват работата с изображенията, понеже сами се грижата за динамичната си памет.
 */
class Picture
{
private:
    String name;
    Type type;
    short maxValue;
    Vector<String> transformations;
    Matrix<Pixel*> pixels;

    /**
     * @brief Булева функция,която проверява дали даден символен низ е коментар (първият символ е #)
     */
    bool isComment(const char* line)
    {
        return line[0] == '#';
    }

    /**
     * @brief Функция, която премахва ненужните разстояния между символите в даден символен низ.
     */
    void trim(char* line)
    {
        for (int i = 0; i < strlen(line); i++)
        {
            if (line[i] == ' ' && line[i + 1] == ' ')
            {
                for (int j = i; j < strlen(line); j++)
                {
                    line[j] = line[j + 1];
                }
                i--;
            }
        }
    }
    /**
     * @brief Функция, която получава поток и създава изображение от тип .pbm(P1)
     */
    void setPBM_Picture(std::ifstream& file)
    {
        char buffer [512];
        file.getline(buffer, 512, '\n');
        if (isComment(buffer))
        {
            while (isComment(buffer))
            {
                file.getline(buffer, 512, '\n');
            }
        }

        String size(buffer);
        Vector<String> sizes = size.split();
        int width = atoi(sizes[0].c_str());
        int height = atoi(sizes[1].c_str());
        if (height <= 0 || width <= 0)
        {
            cout << "Error: picture has a negative size!" << endl;
            stopCreating();
            return;
        }
        pixels = Matrix<Pixel*>(height, width);
        for(int i = 0; i < height; i++)
        {
            file.getline(buffer, 512, '\n');
            trim(buffer);
            String line(buffer); 
            Vector<String> line_pixels = line.split();
            if(line_pixels.getSize() != width)
            {
                cout << "Error: line " << i << " has a different length than the set width!" << endl;
                stopCreating();
                return;
            }
            for(int j = 0; j < width; j++)
            {
                pixels.set(i, j,new BWPixel(atoi(line_pixels[j].c_str())));
            }
        }

        // Printing tha picture
        // for(int i = 0; i < height; i++)
        // {
        //     for(int j = 0; j < width; j++)
        //     {
        //         pixels.get(i, j)->print();
        //     }
        //     cout << endl;
        // }
    }
    /**
     * @brief Функция, която получава поток и създава изображение от тип .pgm(P2)
     */
    void setPGM_Picture(std::ifstream& file)
    {
        char buffer [512];
        file.getline(buffer, 512, '\n');
        if (isComment(buffer))
        {
            while (isComment(buffer))
            {
                file.getline(buffer, 512, '\n');
            }
        }

        String size(buffer);
        Vector<String> sizes = size.split();
        int width = atoi(sizes[0].c_str());
        int height = atoi(sizes[1].c_str());
        if(height <= 0 || width <= 0)
        {
            cout << "Error: picture has a negative size!" << endl;
            stopCreating();
            return;
        }
        pixels = Matrix<Pixel*>(height, width);

        file.getline(buffer, 512, '\n');
        if (isComment(buffer))
        {
            while (isComment(buffer))
            {
                file.getline(buffer, 512, '\n');
            }
        }

        maxValue = atoi(buffer);
        if(maxValue <= 0)
        {
            cout << "Error: picture has a negative max value!" << endl;
            stopCreating();
            return;
        }

        for(int i = 0; i < height; i++)
        {
            file.getline(buffer, 512, '\n');
            trim(buffer);
            String line(buffer); 
            Vector<String> line_pixels = line.split();
            if(line_pixels.getSize() != width)
            {
                cout << "Error: line " << i << " has a different length than the set width!" << endl;
                stopCreating();
                return;
            }
            for(int j = 0; j < width; j++)
            {
                pixels.set(i, j, new GPixel(atoi(line_pixels[j].c_str()), maxValue));
            }
        }

        // Printing tha picture
        // for(int i = 0; i < height; i++)
        // {
        //     for(int j = 0; j < width; j++)
        //     {
        //         pixels.get(i, j)->print();
        //     }
        //     cout << endl;
        // }
    }
    /**
     * @brief Функция, която получава поток и създава изображение от тип .ppm(P3)
     */
    void setPPM_Picture(std::ifstream& file)
    {
        char buffer [512];
        file.getline(buffer, 512, '\n');
        if (isComment(buffer))
        {
            while (isComment(buffer))
            {
                file.getline(buffer, 512, '\n');
            }
        }

        String size(buffer);
        Vector<String> sizes = size.split();
        int width = atoi(sizes[0].c_str());
        int height = atoi(sizes[1].c_str());
        if(height <= 0 || width <= 0)
        {
            cout << "Error: picture has a negative size!" << endl;
            stopCreating();
            return;
        }
        pixels = Matrix<Pixel *>(height, width);

        file.getline(buffer, 512, '\n');
        if (isComment(buffer))
        {
            while (isComment(buffer))
            {
                file.getline(buffer, 512, '\n');
            }
        }

        maxValue = atoi(buffer);
        if(maxValue <= 0)
        {
            cout << "Error: picture has a negative max value!" << endl;
            stopCreating();
            return;
        }

        for(int i = 0; i < height; i++)
        {
            file.getline(buffer, 512, '\n');
            trim(buffer);
            String line(buffer);
            Vector<String> line_pixels = line.split();
            if(line_pixels.getSize() != width*3)
            {
                cout << "Error: line " << i << " has a different length than the set width!" << endl;
                stopCreating();
                return;
            }
            for(int j = 0; j < width; j++)
            {
                pixels.set(i, j, new RGBPixel(atoi(line_pixels[j].c_str()), atoi(line_pixels[j + width].c_str()), atoi(line_pixels[j + width * 2].c_str()), maxValue));
            }
        }

        // Printing tha picture
        // for(int i = 0; i < height; i++)
        // {
        //     for(int j = 0; j < width; j++)
        //     {
        //         pixels.get(i, j)->print();
        //     }
        //     cout << endl;
        // }

    }

    /**
     * @brief Функция, която бива извикана при засичане на невалидни данни в изображението
     */
    void stopCreating()
    {
        cout << "Invalid information detected!" << endl;
        name = "Invalid name";
        type = invalid;
        pixels = Matrix<Pixel*>(0, 0);
        pixels.set(0,0, nullptr);
        return;
    }

public:
    /**
     * @brief Конструктор по подразбиране
     */
    Picture() = default;
    /**
     * @brief Конструктор с параметри, поток и име на изображението
     */
    Picture(std::ifstream& file, const String& _name)
    {
        name = _name;
        char buffer[1024];
          
        file.getline(buffer,1024,'\n');
        if(isComment(buffer))
        {
            while(isComment(buffer))
            {
                file.getline(buffer,1024,'\n');
            }
        }
        
        if(buffer[0] == 'P' && buffer[1] == '1')
        {
            type = P1;
            // cout << "Type: P1" << endl;
            maxValue = 1;
            setPBM_Picture(file);
        }
        if(buffer[0] == 'P' && buffer[1] == '2')
        {
            type = P2;
            // cout << "Type: P2" << endl;
            setPGM_Picture(file);
        }
        if(buffer[0] == 'P' && buffer[1] == '3')
        {
            type = P3;
            // cout << "Type: P3" << endl;
            setPPM_Picture(file);
        }
        if(buffer[0] != 'P' || (buffer[1] != '1' && buffer[1] != '2' && buffer[1] != '3'))
        {
            cout << "Error: Unknown file type!" << endl;
            stopCreating();
            return;
        }
    }
    /**
     * @brief Фунцкия, която връща типа на изображението
     */
    const Type& getType() const
    {
        return this->type;
    }
    /**
     * @brief Фунцкия, която връща името на изображението
     */
    const String& getName() const
    {
        return this->name;
    }
    /**
     * @brief Фунцкия, която връща широчината на изображението
     */
    int getWidth() const
    {
        return this->pixels.getCols();
    }
    /**
     * @brief Фунцкия, която връща височината на изображението
     */
    int getHeight() const
    {
        return this->pixels.getRows();
    }
    /**
     * @brief Фунцкия, която връща максималната допустима стойност на пиксел в изображението
     */
    const short getMaxValue() const
    {
        return this->maxValue;
    }
    /**
     * @brief Фунцкия, която принтира трансформациите в изображението
     */
    void getTransformation() const
    {
        if(transformations.isEmpty())
        {
            cout << "No transformations!" << endl;
            return;
        }
        cout << "Transformation: ";
        for(int i = 0; i < transformations.getSize(); i++)
        {
            cout << transformations[i] << ", ";
        }
    }
    /**
     * @brief Фунцкия, която връща референция към вектора от трансформации на изображението
     */
    Vector<String>& doTransformations()
    {
        return this->transformations;
    }
    /**
     * @brief Фунцкия, която връща референция към матрицата от пиксели на изображението
     */
    Matrix<Pixel*>& getMatrix()
    {
        return this->pixels;
    }
    /**
     * @brief Фунцкия, която добавя трансформация към изображението
     */
    void addTransformation(const String& transformation)
    {
        transformations.push(transformation);
    }
    /**
     * @brief Фунцкия, която премахва последната трансформация от изображението
     */
    void removeTransformation()
    {
        if(transformations.getSize() > 0)
        {
            transformations.pop();
        }
    }
    /**
     * @brief Фунцкия, която премахва всички трансформации от изображението
     */
    void clearTransformations()
    {
        transformations.clear();
    }
    /**
     * @brief Фунцкия, която създава нов файл и записва в него промененото изображение.
     */
    void createFile()
    {
        String newFileName = name + DateTime::getDateTime();
        if(type == P1)
        {
            newFileName += ".pbm";
        }
        else if(type == P2)
        {
            newFileName += ".pgm";
        }
        else if(type == P3)
        {
            newFileName += ".ppm";
        }
        
        std::ofstream file(newFileName.c_str());
        if(!file.is_open())
        {
            cout << "Error: Could not create file!" << endl;
            return;
        }
        file << "P" << type << endl;
        file << getWidth() << " " << getHeight() << endl;
        if(type != P1)
        {
            file << getMaxValue() << endl;
        }
        for(int i = 0; i < getHeight(); i++)
        {
            for(int j = 0; j < getWidth(); j++)
            {
                pixels.get(i, j)->write(file);
            }
            file << endl;
        }
        file.close();
    }
};