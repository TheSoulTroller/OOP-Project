#pragma once
#include "Session.h"

/**
 * @brief Клас Workspace съдържа вектор от сесии и индекс на сесията с която работим в момента.
 */
class Workspace
{
private:
    Vector<Session> sessions;
    int currentSession;

public:
    /**
     * @brief Конструктор по подразбиране на Workspace.
     */
    Workspace()
    {
        cout << "Workspace created." << endl;
        currentSession = 0;
    }

    /**
     * @brief Деструктор на Workspace.
     */
    ~Workspace()
    {
        cout << "Workspace destroyed." << endl;
    }

    /**
     * @brief Функция, която връща вектор от имената на изображенията в текущата сесия
     */
    Vector<String> getSessionNames() const
    {
        return sessions[currentSession].getNames();
    }

    /**
     * @brief Функция, която принтира информация за текущата сесия.
     */
    void getSessionInfo() const
    {
        sessions[currentSession].sessionInfo();
    }
    /**
     * @brief Функция, която сменя текущата сесия по подаден индекс, ако такава не съществува се връща съобщение.
     */
    void switchSession(int sessionId)
    {
        if(sessions[currentSession].getId() == sessionId)
        {
            cout << "You are already in the session with ID " << sessionId << "." << endl;
            return;
        }

        for (int i = 0; i < sessions.getSize(); i++)
        {
            if (sessions[i].getId() == sessionId)
            {
                currentSession = i;
                cout << "Switched to session with ID: " << sessionId << '!' << endl;
                return;
            }
        }
        
        cout << "Session with ID " << sessionId << " does not exist." << endl;
    }
    /**
     * @brief Функция, която създава нова сесия в която се зареждат подадените изображения. Новата сесия става текущата.
     */
    void load(const Vector<String>& pics)
    {
        Session crtSesion(1);
        for(int i = 1; i < pics.getSize(); i++)
        {
            crtSesion.addPicture(pics[i]);
        }
        sessions.push(crtSesion);
        currentSession = sessions.getSize() - 1;
    }
    /**
     * @brief Функция, която добавя едно изображение в текущата сесия.
     */
    void add(const String& pic)
    {
        sessions[currentSession].addPicture(pic);
    }
    /**
     * @brief Функция, която добавя подадена трансформация във вектора с трансформациите на всяко изображение в текущата сесия.
     */
    void addTransformation(const String& transform)
    {
        sessions[currentSession].addTransformation(transform);
    }
    /**
     * @brief Функция, която премахва последната трансформация от вектора с трансформациите на всяко изображение в текущата сесия, ако има такава(трансформация).
     */
    void removeTransformation()
    {
        sessions[currentSession].removeTransformation();
    }
    /**
     * @brief Функция, която създава файловете с новите изображения от текущата сесия
     */
    void saveSession()
    {
        sessions[currentSession].save();
    }
    /**
     * @brief Функция, която връща броя на сесиите в Workspace-a.
     */
    int getSessionsCount() const
    {
        return sessions.getSize();
    }
};