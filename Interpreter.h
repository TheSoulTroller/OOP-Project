#pragma once
#include "Helpers/String.h"
#include "Workspace.h"

/**
 * @brief Интерпретатор, който получава стринг и по неговото съдържание избира коя операция да изпълни.
 * @details Основата функция е от тип bool (interpretate) и връща true единствено когато подадената операция е exit, тогава програмата спира.
 */
class Interpreter
{
private:
    /**
     * @brief Функция, която премахва невалидните имена на изображения
     */
    static void removeInvalid(Vector<String>& files)
    {
        for (int i = 1; i < files.getSize();)
        {
            if (!(files[i].validFileName()))
            {
                files.pop(i);
                i=1;
                continue;
            }
            i++;
        }
    }  
public:
    /**
     * @brief Основаната функция на класа, която определя какво ще се случи при подадена команда от потребителя.
     */
    static bool interpretate(String &cmd, Workspace &worksp)
    {
        if(cmd.length() == 0)
        {
            cout << "Command is empty." << endl;
            return false;
        }

        // Commands using only one word
        if (cmd == "exit")
        {
            cout << "Programm closed!" << endl;
            return true;
        }
        if(cmd == "monochrome")
        {
            if(worksp.getSessionsCount() > 0)
            {
                worksp.addTransformation(cmd);
                // worksp.addTransformation("monochrome");
            }
            else
            {
                cout << "No session opened." << endl;
            }
            return false;
        }
        if(cmd == "grayscale")
        {
            if(worksp.getSessionsCount() > 0)
            {
                worksp.addTransformation(cmd);
                // worksp.addTransformation("grayscale");
            }
            else
            {
                cout << "No session opened." << endl;
            }
            return false;
        }
        if(cmd == "negative")
        {
            if(worksp.getSessionsCount() > 0)
            {
                worksp.addTransformation(cmd);
                // worksp.addTransformation("negative");
            }
            else
            {
                cout << "No session opened." << endl;
            }
            return false;
        }
        if(cmd == "undo")
        {
            if(worksp.getSessionsCount() > 0)
            {
                worksp.removeTransformation();
            }
            else
            {
                cout << "There is no session to undo." << endl;
            }
            return false;
        }
        if(cmd == "save")
        {
            if(worksp.getSessionsCount() == 0)
            {
                cout << "There is no session to save!" << endl;
                return false;
            }
            worksp.saveSession();
            return false;
        }
        if(cmd == "help")
        {
            cout << "exit - closes the programm" << endl;
            cout << "help - shows this window with commands" << endl;
            cout << "load <picture> [picture] - creates a session with unique ID and loads the file/files" << endl;
            cout << "add <picture> - adds a picture to the current session" << endl;
            cout << "monochrome - makes the pictures in the current session black and white" << endl;
            cout << "grayscale - makes the pictures in the current session grayscale" << endl;
            cout << "negative - makes the pictures in the current session negative colours" << endl;
            cout << "rotate <left/right> - rotates the pictures in the current session" << endl;
            cout << "flip <vertical/horizontal> - flips the pictures in the current session" << endl;
            cout << "undo - removes the last transformation" << endl;
            cout << "save - saves the file/files from the current session" << endl;
            cout << "switch <index> - switches between sessions" << endl;
            cout << "session info - show information about the current session" << endl;            
            return false;
        }

        // Commands using two or more words
        Vector<String> words = cmd.split();
        if(words.isEmpty())
        {
            cout << "Invalid command!" << endl;
            return false;
        }

        if(words[0] == "switch")
        {
            worksp.switchSession(atoi(words[1].c_str()));
            return false;
        }

        if(words[0] == "load")
        {
            Interpreter::removeInvalid(words);
            words.removeDuplicates();
            worksp.load(words);
            return false;
        }

        if(words[0] == "add")
        {
            if(worksp.getSessionsCount() == 0)
            {
                cout << "There is no session to add pictures to!" << endl;
                return false;
            }
            if(!(words[1].validFileName()))
            {
                cout << "Invalid file name!" << endl;
                return false;
            }
            String name = words[1];
            name-=4;
            Vector<String> loadedFiles = worksp.getSessionNames();
            for(int i = 0; i < loadedFiles.getSize(); i++)
            {
                if(loadedFiles[i] == name)
                {
                    cout << "File already loaded!" << endl;
                    return false;
                }
            }
            worksp.add(words[1]);
            cout << "File added!" << endl;
            return false;
        }

        if(words[0] == "flip")
        {
            if(words[1] == "vertical")
            {
                if(worksp.getSessionsCount() > 0)
                {
                    worksp.addTransformation(words[1]);
                    // worksp.addTransformation("vertical");
                }
                else
                {
                    cout << "There is no session to flip!" << endl;
                }
            }
            else if(words[1] == "horizontal")
            {
                if(worksp.getSessionsCount() > 0)
                {
                    worksp.addTransformation(words[1]);
                    // worksp.addTransformation("horizontal");
                }
                else
                {
                    cout << "There is no session to flip!" << endl;
                }
            }
            else
            {
                cout << "Unknown word in command flip!" << endl;
            }
            return false;
        }

        if(words[0] == "rotate")
        {
            if(words[1] == "left")
            {
                if(worksp.getSessionsCount() > 0)
                {
                    worksp.addTransformation(words[1]);
                    // worksp.addTransformation("left");
                }
                else
                {
                    cout << "There is no session to rotate!" << endl;
                }
            }
            else if(words[1] == "right")
            {
                if(worksp.getSessionsCount() > 0)
                {
                    worksp.addTransformation(words[1]);
                    // worksp.addTransformation("right");
                }
                else
                {
                    cout << "There is no session to rotate!" << endl;
                }

            }
            else
            {
                cout << "Unknown word in command rotate!" << endl;
            }
            return false;
        }  

        if(words[0] == "session" && words[1] == "info")
        {
            if(worksp.getSessionsCount() > 0)
            {
                worksp.getSessionInfo();
            }
            else
            {
                cout << "There is no session to show information about!" << endl;
            }
            return false;
        }

        cout << "Unknown command!" << endl;
        return false;
    }
};
