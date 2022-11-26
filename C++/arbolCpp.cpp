#include <iostream>
using namespace std;
//angelly cortes, lilliam solis, jeff vargas

class ArbolABB { //Se inicializa una clase arbol
private: //Establecemos sus variables privadas
	class Nodo{ //Inicializamos la clase nodo
	public: //Se establecen sus variables, se necesita todo publico ya que necesitamos acceder a los datos mediante nodos
		Nodo(const int dat, Nodo *izq=NULL, Nodo *der=NULL) : //inicializamos el constructor del nodo con un ziquierdo y un derecho
			dato(dat), izquierdo(izq), derecho(der) {} //recibe un int dat (al ser un arbol de ints), un nodo izquierda y derecha en NULL, que funcionaran como las hojas de cada nodo
		//Inicializamos las variables
		int dato; 
		Nodo *izquierdo; 
		Nodo *derecho; 
	}; //Se cierra la clase nodo
	//Inicializamos las variables
	Nodo *raiz; //Raiz del arbol
	Nodo *actual; //Actual para saber donde estamos en el arbol
	int contador; //Contador que funcionara como aux
	int altura; //Guarda la altura de cada nodo como un aux
	
public: //Establacemos las variables publicas
	ArbolABB() : raiz(NULL), actual(NULL) {} //Inicializamos el constructor, con una raiz nula y un actual nulo
	~ArbolABB() { Podar(raiz); } //un destructor que llamara el podar que ira funcoinando de forma recursiva, en este caso desde la raiz
	//inicializamos los metodos
	void Insertar(const int dat); // se manda por parametro un dato de tipo entero que va a ser constante
	void Borrar(const int dat); // se manda por parametro un dato de tipo entero que va a ser usado para borrar que va a ser constante
	bool Buscar(const int dat);// se manda por parametro un dato de tipo entero va a ser usado para buscar que va a ser constante
	bool Vacio(Nodo *r) { return r==NULL; }//me indica si el arbol esta vacio
	bool EsHoja(Nodo *r) { return !r->derecho && !r->izquierdo; }//me indica si es hoja, es decir si no es rama izq ni rama derecha entonces es una hoja
	const int NumeroNodos(); //un entero que indica el numero de nodos
	const int AlturaArbol(); //un entero que indica la altura del arbol
	int Altura(const int dat);//metodo que calcula cual es la altura el arbol
	int &ValorActual() { return actual->dato; }
	void Raiz() { actual = raiz; }
	void InOrden(void (*func)(int&) , Nodo *nodo=NULL, bool r=true);
	void PreOrden(void (*func)(int&) , Nodo *nodo=NULL, bool r=true);
	void PostOrden(void (*func)(int&) , Nodo *nodo=NULL, bool r=true);
	void Podar(Nodo* &);
	void auxContador(Nodo*);
	void auxAltura(Nodo*, int);
};

void ArbolABB::Podar(Nodo* &nodo) //Inicializamos el metodo Poda, que recibe el nodo en el que deseemos iniciar a podar
{
	if(nodo) { //recibe el nodo y a partir de este ira recursivamente llamandose a el mismo
		Podar(nodo->izquierdo); //Se llamara a el mismo para sus nodos hijos y hara los mismo con estos para eliminar desde el nodo el arbol hacia abajo
		Podar(nodo->derecho); //Aqui lo mismo pero con su nodo derecho
		delete nodo; //Eliminamos el nodo que llamamos, al eliminar sus hijos, si este no tiene hijos pasa directamente aca         
		nodo = NULL; //Establecemos de nuevo el nodo a NULL, para que la memoria no quede en el aire
	}
}

