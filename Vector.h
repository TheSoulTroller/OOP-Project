#pragma once
#include <iostream>
#include <cstddef>
#include <exception>
template <typename T>
/**
 * @brief Клас Вектор, представляващ динамичен саморазширяващ се масив от еднотипни елементи.
 * @details Класът се използва на много места в проекта и доста улеснява работата, защото той сам се грижи за динамичната памет.
 */
class Vector
{
private:
    T* data;
    size_t capacity;
    int size;

    /**
     * @brief Копираща функция
     */
    void copy(const Vector& other)
    {
        data = new T[other.capacity];
        capacity = other.capacity;
        size = other.size;
        for (int i = 0; i < size; i++)
        {
            data[i] = other.data[i];
        }
    }
    /**
     * @brief Освобождава динамично заделената памет за вектора
     */
    void erase()
    {
        delete[] data;
    }
    /**
     * @brief Заделя допълнително памет за вектора
     */
    void upsize()
    {
        T* temp = new T[capacity * 2];
        for (int i = 0; i < size; i++)
        {
            temp[i] = data[i];
        }
        erase();
        data = temp;
        capacity *= 2;
    }
    /**
     * @brief Намалява заделената памет за вектора, ако тя е твърде много
     */
    void downsize()
    {   
        T* temp = new T[capacity / 2];
        for (int i = 0; i < size; i++)
        {
            temp[i] = data[i];
        }
        erase();
        data = temp;
        capacity /= 2;
    }

public:
    /**
     * @brief Конструктор по подразбиране
     */ 
    Vector()
    {
        capacity = 1;
        size = 0;
        data = new T[capacity];
    }
    /**
     * @brief Копиращ конструктор
     */
    Vector(const Vector& other)
    {
        copy(other);
    }
    /**
     * @brief Предефиниран оператор равно
     */
    Vector& operator=(const Vector& other)
    {
        if (this != &other)
        {
            erase();
            copy(other);
        }
        return *this;
    }
    /**
     * @brief Деструктор
     */
    ~Vector()
    {
        erase();
    }
    /**
     * @brief Функция премахваща дубликатите от вектора
     */
    void removeDuplicates()
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = i + 1; j < size;)
            {
                if (data[i] == data[j])
                {
                    pop(j);
                    j = i + 1;
                    continue;
                }
                j++;
            }
        }
    }
    /**
     * @brief Функция за добавяне на елемент в края на вектора
     */
    void push(const T& element)
    {
        if (size >= capacity)
        {
            upsize();
        }
        data[size++] = element;
    }
    /**
     * @brief Функция за премахване на елемент от края на вектора
     */
    void pop()
    {
        if (size <= 0)
        {
            // throw std::invalid_argument("Vector is empty (called by pop)");
            std::cout << "Vector is empty (called by pop)" << std::endl;
        }
        if (size == capacity / 4)
        {
            downsize();
        }
        size--;
    }
    /**
     * @brief Функция за премахване на елемент от вектора по подаден индекс
     */
    void pop(int index)
    {
        if (index < 0 || index >= size)
        {
            throw std::invalid_argument("Index out of bounds (called by pop)");
        }
        if (index == size - 1)
        {
            pop();
            return;
        }
        for (int i = index; i < size - 1; i++)
        {
            data[i] = data[i + 1];
        }
        if (size == capacity / 4)
        {
            downsize();
        }
        size--;
    }
    /**
     * @brief Функция принтираща съдържанието на вектора
     */
    void print() const
    {
        if(size <= 0)
        {
            std::cout << "Vector is empty" << std::endl;
            return;
        }
        std::cout << "Content of vector:\n";
        for (size_t i = 0; i < size; i++)
        {
            std::cout << data[i] << ' '; // << std::endl;
        }
        std::cout << std::endl;
    }
    /**
     * @brief Булева функция, която проверява дали векторът е празен
     */
    bool isEmpty() const
    {
        return size == 0;
    }
    /**
    * @brief Функция, която връща текущия брой елементи във вектора.
    */
    const int getSize() const
    {
        return size;
    }
    /**
     * @brief Функция, която връща броят елементи, за които е заделена памет във вектора.
     */
    const size_t getCapacity() const
    {
        return capacity;
    }
    /**
     * @brief Функция, която връща коснтанта референция към елемент от вектора по подаден индекс.
     */
    const T& operator[](int index) const
    {
        if (index < 0 || index > size)
        {
            throw std::invalid_argument("Index is out of range in const T& operator[]");
        }
        return data[index];
    }
    /**
     * @brief Функция, която връща елемент от вектора по подаден индекс.
     */
    T& operator[](int index)
    {
        if(size == 0)
        {
            throw std::invalid_argument("Vector is empty (called by T& operator[])");
        }
        // std::cout << index << std::endl;
        if (index < 0 || index > size)
        {
            throw std::invalid_argument("Index is out of range in T& operator[]");
        }
        return data[index];
    }
    /**
     * @brief Функция, която изпразва вектора.
     */
    void clear()
    {
        erase();
        capacity = 1;
        size = 0;
        data = new T[capacity];
    }
};