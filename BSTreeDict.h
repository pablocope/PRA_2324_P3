#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>         // Para flujos de salida
#include <stdexcept>       // Para manejo de excepciones
#include "Dict.h"          // Interfaz base para un diccionario genérico
#include "BSTree.h"        // Implementación de un Árbol Binario de Búsqueda
#include "TableEntry.h"    // Clase que representa entradas clave-valor

// Clase genérica que implementa un diccionario basado en un Árbol Binario de Búsqueda (ABB)
template <typename V>
class BSTreeDict : public Dict<V> { // Hereda de la interfaz Dict<V>
private:
    BSTree<TableEntry<V>>* tree;  // Puntero al ABB que almacena las entradas del diccionario

public:
    // Constructor
    BSTreeDict() {
        tree = new BSTree<TableEntry<V>>();  // Inicializa el ABB vacío
    }

    // Destructor
    ~BSTreeDict() {
        delete tree;  // Libera la memoria ocupada por el ABB
    }

    // Sobrecarga del operador << para imprimir el diccionario
    friend std::ostream& operator<<(std::ostream &out, const BSTreeDict<V> &dict) {
        out << *dict.tree;  // Llama al operador << del ABB
        return out;
    }

    // Sobrecarga del operador [] para buscar un valor a partir de una clave
    V operator[](std::string key) {
        // Crea una entrada temporal con la clave (el valor es irrelevante)
        TableEntry<V> entry(key, V());
        // Busca la entrada correspondiente en el ABB y devuelve su valor
        return (*tree)[entry].getValue();
    }

    // Métodos que implementan la interfaz Dict<V>

    // Inserta una nueva entrada clave-valor en el diccionario
    void insert(std::string key, V value) override {
        TableEntry<V> entry(key, value);  // Crea una nueva entrada clave-valor
        tree->insert(entry);             // Inserta la entrada en el ABB
    }

    // Busca un valor a partir de una clave en el diccionario
    V search(std::string key) override {
        // Crea una entrada temporal con la clave para buscar en el ABB
        TableEntry<V> entry(key, V());
        // Busca la entrada en el ABB y devuelve el valor asociado
        return (*tree)[entry].getValue();
    }

    // Elimina una entrada del diccionario a partir de su clave
    void remove(std::string key) override {
        // Crea una entrada temporal con la clave para eliminar del ABB
        TableEntry<V> entry(key, V());
        tree->remove(entry);  // Elimina la entrada del ABB
    }

    // Devuelve todas las entradas del diccionario como un vector
    std::vector<TableEntry<V>> entries() const override {
        std::vector<TableEntry<V>> result;  // Contenedor para almacenar las entradas
        // Realiza un recorrido in-order del ABB para obtener las entradas en orden
        tree->print_inorder([&result](const TableEntry<V>& entry) {
            result.push_back(entry);  // Añade cada entrada al vector
        });
        return result;  // Devuelve el vector con todas las entradas
    }
};

#endif
