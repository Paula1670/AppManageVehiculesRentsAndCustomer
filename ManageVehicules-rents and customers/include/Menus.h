#ifndef MENUS_H
#define MENUS_H

#include <windows.h>
#include "Comun.h"
#include "GestorClientes.h"
#include "GestorAlquiler.h"
#include "GestorVehiculos.h"

class Menus
{
    cadena nomFichGC = "ClientesSin.dat";
    cadena nomFichGV = "vehiculos.bin";
    cadena nomFichGA = "Alquileres.dat";
    public:
        Menus();
        virtual ~Menus();

        void menuPrincipal();
        void menuGestionClientes();
        void menuGestionVehiculos();
        void menuGestionAlquileres();
};

void textcolor(int color);

#endif // MENUS_H
