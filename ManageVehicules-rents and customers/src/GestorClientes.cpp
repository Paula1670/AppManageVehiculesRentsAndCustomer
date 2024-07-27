#include "GestorClientes.h"
#include "Menus.h"
#include <cstdlib>
#include <cstdio>
#include <stdlib.h>


//Constructor de la clase que debe inicializar los atributos de la clase así como abrir el fichero
//cuyo nombre es pasado por parámetro. El fichero quedará abierto mientras exista el objeto.
GestorClientes::GestorClientes(cadena NomFile){

    //inicializar los atributos de la clase
    numClientes = -1;
    //abrir el fichero cuyo nombre es pasado por parámetro

    abrirGestorClientes(NomFile);
    if(!abrirGestorClientes(NomFile))
    {
        cout << "\nError al abrir el fichero\n" << endl;
    }

}//fin del constructor GestorClientes(cadena NomFile)

//Destructor de la clase que debe cerrar el fichero.
GestorClientes::~GestorClientes()
{
    //dtor
    fichero.close();
    fichero.clear();
    numClientes = -1;

}//fin del destructor ~GestorClientes()

//Devuelve el número de clientes.
int GestorClientes::getNumClientes(){
    return numClientes;
}//fin de getNumClientes()

bool GestorClientes::abrirGestorClientes(cadena nomFile)
{
    bool hayCliente = false;
    if(!hayClientes())
    {
        fichero.open(nomFile, ios::in | ios::out | ios::binary);
        if(!fichero.fail())
        {
            fichero.seekg(0, ios::beg);
            fichero.read((char*)&numClientes, sizeof(int));
            hayCliente = true;
        }
    }
    else
    {
        hayCliente;
    }
    return hayCliente;
}

//  Devuelve true si hay clientes.
bool GestorClientes::hayClientes()
{
    bool hayCliente = false;
    if(numClientes !=-1)
    {
        hayCliente = true;
    }
    else
    {
        hayCliente = false;
    }
    return hayCliente;
}//fin del método hayClientes

//Mostrará por pantalla el cliente del fichero cuyo Dni coincide con el pasado por parámetro. Si
//parámetro es un asterisco (*) se mostrarán todos los clientes del fichero. El método devolverá
//true si ha mostrado al menos un cliente por pantalla, false en caso contrario.
bool GestorClientes::mostrar(cadena Dni){
    bool mostrado = false;

    return mostrado;
}

//Devolverá la posición del primer cliente del fichero cuyo Dni coincida con el pasado por parámetro.
//Si no se encuentra ningún cliente devolverá -1.
int GestorClientes::buscar(cadena Dni){
    int pos = -1, i = 0;
    TCliente cli;
    bool encontrado = false;
    if(hayClientes()){
        fichero.seekg(sizeof(numClientes), ios::beg);
        while((i<numClientes) && (!encontrado)){
            fichero.read((char*)&cli, sizeof(TCliente));
            if(strcmp(Dni, cli.Dni)==0){
                pos = i;
                encontrado = true;
            }
            else{
                i++;
            }
        }
    }
    if(encontrado){
        pos;
    }
    else{
        pos = -1;
    }
    return pos;
}//fin del método buscar

//Devolverá el cliente del fichero cuya posición es pasada por parámetro. Si la posición es incorrecta
//devolverá un cliente con las cadenas inicializadas a ”*”.
TCliente GestorClientes::consultar(int Posicion){
    TCliente cli;
    if(hayClientes()){
        fichero.seekg(sizeof(int) + Posicion*sizeof(TCliente), ios::beg);
        fichero.read((char*)&cli, sizeof(TCliente));
        if(fichero.fail()){
            cout << "Error de fichero" << endl;
            strcpy(cli.Dni, "*");
            strcpy(cli.Nombre, "*");
            strcpy(cli.Provincia, "*");
            cli.AcumuKm = 0;
            cli.AcumuEuros = 0;
            cli.VEnAlquiler = false;
        }
    }
    return cli;
}//fin del método consultar

