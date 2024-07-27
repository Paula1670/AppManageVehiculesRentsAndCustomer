#include "GestorVehiculos.h"

//Constructor de la clase que se encarga de inicializar los atributos de la clase. Cargar� en el
//vector din�mico veh�culos toda la informaci�n que contiene el fichero binario cuyo nombre es pasado
//por par�metro. Una vez cargado el fichero se cerrar�.
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

//Destructor de la clase que se encargar� de abrir el fichero binario de veh�culos y guardar todos los
//datos del vector din�mico en el fichero. Una vez guardados se destruir� el vector din�mico y el
//fichero ser� cerrado.
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

//Devuelve el n�mero de veh�culos del vector din�mico.
int GestorVehiculos::getNumVehiculos()
{
    return numVehiculos;
}//fin del m�todo getNumVehiculos()

//Muestra por pantalla todos los veh�culos del vector din�mico que verifiquen que la provincia del
//veh�culo coincide con el valor del par�metro. Si el par�metro es �*� se mostrar� todos los
//veh�culos.
void GestorVehiculos::mostrar(cadena provincia)
{

}//fin del m�todo mostrar(cadena provincia)

//Devolver� el Veh�culo del vector din�mico cuya posici�n es indicada por par�metro. Si la posici�n es
//incorrecta devolver� un veh�culo con la matricula puesta a �0�
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

}//fin del m�todo consultar(int posicion)

//Busca en el vector el veh�culo cuya matricula coincide con la pasada por par�metro. Si lo encuentra
//devolver� la posici�n y en caso contrario -1
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
}//fin del m�todo consultar(cadena matricula)

//Inserta en el vector din�mico el veh�culo v pasado por par�metro. La inserci�n debe verificar que
//todos los veh�culos del vector din�mico est�n ordenados en funci�n de la provincia.
//Si hay m�s veh�culos con la misma provincia que la del veh�culo insertado, �ste deber� quedar el
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
        cout << "\nEl veh�culo se ha a�adido correctamente." << endl;
    }
    else
    {
        cout << "\nNo se ha podido a�adir el veh�culo." << endl;
    }
}//fin del m�todo insertar(Vehiculo v)
//Modifica los datos del vector din�mico cuya posici�n es pasada por par�metro, con los datos del
//veh�culo v pasado por par�metro. Si la posici�n es incorrecta se mostrar� un mensaje de error.
void GestorVehiculos::modificar(Vehiculo v, int posicion)
{
    if(posicion>=0 && posicion<numVehiculos)
    {
        vehiculos[posicion] = v;
        ordenarVehiculos();
        cout << "\nEl veh�culo con matr�cula " << v.matricula << " ha sido a�adido." << endl;
    }
    else
    {
        cout << "\nEl veh�culo no existe en nuestro sistema." << endl;
    }
}//fin del m�todo modificar(Vehiculo v, int posicion)

//Elimina del vector din�mico el veh�culo cuya posici�n es pasada por par�metro. Tras la eliminaci�n
//los veh�culos almacenados en el vector din�mico deben estar ordenados por el campo provincia. Si la
//posici�n es incorrecta se mostrar� un mensaje de error.
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
        cout << "\nLa posici�n que pide no es correcta." << endl;
    }
}//fin del m�todo eliminarPorPosicion(int posicion)

//Aumenta el tama�o del vector din�mico veh�culos en el n�mero de posiciones que indica la constante
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
}//fin del m�todo aumentarArray()

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
}//fin del m�todo decrementarArray()

bool GestorVehiculos::hayVehiculos()
{
    bool hayVehiculo = false;
    if(vehiculos != NULL)
    {
        hayVehiculo = true;
    }
    return hayVehiculo;
}//fin del m�todo hayVehiculos()

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
}//fin del m�todo abrirGestorVehiculos(cadena nomFile)

bool GestorVehiculos::cerrarGestorVehiculos()
{

}//fin del m�todo cerrarGestorVehiculos()

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
}//fin del m�todo guardarGestorVehiculos()

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
}//fin del m�todo ordenarVehiculos()
