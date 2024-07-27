#include "GestorAlquiler.h"

//Constructor de la clase que se encarga de inicializar los atributos de la clase. Cargará en el
//vector dinámico Alquileres toda la información que contiene el fichero binario cuyo nombre es pasado
//por parámetro. Una vez cargado el fichero se cerrará.
GestorAlquiler::GestorAlquiler(cadena nomPpal)
{
    //inicializar los atributos de la clase
    numAlquiler = -1;
    tam = -1;

    abrirGestorAlquileres(nomPpal);
    if(!abrirGestorAlquileres(nomPpal))
    {
        cout << "\nError al abrir el fichero\n" << endl;
    }


}//fin del constructor GestGestorAlquiler(cadena nomPpal)

//Destructor de la clase que se encargará de abrir el fichero binario de Alquileres y guardar todos
//los datos del vector dinámico en el fichero. Una vez guardados se destruirá el vector dinámico y el
//fichero será cerrado.
GestorAlquiler::~GestorAlquiler()
{
    /*
    guardarGestorAlquileres();
    if(Alquileres != NULL)
    {
        delete [] Alquileres;
        Alquileres = NULL;
    }
    numAlquiler = -1;
    tam = -1;
    */
    fichero.open(nomFichero, ios::out|ios::trunc|ios::binary);
    fichero.write((char *) &Alquileres, sizeof(Alquileres));
    delete[] Alquileres;
    fichero.close();
}//fin del destructor ~GestorAlquiler()
//Devuelve el número de vehículos del vector dinámico.
int GestorAlquiler::getNumAlquiler()
{
    return numAlquiler;
}//fin del método getNumAlquiler()

//Añade al final del vector dinámico el Alquiler pasado por parámetro. Los datos del vector dinámico
//no están ordenados por ningún campo.
void GestorAlquiler::nuevo(TAlquiler A)
{
    bool estaAnadido = false;
    if(hayAlquileres())
    {
        aumentarArray();
        Alquileres[numAlquiler] = A;
        numAlquiler++;
        estaAnadido = true;
    }
    if(estaAnadido)
    {
        cout << "\nEl alquiler se ha añadido correctamente." << endl;
    }
    else
    {
        cout << "\nNo se ha podido añadir el alquiler." << endl;
    }

}//fin del método nuevo(TAlquiler A)

//Busca en el vector dinámico el Alquiler cuyo campo Dni (D) o Matricula (M) coincide con el parámetro
//Datos. El campo por donde buscar lo indica el parámetro DM. Si lo encuentra devuelve la posición en
//caso contrario -1
int GestorAlquiler::Buscar(cadena Datos, char DM)
{
    int pos = -1, i = 0;
    bool encontrado = false;
    if(DM == 'D')
    {
        while(i<numAlquiler && !encontrado)
        {
            if(strcmp(Datos, Alquileres[i].Dni)==0)
            {
                encontrado = true;
            }
            else
            {
                i++;
            }
        }
    }
    else
    {
        while(i<numAlquiler && !encontrado)
        {
            if(strcmp(Datos, Alquileres[i].Matricula)==0)
            {
                encontrado = true;
            }
            else
            {
                i++;
            }
        }
    }
    if(encontrado)
    {
        pos = i;
    }
    else
    {
        pos = -1;
    }
    return pos;
}//fin del método Buscar(cadena Datos, char DM)

//Devolverá el Alquiler del vector dinámico cuya posición es indicada por parámetro. Si la posición es
//incorrecta devolverá un alquiler con los campos cadena puestos a ”*” y los campos numéricos a 0.
TAlquiler GestorAlquiler::consultar(int posicion)
{
    TAlquiler alq ;
    if(posicion>=0 && posicion<numAlquiler)
    {
        alq = Alquileres[posicion];
    }
    else
    {
        strcpy(alq.Dni, "*");
        strcpy(alq.Matricula, "*");
        alq.KmsCir = 0;
        alq.NDiasCir = 0;
    }
    return alq;
}//fin del método consultar(int posicion)

