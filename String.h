#pragma once
#include <iostream>
#include <cstring>
#include <cstddef>
#include <fstream>
#include "Vector.h"

using std::cin;
using std::cout;
using std::endl;

/**
 * @brief Клас Стринг, представляващ символен низ с произволна дължина.
 * @details Класът се използва за имената на файловете, както и за разчитане на функции въведени от потребителя.
 */
class String
{
    char *symbols;
    size_t size;
    size_t capacity;

    /**
     * @brief Копираща функция
     */
    void copy(const String &other)
    {
        this->size = other.size;
        this->capacity = other.capacity;
        this->symbols = new char[this->capacity];
        strcpy(this->symbols, other.symbols);
    }
    /**
     * @brief Заделя допълнително памет за стринга
     */
    void resize()
    {
        this->capacity *= 2;
        char *temp = new char[this->capacity];
        strcpy(temp, this->symbols);
        delete[] this->symbols;
        this->symbols = temp;
    }
    /**
     * @brief Намалява заделената памет за стринга
     */
    void downsize()
    {
        if (this->size * 3 <= this->capacity)
        {
            this->capacity /= 2;
            char *temp = new char[this->capacity];
            strcpy(temp, this->symbols);
            delete[] this->symbols;
            this->symbols = temp;
        }
    }
    /**
     * @brief Освобождава динамично заделената памет
     */
    void erase()
    {
        delete[] this->symbols;
    }

public:
    /**
     * @brief Конструктор по подразбиране
     */
    String()
    {
        this->symbols = new char[1];
        this->symbols[0] = '\0';
        this->size = 0;
        this->capacity = 1;
    }
    /**
     * @brief Конструктор с параметри, който копира само част от подаден char*
     */
    String(const char* source, int length)
    {
        if(source != nullptr)
        {
            this->size = length;
            this->capacity = length * 2;
            this->symbols = new char[this->capacity];
            for(int i = 0; i < length; i++)
            {
                this->symbols[i] = source[i];
            }
            this->symbols[length] = '\0';
        }
    }
    /**
     * @brief Конструктор с параметри, който копира целия char*
     */
    String(const char *source)
    {
        if(source != nullptr)
        {
            this->size = strlen(source);
            this->capacity = this->size * 2;
            this->symbols = new char[this->capacity];
            strcpy(this->symbols, source);
        }
    }
    /**
     * @brief Копиращ конструктор
     */
    String(const String &other)
    {
        this->copy(other);
    }
    /**
     * @brief Предифиниран оператор равно, който приема символен низ
     */
    String &operator=(const char *source)
    {
        if(source != nullptr)
        {
            this->erase();
            this->size = strlen(source);
            this->capacity = this->size * 2;
            this->symbols = new char[this->capacity];
            strcpy(this->symbols, source);
            return *this;
        }
    }
    /**
     * @brief Предифиниран оператор равно, който приема String
     */
    String &operator=(const String &other)
    {
        if (this != &other)
        {
            this->erase();
            this->copy(other);
        }
        return *this;
    }
    /**
     * @brief Деструктор
     */
    ~String()
    {
        this->erase();
    }
    /**
     * @brief Функция връщаща дължината на стринга
     */
    int length() const
    {
        return this->size;
    }
    /**
     * @brief Функция връщаща символите в стринга
     */
    const char* c_str() const
    {
        return this->symbols;
    }
    /**
     * @brief Оператор за сравняване на стрингове
     */
    bool operator==(const String &other) const
    {
        return strcmp(this->symbols, other.symbols) == 0;
    }
    /**
     * @brief Оператор за сравняване на стрингове приемащ параметър char*
     */
    bool operator==(const char *other) const
    {
        return strcmp(this->symbols, other) == 0;
    }
    /**
     * @brief Оператор за различие на стрингове приемащ параметър String
     */
    bool operator!=(const String &other) const
    {
        return !(*this == other);
    }
    /**
     * @brief Оператор + който връща нов стринг, получен от конкатиниранте на два други стринга
     */
    String operator+(const String &other)
    {
        String result;
        result.size = this->size + other.size;
        result.capacity = result.size * 2;
        result.symbols = new char[result.capacity];
        strcpy(result.symbols, this->symbols);
        strcat(result.symbols, other.symbols);

        return result;
    }
    /**
     * @brief Оператор += който конкатинира към текущия стринг, подаден такъв
     */
    String &operator+=(const String &other)
    {
        while (this->size + other.size >= this->capacity)
        {
            this->resize();
        }
        strcat(this->symbols, other.symbols);
        this->size += other.size;
        return *this;
    }
    /**
     * @brief Оператор -= който премахва от текущия стринг подадена дъжлина
     */
    String &operator-=(int length)
    {
        if (length > this->size)
        {
            length = this->size;
        }
        this->size -= length;
        this->symbols[this->size] = '\0';
        return *this;
    }
    /**
     * @brief Оператор [] който връща символа на позиция index, но не може да бъде променян
     */
    const char &operator[](int index) const
    {
        if (index < 0 || index >= this->size)
        {
            throw std::invalid_argument("Index is out of range");
        }
        return this->symbols[index];
    }
    /**
     * @brief Оператор [] който връща символа на позиция index, но може да бъде променен
     */
    char &operator[](int index)
    {
        if (index < 0 || index >= this->size)
        {
            throw std::invalid_argument("Index is out of range");
        }
        return this->symbols[index];
    }
    /**
     * @brief Функция която разбива стринга на всичките му съставни думи и ги добавя във вектор.
     */
    Vector<String> split()
    {
        Vector<String> result;
        try
        {
            if (this->size == 0)
            {
                throw std::invalid_argument("String is empty");
            }
            for (int i = 0; i < this->size; i++)
            {
                int j = i;
                while (j < this->size && this->symbols[j] != ' ')
                {
                    j++;
                }
                result.push(String(this->symbols + i, j - i));
                i = j;
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
        return result;
    }
    /**
     * @brief Функция проверява дали подаден файл не съдържа забранени символи и дали разширението е .pbm/.pgm/.ppm. Ако някое от условията не е изпълнено връща false.
     */
    bool validFileName()
    {
        for (int i = 0; i < this->size; i++)
        {
            if (this->symbols[i] == '\\' || this->symbols[i] == '/' || this->symbols[i] == ':' || this->symbols[i] == '*' ||
                this->symbols[i] == '?' || this->symbols[i] == '"' || this->symbols[i] == '<' || this->symbols[i] == '>' || this->symbols[i] == '|')
            {
                cout << "Forbiden symbol found in filename" << endl;
                return false;
            }
        }
        // check if the last symbols are .pgm/.pbm/.ppm
        if(this->symbols[this->size-1] != 'm' || (this->symbols[this->size - 2] != 'g' && this->symbols[this->size - 2] != 'p' && this->symbols[this->size - 2] != 'b')
            || this->symbols[this->size - 3] != 'p' || this->symbols[this->size - 4] != '.')
        {
            cout << "Invalid extension!" << endl;
            return false;
        }
        return true;
    }
    /**
     * @brief Предефиниран оператор за извеждане на стринга.
     */
    friend std::ostream &operator<<(std::ostream &out, const String &str)
    {
        if (str.symbols == nullptr || str.symbols[0] == '\0')
        {
            out << "String is empty";
        }
        else
        {
            out << str.symbols;
        }
        return out;
    }
    /**
     * @brief Предефиниран оператор за въвеждане на стринга.
     */
    friend std::istream &operator>>(std::istream &in, String &str)
    {
        const int buffSz = 16;
        char buff[buffSz];
        str.size = 0;
        str.capacity = buffSz * 2;
        str.erase();
        str.symbols = new char[str.capacity];
        int iter = 0;

        while (in.get(buff, buffSz, '\n'))
        {
            if (iter == 0)
            {
                str.size = strlen(buff);
                strcpy(str.symbols, buff);
                iter++;
            }
            else
            {
                if (str.size + strlen(buff) >= str.capacity)
                {
                    str.resize();
                }
                str.size += strlen(buff);
                strcat(str.symbols, buff);
            }
        }
        return in;
    }
};