void ArbolABB::Insertar(const int dat) //Inicializamos el metodo insertar que recibe un parametro int
{
	Nodo *padre = NULL; //Una variable Nodo como auxiliar llamada "padre"
	
	actual = raiz; //igualo el actual a lo que tiene la raiz
	while(!Vacio(actual) && dat != actual->dato) { //verifica que no esté vacio y que no se repita
		padre = actual; //igualo la variable de nodo "padre" al dato que tenga actual
		if(dat > actual->dato) { //si el dato que está entrando es mayor al que ya tengo 
			actual = actual->derecho; //ingresa a la derecha
		}else if(dat < actual->dato){//en caso contrario si el dato que está entrando es menor al que ya tengo 
			actual = actual->izquierdo; //ingresa a la izquierda
		}
	}
    //se mete aqui cuando es el primer dato que se va a ingreasar
	if(!Vacio(actual)){// Si se ha encontrado el elemento,no se inserta
		return;
	}
	if(Vacio(padre)){ // Si la varible nodo "padre" es NULL, entonces el árbol estaba vacío, el nuevo nodo será el nodo raiz(primer dato)
		raiz = new Nodo(dat);
	}else if(dat < padre->dato){// Si el dato es menor que el que contiene el nodo padre, lo insertamos en la rama izquierda 
		padre->izquierdo = new Nodo(dat);
	}else if(dat > padre->dato){ // Si el dato es mayor que el que contiene el nodo padre, lo insertamos en la rama derecha 
		padre->derecho = new Nodo(dat);
	}
}
// Eliminar un elemento de un árbol
void ArbolABB::Borrar(const int dat)
{
	Nodo *padre = NULL; //variable de nodo "padre" que va a ser usada como auxiliar
	Nodo *nodo;////variable de nodo "nodo" que va a ser usada como auxiliar
	int aux;//variable de tipo entero llamada aux
	
	actual = raiz; //igualo la variable actual a lo que tenga la raiz
	while(!Vacio(actual)) { //mientras tenga algun dato
		if(dat == actual->dato) { //si el dato que entra es igual al que esta en el nodo actual
			if(EsHoja(actual)) { //y ademas es una hoja
				if(padre) // Si tiene padre (no es el nodo raiz) 
					if(padre->derecho == actual){//si lo que tengo en nodo padre es igual a lo que tengo en nodo actual
					padre->derecho = NULL; //lo igualo a NULL
				}else if(padre->izquierdo == actual){//si lo que tengo en nodo padre es igual a lo que tengo en nodo actual
					   padre->izquierdo = NULL;//lo igualo a NULL
					}
				delete actual; //borra el nodo
				actual = NULL;
				return;
			}
			else { // Si el valor está en el nodo actual, pero no es hoja 
				padre = actual;//igualo la varible nodo padre a lo que tenga actual
				if(actual->derecho) {  // Buscar nodo más izquierdo de rama derecha 
					nodo = actual->derecho;
					while(nodo->izquierdo) {
						padre = nodo;
						nodo = nodo->izquierdo;
					}
				}
				else {//Buscaria el nodo más a la derecha de rama izquierda 
					nodo = actual->izquierdo;//nodo se iguala a el nodo actual apuntando al contenido de izquirdo para iniciar la busqueda
					while(nodo->derecho) {//... buscando
						padre = nodo;//..
						nodo = nodo->derecho;//..
					}
				}					
				aux = actual->dato;//Se ntercambiaria valores que no cumplan ya que se necesita moverse
				//y continuar, cerrando el bucle. El nodo encontrado no tiene
				//por qué ser un nodo hoja, cerrando el bucle nos aseguramos de que sólo 
				//se eliminan los nodos  tipo hoja
				actual->dato = nodo->dato;
				nodo->dato = aux;
				actual = nodo;
			}
		}
		else { 
			padre = actual;	//si todavía no se encontra el dato, seguir buscándolo el dato
			if(dat > actual->dato) actual = actual->derecho;
			else if(dat < actual->dato) actual = actual->izquierdo;
		}
	}
}
/*	Se recorre el árbol en InOrden
	Durante el recorrido, se muestra el valor de cada nodo
	*/
