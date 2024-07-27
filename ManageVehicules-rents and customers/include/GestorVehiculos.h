#ifndef GESTORVEHICULOS_H
#define GESTORVEHICULOS_H
#include "Comun.h"

struct Vehiculo{
    cadena modelo; //Modelo de veh�culo
    cadena matricula; //Matr�cula del veh�culo
    cadena provincia; //Provincia donde est� el veh�culo
    int kilometros; //cuentakil�metros del veh�culo
    float precio_km; //Precio de alquiler por kil�metro realizado
    cadena estado; //Estado del veh�culo, Libre, Ocupado, Pendiente de Revisi�n. Un veh�culo se puede
    //alquilar si su estado es Libre.
};
class GestorVehiculos{
        fstream ficheroPrincipal; //Fichero que contiene los veh�culos de la empresa.
        int numVehiculos; //N�mero de veh�culo en el vector din�mico.
        int tam; //Tama�o de la memoria din�mica del vector.
        Vehiculo *vehiculos; //Vector din�mico de Veh�culos
        cadena nomFichero; //Nombre del fichero binario que contiene los Veh�culos
        //Aumenta el tama�o del vector din�mico veh�culos en el n�mero de posiciones que indica la constante
        //INCREMENTO
        void aumentarArray();
        void decrementarArray();
        void ordenarVehiculos();
    public:
        //Constructor de la clase que se encarga de inicializar los atributos de la clase. Cargar� en el
        //vector din�mico veh�culos toda la informaci�n que contiene el fichero binario cuyo nombre es pasado
        //por par�metro. Una vez cargado el fichero se cerrar�.
        GestorVehiculos(cadena nomPpal);
        //Destructor de la clase que se encargar� de abrir el fichero binario de veh�culos y guardar todos los
        //datos del vector din�mico en el fichero. Una vez guardados se destruir� el vector din�mico y el
        //fichero ser� cerrado.
        ~GestorVehiculos();
        //Devuelve el n�mero de veh�culos del vector din�mico.
        int getNumVehiculos();
        //Muestra por pantalla todos los veh�culos del vector din�mico que verifiquen que la provincia del
        //veh�culo coincide con el valor del par�metro. Si el par�metro es �*� se mostrar� todos los
        //veh�culos.
        void mostrar(cadena provincia);
        //Devolver� el Veh�culo del vector din�mico cuya posici�n es indicada por par�metro. Si la posici�n es
        //incorrecta devolver� un veh�culo con la matricula puesta a �0�
        Vehiculo consultar(int posicion);
        //Busca en el vector el veh�culo cuya matricula coincide con la pasada por par�metro. Si lo encuentra
        //devolver� la posici�n y en caso contrario -1
        int consultar(cadena matricula);
        //Inserta en el vector din�mico el veh�culo v pasado por par�metro. La inserci�n debe verificar que
        //todos los veh�culos del vector din�mico est�n ordenados en funci�n de la provincia.
        //Si hay m�s veh�culos con la misma provincia que la del veh�culo insertado, �ste deber� quedar el
        //primero de todos ellos.
        void insertar(Vehiculo v);
        //Modifica los datos del vector din�mico cuya posici�n es pasada por par�metro, con los datos del
        //veh�culo v pasado por par�metro. Si la posici�n es incorrecta se mostrar� un mensaje de error.
        void modificar(Vehiculo v, int posicion);
        //Elimina del vector din�mico el veh�culo cuya posici�n es pasada por par�metro. Tras la eliminaci�n
        //los veh�culos almacenados en el vector din�mico deben estar ordenados por el campo provincia. Si la
        //posici�n es incorrecta se mostrar� un mensaje de error.
        void eliminarPorPosicion(int posicion);

        bool hayVehiculos();

        bool abrirGestorVehiculos(cadena nomFile);

        bool cerrarGestorVehiculos();

        bool guardarGestorVehiculos();

};

#endif // GESTORVEHICULOS_H
