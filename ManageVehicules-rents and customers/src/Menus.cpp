#include "Menus.h"
#include "Comun.h"
#include "GestorClientes.h"
#include "GestorAlquiler.h"
#include "GestorVehiculos.h"
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <iomanip>
#include <cstdlib>

Menus::Menus()
{
    //ctor
}

Menus::~Menus()
{
    //dtor
}

//desarrollamos nuestro menú principal
void Menus::menuPrincipal(){
    int opcion;
    do{
        system("cls");
        cout << endl;
        cout << "\t----- Menu Principal -----" << endl;
        cout << "\t1.- Gestion de Clientes." << endl;
        cout << "\t2.- Gestion de Vehiculos." << endl;
        cout << "\t3.- Gestion de Alquileres." << endl;
        cout << "\t0.- Salir." << endl << endl;
        cout << "\t .- Indique una opcion: ";
        cin >> opcion;

        switch(opcion){
            case 1:
                menuGestionClientes();
                break;
            case 2:
                menuGestionVehiculos();
                break;
            case 3:
                menuGestionAlquileres();
                break;
            case 0:

                break;
            default:
                cout << "\n\t\t\tOpción equivocada, inténtelo de nuevo." << endl << endl;
                system("pause");
                break;
        }
        cout << endl;
    }while(opcion !=0);
}//fin de menuPrincipal

