
#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include "../Dict.h"
#include "BSTree.h"
#include "../TableEntry.h"

using namespace std;

template <typename V>
class BSTreeDict: public Dict<V> {

    private:
	BSTree<TableEntry<V>>* tree;

    public:
        BSTreeDict(){
		tree = new BSTree<TableEntry<V>>;
	}

	~BSTreeDict(){
		delete tree;
	}

	friend ostream& operator<<(ostream &out, const BSTreeDict<V> &bs){ //imprimir el arbol
		out << *(bs.tree);
		return out;
	}

	V operator[](string key){ //acceder al valor asociado a una clave en el diccionario
		return search(key);
	}

	
	//Metodos heredados
	

	virtual void insert(string key, V value) override{ //inserta par clave-valor
		TableEntry<V> aux(key,value);
		tree->insert(aux);	
	}

	virtual V search(string key) override{ //buscar par clave-valor
		TableEntry<V> aux = tree->search(key);
		return aux.value;
	}

	virtual V remove(string key)override{ //eliminar par clave-valor
		V aux = search(key);
		tree->remove(key);
		return aux;
	}

	virtual int entries() const override{ //obtener numero de elemento
		return tree->size();
	}
	
	/*
	bool containsKey(string key) const{
		return tree->search(key) != nullptr;
	}
	*/
};

#endif
