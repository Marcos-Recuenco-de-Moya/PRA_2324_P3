//Este programa es el nodo que va a estar en todos los espaciones de la tabla, en el que se guarda la clave y el valor
//Define una clase llamada "TableEntry" que representa una entrada de la tabla hash.

#ifndef TABLEENTRY_H
#define TABLEENTRY_H

#include <string>
#include <iostream>

using namespace std;

template <typename V>
class TableEntry {
    public:
        // miembros públicos
	string key;
	V value;

	TableEntry(string key, V value){ //inicializa clave y valor
		this->key = key;
		this->value = value;
	}

	TableEntry(string key){ //inicializa solo clave
		this->key = key;
	}

	TableEntry(){ //inicializa con clave cadena vacía
		key = "";
	}

	friend bool operator==(const TableEntry<V> &te1, const TableEntry<V> &te2){ //permiten comparar 2 objetos TableEntry "="
		if(te1.key == te2.key){
			return true;
		}else{
			return false;
		}
	}

	friend bool operator!=(const TableEntry<V> &te1, const TableEntry<V> &te2){ //permiten comparar 2 objetos TableEntry "!="
		if(te1.key != te2.key){
			return true;
		}else{
			return false;
		}
	}

	friend ostream &operator<<(ostream &out, const TableEntry<V> &te){ //impresión de los objetos TableEntry

		out << "('" << te.key << "' =>  "  << te.value << ") ";
		return out;
	}


	friend bool operator<(const TableEntry<V> &te1, const TableEntry<V> &te2){ //permiten comparar 2 objetos TableEntry "<"
		return te1.key < te2.key; 
	}
	
	friend bool operator>(const TableEntry<V> &te1, const TableEntry<V> &te2){ //permiten comparar 2 objetos TableEntry ">"
		return te1.key > te2.key;
	}
	
};

#endif
