#include <iostream>
#include "windows.h"
using namespace std;


struct nodo{
	int num;
	struct nodo *sig;
};

struct cola{
	nodo *delante;
	nodo *atras;
};

void insertar(struct cola &q, int valor){
	struct nodo *aux = new (struct nodo);
	aux->num = valor;
	aux->sig = NULL;
	if(q.delante == NULL){
		q.delante = aux;
	}else{
		q.atras->sig = NULL;
	}
	q.atras = aux;
}

int desencolar(struct cola &q){
	
	if(q.delante == NULL){
		return NULL; //utilizar manejo de excepciones
	}else{
		int n;
		struct nodo *aux;
		aux=q.delante;
		n=aux->num;
		q.delante=q.delante->sig;
		delete(aux);
		return n;
	}
	
}

void mostrarCola(struct cola q){  //no hace falta la referencia de q solo q
	struct nodo *aux;
	aux = q.delante;
	while(aux!=NULL){
		cout<<" "<<aux->num;
		aux = aux->sig;
	}
	cout<<endl;
}


void eliminarCola(struct cola &q){
	struct nodo *aux;
	while(q.delante != NULL){
		aux = q.delante;
		q.delante = aux->sig;
		delete(aux);
	}
	q.delante=NULL;
	q.atras=NULL;
}
	
void menu(){
	cout<<"\n----colas----\n";
	cout<<"1. insertar\n";
	cout<<"2. desencolar\n";
	cout<<"3. mostrar\n";
	cout<<"4. eliminar\n";
	cout<<"5. salir\n";
}


int main(int argc, char *argv[]) {
	
	struct cola q;
	q.delante=NULL;
	q.atras=NULL;
	int dato;
	int op=0;
	int num;
	do{
		system("cls");
		menu();
		cin>>op;
		switch(op){
		case 1:
			cout<<"Digite el numero\n";
			cin>>dato;
			insertar(q, dato);
			cout<<"numero: "<<dato<<" insertado\n";
			system("pause");
			break;
		case 2:
			num = desencolar(q);
			cout<<"Numero "<<num<<" desencolado\n";
			system("pause");
			break;
		case 3:
			cout<<"----cola----\n";
			if(q.delante!=NULL){
				mostrarCola(q);
			}else{
				cout<<"la cola esta vacia\n";
			}
			system("pause");
			break;
		case 4:
			eliminarCola(q);
			cout<<"se ha eliminado la cola\n";
			system("pause");
			break;
		} 
		
	} while(op!=5);
	
	
	return 0;
}