void ArbolABB::InOrden(void (*func)(int&) , Nodo *nodo, bool r)
{
	if(r) nodo = raiz; // Si r es true, el nodo es la raiz
	if(nodo->izquierdo) InOrden(func, nodo->izquierdo, false);// Se recorre la izquierda del nodo padre
	func(nodo->dato);// Se muestra el valor del nodo
	if(nodo->derecho) InOrden(func, nodo->derecho, false);  // Se recorre la derecha del nodo padre
}

// Recorrido de árbol en inorden, aplicamos la función func, que tiene el prototipo void func(int*);

void ArbolABB::PreOrden(void (*func)(int&), Nodo *nodo, bool r)
{
	if(r) nodo = raiz;
	func(nodo->dato);/* Aplicar la función al dato del nodo  */
	if(nodo->izquierdo) PreOrden(func, nodo->izquierdo, false);/* Subárbol izquierdo */
	if(nodo->derecho) PreOrden(func, nodo->derecho, false);/* Subárbol derecho */
}

//Recorrido de árbol en postorden.
//Durante el recorrido se muestra el valor de cada nodo
void ArbolABB::PostOrden(void (*func)(int&), Nodo *nodo, bool r)
{
	if(r) nodo = raiz; //Si r es true, el nodo es la raiz
	if(nodo->izquierdo) PostOrden(func, nodo->izquierdo, false); //Se recorre la izquierda del nodo padre
	if(nodo->derecho) PostOrden(func, nodo->derecho, false); //Se recorre la derecha del nodo padre
	func(nodo->dato);// Se muestra el valor del nodo
}

bool ArbolABB::Buscar(const int dat)
{
	actual = raiz;//igualo el nodo actual a lo que ten el nodo raiz
	
	
	while(!Vacio(actual)) { //si no esta vacio
		if(dat == actual->dato) return true; //y el dato que me ingreso existe y es igual al dato retorna verdadero
		else if(dat > actual->dato) actual = actual->derecho; //el dato que me ingreso es mayor al dato que tengo lo busca en la rama derecha
		else if(dat < actual->dato) actual = actual->izquierdo;//el dato que me ingreso es menor al dato que tengo lo busca en la rama izquierda
	}
	return false; //y si no lo encuentra retorna falso
}


// Buscar un valor en el árbol 
int ArbolABB::Altura(const int dat)
{
	int altura = 0; //varible local tipo entera que se iguala a 0
	actual = raiz; //igualo el nodo actual a lo qu tenga nodo raiz
	
	while(!Vacio(actual)) {//si no esta vacion voy a buscar el dato que me entró
		if(dat == actual->dato) return altura; //si encuentro el dato que sea igual a lo que hay en actual que es la raiz retorna la altura que corresponde a este
		else {
			altura++; //aumenta cada vez que se desplace 
			if(dat > actual->dato) actual = actual->derecho;//si el dato es mayor lo busco en la rama derecha
			else if(dat < actual->dato) actual = actual->izquierdo;//si el dato es menor lo busco en la rama izquierda
		}
	}
	return -1; 
}

const int ArbolABB::NumeroNodos()
{
	contador = 0;// se asegura que el contador esté en 0 y que no hayan conteos previos o datos basura
	
	auxContador(raiz);//envia a la raiz para que empiece a contar los nodos de la IZQ y DER y regrese el la cantidad de nodos 
	return contador; // retorna la cantidad de nodos
}

void ArbolABB::auxContador(Nodo *nodo)//metodo que realiza el conteo de IZQ y DER
{
	contador++; //incrementará en uno cada vez que se ingrese al mentodo
	if(nodo->izquierdo) auxContador(nodo->izquierdo);//el nodo que entra, se apunta a los nodos de la IZQ y mediante recursividad se vuelve a llamar el metodo para que se vuelva a ejecutar, entonces cont +++
	if(nodo->derecho)   auxContador(nodo->derecho);//despues el nodo que entra, se apunta a los nodos de la DER y mediante recursividad se vuelve a llamar el metodo para que se vuelva a ejecutar, entonces cont +++
}

