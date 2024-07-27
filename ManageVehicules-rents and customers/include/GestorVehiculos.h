#ifndef GESTORVEHICULOS_H
#define GESTORVEHICULOS_H
#include "Comun.h"

struct Vehiculo{
    cadena modelo; //Modelo de vehículo
    cadena matricula; //Matrícula del vehículo
    cadena provincia; //Provincia donde está el vehículo
    int kilometros; //cuentakilómetros del vehículo
    float precio_km; //Precio de alquiler por kilómetro realizado
    cadena estado; //Estado del vehículo, Libre, Ocupado, Pendiente de Revisión. Un vehículo se puede
    //alquilar si su estado es Libre.
};
class GestorVehiculos{
        fstream ficheroPrincipal; //Fichero que contiene los vehículos de la empresa.
        int numVehiculos; //Número de vehículo en el vector dinámico.
        int tam; //Tamaño de la memoria dinámica del vector.
        Vehiculo *vehiculos; //Vector dinámico de Vehículos
        cadena nomFichero; //Nombre del fichero binario que contiene los Vehículos
        //Aumenta el tamaño del vector dinámico vehículos en el número de posiciones que indica la constante
        //INCREMENTO
        void aumentarArray();
        void decrementarArray();
        void ordenarVehiculos();
    public:
        //Constructor de la clase que se encarga de inicializar los atributos de la clase. Cargará en el
        //vector dinámico vehículos toda la información que contiene el fichero binario cuyo nombre es pasado
        //por parámetro. Una vez cargado el fichero se cerrará.
        GestorVehiculos(cadena nomPpal);
        //Destructor de la clase que se encargará de abrir el fichero binario de vehículos y guardar todos los
        //datos del vector dinámico en el fichero. Una vez guardados se destruirá el vector dinámico y el
        //fichero será cerrado.
        ~GestorVehiculos();
        //Devuelve el número de vehículos del vector dinámico.
        int getNumVehiculos();
        //Muestra por pantalla todos los vehículos del vector dinámico que verifiquen que la provincia del
        //vehículo coincide con el valor del parámetro. Si el parámetro es ”*” se mostrará todos los
        //vehículos.
        void mostrar(cadena provincia);
        //Devolverá el Vehículo del vector dinámico cuya posición es indicada por parámetro. Si la posición es
        //incorrecta devolverá un vehículo con la matricula puesta a ”0”
        Vehiculo consultar(int posicion);
        //Busca en el vector el vehículo cuya matricula coincide con la pasada por parámetro. Si lo encuentra
        //devolverá la posición y en caso contrario -1
        int consultar(cadena matricula);
        //Inserta en el vector dinámico el vehículo v pasado por parámetro. La inserción debe verificar que
        //todos los vehículos del vector dinámico están ordenados en función de la provincia.
        //Si hay más vehículos con la misma provincia que la del vehículo insertado, éste deberá quedar el
        //primero de todos ellos.
        void insertar(Vehiculo v);
        //Modifica los datos del vector dinámico cuya posición es pasada por parámetro, con los datos del
        //vehículo v pasado por parámetro. Si la posición es incorrecta se mostrará un mensaje de error.
        void modificar(Vehiculo v, int posicion);
        //Elimina del vector dinámico el vehículo cuya posición es pasada por parámetro. Tras la eliminación
        //los vehículos almacenados en el vector dinámico deben estar ordenados por el campo provincia. Si la
        //posición es incorrecta se mostrará un mensaje de error.
        void eliminarPorPosicion(int posicion);

        bool hayVehiculos();

        bool abrirGestorVehiculos(cadena nomFile);

        bool cerrarGestorVehiculos();

        bool guardarGestorVehiculos();

};

#endif // GESTORVEHICULOS_H
