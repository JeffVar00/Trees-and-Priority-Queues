#include <iostream>
using namespace std;

struct nodo{
	int valor;
	struct nodo *sig;
};

typedef nodo *pnodo; 

void push(pnodo &p, int valor){
	pnodo aux;
	aux = new(struct nodo);
	aux -> valor = valor; 
	aux -> sig = p;
	p = aux;
}

int pop(pnodo &p){
	int num;
	pnodo aux;
	aux = p;
	num = aux -> valor;
	p = aux -> sig;
	delete(aux);
	return num;
}

void mostrarPila(pnodo &p){
	pnodo aux;
	aux = p;
	while(aux != NULL){
		cout<<"\t"<<aux -> valor<<endl;
		aux = aux -> sig;
	}
}
	
void eliminarPila(pnodo &p){
	pnodo aux;
	while(p != NULL){
		aux = p;
		p = aux -> sig;
		delete(aux);
	}
}
	
void menu(){
	cout<<"Menu"<<endl;
	cout<<"1- Insertar"<<endl;
	cout<<"2- Sacar"<<endl;
	cout<<"3- Imprimir"<<endl;
	cout<<"4- Eliminar Todo"<<endl;
	cout<<"5- Salir"<<endl;
	cout<<"Digite una opcion"<<endl;
}



int main() {
	pnodo p = NULL;
	int dato;
	int op;
	int x;
	
	do{
		
		menu();
		cin>>op;
		switch(op){
		case 1:
			cout<<"digite el numero a insertar"<<endl;
			cin>>dato;
			push(p, dato);
			cout<<"Numero: "<<dato<<" insertado"<<endl;
			system("pause");
			break;
		case 2:
			x = pop(p);
			cout<<"Numero "<<x<<" sacado"<<endl;
			system("pause");
			break;
		case 3:
			cout<<"Datos de la pila"<<endl;
			if(p != NULL){
				mostrarPila(p);
			}else{
				cout<<"Pila Vacia"<<endl;
			}
			system("pause");
			break;
		case 4:
			eliminarPila(p);
			cout<<"Se ha eliminado la pila"<<endl;
			system("pause");
			break;
		}
		
	} while(op != 5);
	
	
	return 0;
}