//desarrollamos el menú de gestión de clientes
void Menus::menuGestionClientes(){
    GestorClientes gestorCli(nomFichGC);
    int opcion;
    //char opc;

    do{
        system("cls");
        cout << endl;
        cout << "\t----- Menu Gestión de Clientes -----" << endl;
        cout << "\t1.- Consulta de clientes." << endl;
        cout << "\t2.- Buscar un cliente." << endl;
        cout << "\t3.- Nuevo cliente." << endl;
        cout << "\t4.- Modificar cliente." << endl;
        cout << "\t5.- Eliminar un cliente." << endl;
        cout << "\t0.- Salir." << endl << endl;
        cout << "\t .- Indique una opcion: ";
        cin >> opcion;

        switch(opcion)
        {
            case 1:
            {
                //consulta de clientes
                TCliente cli;
                cadena dni;
                cout << endl;
                fflush(stdin);
                cout << "\tIntroduce el Dni a mostrar: ";
                cin.getline(dni, 90, '\n');

                if(strcmp(dni, "*") == 0)
                {
                    cout << endl;
                    cout << left << setw(15) << "DNI" << setw(35) << "NOMBRE" << setw(20) << "PROVINCIA" << setw(15) << "ACUMU KM" << setw(15) << "ACUMU Euros" << setw(15) << "VEHICULO" << endl;
                    cout << "************************************************************************************************************" << endl;

                    for(int i=0;i<gestorCli.getNumClientes();i++)
                    {
                        if(i%2==0)
                        {
                            textcolor(1);
                        }
                        else
                        {
                            textcolor(2);
                        }
                        cli = gestorCli.consultar(i);
                        cout << left << setw(15) << cli.Dni << setw(35) << cli.Nombre << setw(20) << cli.Provincia << setw(15) << cli.AcumuKm << setw(15) << cli.AcumuEuros << setw(15) << (cli.VEnAlquiler?"Si":"NO") << endl;
                    }
                    textcolor(7);
                }
                else if(gestorCli.buscar(dni)==-1)
                {
                    cout << "\n\tCliente no encontrado" << endl;
                }
                else
                {
                    cli = gestorCli.consultar(gestorCli.buscar(dni));
                    cout << endl;
                    cout << left << setw(15) << "DNI" << setw(35) << "NOMBRE" << setw(20) << "PROVINCIA" << setw(15) << "ACUMU KM" << setw(15) << "ACUMU Euros" << setw(15) << "VEHICULO" << endl;
                    cout << "************************************************************************************************************" << endl;
                    cout << left << setw(15) << cli.Dni << setw(35) << cli.Nombre << setw(20) << cli.Provincia << setw(15) << cli.AcumuKm << setw(15) << cli.AcumuEuros << setw(15) << (cli.VEnAlquiler?"Si":"NO") << endl;
                }
                pause;
                break;
            }

            case 2:
            {
                //buscar un cliente
                TCliente cli;
                cadena dni;
                cout << endl;
                fflush(stdin);
                cout << "\tIntroduce el Dni a mostrar: ";
                cin.getline(dni, 90, '\n');

                if(gestorCli.buscar(dni)==-1)
                {
                    cout << "\n\tCliente no encontrado" << endl;
                }
                else
                {
                    cli = gestorCli.consultar(gestorCli.buscar(dni));
                    cout << endl;
                    cout << left << setw(15) << "DNI" << setw(35) << "NOMBRE" << setw(20) << "PROVINCIA" << setw(15) << "ACUMU KM" << setw(15) << "ACUMU Euros" << setw(15) << "VEHICULO" << endl;
                    cout << "************************************************************************************************************" << endl;
                    cout << left << setw(15) << cli.Dni << setw(35) << cli.Nombre << setw(20) << cli.Provincia << setw(15) << cli.AcumuKm << setw(15) << cli.AcumuEuros << setw(15) << (cli.VEnAlquiler?"Si":"NO") << endl;
                }
                pause;
                break;
            }

            case 3:
            {
                //nuevo cliente
                TCliente cli;
                cout << endl;
                fflush(stdin);
                cout << "\tDime el DNI del nuevo cliente: ";
                cin.getline(cli.Dni, 90, '\n');
                cout << "\tDime el nombre del nuevo cliente: ";
                cin.getline(cli.Nombre, 90, '\n');
                cout << "\tDime la provincia del nuevo cliente: ";
                cin.getline(cli.Provincia, 90, '\n');
                cli.AcumuEuros = 0;
                cli.AcumuKm = 0;
                cli.VEnAlquiler = false;
                gestorCli.insertar(cli);
                pause;
                break;
            }

            case 4:
            {
                //modificar cliente
                TCliente cli;
                int pos;
                cadena dni, nom, pro;
                char opc;
                cout << endl;
                fflush(stdin);
                cout << "\tDime el DNI del cliente que quieres modificar: ";
                cin.getline(dni, 90, '\n');
                pos = gestorCli.buscar(dni);
                if(pos == -1)
                {
                    cout << "\tCliente no existe en el sistema." << endl;
                }
                else
                {
                    cout << endl;
                    cout << left << setw(15) << "DNI" << setw(35) << "NOMBRE" << setw(20) << "PROVINCIA" << setw(15) << "ACUMU KM" << setw(15) << "ACUMU Euros" << setw(15) << "VEHICULO" << endl;
                    cout << "************************************************************************************************************" << endl;
                    cout << left << setw(15) << cli.Dni << setw(35) << cli.Nombre << setw(20) << cli.Provincia << setw(15) << cli.AcumuKm << setw(15) << cli.AcumuEuros << setw(15) << (cli.VEnAlquiler?"Si":"NO") << endl;

                    do
                    {
                        cout << endl;
                        fflush(stdin);
                        cout << "\n\t¿Desea modificar el nombre(s/n)?" ;
                        cin >> opc;
                        switch(opc)
                        {
                            case 's':
                            case 'S':
                                fflush(stdin);
                                cout << "\n\tIntroduce nombre: ";
                                cin.getline(nom, 90, '\n');
                                strcpy(cli.Nombre, nom);
                                cout << "\tEl cliente ha sido actualizado." << endl;
                                break;
                            case 'n':
                            case 'N':
                                cout << "\tEl cliente no ha sido actualizado." << endl;
                                break;
                            default:
                                cout << "\tTiene que introducir n o s" << endl;
                                break;
                        }
                    }while(opc !='s' && opc !='S' && opc !='n' && opc !='N');

                    do
                    {
                        cout << endl;
                        fflush(stdin);
                        cout << "\n\t¿Desea modificar el provincia(s/n)?" ;
                        cin >> opc;
                        switch(opc)
                        {
                            case 's':
                            case 'S':
                                fflush(stdin);
                                cout << "\n\tIntroduce provincia: ";
                                cin.getline(pro, 90, '\n');
                                strcpy(cli.Provincia, pro);
                                cout << "\tEl cliente ha sido actualizado." << endl;
                                pause;
                                break;
                            case 'n':
                            case 'N':
                                cout << "\tEl cliente no ha sido actualizado." << endl;
                                pause;
                                break;
                            default:
                                cout << "\tTiene que introducir n o s" << endl;
                                break;
                        }
                    }while(opc !='s' && opc !='S' && opc !='n' && opc !='N');
                }
                gestorCli.modificar(cli, pos);
                break;
            }

            case 5:
            {
                //eliminar cliente
                TCliente cli;
                cadena dni;
                cout << endl;
                fflush(stdin);
                cout << endl;
                fflush(stdin);
                char opc;
                int pos;
                cout << "\tDime el DNI del cliente que quieres eliminar: ";
                cin.getline(dni, 90, '\n');
                pos = gestorCli.buscar(dni);
                if(pos == -1)
                {
                    cout << "\tCliente no existe en el sistema." << endl;
                    pause;
                }
                else
                {
                    cli = gestorCli.consultar(pos);
                    cout << endl;
                    cout << left << setw(15) << "DNI" << setw(35) << "NOMBRE" << setw(20) << "PROVINCIA" << setw(15) << "ACUMU KM" << setw(15) << "ACUMU Euros" << setw(15) << "VEHICULO" << endl;
                    cout << "************************************************************************************************************" << endl;
                    cout << left << setw(15) << cli.Dni << setw(35) << cli.Nombre << setw(20) << cli.Provincia << setw(15) << cli.AcumuKm << setw(15) << cli.AcumuEuros << setw(15) << (cli.VEnAlquiler?"Si":"NO") << endl;

                    if(cli.VEnAlquiler)
                    {
                        cout << "\n\tEl cliente no puede ser eliminado al tener un vehículo alquilado." << endl;
                        pause;
                    }
                    else
                    {
                        do
                        {
                            cout << endl;
                            fflush(stdin);
                            cout << "\n\t¿Desea eliminar el cliente(s/n)?" ;
                            cin >> opc;
                            switch(opc)
                            {
                                case 's':
                                case 'S':
                                    gestorCli.eliminar(pos);
                                    cout << "El cliente ha sido eliminado." << endl;
                                    pause;
                                    break;
                                case 'n':
                                case 'N':
                                    cout << "El cliente no ha sido eliminado." << endl;
                                    pause;
                                    break;
                                default:
                                    cout << "Tiene que introducir n o s" << endl;
                                    break;
                            }
                        }while(opc !='s' && opc !='S' && opc !='n' && opc !='N');
                    }
                }
                break;
            }

            case 0:

                break;
            default:
                cout << "\n\t\t\tOpción equivocada, inténtelo de nuevo." << endl << endl;
                system("pause");
                break;
        }
        cout << endl;
    }while(opcion !=0);
}//fin del menú gestión de clientes

