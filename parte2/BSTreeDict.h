
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

	friend ostream& operator<<(ostream &out, const BSTreeDict<V> &bs){
		out << bs.tree[0];
		return out;
	}

	V operator[](string key){
		return search(key);
	}

	
	//Metodos heredados
	

	virtual void insert(string key, V value) override{
		TableEntry<V> aux(key,value);
		tree -> insert(aux);	
	}

	virtual V search(string key) override{
		TableEntry<V> aux = tree->search(key);
		return aux.value;
	}

	virtual V remove(string key)override{
		V aux = search(key);
		tree->remove(key);
		return aux;
	}

	virtual int entries() const override{
		return tree->size();
	}
};

#endif
