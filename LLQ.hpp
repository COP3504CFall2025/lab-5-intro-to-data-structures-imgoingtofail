#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLQ : public QueueInterface<T> {

    private:
    LinkedList<T> list;

    public:
    // Constructor
    LLQ() = default;

    // Insertion
    void enqueue(const T& item) override { this->list.addTail(item); }

    // Deletion
    T dequeue() override { 
        
        if (this->list.getHead() == nullptr) { throw std::runtime_error("outta bounds"); }
        T thingo = this->list.getHead()->getData();
        this->list.removeHead(); 
        return thingo;
    
    }

    // Access
    T peek() const override { 
        
        if (list.getHead() == nullptr) { throw std::runtime_error("outta bounds"); }
        return this->list.getHead()->getData();
    
    }

    // Getter
    std::size_t getSize() const noexcept override { return this->list.getCount(); }

};