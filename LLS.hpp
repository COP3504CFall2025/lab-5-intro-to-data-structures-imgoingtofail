#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLS : public StackInterface<T> {

    private:
    LinkedList<T> list;

    public:    
    LLS() = default;

    // Insertion
    void push(const T& item) override { this->list.addHead(item); }

    // Deletion
    T pop() override { 

        if (this->list.getHead() == nullptr) { throw std::runtime_error("outta bounds"); }
        T thingy = this->list.getHead()->getData();
        this->list.removeHead();
        return thingy;
    
    }

    // Access
    T peek() const override { 
        
        if (this->list.getHead() == nullptr) { throw std::runtime_error("outta bounds"); }
        return this->list.getHead()->getData();
    
    }

    //Getters
    std::size_t getSize() const noexcept override { return list.getCount(); }
};