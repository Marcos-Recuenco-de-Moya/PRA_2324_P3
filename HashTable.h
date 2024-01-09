//Define una clase "HashTable" que hereda de al interfaz "Dict"

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"

#include "../../P1/PRA_2324_P1/ListLinked.h"  //Incluir el archivo ListLinked.h

using namespace std;

template <typename V>
class HashTable: public Dict<V> {

    private:
        // Atributos privados de HashTable
	int n;
	int max;
	ListLinked<TableEntry<V>> *table; //puntero a una lista enlazada TableEntry<V>

	int h(string key){ //función Hash que coge caracter a caracter y hace la suma de su ASCII y luego lo divide por el modulo del maximo
		int res = 0;
		for(int i=0 ; i< key.length() ; i++){
			char c = key.at(i);
			res = res + int(c);
		}
		return res % max;
	}
	
	/* otra función hash
	int h(string key){
		int res = 1;
		for(int i=0 ; i< key.length() ; i++){
			char c = key.at(i);
			res = (res * (i+1) * int(c)) % max;
		}
		return res;
	}
	*///multiplica el codigo ASCII de cada caracter por la posición en la que esta y luego hace el modulo de max

    public:
 	//MIEMBROS DE HASHTABLE.H
	
	HashTable(int size){
		table = new ListLinked<TableEntry<V>>[size];
		n=0;
		max=size;
	}

	~HashTable(){
		delete[] table;
	}

	int capacity() const{ //no modifica el estado interno del objeto (es como una operación de solo lectura)
		return max;
	}

	friend ostream &operator<< (ostream &out, const HashTable<V> &th){ //impresión de la Tabla Hash
		out << "HashTable [entries: " << th.entries() << ", capacity: " << th.capacity() << "]\n";
		out << "==============\n\n";

		for(int i=0 ; i < th.max ; i++){
			cout << "== Cubeta " << i << " ==\n\n";
			out << "List => [\n";
			for(int j=0 ; j < th.table[i].size() ; j++){
				out << "	" << th.table[i].get(j) << endl;
			}
			out << "]\n\n";
		}
		return out;
	}	
	
	//MIEMBROS HEREDADOS DE DICT.H

  	V search(string key) override{ //buscar un elemento a traves de su clave
    		int pos = h(key);
    		for(int i = 0; i < table[pos].size(); i++){
      			if(table[pos].get(i).key == key){
        			return table[pos].get(i).value;
    	  		}
    		}
    		string str = "La clave '" + key + "' no se ha encontrado\n";
    		throw runtime_error(str);
  	}

  	V operator[](string key){ 
    		int pos = h(key);
    		return search(key);
  	}


  	void insert(string key, V value) override{ //Inserta el par key->value en el diccionario
    		int pos = h(key);
    		for(int i = 0; i < table[pos].size(); i++){
      			if(table[pos].get(i).key == key){
        			string str = "";
        			str += "La clave '";
        			str += key;
        			str += "' ya existe\n";
        			throw runtime_error(str);
      			}
    		}
    		TableEntry<V> aux(key, value);
    		table[pos].prepend(aux);
    		n++;
  	}



  	V remove(string key) override{ //Elimina el par key->value si se encuentra en el diccionario
    		int pos = h(key);
    		for(int i = 0; i < table[pos].size(); i++){
      			if(table[pos].get(i).key == key){
        			int x = table[pos].get(i).value;
        			table[pos].remove(i);
        			return x;
      			}
    		}
    		string str = "La clave '" + key + "' no se ha encontrado\n";
    		throw runtime_error(str);
  	}


	int entries() const override{ 
                return n;
        }
        
};

#endif
