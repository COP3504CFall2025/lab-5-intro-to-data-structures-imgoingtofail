#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABS : public StackInterface<T> {

public:
    // Big 5 + Parameterized Constructor
    ABS() { 
        
        this->capacity_ = 1;
        this->curr_size_ = 0;
        this->array_ = new T[1];

    }

    explicit ABS(const size_t capacity) {

        this->capacity_ = capacity;
        this->curr_size_ = 0;
        this->array_ = new T[capacity];

    }

    ABS(const ABS& other) {

        this->array_ = new T[other.capacity_];
        for(size_t i = 0; i < other.curr_size_; i++) { this->array_[i] = other.array_[i]; }
        this->capacity_ = other.capacity_;
        this->curr_size_ = other.curr_size_;

    }

    ABS& operator=(const ABS& rhs) {

        if(this == &rhs) {return *this;}

        T* thingy = new T[rhs.capacity_];
        delete[] this->array_;
        this->array_ = thingy;

        for(size_t i = 0; i < rhs.curr_size_; i++) { this->array_[i] = rhs.array_[i]; }
        this->capacity_ = rhs.capacity_;
        this->curr_size_ = rhs.curr_size_;

        return *this;

    }

    ABS(ABS&& other) noexcept {

        this->array_ = other.array_;
        this->capacity_ = other.capacity_;
        this->curr_size_ = other.curr_size_;

        other.array_ = nullptr;
        other.capacity_ = 1;
        other.curr_size_ = 0;

    }

    ABS& operator=(ABS&& rhs) noexcept {

        if(this == &rhs) {return *this;}

        delete[] this->array_;
        this->array_ = rhs.array_;
        this->capacity_ = rhs.capacity_;
        this->curr_size_ = rhs.curr_size_;
        
        rhs.array_ = nullptr;
        rhs.capacity_ = 1;
        rhs.curr_size_ = 0;

        return *this;

    }

    ~ABS() noexcept override { 
        
        delete[] array_;
        // this->array_ = nullptr;
        // this->capacity_ = 1;
        // this->curr_size_ = 0;
    
    }

    // Get the number of items in the ABS
    [[nodiscard]] size_t getSize() const noexcept override { return this->curr_size_; }

    // Get the max size of the ABS
    [[nodiscard]] size_t getMaxCapacity() const noexcept { return this->capacity_; }

    // Return underlying data for the stack
    [[nodiscard]] T* getData() const noexcept { return this->array_; }

    // Push item onto the stack
    void push(const T& data) override { 

        // if(this->curr_size_ == 0){

        //     this->array_ = new T[1];
        //     this->array_[1] = data;
        //     this->capacity_ = 1;
        //     // this->curr_size_++;
            
        // } else 
        
        if(this->curr_size_ >= this->capacity_) {

            this->capacity_ *= scale_factor_;
            T* thingo = new T[this->capacity_];
            for(size_t i = 0; i < (this->capacity_ / 2); i++) { thingo[i] = this->array_[i]; }
            delete[] this->array_;
            this->array_ = thingo;

        }

        this->array_[curr_size_] = data;
        this->curr_size_++;

    }

    T peek() const override { 
        
        if (curr_size_ == 0) { throw std::out_of_range("outta range bruh"); }
        return this->array_[this->curr_size_ - 1];
    
    }

    T pop() override {

        if(curr_size_ == 0) { throw std::out_of_range("outta range bruh"); }

        T thingo = this->array_[this->curr_size_ - 1];
        // this->array_[this->curr_size_ - 1] = NULL;
        curr_size_--;

        return thingo;

    }

private:
    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;
    
};
