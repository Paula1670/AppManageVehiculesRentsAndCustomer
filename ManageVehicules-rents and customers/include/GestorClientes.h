#ifndef GESTORCLIENTES_H
#define GESTORCLIENTES_H
#include "Comun.h"
struct TCliente
{
    cadena Dni; //Dni del cliente.
    cadena Nombre; //Nombre del cliente.
    cadena Provincia; //Provincia del cliente.
    int AcumuKm; //Acumulado de todos los km conducidos con vehículos de alquiler.
    float AcumuEuros; //Acumulado de todos los euros pagados por el alquiler de vehículos.
    bool VEnAlquiler; //Si el cliente tiene un vehículo alquilado será true, false en caso contrario.
};
class GestorClientes
{
        fstream fichero; //Fichero que almacena los clientes ordenados por el campo Dni.
        int numClientes; //Número de clientes que hay en el fichero.
    public:
        //Constructor de la clase que debe inicializar los atributos de la clase así como abrir el fichero
        //cuyo nombre es pasado por parámetro. El fichero quedará abierto mientras exista el objeto.
        GestorClientes(cadena NomFile);
        //Destructor de la clase que debe cerrar el fichero.
        ~GestorClientes();
        //Devuelve el número de clientes.
        int getNumClientes();
        //Mostrará por pantalla el cliente del fichero cuyo Dni coincide con el pasado por parámetro. Si
        //parámetro es un asterisco (*) se mostrarán todos los clientes del fichero. El método devolverá
        //true si ha mostrado al menos un cliente por pantalla, false en caso contrario.
        bool mostrar(cadena Dni);
        //Devolverá la posición del primer cliente del fichero cuyo Dni coincida con el pasado por parámetro.
        //Si no se encuentra ningún cliente devolverá -1.
        int buscar(cadena Dni);
        //Devolverá el cliente del fichero cuya posición es pasada por parámetro. Si la posición es incorrecta
        //devolverá un cliente con las cadenas inicializadas a ”*”.
        TCliente consultar(int Posicion);
        //Insertará el cliente C en el fichero de manera ordenada por el campo Dni.
        void insertar(TCliente C);
        //Guardará el cliente C en la Posición del fichero pasada por parámetro. Si la posición es incorrecta
        //devolverá false, en caso contrario true.
        bool modificar(TCliente C, int Posicion);
        //Eliminará el cliente cuya posición es indicada por parámetro. Si la posición es incorrecta devolverá
        //false en caso contrario true.
        bool eliminar(int Posicion);

        bool hayClientes();

        bool abrirGestorClientes(cadena nomFile);

        bool cerrarGestorClientes();
};
#endif // GESTORCLIENTES_H
