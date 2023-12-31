#ifndef DICT_H
#define DICT_H
#include <string>

using namespace std;

template <typename V> 
class Dict {
    public:
        // ... aquí los métodos virtuales puros
	
	virtual void insert(string key, V value) = 0;
	virtual V search(string key) = 0;
	virtual V remove(string key) = 0;
	virtual int entries() const = 0; //para el operador que usa th.entries (que funciona con const)
};

#endif
