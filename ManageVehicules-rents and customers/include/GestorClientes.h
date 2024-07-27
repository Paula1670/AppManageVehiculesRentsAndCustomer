#ifndef GESTORCLIENTES_H
#define GESTORCLIENTES_H
#include "Comun.h"
struct TCliente
{
    cadena Dni; //Dni del cliente.
    cadena Nombre; //Nombre del cliente.
    cadena Provincia; //Provincia del cliente.
    int AcumuKm; //Acumulado de todos los km conducidos con veh�culos de alquiler.
    float AcumuEuros; //Acumulado de todos los euros pagados por el alquiler de veh�culos.
    bool VEnAlquiler; //Si el cliente tiene un veh�culo alquilado ser� true, false en caso contrario.
};
class GestorClientes
{
        fstream fichero; //Fichero que almacena los clientes ordenados por el campo Dni.
        int numClientes; //N�mero de clientes que hay en el fichero.
    public:
        //Constructor de la clase que debe inicializar los atributos de la clase as� como abrir el fichero
        //cuyo nombre es pasado por par�metro. El fichero quedar� abierto mientras exista el objeto.
        GestorClientes(cadena NomFile);
        //Destructor de la clase que debe cerrar el fichero.
        ~GestorClientes();
        //Devuelve el n�mero de clientes.
        int getNumClientes();
        //Mostrar� por pantalla el cliente del fichero cuyo Dni coincide con el pasado por par�metro. Si
        //par�metro es un asterisco (*) se mostrar�n todos los clientes del fichero. El m�todo devolver�
        //true si ha mostrado al menos un cliente por pantalla, false en caso contrario.
        bool mostrar(cadena Dni);
        //Devolver� la posici�n del primer cliente del fichero cuyo Dni coincida con el pasado por par�metro.
        //Si no se encuentra ning�n cliente devolver� -1.
        int buscar(cadena Dni);
        //Devolver� el cliente del fichero cuya posici�n es pasada por par�metro. Si la posici�n es incorrecta
        //devolver� un cliente con las cadenas inicializadas a �*�.
        TCliente consultar(int Posicion);
        //Insertar� el cliente C en el fichero de manera ordenada por el campo Dni.
        void insertar(TCliente C);
        //Guardar� el cliente C en la Posici�n del fichero pasada por par�metro. Si la posici�n es incorrecta
        //devolver� false, en caso contrario true.
        bool modificar(TCliente C, int Posicion);
        //Eliminar� el cliente cuya posici�n es indicada por par�metro. Si la posici�n es incorrecta devolver�
        //false en caso contrario true.
        bool eliminar(int Posicion);

        bool hayClientes();

        bool abrirGestorClientes(cadena nomFile);

        bool cerrarGestorClientes();
};
#endif // GESTORCLIENTES_H
