#include<iostream>
#include<string.h>
using namespace std;
int t=50;
void bandera(int i){
	cout<<"BANDERA  "<< i<<endl;
}
void line(){
    cout<<"______________________________________________"<<endl;
}
void menu(){
	cout<<"*---------------------------------------------------------------*"<<endl;
    cout<<"*---------------------------Bienvenido--------------------------*"<<endl;
	cout<<"*---------------------------------------------------------------*"<<endl;
	cout<<"[1].Agregar Universidad"<<endl;
	cout<<"[2].Agregar Programa"<<endl;
	cout<<"[3].Eliminar Universidad"<<endl;
	cout<<"[4].Eliminar Programa"<<endl;
	cout<<"[5].Mostrar Universidades"<<endl;
	cout<<"[6].Buscar y Mostrar Universidad"<<endl;
	cout<<"[7].Mostrar Programas de la universdiad"<<endl;
	cout<<"[8].Consultar un programa ofertado una o mas universidades"<<endl;
	cout<<"[9].Mostrar todas las universidades(Publica o Privada)"<<endl;
	cout<<"[10].Mostrar programa por modalidad(Presencial o Virtual)"<<endl;
	cout<<"[11].Consultar disponibilidad de un programa en todas las universidades"<<endl;
    cout<<"[12].Consultar Universidad por nombre"<<endl;
	cout<<"[13].Salir"<<endl;
	cout<<"----------------------------------------------------------------"<<endl;
}
class Programa{ //	PREGRADOS
	long int codigo;
	short int semestre;
	char *nombre,*modalidad;
	Programa *sig;

