#include <iostream>
#include <locale.h>
#include <windows.h>
#include "Menus.h"
#include "GestorClientes.h"
#include "GestorAlquiler.h"
#include "GestorVehiculos.h"

using namespace std;

int main()
{
    system("mode con: cols=150");
    setlocale(LC_ALL, "");
    Menus menu;
    menu.menuPrincipal();
    pause;
    return 0;
}
