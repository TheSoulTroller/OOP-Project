#include "Interpreter.h"

int main()
{
    String cmd;
    Workspace workspace;
    do
    {
        cout << "Enter command: ";
        cin >> cmd;
        cin.clear();
        cin.ignore();
    } while (!Interpreter::interpretate(cmd, workspace));

    return 0;
}