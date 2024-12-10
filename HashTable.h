#include "../../../Practica_1/PRA_2324_P1/ListLinked.h"
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"

#include <string>
#include <vector>
#include <list>

template <typename V>
class HashTable : public Dict<V> {
    int n; // Elementos almacenados
    int max; // Tamaño de la tabla
    std::list<TableEntry<V>>* table;

    int h(std::string key) {
        int sum = 0;
        for (char c : key) {
            sum += static_cast<int>(c);
        }
        return sum % max;
    }

public:
    HashTable(int size) : n(0), max(size) {
        table = new std::list<TableEntry<V>>[max];
    }

    ~HashTable() {
        delete[] table;
    }

    void insert(std::string key, V value) override {
        int index = h(key);
        for (auto& entry : table[index]) {
            if (entry.key == key) {
                entry.value = value;
                return;
            }
        }
        table[index].emplace_back(key, value);
        ++n;
    }

    V search(std::string key) override {
        int index = h(key);
        for (const auto& entry : table[index]) {
            if (entry.key == key) {
                return entry.value;
            }
        }
        throw std::runtime_error("Key not found");
    }

    V remove(std::string key) override {
        int index = h(key);
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if (it->key == key) {
                V value = it->value;
                table[index].erase(it);
                --n;
                return value;
            }
        }
        throw std::runtime_error("Key not found");
    }

    int entries() override {
        return n;
    }

    int capacity() const {
        return max;
    }

    friend std::ostream& operator<<(std::ostream& out, const HashTable<V>& th) {
        for (int i = 0; i < th.max; ++i) {
            out << "[" << i << "]: ";
            for (const auto& entry : th.table[i]) {
                out << "{" << entry.key << ": " << entry.value << "} ";
            }
            out << "\n";
        }
        return out;
    }

    V operator[](std::string key) {
        return search(key);
    }
};

#endif

/*
template <typename V>
class HashTable: public Dict<V> {

    private:
        int n; //Elementos almacenados
		int max; //Tamaño de la tabla
		ListLinked<TableEntry<V>>* table; //tabla
		int h(std::string key){
			int sum = 0;
        	for (char c : key) {
            	sum += static_cast<int>(c);
        	}
        	return sum % max;
		}

    public:
		
		void insert(std::string key, V value) override{
		    int index = h(key);
        	for (auto& entry : table[index]) {
            	if (entry.key == key) {
                	entry.value = value;  // Actualizar valor si ya existe
                	return;
            	}
        	}
        	table[index].insert(TableEntry<V>(key, value));
        	++n;
		}

		V search(std::string key) override {
        	int index = h(key);
        	TableEntry<V> searchEntry(key);
       		for (const auto& entry : table[index]) {
            	if (entry == searchEntry) {
                	return entry.value;
            	}
        	}
        	throw std::runtime_error("Key not found");
    	}

		V remove(std::string key) override {
        	int index = h(key);
        	TableEntry<V> searchEntry(key);
    	    for (auto it = table[index].begin(); it != table[index].end(); ++it) {
    	        if (*it == searchEntry) {
    	            V value = it->value;
    	            table[index].erase(it);
    	            --n;
    	            return value;
    	        }
    	    }
    	    throw std::runtime_error("Key not found");
    	}

		int entries() override {
        	return n;
    	}

		HashTable(int size) : n(0), max(size) {
        	table = new ListLinked<TableEntry<V>>[max];
    	}
		
		~HashTable() {
        	delete[] table;
    	}

		int capacity() const {
        	return max;
    	}

		friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th) {
        	for (int i = 0; i < th.max; ++i) {
            	out << "[" << i << "]: ";
            	for (const auto& entry : th.table[i]) {
            	    out << "{" << entry.key << ": " << entry.value << "} ";
            	}
            	out << "\n";
        	}
        	return out;
    	}

		V operator[](std::string key) {
        	int index = h(key);
        	for (const auto& entry : table[index]) {
            	if (entry.key == key) {
                	return entry.value;
            	}
        	}
        	throw std::runtime_error("Key not found");
    	}



};

#endif
*/