#pragma once
#include <iostream>
#include <exception>
template <typename T>
/**
 * @brief Клас Матрица, представляващ динамичен двумерен масив от еднотипни елементи.
 * @details Класът се използва за матрицата от стойности на изображението и улеснява работата, защото сам се грижи за динамичната памет.
 */
class Matrix
{
private:
    T** matrix;
    int rows;
    int cols;

    /**
     * @brief Освобождава динамично заделената памет за матрицата
     */
    void erase()
    {
        for (int i = 0; i < rows; i++)
        {
            delete[] matrix[i];
        }
        delete[] matrix;
    }

public:
    /**
     * @brief Конструктор по подразбиране
     */
    Matrix()
    {
        matrix = nullptr;
        rows = 0;
        cols = 0;
    }
    /**
     * @brief Конструктор с параметри размерите на матрицата
     */
    Matrix(int _rows, int _cols)
    {
        if(_rows < 1 || _cols < 1)
        {
            std::cout << "Invalid matrix size!" << std::endl;
            this->rows = 0;
            this->cols = 0;
            matrix = nullptr;
            return;
        }
        this->rows = rows;
        this->cols = cols;
        matrix = new T*[rows];
        for (int i = 0; i < rows; i++)
        {
            matrix[i] = new T[cols];
        }
    }
    /**
     * @brief Копиращ конструктор
     */
    Matrix(const Matrix& other)
    {
        rows = other.rows;
        cols = other.cols;
        matrix = new T*[rows];
        for (int i = 0; i < rows; i++)
        {
            matrix[i] = new T[cols];
        }
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                matrix[i][j] = other.matrix[i][j];
            }
        }
    }
    /**
     * @brief Деструктор
     */
    ~Matrix()
    {
        erase();
    }
    /**
     * @brief Предефиниран оператор равно, който приема Matrix
     */ 
    Matrix& operator=(const Matrix& other)
    {
        if (this != &other)
        {
            erase();
            rows = other.rows;
            cols = other.cols;
            matrix = new T*[rows];
            for (int i = 0; i < rows; i++)
            {
                matrix[i] = new T[cols];
            }
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    matrix[i][j] = other.matrix[i][j];
                }
            }
        }
        return *this;
    }
    /**
     * @brief Функция, която връща броя на редовете на матрицата
     */
    int getRows() const
    {
        return rows;
    }
    /**
     * @brief Функция, която връща броя на колоните на матрицата
     */
    int getCols() const
    {
        return cols;
    }
    /**
     * @brief Функция, която задава стойността на елемент на позиция (i, j), по подаден елемент
     */
    void set(int i, int j, T value)
    {
        matrix[i][j] = value;
    }
    /**
     * @brief Функция, която връща константна референция към елемента от матрицата на позиция (i, j)
     */
    const T& get(int i, int j) const
    {
        return matrix[i][j];
    }
    /**
     * @brief Функция, която връща референция към елемента от матрицата на позиция (i, j)
     */
    T& get(int i, int j)
    {
        return matrix[i][j];
    }
    /**
     * @brief Функция, която завърта матрицата наляво
     */
    void rotateLeft()
    {
        T** temp = new T*[cols];
        for (int i = 0; i < cols; i++)
        {
            temp[i] = new T[rows];
        }

        for (int i = 0; i < cols; i++)
        {
            for (int j = 0; j < rows; j++)
            {
                temp[i][j] = matrix[j][i];
            }
        }
        
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0, k = cols - 1; j < cols/2; j++, k--)
            {
                T save = temp[j][i];
                temp[j][i] = temp[k][i];
                temp[k][i] = save;
            }
        }

        erase();
        int tempRows = rows;
        rows = cols;
        cols = tempRows;
        matrix = temp;
    }
    /**
     * @brief Функция, която завърта матрицата надясно
     */
    void rotateRight()
    {
        T** temp = new T*[cols];
        for (int i = 0; i < cols; i++)
        {
            temp[i] = new T[rows];
        }

        for (int i = 0; i < cols; i++)
        {
            for (int j = 0; j < rows; j++)
            {
                temp[i][j] = matrix[j][i];
            }
        }

        for (int i = 0; i < cols; i++)
        {
            for (int j = 0, k = rows - 1; j < rows/2; j++, k--)
            {
                T save = temp[i][j];
                temp[i][j] = temp[i][k];
                temp[i][k] = save;
            }
        }

        erase();
        int tempRows = rows;
        rows = cols;
        cols = tempRows;
        matrix = temp;
    }
    /**
     * @brief Функция, която завърта матрицата вертикално
     */
    void flipVertical()
    {
        for(int i = 0; i < rows; i++)
        {
            for(int j = 0, k = cols - 1; j < k; j++, k--)
            {
                T save = matrix[i][j];
                matrix[i][j] = matrix[i][k];
                matrix[i][k] = save;
            }
        }
    }
    /**
     * @brief Функция, която завърта матрицата хоризонтално
     */
    void flipHorizontal()
    {
        for(int i = 0; i < cols; i++)
        {
            for(int j = 0, k = rows - 1; j < k; j++, k--)
            {
                T save = matrix[j][i];
                matrix[j][i] = matrix[k][i];
                matrix[k][i] = save;
            }
        }
        
    }
};