const int ArbolABB::AlturaArbol()
{
	altura = 0; //Iniciamos un recorrido del árbol en postorden, con la variable de altura igual a cero.
	auxAltura(raiz, 0);
	return altura;
}

void ArbolABB::auxAltura(Nodo *nodo, int a)
{
	//Cada vez que empecemos a recorrer una nueva rama, incrementamos la altura para ese nodo.
	if(nodo->izquierdo) auxAltura(nodo->izquierdo, a+1);// //recorrido por la izquierda
	if(nodo->derecho)   auxAltura(nodo->derecho, a+1);//recorrido por la derecha
	if(EsHoja(nodo) && a > altura) altura = a;//Después de procesar las dos ramas, verificamos si la altura del nodo es mayor que la variable que almacena la altura actual del árbol, si es así, actualizamos esa variable.
}
//  Función para mostrar el árbol.
void Mostrar(int &d)
{
	cout << d << ","; // //Imprime el dato y coloca una coma para separar cada dato.
}

int main()
{
	ArbolABB ArbolInt;
	ArbolInt.Insertar(10);
	ArbolInt.Insertar(5);
	ArbolInt.Insertar(12);
	ArbolInt.Insertar(4);
	ArbolInt.Insertar(7);
	ArbolInt.Insertar(3);
	ArbolInt.Insertar(6);
	ArbolInt.Insertar(9);
	ArbolInt.Insertar(8);
	ArbolInt.Insertar(11);
	ArbolInt.Insertar(14);
	ArbolInt.Insertar(13);
	ArbolInt.Insertar(2);
	ArbolInt.Insertar(1);
	ArbolInt.Insertar(15);
	ArbolInt.Insertar(10);
	ArbolInt.Insertar(17);
	ArbolInt.Insertar(18);
	ArbolInt.Insertar(16);
	
	cout << "Altura de arbol " << ArbolInt.AlturaArbol() << endl;
	/*Muestra el arbol en tres ordenes distintos*/
	cout << "InOrden: ";
	ArbolInt.InOrden(Mostrar);
	cout << endl;
	cout << "PreOrden: ";
	ArbolInt.PreOrden(Mostrar);
	cout << endl;
	cout << "PostOrden: ";
	ArbolInt.PostOrden(Mostrar);
	cout << endl;
	/*Se borran algumos de nuestros elementos*/
	cout << "N nodos: " << ArbolInt.NumeroNodos() << endl;
	ArbolInt.Borrar(5);
	cout << "Borrar   5: ";
	ArbolInt.InOrden(Mostrar);
	cout << endl;
	ArbolInt.Borrar(8);
	cout << "Borrar   8: ";
	ArbolInt.InOrden(Mostrar);
	cout << endl;
	ArbolInt.Borrar(15);
	cout << "Borrar  15: ";
	ArbolInt.InOrden(Mostrar);
	cout << endl;
	ArbolInt.Borrar(245);
	cout << "Borrar 245: ";
	ArbolInt.InOrden(Mostrar);
	cout << endl;
	ArbolInt.Borrar(4);
	cout << "Borrar   4: ";
	ArbolInt.InOrden(Mostrar);
	ArbolInt.Borrar(17);
	cout << endl;
	cout << "Borrar  17: ";
	ArbolInt.InOrden(Mostrar);
	cout << endl;
	/*Se muestran algunos parametros*/
	cout << "N nodos: " << ArbolInt.NumeroNodos() << endl;
	cout << "Altura de 1 " << ArbolInt.Altura(1) << endl;
	cout << "Altura de 10 " << ArbolInt.Altura(10) << endl;
	cout << "Altura de arbol " << ArbolInt.AlturaArbol() << endl;
	cin.get();
	return 0;
}
