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
                if(n==nullptr){
                        throw runtime_error("Element not found!\n");
                }else if(n->elem < e){
                        return search(n->right, e);
                }else if(n->elem > e){
                        return search(n->left, e);
                }else{
                        return n;
                }
        }

	//Método Privado de Inserción de Elementos
	
	BSNode<T>* insert(BSNode<T>* n, T e){
                if(n == nullptr){
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
	void print_inorder(std::ostream &out, BSNode<T> *n = nullptr) const{
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
                if(n == nullptr){
                        throw runtime_error("Element not found!\n");
                }else if(n->elem < e){
                        n->right = remove(n->right, e);
                }else if(n->elem > e){
                        n->left = remove(n->left, e);
                }else{
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

        T max(BSNode<T>* n) const{
                if(n == nullptr){
                        throw runtime_error("Element not found!\n");
                }else if(n->right != nullptr){
                        return max(n->right);
                }else{
                        return n->elem;
                }
        }

        BSNode<T>* remove_max(BSNode<T>* n){
                if(n->right == nullptr){
                        return n->left;
                }else{
                        n->right = remove_max(n->right);
			return n;
                }
        }

	//Método Privado de Destrucción de Elementos
	
	void delete_cascade(BSNode<T> *n){
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

	int size() const{
		return nelem;
	}

	//Búsqueda de elementos
	
	T search(T e) const{
		return search(root, e)->elem;
	}

	T operator[](T e) const{
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