//desarrollamos el menú de gestión de vehículos
void Menus::menuGestionVehiculos(){
    int opcion;
    GestorVehiculos gestorVeh(nomFichGV);

    do{
        system("cls");
        cout << endl;
        cout << "\t----- Menú Gestión de Vehículos -----" << endl;
        cout << "\t1.- Consulta de vehículos." << endl;
        cout << "\t2.- Buscar un vehículo." << endl;
        cout << "\t3.- Nuevo vehículo." << endl;
        cout << "\t4.- Modificar vehículo." << endl;
        cout << "\t5.- Eliminar un vehículo." << endl;
        cout << "\t0.- Salir." << endl << endl;
        cout << "\t .- Indique una opción: ";
        cin >> opcion;

        switch(opcion){
            case 1:
            {
                //Consulta de vehículos
                Vehiculo veh;
                cadena prov;
                bool estaProvincia = false;
                int pos;
                cout << endl;
                fflush(stdin);
                cout << "\tIntroduce la provincia a buscar: ";
                cin.getline(prov, 90, '\n');
                if(strcmp(prov, "*")==0)
                {
                    cout << left << setw(20) << "MODELO" << setw(15) << "MATRICULA" << setw(15) << "PROVINCIA" << setw(15) << "KILOMETROS" << setw(15) << "PRECIO POR KM" << setw(15) << "ESTADO" << endl;
                    cout << "******************************************************************************************" << endl;

                    for(int i=0;i<gestorVeh.getNumVehiculos();i++)
                    {
                        if(i%2==0)
                        {
                            textcolor(1);
                        }
                        else
                        {
                            textcolor(2);
                        }
                        estaProvincia = true;
                        veh = gestorVeh.consultar(i);
                        cout << left << setw(20) << veh.modelo << setw(15) << veh.matricula << setw(15) << veh.provincia << setw(15) << veh.kilometros << setw(15) << veh.precio_km << setw(15) <<  veh.estado << endl;
                    }
                    textcolor(7);
                }
                else
                {
                    cout << left << setw(20) << "MODELO" << setw(15) << "MATRICULA" << setw(15) << "PROVINCIA" << setw(15) << "KILOMETROS" << setw(15) << "PRECIO POR KM" << setw(15) << "ESTADO" << endl;
                    cout << "******************************************************************************************" << endl;
                    for(int i=0;i<gestorVeh.getNumVehiculos();i++)
                    {
                        if(i%2==0)
                        {
                            textcolor(1);
                        }
                        else
                        {
                            textcolor(2);
                        }
                        veh = gestorVeh.consultar(i);
                        if(strcmp(prov, veh.provincia) == 0)
                        {
                            estaProvincia = true;
                            cout << left << setw(20) << veh.modelo << setw(15) << veh.matricula << setw(15) << veh.provincia << setw(15) << veh.kilometros << setw(15) << veh.precio_km << setw(15) <<  veh.estado << endl;
                        }

                    }
                    textcolor(7);
                }
                if(!estaProvincia)
                {
                    cout << "\tVehiculo no encontrado" << endl;
                }
                pause;
                break;
            }

            case 2:
                //Buscar un vehículo
                Vehiculo veh;
                char opc;
                do{
                    cout << endl;
                    fflush(stdin);
                    cout << "\n\tIntroduce campo de busqueda (P: posicion, M: matricula): ";
                    cin >> opc;
                    opc = toupper(opc);
                    switch(opc)
                    {
                        case 'P':
                        {
                            cout << endl;
                            fflush(stdin);
                            int pos;
                            cout << "\n\tIntroduce la posicion a buscar: ";
                            cin >> pos;
                            if(pos == -1 || pos > gestorVeh.getNumVehiculos())
                            {
                                cout << "\n\tVehiculo no encontrado." << endl;
                            }
                            else
                            {
                                veh = gestorVeh.consultar(pos);
                                cout << left << setw(20) << "MODELO" << setw(15) << "MATRICULA" << setw(15) << "PROVINCIA" << setw(15) << "KILOMETROS" << setw(15) << "PRECIO POR KM" << setw(15) << "ESTADO" << endl;
                                cout << "******************************************************************************************" << endl;
                                cout << left << setw(20) << veh.modelo << setw(15) << veh.matricula << setw(15) << veh.provincia << setw(15) << veh.kilometros << setw(15) << veh.precio_km << setw(15) <<  veh.estado << endl;
                            }
                            pause;
                            break;
                        }
                        case 'M':
                        {
                            cout << endl;
                            fflush(stdin);
                            int pos;
                            cadena mat;
                            cout << "\n\tIntroduce la matricula a buscar: ";
                            cin.getline(mat, 30, '\n');
                            pos = gestorVeh.consultar(mat);
                            if(pos == -1 || pos > gestorVeh.getNumVehiculos())
                            {
                                cout << "\n\tVehiculo no encontrado." << endl;
                            }
                            else
                            {
                                veh = gestorVeh.consultar(pos);
                                cout << left << setw(20) << "MODELO" << setw(15) << "MATRICULA" << setw(15) << "PROVINCIA" << setw(15) << "KILOMETROS" << setw(15) << "PRECIO POR KM" << setw(15) << "ESTADO" << endl;
                                cout << "******************************************************************************************" << endl;
                                cout << left << setw(20) << veh.modelo << setw(15) << veh.matricula << setw(15) << veh.provincia << setw(15) << veh.kilometros << setw(15) << veh.precio_km << setw(15) <<  veh.estado << endl;
                            }
                            pause;
                            break;
                        }
                        default:
                        {
                            cout << "\n\t\t\tOpción equivocada, inténtelo de nuevo." << endl << endl;
                            pause;
                            break;
                        }
                    }

                }while(opc!='P' && opc!='M');
                break;
            case 3:
            {
                //Nuevo vehículo
                Vehiculo veh;
                cout << endl;
                fflush(stdin);
                cout << "\n\tDime la matricula del vehiculo: ";
                cin.getline(veh.matricula, 20, '\n');
                if(gestorVeh.consultar(veh.matricula)!= -1)
                {
                    cout << "\n\tEl vehiculo ya existe en el sistema." << endl;
                }
                else
                {
                    cout << "\n\tDime el modelo del vehiculo: ";
                    cin.getline(veh.modelo, 90, '\n');
                    cout << "\n\tDime la provincia del vehiculo: ";
                    cin.getline(veh.provincia, 90, '\n');
                    int km;
                    cout << "\n\tDime los kilometros del vehiculo: ";
                    cin >> km;
                    veh.kilometros = km;
                    float prKM;
                    cout << "\n\tDime el precio por kilometro del vehiculo: ";
                    cin >> prKM;
                    veh.precio_km = prKM;
                    strcpy(veh.estado, "Libre");

                    gestorVeh.insertar(veh);

                    cout << "\n\tEl vehiculo nuevo es: " << endl;
                    cout << left << setw(20) << "MODELO" << setw(15) << "MATRICULA" << setw(15) << "PROVINCIA" << setw(15) << "KILOMETROS" << setw(15) << "PRECIO POR KM" << setw(15) << "ESTADO" << endl;
                    cout << "******************************************************************************************" << endl;
                    cout << left << setw(20) << veh.modelo << setw(15) << veh.matricula << setw(15) << veh.provincia << setw(15) << veh.kilometros << setw(15) << veh.precio_km << setw(15) <<  veh.estado << endl;
                }
                pause;
                break;
            }

            case 4:
            {
                //Modificar vehículo
                Vehiculo veh;
                char opc;
                cout << endl;
                fflush(stdin);
                int pos;
                cout << "\n\tIntroduce la posicion del vehiculo que quieres modificar: ";
                cin >> pos;
                if(pos == -1 || pos > gestorVeh.getNumVehiculos())
                {
                    cout << "\n\tVehiculo no encontrado." << endl;
                }
                else
                {
                    veh = gestorVeh.consultar(pos);
                    cout << "\n\tVehiculo solicitado: " << endl;
                    cout << left << setw(20) << "MODELO" << setw(15) << "MATRICULA" << setw(15) << "PROVINCIA" << setw(15) << "KILOMETROS" << setw(15) << "PRECIO POR KM" << setw(15) << "ESTADO" << endl;
                    cout << "******************************************************************************************" << endl;
                    cout << left << setw(20) << veh.modelo << setw(15) << veh.matricula << setw(15) << veh.provincia << setw(15) << veh.kilometros << setw(15) << veh.precio_km << setw(15) <<  veh.estado << endl;
                    cout << endl;
                    fflush(stdin);
                    cout << "\n\tDime la nueva provincia del vehiculo: ";
                    cin.getline(veh.provincia, 90, '\n');
                    float prKM;
                    cout << "\n\tDime el nuevo precio por kilometro del vehiculo: ";
                    cin >> prKM;
                    veh.precio_km = prKM;
                    gestorVeh.modificar(veh, pos);
                    cout << "\n\tVehiculo modificado: " << endl;
                    cout << left << setw(20) << "MODELO" << setw(15) << "MATRICULA" << setw(15) << "PROVINCIA" << setw(15) << "KILOMETROS" << setw(15) << "PRECIO POR KM" << setw(15) << "ESTADO" << endl;
                    cout << "******************************************************************************************" << endl;
                    cout << left << setw(20) << veh.modelo << setw(15) << veh.matricula << setw(15) << veh.provincia << setw(15) << veh.kilometros << setw(15) << veh.precio_km << setw(15) <<  veh.estado << endl;
                }
                pause;
                break;
            }
            case 5:
            {
                //Eliminar un vehículo
                Vehiculo veh;
                char opc;
                cout << endl;
                fflush(stdin);
                int pos;
                cout << "\n\tIntroduce la posicion del vehiculo que quieres eliminar: ";
                cin >> pos;
                if(pos == -1 || pos > gestorVeh.getNumVehiculos())
                {
                    cout << "\n\tVehiculo no encontrado." << endl;
                }
                else
                {
                    veh = gestorVeh.consultar(pos);
                    cout << "\n\tVehiculo solicitado: " << endl;
                    cout << left << setw(20) << "MODELO" << setw(15) << "MATRICULA" << setw(15) << "PROVINCIA" << setw(15) << "KILOMETROS" << setw(15) << "PRECIO POR KM" << setw(15) << "ESTADO" << endl;
                    cout << "******************************************************************************************" << endl;
                    cout << left << setw(20) << veh.modelo << setw(15) << veh.matricula << setw(15) << veh.provincia << setw(15) << veh.kilometros << setw(15) << veh.precio_km << setw(15) <<  veh.estado << endl;
                    if(strcmp(veh.estado, "Ocupado")==0)
                    {
                        cout << "\n\tEl vehiculo no se puede eliminar porque esta alquilado." << endl;
                    }
                    else
                    {
                        gestorVeh.eliminarPorPosicion(pos);
                        cout << "\n\tEl vehiculo ha sido eliminado." << endl;
                    }
                }
                pause;
                break;
            }
            case 0:

                break;
            default:
                cout << "\n\t\t\tOpción equivocada, inténtelo de nuevo." << endl << endl;
                system("pause");
                break;
        }
        cout << endl;
    }while(opcion !=0);
}//fin del menú gestión de vehículos

