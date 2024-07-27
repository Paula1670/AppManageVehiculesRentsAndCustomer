#include "GestorVehiculos.h"

//Constructor de la clase que se encarga de inicializar los atributos de la clase. Cargará en el
//vector dinámico vehículos toda la información que contiene el fichero binario cuyo nombre es pasado
//por parámetro. Una vez cargado el fichero se cerrará.
GestorVehiculos::GestorVehiculos(cadena nomPpal)
{
    vehiculos = NULL;
    numVehiculos = -1;
    tam = -1;
    if(!abrirGestorVehiculos(nomPpal))
    {
        cout << "\nError al abrir el fichero\n" << endl;
    }
}//fin del constructor GestorVehiculos(cadena nomPpal)

//Destructor de la clase que se encargará de abrir el fichero binario de vehículos y guardar todos los
//datos del vector dinámico en el fichero. Una vez guardados se destruirá el vector dinámico y el
//fichero será cerrado.
GestorVehiculos::~GestorVehiculos()
{
    guardarGestorVehiculos();
    if(vehiculos != NULL)
    {
        delete [] vehiculos;
        vehiculos = NULL;
    }
    numVehiculos = -1;
    tam = -1;
}//fin del destructor ~GestorVehiculos()

//Devuelve el número de vehículos del vector dinámico.
int GestorVehiculos::getNumVehiculos()
{
    return numVehiculos;
}//fin del método getNumVehiculos()

//Muestra por pantalla todos los vehículos del vector dinámico que verifiquen que la provincia del
//vehículo coincide con el valor del parámetro. Si el parámetro es ”*” se mostrará todos los
//vehículos.
void GestorVehiculos::mostrar(cadena provincia)
{

}//fin del método mostrar(cadena provincia)

//Devolverá el Vehículo del vector dinámico cuya posición es indicada por parámetro. Si la posición es
//incorrecta devolverá un vehículo con la matricula puesta a ”0”
Vehiculo GestorVehiculos::consultar(int posicion)
{
    Vehiculo veh;
    if(posicion>=0 && posicion<numVehiculos)
    {
        veh = vehiculos[posicion];
    }
    else
    {
        strcpy(veh.matricula, 0);
    }
    return veh;

}//fin del método consultar(int posicion)

//Busca en el vector el vehículo cuya matricula coincide con la pasada por parámetro. Si lo encuentra
//devolverá la posición y en caso contrario -1
int GestorVehiculos::consultar(cadena matricula)
{
    int pos = -1, i = 0;
    bool encontrado = false;
    while(i<numVehiculos && !encontrado)
    {
        if(strcmp(matricula, vehiculos[i].matricula) == 0)
        {
            pos = i;
            encontrado = true;
        }
        else
        {
            i++;
        }
    }
    return pos;
}//fin del método consultar(cadena matricula)

//Inserta en el vector dinámico el vehículo v pasado por parámetro. La inserción debe verificar que
//todos los vehículos del vector dinámico están ordenados en función de la provincia.
//Si hay más vehículos con la misma provincia que la del vehículo insertado, éste deberá quedar el
//primero de todos ellos.
void GestorVehiculos::insertar(Vehiculo v)
{
    bool estaAnadido = false;
    if(hayVehiculos())
    {
        int pos = consultar(v.matricula);
        if(pos == -1)
        {
            aumentarArray();
            vehiculos[numVehiculos] = v;
            numVehiculos++;
            estaAnadido = true;
        }
        ordenarVehiculos();
    }
    if(estaAnadido)
    {
        cout << "\nEl vehículo se ha añadido correctamente." << endl;
    }
    else
    {
        cout << "\nNo se ha podido añadir el vehículo." << endl;
    }
}//fin del método insertar(Vehiculo v)
//Modifica los datos del vector dinámico cuya posición es pasada por parámetro, con los datos del
//vehículo v pasado por parámetro. Si la posición es incorrecta se mostrará un mensaje de error.
void GestorVehiculos::modificar(Vehiculo v, int posicion)
{
    if(posicion>=0 && posicion<numVehiculos)
    {
        vehiculos[posicion] = v;
        ordenarVehiculos();
        cout << "\nEl vehículo con matrícula " << v.matricula << " ha sido añadido." << endl;
    }
    else
    {
        cout << "\nEl vehículo no existe en nuestro sistema." << endl;
    }
}//fin del método modificar(Vehiculo v, int posicion)

