// clearConsole.hpp 

#pragma once

#include <stdlib.h>
#include <windows.h>
using namespace std;

void clearConsole() {                       //fonction qui clear la console :                             
    system("cls");                          // Fonctionne pour :                               
    system("clear");                        // Linux, MacOS, Windows
}