//desarrollamos el menú de gestión de alquileres
void Menus::menuGestionAlquileres(){
    GestorAlquiler gestorAlq(nomFichGA);
    GestorClientes gestorCli(nomFichGC);
    GestorVehiculos gestorVeh(nomFichGV);
    int opcion;

    do{
        system("cls");
        cout << endl;
        cout << "\t----- Menú Gestión de Alquileres -----" << endl;
        cout << "\t1.- Mostrar Vehículos alquilados." << endl;
        cout << "\t2.- Alquilar un vehículo." << endl;
        cout << "\t3.- Devolver un vehículo." << endl;
        cout << "\t0.- Salir." << endl << endl;
        cout << "\t .- Indique una opción: ";
        cin >> opcion;

        switch(opcion)
        {
            case 1:
            {
                //Mostrar Vehículos alquilados
                TAlquiler alq;
                cout << left << setw(15) << "MATRICULA" << setw(10) << "KILOM." << setw(15) << "DNI" << setw(35) << "NOMBRE" << setw(10) << "CIR KM" << setw(10) << "CIR DIAS" << endl;
                cout << "*********************************************************************************************" << endl;
                for(int i=0;i<gestorAlq.getNumAlquiler();i++)
                {
                    if(i%2==0)
                    {
                        textcolor(1);
                    }
                    else
                    {
                        textcolor(2);
                    }
                    alq = gestorAlq.consultar(i);
                    cout << left << setw(15) << alq.Matricula << setw(10) << gestorVeh.consultar(gestorVeh.consultar(alq.Matricula)).kilometros
                    << setw(15) << alq.Dni << setw(35) << gestorCli.consultar(gestorCli.buscar(alq.Dni)).Nombre << setw(10) << alq.KmsCir << setw(10) << alq.NDiasCir << endl;
                }
                textcolor(7);
                pause;
                break;
            }
            case 2:
            {
                //Alquilar un vehículo
                TCliente cli;
                TAlquiler alq;
                Vehiculo veh;
                cadena dni;
                cout << endl;
                fflush(stdin);
                cout << "\tIntroduce el Dni del cliente: ";
                cin.getline(dni, 90, '\n');
                cout << endl;
                fflush(stdin);
                int pos;
                cadena mat;
                cout << "\n\tIntroduce la matricula del coche: ";
                cin.getline(mat, 30, '\n');

                if(gestorCli.buscar(dni)==-1)
                {
                    cout << "\n\tCliente no encontrado" << endl;
                }
                else
                {
                    cli = gestorCli.consultar(gestorCli.buscar(dni));
                    cout << endl;
                    cout << left << setw(15) << "DNI" << setw(35) << "NOMBRE" << setw(20) << "PROVINCIA" << setw(15) << "ACUMU KM" << setw(15) << "ACUMU Euros" << setw(15) << "VEHICULO" << endl;
                    cout << "************************************************************************************************************" << endl;
                    cout << left << setw(15) << cli.Dni << setw(35) << cli.Nombre << setw(20) << cli.Provincia << setw(15) << cli.AcumuKm << setw(15) << cli.AcumuEuros << setw(15) << (cli.VEnAlquiler?"Si":"NO") << endl;
                }
                pos = gestorVeh.consultar(mat);
                if(pos == -1 || pos > gestorVeh.getNumVehiculos())
                {
                    cout << "\n\tVehiculo no encontrado." << endl;
                }
                else
                {
                    veh = gestorVeh.consultar(pos);
                    cout << left << setw(20) << "MODELO" << setw(15) << "MATRICULA" << setw(15) << "PROVINCIA" << setw(15) << "KILOMETROS" << setw(15) << "PRECIO POR KM" << setw(15) << "ESTADO" << endl;
                    cout << "******************************************************************************************" << endl;
                    cout << left << setw(20) << veh.modelo << setw(15) << veh.matricula << setw(15) << veh.provincia << setw(15) << veh.kilometros << setw(15) << veh.precio_km << setw(15) <<  veh.estado << endl;
                }
                cout << "\n\t¿Son los datos correctos? (s/n): ";
                if(gestorVeh.consultar(mat)!=-1 && strcmp(gestorVeh.consultar(gestorVeh.consultar(mat)).estado, "Libre")==0 && gestorCli.buscar(dni)!=-1 &&
                   strcmp(alq.Dni, gestorCli.consultar(gestorCli.buscar(dni)).Dni)!=0 && strcmp(gestorVeh.consultar(gestorVeh.consultar(mat)).matricula, alq.Matricula)!=0)
                {
                    cout << "s" << endl;
                    cout << "\tIntroduce el maximo de km a circular: ";
                    cin >> alq.KmsCir;
                    cout << "\tIntroduce el numero de dias a circular: ";
                    cin >> alq.NDiasCir;

                    strcpy(alq.Matricula, mat);
                    strcpy(alq.Dni, dni);
                    gestorAlq.nuevo(alq);
                    cout << "\tEl coche se ha alquilado." << endl;
                }
                else
                {
                    cout << "n" << endl;
                    cout << "\tEl coche no se ha alquilado." << endl;
                }
                pause;
                break;
            }
            case 3:
            {
                //Devolver un vehículo
                TCliente cli;
                TAlquiler alq;
                Vehiculo veh;
                cadena dni;
                char opc;
                int pos;
                cout << endl;
                fflush(stdin);
                cout << "\tIntroduce el Dni del cliente: ";
                cin.getline(dni, 90, '\n');
                pos = gestorAlq.Buscar(dni, 'D');
                if(pos == -1)
                {
                    cout << "\n\tNingún cliente con ese DNI tiene alquilado un coche." << endl;
                }
                else
                {
                    alq = gestorAlq.consultar(pos);
                    cout << left << setw(15) << "MATRICULA" << setw(10) << "KILOM." << setw(15) << "DNI" << setw(35) << "NOMBRE" << setw(10) << "CIR KM" << setw(10) << "CIR DIAS" << endl;
                    cout << "*********************************************************************************************" << endl;
                    cout << left << setw(15) << alq.Matricula << setw(10) << gestorVeh.consultar(gestorVeh.consultar(alq.Matricula)).kilometros
                    << setw(15) << alq.Dni << setw(35) << gestorCli.consultar(gestorCli.buscar(alq.Dni)).Nombre << setw(10) << alq.KmsCir << setw(10) << alq.NDiasCir << endl;
                    cout << "\n\t¿Son los datos correctos? (s/n): ";
                    cin >> opc;
                    opc = tolower(opc);
                    if(opc =='s')
                    {
                        int KMR = rand() % (alq.KmsCir-1)+1;
                        int NDC = rand() % (alq.NDiasCir-1)+1;
                        float precioKMR = KMR * gestorVeh.consultar(gestorVeh.consultar(alq.Matricula)).precio_km/100;
                        float precioNDC = NDC * 50;
                        float precioAlq = precioKMR + precioNDC;
                        cout << "\n\tDias circulados: " << NDC << endl;
                        cout << "\tKm Recorridos: " << KMR << endl;
                        cout << "\tPrecio Km Recorridos: " << fixed << setprecision(2) << precioKMR << endl;
                        cout << "\tPrecio Dias Alquiler: " << precioNDC << endl;
                        cout << "\tPrecio Total: " << precioAlq << endl;
                    }
                    else
                    {
                        cout << "\n\tEl coche no ha sido devuelto." << endl;
                    }
                }
                pause;
                break;
            }
            case 0:

                break;
            default:
                cout << "\n\t\t\tOpción equivocada, inténtelo de nuevo." << endl << endl;
                system("pause");
                break;
        }
        cout << endl;
    }while(opcion !=0);
}//fin del menú gestión de alquileres

void textcolor(int color){
HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
   SetConsoleTextAttribute(h,color);
}//fin del método textcolor(int color)
