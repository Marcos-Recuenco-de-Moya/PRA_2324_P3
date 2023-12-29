#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"

#include "../../P1/PRA_2324_P1/ListLinked.h"  //Modificado

using namespace std;

template <typename V>
class HashTable: public Dict<V> {

    private:
        // Atributos privados de HashTable
	int n;
	int max;
	ListLinked<TableEntry<V>> *table;

	int h(string key){
		int res = 0;
		for(int i=0 ; i< key.length() ; i++){
			char c = key.at(i);
			res = res + int(c);
		}
		return res % max;
	}

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

	int capacity() const{
		return max;
	}

	friend ostream &operator<< (ostream &out, const HashTable<V> &th){
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

/*
	void insert(string key, V value) override {
		int pos = h(key);

                if((operator==(this->key, key)) == true){
			for(int i=0 ; i<n ; i++){
				table[pos].get(i).key;
			}

                        throw runtime_error ("La clave ya existe en el diccionario.\n");
                }else{
			TableEntry<V> aux(key, value);
			table[pos].prepend(aux);
			n++;
		}
	}
*/

  	V search(string key) override{ 
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
