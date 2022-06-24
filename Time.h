#pragma once
#include <ctime>
#include <cstring>
/**
 * @brief Структура за текущо време.
 * @details Структурата се използва за новото име при записването на изображение с промени.
 */
struct DateTime
{
    /**
     * @brief Статична функция която връща символен низ от текуща дата и час
     */
    static const char* getDateTime()
    {
        time_t t = time(0);
        struct tm* now = localtime(&t);
        char* dateTime = new char[100];
        strftime(dateTime, 100, "_%d_%m_%y-%H_%M", now);
        /**
         * @brief Функцията strftime получава като параметри символен низ, максимална дължина на низа, формат за дата и часа и поинтър към time_t структура.
         */
        // strftime accepts a char*, max size, a format (in type '%letter' where diffrent letters represent
        // different time related outputs), and a pointer to a time_t struct.

        return dateTime;
    }
};