#ifndef GESTORALQUILER_H
#define GESTORALQUILER_H
#include "Comun.h"


struct TAlquiler
{
    cadena Dni; //Dni del cliente
    cadena Matricula; //Matrícula del vehículo
    int KmsCir; //Kilómetros contratados para circular con el vehículo.
    int NDiasCir; //Número de días contratados para circular con el vehículo.
};
class GestorAlquiler
{
        fstream fichero; //Fichero que contiene los alquileres de la empresa.
        int numAlquiler; //Número de alquileres en el vector dinámico.
        int tam; //Tamaño de la memoria dinámica del vector.
        TAlquiler *Alquileres; //Vector dinámico de Alquileres.
        cadena nomFichero; //Nombre del fichero binario que contiene los Alquileres.
        //Aumenta el tamaño vector dinámico alquileres en el número de posiciones que indica la constante
        //INCREMENTO
        void aumentarArray();
        void decrementarArray();
    public:
        //Constructor de la clase que se encarga de inicializar los atributos de la clase. Cargará en el
        //vector dinámico Alquileres toda la información que contiene el fichero binario cuyo nombre es pasado
        //por parámetro. Una vez cargado el fichero se cerrará.
        GestorAlquiler(cadena nomPpal);
        //Destructor de la clase que se encargará de abrir el fichero binario de Alquileres y guardar todos
        //los datos del vector dinámico en el fichero. Una vez guardados se destruirá el vector dinámico y el
        //fichero será cerrado.
        ~GestorAlquiler();
        //Devuelve el número de vehículos del vector dinámico.
        int getNumAlquiler();
        //Añade al final del vector dinámico el Alquiler pasado por parámetro. Los datos del vector dinámico
        //no están ordenados por ningún campo.
        void nuevo(TAlquiler A);
        //Busca en el vector dinámico el Alquiler cuyo campo Dni (D) o Matricula (M) coincide con el parámetro
        //Datos. El campo por donde buscar lo indica el parámetro DM. Si lo encuentra devuelve la posición en
        //caso contrario -1
        int Buscar(cadena Datos, char DM);
        //Devolverá el Alquiler del vector dinámico cuya posición es indicada por parámetro. Si la posición es
        //incorrecta devolverá un alquiler con los campos cadena puestos a ”*” y los campos numéricos a 0.
        TAlquiler consultar(int posicion);
        //Modifica los datos del vector dinámico cuya posición es pasada por parámetro, con los datos del
        //Alquiler A pasado por parámetro. Si la posición es correcta devuelve true, en caso contrario false.
        bool modificar(TAlquiler A, int posicion);
        //Elimina del vector dinámico el Alquiler cuya posición es pasada por parámetro. Si la posición es
        //correcta devolverá true, en caso contrario false.
        bool eliminarPorPosicion(int posicion);

        bool abrirGestorAlquileres(cadena nomFile);

        bool guardarGestorAlquileres();

        bool hayAlquileres();
};
#endif // GESTORALQUILER_H
