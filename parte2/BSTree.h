#ifndef BSTREE_H
#define BSTREE_H

using namespace std;

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T> 
class BSTree {
    private:
        //miembros privados
	
	int nelem;
	BSNode<T> *root;

	//Método Privado de Búsqueda de Elementos
	
	BSNode<T> *search(BSNode<T> *n , T e) const{
                if(n==nullptr){ //elemento no esta en el arbol
                        throw runtime_error("Element not found!\n");
                }else if(n->elem < e){ 
                        return search(n->right, e);
                }else if(n->elem > e){
                        return search(n->left, e);
                }else{
                        return n; //devuelve el nodo buscado
                }
        }

	//Método Privado de Inserción de Elementos
	
	BSNode<T>* insert(BSNode<T>* n, T e){
                if(n == nullptr){ //siempre pasa por aquí, porque inserta en nodos vacíos
                        //return new BSNode<T>(e);
			n = new BSNode<T>(e);
			nelem++;
                }else if(n->elem == e){
                        throw runtime_error("Duplicated element!\n");
                }else if(n->elem < e){
                        n->right = insert(n->right, e);
                }else{
                        n->left = insert(n->left, e);
                }
                return n;
		
        }

	//Método Privado de Recorrido INORDER
    public:
	void print_inorder(std::ostream &out, BSNode<T> *n = nullptr) const{ //Se puede partir de un nodo específico o si no hay nada se parte del nulo (*n = nullptr)
                if(n==nullptr){
			n = root;
		}

		/*if(n != nullptr){
                        print_inorder(out, n->left);
                        out << "Node: " << n->elem << std::endl;
                        print_inorder(out , n->right);
                }
		*/

		if(n !=nullptr){
			if(n->left != nullptr){
				print_inorder(out, n->left);
			}

			//out << "Node: " << n->elem << std::endl;
			out << *n << " ";

			if(n->right != nullptr){
				print_inorder(out, n->right);
			}
		}
        }
	

	//Métodos Privados de Eliminación de Elementos
    private:
	 BSNode<T>* remove(BSNode<T>* n, T e){
                if(n == nullptr){ //el elemento no esta en el arbol
                        throw runtime_error("Element not found!\n");
                }else if(n->elem < e){
                        n->right = remove(n->right, e);
                }else if(n->elem > e){
                        n->left = remove(n->left, e);
                }else{ //hemos encontrado el nodo a eliminar
                        if(n->left != nullptr && n->right != nullptr){ //2 hijos
                                n->elem = max(n->left);
                                n->left = remove_max(n->left);
				nelem--;
                        }else{ //1 o 0 Hijos
                                if(n->left != nullptr){
                                        n = n->left;
                                }else{
                                        n = n->right;
                                }
				nelem--;
                        }
                }
		return n;
        }

        T max(BSNode<T>* n) const{ //encuentra el elemento maximo en un subárbol (el elemento mas a la derecha en un subárbol)
                if(n == nullptr){
                        throw runtime_error("Element not found!\n");
                }else if(n->right != nullptr){
                        return max(n->right);
                }else{
                        return n->elem;
                }
        }

        BSNode<T>* remove_max(BSNode<T>* n){ //elimina el nodo con el valor máximo en un subarbol
                if(n->right == nullptr){
                        return n->left;
                }else{
                        n->right = remove_max(n->right);
			return n;
                }
        }

	//Método Privado de Destrucción de Elementos
	
	void delete_cascade(BSNode<T> *n){ //elimina todos los nodos del arbol
                if(n != nullptr){
                        delete_cascade(n->left);
                        delete_cascade(n->right);
                        delete n;
                }
        }


    public:

        // miembros públicos
	
	BSTree(){
		nelem = 0;
		root = nullptr;
	}

	int size() const{ //return numero elementos en el arbol
		return nelem;
	}

	//Búsqueda de elementos
	
	T search(T e) const{ //busca un elemento llamando al metodo privado
		return search(root, e)->elem;
	}

	T operator[](T e) const{ //permite acceder a un elemento específico 
		return search(e);
	}


	//Inserción de Elementos
	
	void insert(T e){ //función lanzadera
		root = insert(root, e); // n -> nodo raíz
	}

	//Recorrido e Impresión del Árbol
	
	friend std::ostream& operator<<(std::ostream &out, const BSTree<T> &bst){
		bst.print_inorder(out);
		return out;
	}

	
	//Eliminación de Elementos
	
	void remove(T e){ //función lanzadera
		root = remove(root, e); //n -> nodo raiz
	}

	//Destrucción de Elementos
	
	~BSTree(){
		delete_cascade(root);
	}

    
};

#endif