//Elimina del vector dinámico el vehículo cuya posición es pasada por parámetro. Tras la eliminación
//los vehículos almacenados en el vector dinámico deben estar ordenados por el campo provincia. Si la
//posición es incorrecta se mostrará un mensaje de error.
void GestorVehiculos::eliminarPorPosicion(int posicion)
{
    if(hayVehiculos())
    {
        if(posicion>=0 && posicion<numVehiculos)
        {
            for(int i=posicion;i<numVehiculos;i++)
            {
                vehiculos[i]=vehiculos[i+1];
            }
            numVehiculos--;
            decrementarArray();
        }
        ordenarVehiculos();
    }
    else
    {
        cout << "\nLa posición que pide no es correcta." << endl;
    }
}//fin del método eliminarPorPosicion(int posicion)

//Aumenta el tamaño del vector dinámico vehículos en el número de posiciones que indica la constante
//INCREMENTO
void GestorVehiculos::aumentarArray()
{
    if(numVehiculos == tam)
    {
        tam += INCREMENTO;
        Vehiculo *aux = new Vehiculo[tam];
        for(int i = 0;i < numVehiculos;i++)
        {
            aux[i] = vehiculos[i];
        }
        delete [] vehiculos;
        vehiculos = aux;
    }
}//fin del método aumentarArray()

void GestorVehiculos::decrementarArray()
{
    if(tam-numVehiculos>=INCREMENTO && tam>INCREMENTO)
    {
        tam -= INCREMENTO;
        Vehiculo *aux = new Vehiculo[tam];
        for(int i=0;i<numVehiculos;i++)
        {
            aux[i] = vehiculos[i];
        }
        delete [] vehiculos;
        vehiculos = aux;
    }
}//fin del método decrementarArray()

bool GestorVehiculos::hayVehiculos()
{
    bool hayVehiculo = false;
    if(vehiculos != NULL)
    {
        hayVehiculo = true;
    }
    return hayVehiculo;
}//fin del método hayVehiculos()

bool GestorVehiculos::abrirGestorVehiculos(cadena nomFile)
{
    bool estaAbierto = false;
    ficheroPrincipal.open(nomFile, ios::in | ios::out | ios::binary);
    if(!ficheroPrincipal.fail())
    {
        ficheroPrincipal.seekg(0, ios::beg);
        ficheroPrincipal.seekg(0, ios::end);
        numVehiculos = ficheroPrincipal.tellg()/sizeof(Vehiculo);
        //ficheroPrincipal.read((char*)modelo, sizeof(cadena));
        //ficheroPrincipal.read((char*)matricula, sizeof(cadena));
        //ficheroPrincipal.read((char*)provincia, sizeof(cadena));
        //ficheroPrincipal.read((char*)&kilometros, sizeof(int));
        //ficheroPrincipal.read((char*)&precio_km, sizeof(float));
        //ficheroPrincipal.read((char*)estado, sizeof(cadena));

        tam = numVehiculos + INCREMENTO;
        vehiculos = new Vehiculo[tam];

        if(vehiculos != NULL)
        {
            ficheroPrincipal.seekg(0, ios::beg);
            ficheroPrincipal.read((char*)vehiculos, numVehiculos * sizeof(Vehiculo));
            estaAbierto = true;
        }
    }
    ficheroPrincipal.close();
    return estaAbierto;
}//fin del método abrirGestorVehiculos(cadena nomFile)

bool GestorVehiculos::cerrarGestorVehiculos()
{

}//fin del método cerrarGestorVehiculos()

bool GestorVehiculos::guardarGestorVehiculos()
{
    bool estaGuardado = false;
    if(hayVehiculos())
    {
        ficheroPrincipal.open(nomFichero,ios:: out | ios::trunc | ios::binary);
        if(!ficheroPrincipal.fail())
        {
            ficheroPrincipal.seekp(0, ios::beg);
            ficheroPrincipal.write((char*)vehiculos, numVehiculos * sizeof(Vehiculo));
            estaGuardado = true;
            ficheroPrincipal.close();
        }
    }
    return estaGuardado;
}//fin del método guardarGestorVehiculos()

void GestorVehiculos::ordenarVehiculos()
{
    Vehiculo aux;
    for(int i=0;i<numVehiculos;i++)
    {
        for(int j=i+1;j<numVehiculos;j++)
        {
            if(strcmp(vehiculos[i].provincia, vehiculos[j].provincia)>0)
            {
                aux = vehiculos[i];
                vehiculos[i] = vehiculos[j];
                vehiculos[j] = aux;
            }
            else
            {
                if(strcmp(vehiculos[i].provincia, vehiculos[j].provincia)==0)
                {
                    aux = vehiculos[i];
                    vehiculos[i] = vehiculos[j];
                    vehiculos[j] = aux;
                }
            }
        }
    }
}//fin del método ordenarVehiculos()
