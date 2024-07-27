#ifndef GESTORALQUILER_H
#define GESTORALQUILER_H
#include "Comun.h"


struct TAlquiler
{
    cadena Dni; //Dni del cliente
    cadena Matricula; //Matr�cula del veh�culo
    int KmsCir; //Kil�metros contratados para circular con el veh�culo.
    int NDiasCir; //N�mero de d�as contratados para circular con el veh�culo.
};
class GestorAlquiler
{
        fstream fichero; //Fichero que contiene los alquileres de la empresa.
        int numAlquiler; //N�mero de alquileres en el vector din�mico.
        int tam; //Tama�o de la memoria din�mica del vector.
        TAlquiler *Alquileres; //Vector din�mico de Alquileres.
        cadena nomFichero; //Nombre del fichero binario que contiene los Alquileres.
        //Aumenta el tama�o vector din�mico alquileres en el n�mero de posiciones que indica la constante
        //INCREMENTO
        void aumentarArray();
        void decrementarArray();
    public:
        //Constructor de la clase que se encarga de inicializar los atributos de la clase. Cargar� en el
        //vector din�mico Alquileres toda la informaci�n que contiene el fichero binario cuyo nombre es pasado
        //por par�metro. Una vez cargado el fichero se cerrar�.
        GestorAlquiler(cadena nomPpal);
        //Destructor de la clase que se encargar� de abrir el fichero binario de Alquileres y guardar todos
        //los datos del vector din�mico en el fichero. Una vez guardados se destruir� el vector din�mico y el
        //fichero ser� cerrado.
        ~GestorAlquiler();
        //Devuelve el n�mero de veh�culos del vector din�mico.
        int getNumAlquiler();
        //A�ade al final del vector din�mico el Alquiler pasado por par�metro. Los datos del vector din�mico
        //no est�n ordenados por ning�n campo.
        void nuevo(TAlquiler A);
        //Busca en el vector din�mico el Alquiler cuyo campo Dni (D) o Matricula (M) coincide con el par�metro
        //Datos. El campo por donde buscar lo indica el par�metro DM. Si lo encuentra devuelve la posici�n en
        //caso contrario -1
        int Buscar(cadena Datos, char DM);
        //Devolver� el Alquiler del vector din�mico cuya posici�n es indicada por par�metro. Si la posici�n es
        //incorrecta devolver� un alquiler con los campos cadena puestos a �*� y los campos num�ricos a 0.
        TAlquiler consultar(int posicion);
        //Modifica los datos del vector din�mico cuya posici�n es pasada por par�metro, con los datos del
        //Alquiler A pasado por par�metro. Si la posici�n es correcta devuelve true, en caso contrario false.
        bool modificar(TAlquiler A, int posicion);
        //Elimina del vector din�mico el Alquiler cuya posici�n es pasada por par�metro. Si la posici�n es
        //correcta devolver� true, en caso contrario false.
        bool eliminarPorPosicion(int posicion);

        bool abrirGestorAlquileres(cadena nomFile);

        bool guardarGestorAlquileres();

        bool hayAlquileres();
};
#endif // GESTORALQUILER_H
