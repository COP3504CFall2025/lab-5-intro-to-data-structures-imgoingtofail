#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <utility>



template <typename T>
class LLDQ : public DequeInterface<T> {

private:
    LinkedList<T> list;

public:
    // Constructor
    LLDQ() = default;

    // Core Insertion Operations
    void pushFront(const T& item) override { this->list.addHead(item); }
    void pushBack(const T& item) override { this->list.addTail(item); }

    // Core Removal Operations
    T popFront() override { 

        T thingy = this->list.getHead()->getData();
        this->list.removeHead();
        return thingy;

    }

    T popBack() override {

        T thingo = this->list.getTail()->getData();
        this->list.removeTail();
        return thingo;

    }

    // Element Accessors
    const T& front() const override { return this->list.getHead()->getData(); }
    const T& back() const override { return this->list.getTail()->getData(); }

    // Getter
    std::size_t getSize() const noexcept override { return this->list.getCount(); }
};






