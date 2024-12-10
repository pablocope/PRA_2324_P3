#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T> 
class BSTree {
    private:
        int nelem;
	BSNode<T> *root;

	BSNode<T>* search(BSNode<T>* n, T e) const {
        	if (!n) {
            		throw std::runtime_error("Elemento no encontrado");
        	} else if (e < n->elem) {
            		return search(n->left, e);
        	} else if (e > n->elem) {
            		return search(n->right, e);
        	} else {
			return n;
       		}
    	}

	BSNode<T>* insert(BSNode<T>* n, T e) {
        	if (!n) {
            		// Crear un nuevo nodo si llegamos a una posición vacía
            		nelem++; // Incrementar el contador de elementos
            		return new BSNode<T>(e);
        	} else if (e == n->elem) {
            		// Lanzar excepción si el elemento ya existe
            		throw std::runtime_error("Elemento duplicado");
        	} else if (e < n->elem) {
            		// Insertar en el subárbol izquierdo
            		n->left = insert(n->left, e);
        	} else {
            		// Insertar en el subárbol derecho
            		n->right = insert(n->right, e);
        	}
        	return n; // Devolver el nodo actual
    	}

	void print_inorder(std::ostream &out, BSNode<T>* n) const {
        	if (n) {
            		print_inorder(out, n->left);  // Recorrer el subárbol izquierdo
            		out << n->elem << " ";        // Imprimir el nodo actual
            		print_inorder(out, n->right); // Recorrer el subárbol derecho
        	}
    	}

	 BSNode<T>* remove(BSNode<T>* n, T e) {
        if (!n) {
            throw std::runtime_error("Elemento no encontrado");
        } else if (e < n->elem) {
            n->right = remove(n->right, e);
        } else if (e > n->elem) {
            n->left = remove(n->left, e);
        } else {
            // Nodo encontrado
            if (n->left && n->right) {
                // Nodo con dos hijos
                n->elem = max(n->left); // Reemplazamos con el máximo del subárbol izquierdo
                n->left = remove_max(n->left); // Elimina el máximo del subárbol izquierdo
            } else {
                // Nodo con uno o ningún hijo
                BSNode<T>* temp = n;
                n = (n->left) ? n->left : n->right;
                delete temp; // Liberamos el nodo
            }
        }
        return n; // Retorna el subárbol modificado
    }

	 T max(BSNode<T>* n) const {
        if (!n) {
            throw std::runtime_error("Subárbol vacío");
        } else if (n->right) {
            return max(n->right); // Recorre a la derecha hasta encontrar el máximo
        } else {
            return n->elem;
        }
    }

	 BSNode<T>* remove_max(BSNode<T>* n) {
        if (!n->right) {
            BSNode<T>* temp = n;
            n = n->left; // Elimina el máximo
            delete temp;
        } else {
            n->right = remove_max(n->right); // Elimina el máximo del subárbol derecho
        }
        return n;
    }

	 void delete_cascade(BSNode<T>* n) {
        if (n) {
            delete_cascade(n->left);  // Liberar memoria del subárbol izquierdo
            delete_cascade(n->right); // Liberar memoria del subárbol derecho
            delete n;                 // Liberar memoria del nodo actual
        }
    }


    public:
	
	//Creación y tamaño
	BSTree(){
		nelem = 0;
		root = nullptr;
	}

	int size() const{
		return nelem;
	}

	
	T search(T e) const{
		BSNode<T>* result = search(root, e);
        	return result->elem;
	}

	T operator[](T e) const {
        	return search(e);
    	}

	void insert(T e) {
        	root = insert(root, e); // Llamada a la versión recursiva
    	}

        friend std::ostream& operator<<(std::ostream &out, const BSTree<T> &bst) {
        	bst.print_inorder(out, bst.root); // Llama al recorrido inorden
        	return out;
    	}
    
	void remove(T e) {
        	root = remove(root, e); // Llamada a la versión recursiva
    	}

	~BSTree() {
        	delete_cascade(root); // Llamada al método recursivo para eliminar todos los nodos
    	}
};

#endif