//Insertará el cliente C en el fichero de manera ordenada por el campo Dni.
void GestorClientes::insertar(TCliente C){
    bool insertado = false;
    bool encontrado = false;
    TCliente cli;
    int posIns = sizeof(int);
    if(buscar(C.Dni)!=-1){
        insertado = false;
    }
    else{
        /*
        tamano =sizeof(int) + sizeof(TCliente) * numClientes;
        fichero.clear();
        fichero.seekp(tamano, ios::beg);
        fichero.write((char*)&C, sizeof(TCliente));

        numClientes = getNumClientes();
        numClientes++;
        fichero.seekp(0, ios::beg);
        fichero.write((char*)&numClientes, sizeof(int));
        */
        fichero.clear();
        fichero.seekg(sizeof(int), ios::beg);
        while(fichero.read((char*)&cli, sizeof(TCliente)) && !fichero.eof())
        {
            if(strcmp(cli.Dni, C.Dni)>0)
            {
                break;
            }
            posIns += sizeof(TCliente);
        }
        fichero.seekg(0, ios::end);
        int finFich = fichero.tellg();
        for(int i = finFich; i>posIns;i-= sizeof(TCliente))
        {
            fichero.seekg(i - sizeof(TCliente));
            fichero.read((char*) &cli, sizeof(TCliente));
            fichero.seekp(i);
            fichero.write((char*) &cli, sizeof(TCliente));
        }
        fichero.seekp(posIns);
        fichero.write((char*) &C, sizeof(TCliente));

        numClientes++;
        fichero.seekp(0, ios::beg);
        fichero.write((char*) &numClientes, sizeof(int));
        fichero.seekg(0, ios::beg);
        insertado = true;
    }
    if(insertado){
        cout << "\tCliente insertado" << endl;
    }
    else{
        cout << "\tCliente no insertado, ya existe en el sistema." << endl;
    }
}//fin del método insertar

//Guardará el cliente C en la Posición del fichero pasada por parámetro. Si la posición es incorrecta
//devolverá false, en caso contrario true.
bool GestorClientes::modificar(TCliente C, int Posicion)
{
    bool modificado = false;
    if(Posicion < 0 || Posicion > numClientes)
    {
        modificado;
    }
    else
    {
        fichero.seekp(sizeof(int) + sizeof(TCliente) * Posicion, ios::beg);
        fichero.write((char*)&C, sizeof(TCliente));
        modificado = true;
    }
    return modificado;
}//fin del método modificar

//Eliminará el cliente cuya posición es indicada por parámetro. Si la posición es incorrecta devolverá
//false en caso contrario true.
bool GestorClientes::eliminar(int Posicion)
{
    bool estaEliminado = false;
    TCliente cli;
    /*
    if(Posicion == -1 || (Posicion < 0 || Posicion > numClientes))
    {
        estaEliminado;
    }
    else
    {
        if(fichero.is_open())
        {

            fichero.seekg(0, ios::beg);
            fichero.read((char*)&numClientes, sizeof(int));
            for(int i = Posicion;i < numClientes; i++)
            {
                fichero.seekg((sizeof(TCliente)*(i+1)), ios::beg);
                fichero.read((char*)&cli, sizeof(TCliente));
                fichero.seekg((sizeof(TCliente)*(i)), ios::beg);
                fichero.write((char*)&cli,sizeof(TCliente));
            }

            numClientes--;
            fichero.seekp(0, ios::beg);
            fichero.write((char*)&numClientes, sizeof(int));
            estaEliminado = true;
        }
    }
    return estaEliminado;
    */
    if(fichero.fail())
    {
        cout << "\tErro al abrir el fichero." << endl;
        exit(EXIT_FAILURE);
    }
    if(Posicion < 0 || Posicion >= numClientes)
    {
        estaEliminado;
    }
    else
    {
        fichero.seekp(sizeof(int) + Posicion*sizeof(TCliente), ios::beg);

        for (int i = Posicion; i < numClientes; i++)
        {
            fichero.seekg(sizeof(int) + (i+1) * sizeof(TCliente), ios::beg);
            fichero.read((char*)&cli, sizeof(TCliente));
            fichero.seekp(sizeof(int) + i * sizeof(TCliente), ios::beg);
            fichero.write((char*)&cli, sizeof(TCliente));
        }

        numClientes--;
        fichero.seekp(0, ios::beg);
        fichero.write((char*) &numClientes, sizeof(int));
        fichero.seekg(0, ios::beg);
        estaEliminado =true;
    }

    return estaEliminado;

}//fin del método eliminar(int Posicion)
