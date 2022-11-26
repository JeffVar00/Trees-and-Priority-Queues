class Nodo:

    def __init__(self, dato=None, izq=None, der=None):
        self._dato = dato
        self._izquierda = izq
        self._derecha = der

    def izquierda(self):
        return self._izquierda

    def derecha(self):
        return self._derecha

    def dato(self):
        return self._dato
