#include "GestorAlquiler.h"

//Constructor de la clase que se encarga de inicializar los atributos de la clase. Cargar� en el
//vector din�mico Alquileres toda la informaci�n que contiene el fichero binario cuyo nombre es pasado
//por par�metro. Una vez cargado el fichero se cerrar�.
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

//Destructor de la clase que se encargar� de abrir el fichero binario de Alquileres y guardar todos
//los datos del vector din�mico en el fichero. Una vez guardados se destruir� el vector din�mico y el
//fichero ser� cerrado.
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
//Devuelve el n�mero de veh�culos del vector din�mico.
int GestorAlquiler::getNumAlquiler()
{
    return numAlquiler;
}//fin del m�todo getNumAlquiler()

//A�ade al final del vector din�mico el Alquiler pasado por par�metro. Los datos del vector din�mico
//no est�n ordenados por ning�n campo.
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
        cout << "\nEl alquiler se ha a�adido correctamente." << endl;
    }
    else
    {
        cout << "\nNo se ha podido a�adir el alquiler." << endl;
    }

}//fin del m�todo nuevo(TAlquiler A)

//Busca en el vector din�mico el Alquiler cuyo campo Dni (D) o Matricula (M) coincide con el par�metro
//Datos. El campo por donde buscar lo indica el par�metro DM. Si lo encuentra devuelve la posici�n en
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
}//fin del m�todo Buscar(cadena Datos, char DM)

//Devolver� el Alquiler del vector din�mico cuya posici�n es indicada por par�metro. Si la posici�n es
//incorrecta devolver� un alquiler con los campos cadena puestos a �*� y los campos num�ricos a 0.
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
}//fin del m�todo consultar(int posicion)

//Modifica los datos del vector din�mico cuya posici�n es pasada por par�metro, con los datos del
//Alquiler A pasado por par�metro. Si la posici�n es correcta devuelve true, en caso contrario false.
bool GestorAlquiler::modificar(TAlquiler A, int posicion)
{
    bool estaModificado = false;
    if(posicion>=0 && posicion<numAlquiler)
    {
        Alquileres[posicion] = A;
        estaModificado = true;
    }
    return estaModificado;
}//fin del m�todo modificar(TAlquiler A, int posicion)

//Elimina del vector din�mico el Alquiler cuya posici�n es pasada por par�metro. Si la posici�n es
//correcta devolver� true, en caso contrario false.
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
}//fin del m�todo eliminarPorPosicion(int posicion)

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
}//fin del m�todo abrirGestorAlquileres(cadena nomFile)

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
}//fin del m�todo guardarGestorAlquileres()

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
}//fin del m�todo decrementarArray()

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
}//fin del m�todo aumentarArray()

bool GestorAlquiler::hayAlquileres()
{
    bool hayAlquiler = false;
    if(numAlquiler != -1)
    {
        hayAlquiler = true;
    }
    return hayAlquiler;
}//fin del m�todo hayAlquiler()
