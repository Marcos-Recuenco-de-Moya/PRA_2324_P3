//Define una interfaz abstracta "Dict" que representa un diccionario genérico

#ifndef DICT_H
#define DICT_H
#include <string>

using namespace std;

template <typename V> 
class Dict {
    public:
        // ... aquí los métodos virtuales puros
	
	virtual void insert(string key, V value) = 0; //metodos virtuales puros que se implementan en clases derivadas
	virtual V search(string key) = 0;
	virtual V remove(string key) = 0;
	virtual int entries() const = 0; //para el operador que usa th.entries (que funciona con const)
	//el metodo entries es constante (const) ya que no modifica el estado interno del diccionario.
};

#endif

//La interfaz define operaciones básicas que se esperan de cualquier diccionario, y permite que diferentes implementaciones de diccionarios compartan un conjunto común de operaciones.
