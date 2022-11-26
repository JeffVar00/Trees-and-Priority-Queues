// cola de prioridad

#include <iostream>

using namespace std;
//definimos la estructura del nodo
struct nodo
{
	char dato;					// dato del nodo para la cola
	int priori;        // prioridad del nodo
	struct nodo *sgte;  //siguiente
};

struct cola{   //definimos la estructura de la cola compuesta de nodos.
	nodo *delante;
	nodo *atras  ;
};

struct nodo *crearNodo(char x, int pr){  //crear una estructura donde recibimos los datos del nodo
	struct nodo *nuevoNodo = new(struct nodo); //creamos un nuevo nodo
	nuevoNodo->dato = x;
	nuevoNodo->priori = pr;  //igualamos priori a lo que se recibe por parametros
	return nuevoNodo;  //retornamos el nuevo nodo
}
	
	//metodo para insertar dentro de la cola
	void encolar(struct cola &q, char valor, int priori){
		struct nodo *aux = crearNodo(valor, priori);
		aux->sgte = NULL;
		if(q.delante == NULL)  //condicion para saber si la cola esta vacia
			q.delante = aux;   // encola el primero elemento
		else
			(q.atras)->sgte = aux;
		q.atras = aux;        // puntero que siempre apunta al ultimo elemento 
	}
		
		void muestraCola( struct cola q ){ //metodo para recorrer e imprimir los elementos de la cola
			struct nodo *aux;
			aux = q.delante;  //posiciona en el primer elemento
			cout << " Caracter  Prioridad " << endl;
			cout << " ------------------- " << endl;
			while( aux != NULL ){
				cout<<"    "<< aux->dato << "     |   " << aux->priori << endl; //imprime el dato y la prioridad
				aux = aux->sgte; //apuntamos al siguiente elemento
			}    
		}
			
			void ordenarPrioridad( struct cola &q ){ //ordena la cola
				struct nodo *aux1, *aux2;
				int p_aux;
				char c_aux;
				aux1 = q.delante;  //aux 1 se posiciona en el primer elemento de la cola
				while( aux1->sgte != NULL){  //ordenamiento burbuja
					aux2 = aux1->sgte; //aux 2 va a iniciar en el siguiente elemento de aux1 (primer elemento)
					while( aux2 != NULL){ 
						if( aux1->priori > aux2->priori){ //prioridad mas baja en la que gana
							p_aux = aux1->priori;
							c_aux = aux1->dato;
							aux1->priori = aux2->priori;
							aux1->dato   = aux2->dato;
							aux2->priori = p_aux;
							aux2->dato   = c_aux;
						}
						aux2 = aux2->sgte;
					}
					aux1 = aux1->sgte;
				}
			}
				void insertar( struct cola &q, char c, int pr ){
					encolar( q, c, pr );  //llamado al metodo encolar
					ordenarPrioridad( q ); //llamado al metodo ordenar con prioridad
				}
					
					void menu(){  //menu del programa separado del main
						cout<<"\n\t COLAS CON PRIORIDAD EN C++ \n\n";
						cout<<" 1. ENCOLAR                           "<<endl;
						cout<<" 2. MOSTRAR                           "<<endl;
						cout<<" 3. SALIR                             "<<endl;
						cout<<"\n INGRESE OPCION: ";
					}
						int main(){ //funcion principal
							struct cola q;  //definicion de la cola a utilizar
							q.delante = NULL; //inicializamos las variables
							q.atras   = NULL;
							char c ;     // caracter a encolar
							int pr;      // prioridad del caracter
							int op;      // opcion del menu
							int x ;      // numero que devuelve la funcion pop
							do{
								menu();
								cin>>op;
								switch(op){
								case 1:{
									cout<< "\n Ingrese caracter: ";
									cin>> c;
									cout<< "\n Ingrese prioridad: ";   
									cin>> pr;
									insertar( q, c, pr );
									cout<<"\n\n\t\tCaracter '" << c << "' encolado...\n\n";
									break;
								}
								case 2:{
										cout << "\n\n MOSTRANDO COLA DE PRIORIDAD\n\n";
										if(q.delante!=NULL)
											muestraCola( q );
										else   
											cout<<"\n\n\tCola vacia...!"<<endl;
										break;
									}
								case 3:{
											cout<<"\n\tAdios mundo..!"<<endl;
											system("pause");
											exit(0);
										}
								default:{
												cout<<"\n\tOpcion incorecta..!"<<endl;
												system("pause");
												break;
											}
											cout<<endl<<endl;
											system("pause");   
											system("cls");
								}
							}while(op!=3);
							return 0;
						}
