#pragma once
#include "Helpers/Vector.h"
#include "Picture/Netpbm.h"
#include "Transformation.h"

using std::cin;
using std::cout;
using std::endl;
/**
 * @brief Клас Сесия съдържа вектор от изображения и уникален идентификатор.
 * @details Възможността за уникален идентификатор се постига със static int nextId, а с помощта на Вектора не се грижим за динамичната памет.
 */
class Session
{
private:
    // session has a unique ID
    int id;
    static int nextId;
    // session has a vector of files
    Vector<Picture> pictures;

public:
    /**
     * @brief Констурктор по подразбиране.
     */
    Session() = default;
    /**
     * @brief Констурктор на класа с параметри.
     * @details Идентификатора подаден като параметър не се използва никъде. Използва се единствено, за да се различи от конструктора по подразбиране.
     */
    Session(int _id)
    {
        id = nextId;
        nextId++;
        cout << "Session with ID " << id << " created." << endl;
    }
    /**
     * @brief Деструктор на класа.
     */
    ~Session() = default;
    /**
     * @brief Фунцкия, която връща идентификатора на сесията.
     */
    int getId() const
    {
        return id;
    }
    /**
     * @brief Фунцкия, която принтира информация за изображенията в сесията и трансформациите за всяко едно от тях.
     */
    void sessionInfo() const
    {
        cout << "Session with ID " << id << " has " << pictures.getSize() << " files." << endl;
        for (int i = 0; i < pictures.getSize(); i++)
        {
            cout << "File " << i + 1 << ": " << pictures[i].getName() << endl;
            pictures[i].getTransformation();
            cout << "\n_______________________________" << endl;
        }
    }
    /**
     * @brief Фунцкия, която добавя изображение в сесията.
     * @details При добавянето на изображение в сесията, изображението се създава, проверява се неговата валидност и чак товагава се довабя във вектора на сесията.
     */
    void addPicture(const String& picture)
    {
        std::ifstream file(picture.c_str());
        if (!file.good())
        {
            cout << "File is not good!" << endl;
            return;
        }
        String filename = picture;
        // removing .pbm/pgm/ppm from the filename
        filename -= 4;
        Picture pic(file, filename);
        file.close();
        if(pic.getType() == 0)
        {
            cout << "File is not valid!" << endl;
            return;
        }
        pictures.push(pic);
    }
    /**
     * @brief Фунцкия, която добавя трансформация към вектора от трансформации на всяко изображение в сесията.
     */
    void addTransformation(const String& transformation)
    {
        for (int i = 0; i < pictures.getSize(); i++)
        {
            pictures[i].addTransformation(transformation);
        }
    }
    /**
     * @brief Фунцкия, която премахва последната трансформация от вектора от трансформации на всяко изображение в сесията.
     * @details Ако вектора е празен нищо няма да се случи.
     */
    void removeTransformation()
    {
        for (int i = 0; i < pictures.getSize(); i++)
        {
            pictures[i].removeTransformation();
        }
    }

    /**
     * @brief Фунцкия, която създава нов файл в който се записва изображението с вече приложените промени
     * @details Функцията проверява дали изобщо има трансформации за самото изображение, ако няма изображението не се записва, ако има влиза във функция transform(), където се извършват нужните промени по изображението.
     * @details След като бъде записан файла, векторът от трансформации се изчиства.
     */
    void save()
    {
        for (int i = 0; i < pictures.getSize(); i++)
        {
            if(pictures[i].doTransformations().getSize() == 0)
            {
                cout << "File " << pictures[i].getName() << " has not been changed so it will not be saved." << endl;
            }
            else
            {
                if(Transform::transform(pictures[i].doTransformations(), pictures[i].getMatrix(), pictures[i].getType(), pictures[i].getMaxValue()))
                {
                    pictures[i].createFile();
                    cout << "Saving the picture!" << endl;
                    pictures[i].clearTransformations();
                }
            }
        }
    }

    /**
     * @brief Фунцкия, която връща вектор с имета на всички файлове в сесията.
     */
    Vector<String> getNames() const
    {
        Vector<String> names;
        for (int i = 0; i < pictures.getSize(); i++)
        {
            names.push(pictures[i].getName());
        }
        return names;
    }

};
