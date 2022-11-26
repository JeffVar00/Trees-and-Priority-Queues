
from nodo import Nodo

class Arbol:

    def __init__(self, raiz=None, actual=None):
        self._raiz = raiz
        self._actual = actual
        self._contador = 0
        self._altura = 0
        self._tamanno = 0

    def Vacio(self, nodo):
        if nodo is None:
            return True
        return False

    def EsHoja(self, nodo):
        if nodo.izquierda() is None and nodo.derecha() is None:
            return True
        return False

    def eliminarArbol(self):
        self.podar(self._raiz)

    def podar(self, nodo):
        if nodo is not None:
            self.podar(nodo.izquierda())
            self.podar(nodo.derecha())
            nodo = None

    def insertar(self, dato):

        padre = None
        self._actual = self._raiz

        while self.Vacio(self._actual) is not True and dato != self._actual.dato():
            padre = self._actual
            if dato > self._actual.dato():
                self._actual = self._actual.derecha()
            elif dato < self._actual.dato():
                self._actual = self._actual.izquierda()

        if self.Vacio(self._actual) is not True:
            return
        if self.Vacio(padre) is True:
            self._raiz = Nodo(dato)
            self._tamanno += 1
        elif dato < padre.dato():
            padre._izquierda = Nodo(dato)
            self._tamanno += 1
        elif dato > padre.dato():
            padre._derecha = Nodo(dato)
            self._tamanno += 1

    def _obtener(self, dato, nodoActual):
        if not nodoActual:
            return None
        elif nodoActual.dato() == dato:
            return nodoActual
        elif dato < nodoActual.dato():
            return self._obtener(dato, nodoActual.izquierda())
        else:
            return self._obtener(dato, nodoActual.derecha())

    def borrar(self, dato): #no funciona
        padre = None
        nodo = Nodo()
        self._actual = self._raiz
        while self.Vacio(self._actual) is not True:
            if dato == self._actual.dato():
                if self.EsHoja(self._actual) is True:
                    if padre:
                        if padre.derecha() == self._actual:
                            padre._derecha = None
                        elif padre.izquierda() == self._actual:
                            padre._izquierda = None
                    self._actual = None
                    return
                else:
                    padre = self._actual
                    if self._actual.derecha():
                        nodo = self._actual.derecha()
                        while nodo.izquierda():
                            padre = nodo
                            nodo = nodo.izquierda()
                    elif self._actual.izquierda():
                        nodo = self._actual.izquierda()
                        while nodo.derecha():
                            padre = nodo
                            nodo = nodo.derecha()
                    aux = self._actual.dato()
                    self._actual._dato = nodo.dato()
                    nodo._dato = aux
                    self._actual = nodo
            else:
                padre = self._actual
                if dato > self._actual.dato():
                    self._actual = self._actual.derecha()
                elif dato < self._actual.dato():
                    self._actual = self._actual.izquierda()

    def mostrar(self, d):
        return "{}, ".format(d)

    def InOrden(self, nodo=None, r=True):
        if r:
            nodo = self._raiz
        if nodo.izquierda():
            self.InOrden(nodo.izquierda(), False)
        print(self.mostrar(nodo.dato()), end="")
        if nodo.derecha():
            self.InOrden(nodo.derecha(), False)

    def PreOrden(self, nodo=None, r=True):
        if r:
            nodo = self._raiz
        print(self.mostrar(nodo.dato()), end="")
        if nodo.izquierda():
            self.PreOrden(nodo.izquierda(), False)
        if nodo.derecha():
            self.PreOrden(nodo.derecha(), False)

    def PostOrden(self, nodo=None, r=True):
        if r:
            nodo = self._raiz
        if nodo.izquierda():
            self.PostOrden(nodo.izquierda(), False)
        if nodo.derecha():
            self.PostOrden(nodo.derecha(), False)
        print(self.mostrar(nodo.dato()), end="")

    def Buscar(self, dato):
        self._actual = self._raiz
        while self.Vacio(self._actual) is not True:
            if dato == self._actual.dato():
                return True
            elif dato > self._actual.dato():
                self._actual = self._actual.derecha()
            elif dato < self._actual.dato():
                self._actual = self._actual.izquierda()
        return False

    def Altura(self, dato):
        altura = 0
        self._actual = self._raiz
        while self.Vacio(self._actual) is not True:
            if dato == self._actual.dato():
                return altura
            else:
                altura += 1
                if dato > self._actual.dato():
                    self._actual = self._actual.derecha()
                elif dato < self._actual.dato():
                    self._actual = self._actual.izquierda()
        return -1

    def NumeroNodos(self):
        self._contador = 0
        self.auxContador(self._raiz)
        return self._contador

    def auxContador(self, nodo):
        self._contador += 1
        if nodo.izquierda():
            self.auxContador(nodo.izquierda())
        if nodo.derecha():
            self.auxContador(nodo.derecha())

    def AlturaArbol(self):
        self._altura = 0
        self.auxAltura(self._raiz, 0)
        return self._altura

    def auxAltura(self, nodo, cont):
        if nodo.izquierda():
            self.auxAltura(nodo.izquierda(), cont + 1)
        if nodo.derecha():
            self.auxAltura(nodo.derecha(), cont + 1)
        if self.EsHoja(nodo) and cont > self._altura:
            self._altura = cont