//Modifica los datos del vector dinámico cuya posición es pasada por parámetro, con los datos del
//Alquiler A pasado por parámetro. Si la posición es correcta devuelve true, en caso contrario false.
bool GestorAlquiler::modificar(TAlquiler A, int posicion)
{
    bool estaModificado = false;
    if(posicion>=0 && posicion<numAlquiler)
    {
        Alquileres[posicion] = A;
        estaModificado = true;
    }
    return estaModificado;
}//fin del método modificar(TAlquiler A, int posicion)

//Elimina del vector dinámico el Alquiler cuya posición es pasada por parámetro. Si la posición es
//correcta devolverá true, en caso contrario false.
bool GestorAlquiler::eliminarPorPosicion(int posicion)
{
    bool estaEliminado = false;
    if(hayAlquileres())
    {
        if(posicion>=0 && posicion<numAlquiler)
        {
            for(int i = posicion;i<numAlquiler;i++)
            {
                Alquileres[i] = Alquileres[i+1];
            }
            numAlquiler--;
            decrementarArray();
            estaEliminado = true;
        }
    }
    return estaEliminado;
}//fin del método eliminarPorPosicion(int posicion)

bool GestorAlquiler::abrirGestorAlquileres(cadena nomFile)
{
    /*
    bool hayAlquiler = false;
    if(!hayAlquileres())
    {
        fichero.open(nomFile, ios::in | ios::out | ios::binary);
        if(!fichero.fail())
        {
            fichero.seekg(0, ios::beg);
            fichero.read((char*)&numAlquiler, sizeof(int));
            hayAlquiler = true;
        }
    }
    */
    bool hayAlquiler = false;
    fichero.open(nomFile, ios::in | ios::out | ios::binary);
    if(!fichero.fail())
    {
        fichero.seekg(0, ios::beg);
        fichero.read((char*)&numAlquiler, sizeof(int));
        fichero.seekg(0, ios::end);
        numAlquiler = (fichero.tellg()-sizeof(int))/sizeof(TAlquiler);
        tam = numAlquiler + INCREMENTO;
        Alquileres = new TAlquiler[tam];

        if(Alquileres != NULL)
        {
            fichero.seekg(sizeof(int), ios::beg);
            fichero.read((char*)Alquileres, numAlquiler * sizeof(TAlquiler));
            hayAlquiler = true;
        }
    }
    fichero.close();
    return hayAlquiler;
}//fin del método abrirGestorAlquileres(cadena nomFile)

bool GestorAlquiler::guardarGestorAlquileres()
{
    bool estaGuardada = false;
    if(hayAlquileres())
    {
        fichero.open(nomFichero, ios::binary | ios::out);
        if(!fichero.fail())
        {
            fichero.seekp(0, ios::beg);
            fichero.write((char*)&numAlquiler, sizeof(TAlquiler));
            fichero.write((char*)Alquileres, numAlquiler * sizeof(TAlquiler));
            estaGuardada = true;
            fichero.close();
        }
    }
    return estaGuardada;
}//fin del método guardarGestorAlquileres()

void GestorAlquiler::decrementarArray()
{
    if(tam-numAlquiler>=INCREMENTO && tam>INCREMENTO)
    {
        tam -= INCREMENTO;
        TAlquiler *aux = new TAlquiler[tam];
        for(int i=0;i<numAlquiler;i++)
        {
            aux[i] = Alquileres[i];
        }
        delete [] Alquileres;
        Alquileres = aux;
    }
}//fin del método decrementarArray()

void GestorAlquiler::aumentarArray()
{
    if(numAlquiler == tam)
    {
        tam += INCREMENTO;
        TAlquiler *aux = new TAlquiler[tam];
        for(int i = 0;i < numAlquiler;i++)
        {
            aux[i] = Alquileres[i];
        }
        delete [] Alquileres;
        Alquileres = aux;
    }
}//fin del método aumentarArray()

bool GestorAlquiler::hayAlquileres()
{
    bool hayAlquiler = false;
    if(numAlquiler != -1)
    {
        hayAlquiler = true;
    }
    return hayAlquiler;
}//fin del método hayAlquiler()