	public:
		void crearCabAd(Programa *&cab,long int codigo,char nombre[],char modalidad[],short int semestre){ //Crear la cabeza de Programa //pregrado
			cab=new Programa;
			cab->nombre=new char[t];
			cab->modalidad=new char[t];
			cab->codigo=codigo;
			cab->semestre=semestre;
			strcpy(cab->nombre,nombre);
			strcpy(cab->modalidad,modalidad);
			cab->sig=NULL;
		}
		void agregarNodoAdya(Programa *&cab,long int codigo,char nombre[],char modalidad[],short int semestre){
			Programa *aux=cab;
			while(aux->sig!=NULL)
				aux=aux->sig;
			aux->sig=new Programa;
			aux=aux->sig;
			aux->nombre=new char[t];
			aux->modalidad=new char[t];
			aux->codigo=codigo;
			aux->semestre=semestre;
			strcpy(aux->nombre,nombre);
			strcpy(aux->modalidad,modalidad);
			aux->sig=NULL;
		}
		Programa* buscarP(Programa *cab,long int codigo){
			Programa *aux=NULL,*aux2=cab;
			while(aux2){
				if(aux2->codigo==codigo)
					aux=aux2;
				aux2=aux2->sig;
			}
			return aux;
		}
		void crearPrograma(Programa *&cab){
			int op;
			long int codigo;
			short int semestre;
			char nombre[t],modalidad[t],vi[]={"Virtual"},pre[]={"Presencial"};
			//cout<<"Registrando programas...\n";
			do{
				fflush(stdin);
				cout<<"Nombre del programa : ";
				gets(nombre);
				cout<<"Codigo del programa : ";
				cin>>codigo;
				cout<<"Semestre del programa: ";
				cin>>semestre;
				cout<<"Modalidad del programa:\n[1].Presencial\n[2].Virtual\n>";
				cin>>op;
				if(op==1){
					strcpy(modalidad,pre);
				}else{
					strcpy(modalidad,vi);
				}
				if(!cab){
					crearCabAd(cab,codigo,nombre,modalidad,semestre);
				}else{
					Programa *aux=cab;
					aux=buscarP(cab,codigo);
					if(!aux){
						agregarNodoAdya(cab,codigo,nombre,modalidad,semestre);
					}else{
						cout<<"	Codigo ya registrado... :("<<endl;
					}
				}
				cout<<endl<<"Desea seguir ingresando mas programas \n";
					cout<<"1) Si \n";
					cout<<"2) No \n";
					cin>>op;

			}while(op==1);
		}
		void mostrarAdy(Programa *cab){
			Programa *aux=cab;
			while(aux){
				cout<<"\t\t---------------------------------\n";
				cout<<"\t\t Nombre del programa : "<<aux->nombre<<endl;
				cout<<"\t\t Codigo del programa : "<<aux->codigo<<endl;
				cout<<"\t\t Semestre del programa : "<<aux->semestre<<endl;
				cout<<"\t\t Modalidad del programa : "<<aux->modalidad<<endl;
				cout<<"\t\t---------------------------------\n";
				cout<<endl;
				aux=aux->sig;
			}
		}
		void eliminarProgramaALL(Programa *&cab){
			Programa *aux=cab;
			while(cab){
				aux=cab;
				cab=cab->sig;
				delete aux;
			}
		}
		void eliminarPrograma(Programa *&cab,long int codigo){
			Programa *aux=cab,*aux2=NULL;
			while(aux&&aux->codigo!=codigo){
				aux2=aux;
				aux=aux->sig;
			}
			if(aux){
				if(aux==cab){//CABEZA DE LA LISTA
					cab=aux->sig;
					aux->sig=NULL;
				}else if(aux->sig){//NODO MEDIO DE LA LISTA
					aux2->sig=aux->sig;
					aux->sig=NULL;
				}else{//COLA DE LA LISTA
					aux2->sig=NULL;
				}
				delete aux;
			}else
				cout<<"Codigo no encontrado... :("<<endl;
		}
        void consultarPrograma(Programa *&cab,long int codigo,char nombre[],char modalidad[],short int semestre){
			Programa *aux;
			aux = buscarP(cab,codigo);
            if(aux){
                line();
                cout<<"[PROGRAMA ENCONTRADO]"<<endl;
                cout<<"PROGRAMA  ["<<aux->nombre<<"]"<<endl<<"CODIGO    ["<<aux->codigo<<"]"<<endl;
                cout<<"MODALIDAD ["<<aux->modalidad<<"]"<<endl<<"SEMESTRE  ["<<aux->semestre<<"]"<<endl;
                line();
            }
        }
        void consultarDisponibilidad(Programa *&cab,long int codigo,char nombre[],char modalidad[],short int semestre,char name[]){
			Programa *aux = cab;
            int auxI;
            while(aux){
            auxI = strcmp(aux->nombre,name);
                if(auxI == 0){
                    line();
                    cout<<"ESTA UNIVERSIDAD ["<<nombre<<"] OFERTA ESTE PROGRAMA"<<endl;
                    cout<<"[PROGRAMA ENCONTRADO]"<<endl;
                    cout<<"PROGRAMA  ["<<aux->nombre<<"]"<<endl<<"CODIGO    ["<<aux->codigo<<"]"<<endl;
                    cout<<"MODALIDAD ["<<aux->modalidad<<"]"<<endl<<"SEMESTRE  ["<<aux->semestre<<"]"<<endl;
                    line();
                }
             aux = aux-> sig;
            }
        }
        void consultarVirtuales(Programa *&cab,long int codigo,char nombre[],char modalidad[],short int semestre){
            Programa *aux = cab;
            int masterAux;
            while(aux){
            masterAux = strcmp(aux -> modalidad,"Virtual");
                if(masterAux == 0){
                    cout<<"PROGRAMA  ["<<aux->nombre<<"]"<<endl<<"CODIGO    ["<<aux->codigo<<"]"<<endl;
                    cout<<"MODALIDAD ["<<aux->modalidad<<"]"<<endl<<"SEMESTRE  ["<<aux->semestre<<"]"<<endl;
                }
                    aux = aux-> sig;
            }
            /*
            Programa *aux = cab;
            int masterAux = 0;
            masterAux = strcmp(aux -> modalidad,"Virtual");
            while(aux){
                if(masterAux == 0){
                    cout<<"PROGRAMA  ["<<aux->nombre<<"]"<<endl<<"CODIGO    ["<<aux->codigo<<"]"<<endl;
                    cout<<"MODALIDAD ["<<aux->modalidad<<"]"<<endl<<"SEMESTRE  ["<<aux->semestre<<"]"<<endl;
                }
                    aux = aux-> sig;
            }
            */
        }
        void consultarPresenciales(Programa *&cab,long int codigo,char nombre[],char modalidad[],short int semestre){
            Programa *aux = cab;
            int supremeAux;
            while(aux){
                supremeAux = strcmp(aux -> modalidad,"Presencial");
                if(supremeAux == 0){
                    cout<<"PROGRAMA  ["<<aux->nombre<<"]"<<endl<<"CODIGO    ["<<aux->codigo<<"]"<<endl;
                    cout<<"MODALIDAD ["<<aux->modalidad<<"]"<<endl<<"SEMESTRE  ["<<aux->semestre<<"]"<<endl;
                }
                    aux = aux-> sig;
            }
        }
};
class Universidad{ //UNIVERSIDADES
	char *nombre,*caracter;
	long int nit;
	Universidad *abajo;
	Programa *frente;
	public:
		void crearCabVer(Universidad *&cab,char nombre[],char caracter[],long int nit){
			cab=new Universidad;
			cab->nombre=new char[t];
			cab->caracter=new char[t];
			cab->nit = nit;
			strcpy(cab->nombre,nombre);
			strcpy(cab->caracter,caracter);
			cab->abajo=NULL;
			cab->frente=NULL;
		}
		void agregarNodoUniversidad(Universidad *&cab,char nombre[],char caracter[],long int nit){
			Universidad *aux=cab;
			while(aux->abajo){
				aux=aux->abajo;
			}
			aux->abajo=new Universidad;
			aux=aux->abajo;
			aux->nombre=new char[t];
			aux->caracter=new char[t];
			aux->nit=nit;
			strcpy(aux->nombre,nombre);
			strcpy(aux->caracter,caracter);
			aux->abajo=NULL;
			aux->frente=NULL;
		}
		Universidad* buscarU(Universidad *cab,long int nit){
			Universidad *aux=NULL,*aux2=cab;
			while(aux2){
				if(aux2->nit==nit)
					aux=aux2;
				aux2=aux2->abajo;
			}
			return aux;
		}
		void crearUniversidad(Universidad *&cab){
			int op;
			long int nit;
			char nombre[t];
			char caracter[t];
			fflush(stdin);
			cout<<"Escriba [.] en el nombre de la universidad para finalizar el registro\n"<<endl;
			cout<<"Registrando universidades... \n"<<endl;
			while(nombre[0]!='.'){
				cout<<"Nombre de la universdiad : ";
				cin.getline(nombre,t,'\n');
				if(nombre[0]!='.'){
					cout<<"Modalidad de la universdiad(publica o privada):\n[1].Publica\n[2].Privada\n>";
					cin>>op;
					if(op==1){
						char p[]="Publica";
						strcpy(caracter,p);
					}else{
						char p[]="Privada";
						strcpy(caracter,p);
					}
					cout<<"NIT de la universdiad : ";
					cin>>nit;
					if(!cab){
						crearCabVer(cab,nombre,caracter,nit);
						system("pause");
						cout<<endl;
					}else{
						Universidad *aux;
						aux=buscarU(cab,nit);
						if(!aux){
							agregarNodoUniversidad(cab,nombre,caracter,nit);
							system("pause");
							cout<<endl;
						}
						else{
							cout<<"\t\tNIT YA REGISTRADO ... :("<<endl;
							system("pause");
							cout<<endl;
						}

					}
				}
				fflush(stdin);
			}
		}
		void agregarAyacenteVer(Universidad *&cab,long int nit){ //Agregar un adyacente en el parte frente del Universidad
			Programa A1;
			Universidad *aux;
			aux=buscarU(cab,nit);
			if(!aux){

				cout<<"\t EL NIT NO EXISTE... :( \a"<<endl;
				system("pause");
				cout<<endl;
			}
			else{

				cout<<"Agregando programas a la universidad ("<<aux->nombre<<")"<<endl;
				A1.crearPrograma(aux->frente);
			}
		}
		void mostrarUniversidades(Universidad *cab){
			Universidad *aux=cab;
			Programa A1;
			while(aux){
				cout<<"----------------------------------"<<endl;
				cout<<"Nombre : "<<aux->nombre<<endl;
				cout<<"NIT : "<<aux->nit<<endl;
				cout<<"Caracter : "<<aux->caracter<<endl;
				if(aux->frente){
					cout<<"\t-----------"<<endl;
					cout<<"\tPROGRAMAS "<<endl;
					A1.mostrarAdy(aux->frente);
					cout<<"\t----------"<<endl;
				}else{
					cout<<"\t-------------------"<<endl;
					cout<<"\tNO TIENE PROGRAMAS "<<endl;
					cout<<"\t-------------------"<<endl;
				}
				cout<<"----------------------------------"<<endl;
				aux=aux->abajo;
			}
		}
		void eliminarUniversidad(Universidad *&cab,long int nit){
			Universidad *aux=cab,*aux2=NULL;
			Programa A1;
			while(aux&&aux->nit!=nit){
				aux2=aux;
				aux=aux->abajo;
			}
			if(aux){
				if(aux==cab){
					cab=aux->abajo;
					aux->abajo=NULL;
				}else if(aux->abajo){
					aux2->abajo=aux->abajo;
					aux->abajo=NULL;
				}else
					aux2->abajo=NULL;
				A1.eliminarProgramaALL(aux->frente);
				delete aux;
				cout<<"\t\tUNIVERSIDAD ELIMINADA EXITOSAMENTE... :)"<<endl;
			}else
				cout<<"\t\tNIT NO ENCONTRADO... :("<<endl;
		}
		void eliminarPrograma(Universidad *&cab,long int nit,long int codigo){
			Universidad *aux;
			Programa A1;
			aux=buscarU(cab,nit);
			if(aux){
				A1.eliminarPrograma(aux->frente,codigo);
				cout<<"\t\tPROGRAMA ELIMINADO EXITOSAMENTE... :)"<<endl;
			}else
				cout<<"\t\tNIT NO ENCONTRADO... :("<<endl;
		}
		void BuscarPorUniversidad(Universidad *cab, long int nit){
			Universidad U, *aux=NULL;
			aux=U.buscarU(cab,nit);
			if(aux){
				cout<<"----------------------------------"<<endl;
				cout<<"Nombre : "<<aux->nombre<<endl;
				cout<<"NIT : "<<aux->nit<<endl;
				cout<<"Caracter : "<<aux->caracter<<endl;
				cout<<"----------------------------------"<<endl;
			}else{
				cout<<"LA UNIVERSIDAD NO ESTA REGISTRADA \n";
			}
		}
		void MostrarPregados(Universidad *cab, long int nit){
			Universidad U, *aux=NULL;
			Programa P;
			aux=U.buscarU(cab,nit);
			if(aux){
				cout<<"UNIVERSIDAD : "<<aux->nombre<<endl;
				if(aux->frente){
					P.mostrarAdy(aux->frente);
				}else{
					cout<<endl<<"\t\tLA UNIVERSIDAD NO TIENE PREGRADOS"<<endl;
				}


			}else{
				cout<<endl<<"LA UNIVERSIDAD NO EXISTE \n";
			}
		}
		void buscarPrograma(Universidad *&cab,long int nit,long int codigo,char nombre[],char modalidad[],short int semestre){//<<ALEJANDRO :V
			Universidad *aux = cab;
			Programa A1, *auxI = frente;
			while(aux){
                if(aux -> frente){
                       cout<<"UNIVERSIDAD >> ["<<aux -> nombre<<"]"<<endl;
                       A1.consultarPrograma(aux->frente,codigo,nombre,modalidad,semestre);
                       aux = aux -> abajo;
                }else{
                    cout<<"ESTA UNIVERSIDAD ["<<aux ->nombre<<"] AUN NO TIENE PROGRAMAS REGISTRADOS"<<endl;
                    aux = aux -> abajo;
                }
			}
		}
		void buscarProgramaNombre(Universidad *&cab,long int nit,long int codigo,char nombre[],char modalidad[],short int semestre){//<<ALEJANDRO :V
			Universidad *aux = cab;
			Programa A1, *auxI = frente;
			char name[25];
            cout<<"DATA ENTER:"<<endl;
            cin.ignore();
            cin.getline(name,25,'\n');
			while(aux){
                if(aux -> frente){
                       A1.consultarDisponibilidad(aux->frente,codigo,aux -> nombre,modalidad,semestre,name);
                       aux = aux -> abajo;
                }else{
                    cout<<"ESTA UNIVERSIDAD ["<<aux ->nombre<<"] AUN NO TIENE PROGRAMAS REGISTRADOS"<<endl;
                    aux = aux -> abajo;
                }
			}
		}
		void mostrarPublica(Universidad *cab,char caracter[]){//<<ALEJANDRO :V
			Universidad *aux=cab;
			Programa A1;
			int masterAux = 0;
            line();
            cout<<"UNIVERSIDADES PUBLICAS"<<endl;
            line();
			while(aux){
                masterAux = strcmp(aux -> caracter,"Publica");
                if(masterAux == 0){
                    line();
                    cout<<"Nombre : "<<aux->nombre<<endl;
                    cout<<"NIT : "<<aux->nit<<endl;
                    cout<<"Caracter : "<<aux->caracter<<endl;
                    line();
                }
                aux=aux->abajo;
			}
        }
        void mostrarPrivada(Universidad *cab,char caracter[]){//<<ALEJANDRO :V
			Universidad *aux=cab;
			Programa A1;
			int masterAux = 0;
            line();
            cout<<"UNIVERSIDADES PRIVADAS"<<endl;
            line();
			while(aux){
                masterAux = strcmp(aux -> caracter,"Privada");
                if(masterAux == 0){
                    line();
                    cout<<"Nombre : "<<aux->nombre<<endl;
                    cout<<"NIT : "<<aux->nit<<endl;
                    cout<<"Caracter : "<<aux->caracter<<endl;
                    line();
                }
                aux=aux->abajo;
			}
        }
        void mostrarProgramasV(Universidad *cab,long int nit,long int codigo,char nombre[],char modalidad[],short int semestre){//<<ALEJANDRO :V
			Universidad *aux=cab;
			Programa A1;
            line();
            cout<<">>PROGRAMAS VIRTUALES<<"<<endl;
            line();
			while(aux){
                if(aux -> frente){
                    A1.consultarVirtuales(aux->frente,codigo,nombre,modalidad,semestre);
                    aux=aux->abajo;
                }else{
                    cout<<"ESTA UNIVERSIDAD ["<<aux ->nombre<<"] AUN NO TIENE PROGRAMAS REGISTRADOS"<<endl;
                    aux=aux->abajo;
                }
			}
        }
        void mostrarProgramasP(Universidad *cab,long int nit,long int codigo,char nombre[],char modalidad[],short int semestre){//<<ALEJANDRO :V
			Universidad *aux=cab;
			Programa A1 ;
            line();
            cout<<">>PROGRAMAS PRESENCIALES<<"<<endl;
            line();
			while(aux){
                if(aux -> frente){
                    A1.consultarPresenciales(aux->frente,codigo,nombre,modalidad,semestre);
                    aux=aux->abajo;
                }else{
                    cout<<"ESTA UNIVERSIDAD ["<<aux ->nombre<<"] AUN NO TIENE PROGRAMAS REGISTRADOS"<<endl;
                    aux=aux->abajo;
                }
			}
        }
		void buscarUniversidadNombre(Universidad *&cab,long int nit,long int codigo,char nombre[],char modalidad[],short int semestre){//<<ALEJANDRO :V
			Universidad *aux = cab,*aux2 = NULL;
			Programa A1;
			int auxI;
			char name[50];
            cout<<"DIGITAR:"<<endl;
            cin.ignore();
            cin.getline(name,25,'\n');
			while(aux){
                auxI = strcmp(aux -> nombre,name);
                if(auxI == 0){
                    aux2 = aux;
                }
                aux = aux->abajo;
			}
			if(aux2)
            {
                line();
                cout<<"[UNIVERSIDAD ENCONTRADA]"<<endl;
                cout<<"NOMBRE  ["<<aux2->nombre<<"]"<<endl<<"NIT    ["<<aux2->nit<<"]"<<endl;
                line();
            }else{

                cout<<"[UNIVERSIDAD NO ENCOTRADA... :(]"<<endl;
            }
		}
};
int main(){
	int opt,keyI;
	char *nombre,*modalidad,*caracter;
	long int nit,codigo;
	short int semestre;
	Universidad obj,*cab=NULL;
	obj.crearUniversidad(cab);
	do{
		system("cls");
		fflush(stdin);
		menu();
		cout<<">";
		cin>>opt;
		switch(opt){
		case 1://[1].Agregar Universidad
		system("cls");
			cout<<"------------------------------------*"<<endl;
			cout<<"*--------AGREGAR UNIVERSIDAD--------*\n";
			cout<<"------------------------------------*"<<endl<<endl;
				cout<<"Digite el NIT de la universidad: ";
				obj.crearUniversidad(cab);
				system("pause");
			break;
		case 2://[2].Agregar Programa
		system("cls");
			cout<<"---------------------------------*"<<endl;
			cout<<"*--------AGREGAR PROGRAMA--------*\n";
			cout<<"---------------------------------*"<<endl<<endl;
				cout<<"Digite el NIT de la universidad: ";
				cin>>nit;
				obj.agregarAyacenteVer(cab,nit);
				system("pause");
			break;
		case 3://[3].Eliminar Universidad
			system("cls");
			cout<<"-------------------------------------*"<<endl;
			cout<<"*--------ELIMINAR UNIVERSIDAD--------*\n";
			cout<<"-------------------------------------*"<<endl<<endl;
				cout<<"Digite NIT de la universidad: ";
				cin>>nit;
				obj.eliminarUniversidad(cab,nit);
				system("pause");
			break;
		case 4://[4].Eliminar Programa
			system("cls");
			cout<<"----------------------------------*"<<endl;
			cout<<"*--------ELIMINAR PROGRAMA--------*\n";
			cout<<"----------------------------------*"<<endl<<endl;
				cout<<"Digite NIT de la universidad: ";
				cin>>nit;
				cout<<"Digite Codigo del programa: ";
				cin>>codigo;
				obj.eliminarPrograma(cab,nit,codigo);
				system("pause");
			break;
		case 5://[5].Mostrar Universidades
			system("cls");
			cout<<"*----------------------------------------------*"<<endl;
			cout<<"*-----MOSTRAR LAS UNIVERSIDADES EXISTENTES-----*\n";
			cout<<"*----------------------------------------------*"<<endl<<endl;
				obj.mostrarUniversidades(cab);
				system("pause");
			break;
		case 6://[6].Mostrar Universidad
			system("cls");
			cout<<"*---------------------------------------------------------------*"<<endl;
			cout<<"*-----BUSCAR Y MOSTRAR LOS DATOS BASICOS DE UNA UNIVERSIDAD-----*\n";
			cout<<"*---------------------------------------------------------------*"<<endl<<endl;
			cout<<"Ingrese el nit de la universidad a buscar \n";
			cout<<": ";
				cin>>nit;
			obj.BuscarPorUniversidad(cab,nit);
			system("pause");
			break;
		case 7://[7].Mostrar Programas de la universdiad
			system("cls");
			cout<<"*--------------------------------------------------*"<<endl;
			cout<<"*-----MOSTRAR LOS PROGRAMAS DE UNA UNIVERSIDAD-----*\n";
			cout<<"*--------------------------------------------------*"<<endl<<endl;
			cout<<"Ingrese el nit de la universidad "<<endl;
			cout<<": ";
				cin>>nit;
			obj.MostrarPregados(cab,nit);
			system("pause");
			break;
		case 8://[8].Consulta programa en todo el grafo
		system("cls");
			cout<<"*----------------------------------------------------------------*"<<endl;
			cout<<"*-----CONSULTAR UN PROGRAMA OFERTADO UNA O MAS UNIVERSIDADES-----*\n";
			cout<<"*----------------------------------------------------------------*"<<endl<<endl;
			cout<<"Digite Codigo del programa: ";//<<ALEJANDRO :V
			cin>>codigo;
			obj.buscarPrograma(cab,nit,codigo,nombre,modalidad,semestre);

			system("pause");
			break;
		case 9://[9].Mostrar todas las universidades(Publica o Privada
		system("cls");
			cout<<"*-----------------------------------------------------------------*"<<endl;
			cout<<"*-----MOSTRAR LAS UNIVERSIDADES DE CARACTER PUBLICO O PRIVADO-----*\n";
			cout<<"*-----------------------------------------------------------------*"<<endl<<endl;
			cout<<"MOSTRAR UNIVERSIDAD PUBLICA [1] - UNIVERSIDAD PRIVADA [2]"<<endl;//<<ALEJANDRO :V
            cout<<">";
            cin>>keyI;
            if(keyI == 1){
            obj.mostrarPublica(cab,caracter);
            }else if(keyI == 2){
            obj.mostrarPrivada(cab,caracter);
            }else{
            cout<<"DIGITE LA SELECCION CORRECTAMENTE"<<endl;
            }
			system("pause");
			break;
		case 10://[10].Mostrar programa por modalidad(Presencial o Virtual
		system("cls");
			cout<<"*-------------------------------------------------------------------*"<<endl;
			cout<<"*-----MOSTRAR PROGRAMAS SEGUN SU MODALIDAD (PRESENCIAL/VIRTUAL)-----*\n";
			cout<<"*-------------------------------------------------------------------*"<<endl<<endl;
			 cout<<"MOSTRAR PROGRAMAS PRESENCIALES [1] - PROGRAMAS VIRTUALES[2]"<<endl;//<<ALEJANDRO :V
            cout<<">";
            cin>>keyI;
            if(keyI == 1){
            obj.mostrarProgramasP(cab,nit,codigo,nombre,modalidad,semestre);
            }else if(keyI == 2){
            obj.mostrarProgramasV(cab,nit,codigo,nombre,modalidad,semestre);
            }else{
            cout<<"DIGITE LA SELECCION CORRECTAMENTE"<<endl;
            }
			system("pause");
			break;
        case 11:
            system("cls");
            obj.buscarProgramaNombre(cab,nit,codigo,nombre,modalidad,semestre);
            system("pause");
            break;
        case 12:
            obj.buscarUniversidadNombre(cab,nit,codigo,nombre,modalidad,semestre);
            system("pause");
            break;

		case 13://[11].Salir
			system("cls");
			cout<<"\t\t\t SALIENDO DEL PROGRAMA "<<endl<<endl;
			cout<<"profe ponganos 5 plis :,D"<<endl;
			system("pause");
			break;
		default:
			break;
		}
	}while(opt!=13);
}

