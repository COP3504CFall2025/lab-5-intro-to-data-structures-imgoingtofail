#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABQ : public QueueInterface<T>{

    public:

    // Constructors + Big 5
    ABQ() {

        this->capacity_ = 1;
        this->curr_size_ = 0;
        this->array_ = new T[1];
        
    }

    explicit ABQ(const size_t capacity) {

        this->capacity_ = capacity;
        this->curr_size_ = 0;
        this->array_ = new T[capacity];

    }

    ABQ(const ABQ& other) {

        this->array_ = new T[other.capacity_];
        for(size_t i = 0; i < other.curr_size_; i++) { this->array_[i] = other.array_[i]; }
        this->capacity_ = other.capacity_;
        this->curr_size_ = other.curr_size_;

    }

    ABQ& operator=(const ABQ& rhs) {

        if(this == &rhs) {return *this;}

        T* thingy = new T[rhs.capacity_];
        delete[] this->array_;
        this->array_ = thingy;

        for(size_t i = 0; i < rhs.curr_size_; i++) { this->array_[i] = rhs.array_[i]; }
        this->capacity_ = rhs.capacity_;
        this->curr_size_ = rhs.curr_size_;

        return *this;

    }

    ABQ(ABQ&& other) noexcept {

        this->array_ = other.array_;
        this->capacity_ = other.capacity_;
        this->curr_size_ = other.curr_size_;

        other.array_ = nullptr;
        other.capacity_ = 1;
        other.curr_size_ = 0;

    }

    ABQ& operator=(ABQ&& rhs) noexcept {

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

    ~ABQ() noexcept override {

        delete[] array_;
        // this->array_ = nullptr;
        // this->capacity_ = 0;
        // this->curr_size_ = 0;

    }

    // Getters
    [[nodiscard]] size_t getSize() const noexcept override { return this->curr_size_; }
    [[nodiscard]] size_t getMaxCapacity() const noexcept { return this->capacity_; }
    [[nodiscard]] T* getData() const noexcept { return this->array_; }

    // Insertion
    void enqueue(const T& data) override {

        // if(this->capacity_ == 0){

        //     this->array_ = new T[1];
        //     this->array_[1] = data;
        //     this->capacity_ = 1;
        //     // this->curr_size_++;
            
        // } else 
        if(this->curr_size_ >= this->capacity_) {

            this->capacity_ *= scale_factor_;
            T* thingo = new T[this->capacity_];
            for(size_t i = 0; i < this->curr_size_; i++) { thingo[i] = this->array_[i]; }
            delete[] this->array_;
            this->array_ = thingo;

        }

        this->array_[curr_size_] = data;
        this->curr_size_++;

    }

    // Access
    T peek() const override { 
        
        if (curr_size_ == 0) { throw std::runtime_error("outta bounds"); }
        return this->array_[0]; 
    
    }

    // Deletion
    T dequeue() override {

        if(curr_size_ == 0 || capacity_ == 0) { throw std::runtime_error("outta bounds"); }

        T thingo = this->array_[0];
        // this->array_[0] = NULL;
        for(size_t i = 1; i < this->curr_size_; i++) { this->array_[i-1] = this->array_[i]; }
        curr_size_--;

        return thingo;

    }

    private:
    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;

};
