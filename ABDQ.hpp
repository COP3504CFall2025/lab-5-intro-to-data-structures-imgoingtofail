#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>

template <typename T>
class ABDQ : public DequeInterface<T> {

    public: 
    // Big 5
    ABDQ() {

        this->data_ = new T[4];
        this->capacity_ = 4;
        this->size_ = 0;
        this->front_ = 0;
        this->back_ = 0;

    }

    explicit ABDQ(std::size_t capacity) {

        this->data_ = new T[capacity];
        this->capacity_ = capacity;
        this->size_ = 0;
        this->front_ = 0;
        this->back_ = 0;

    }

    ABDQ(const ABDQ& other) {

        this->data_ = new T[other.capacity_];
        this->capacity_ = other.capacity_;
        this->size_ = other.size_;
        for(size_t i = 0; i < other.size_; i++) { this->data_[i] = other.data_[(other.front_ + i) % capacity_]; }
        this->front_ = 0;
        this->back_ = size_;

    }

    ABDQ(ABDQ&& other) noexcept {

        // delete[] this->data_; 

        this->data_ = other.data_;
        this->capacity_ = other.capacity_;
        this->size_ = other.size_;
        this->front_ = other.front_;
        this->back_ = other.back_;

        other.data_ = nullptr;
        other.capacity_ = 1;
        other.size_ = 0;
        other.front_ = 0;
        other.back_ = 0;
    }

    ABDQ& operator=(const ABDQ& other) {

        if(this == &other) { return *this; }

        T* thingy = new T[other.capacity_];
        delete[] this->data_;
        this->data_ = thingy;

        this->capacity_ = other.capacity_;
        this->size_ = other.size_;
        this->front_ = other.front_;
        this->back_ = other.back_;
        for(size_t i = 0; i < other.size_; i++) { this->data_[(this->front_ + i) % capacity_] = other.data_[(other.front_ + i) % capacity_]; }

        return *this;

    }

    ABDQ& operator=(ABDQ&& other) noexcept {

        if(this == &other) { return *this; }

        delete[] this->data_;

        this->data_ = other.data_;
        this->capacity_ = other.capacity_;
        this->size_ = other.size_;
        this->front_ = other.front_;
        this->back_ = other.back_;

        other.data_ = nullptr;
        other.capacity_ = 1;
        other.size_ = 0;
        other.front_ = 0;
        other.back_ = 0;

        return *this;

    }

    ~ABDQ() override {

        delete[] this->data_;
        // this->data_ = nullptr;
        // this->capacity_ = 0;
        // this->size_ = 0;
        // this->front_ = 0;
        // this->back_ = 0;

    }

    // Insertion
    void pushFront(const T& item) override {

        // if(this->capacity_ == 0){

        //     this->data_ = new T[1];
        //     this->data_[1] = item;
        //     this->capacity_ = 1;
        //     // this->size_++;
            
        // } else 
        
        if(this->size_ >= this->capacity_) {

            size_t ogCap = this->capacity_;

            T* thingo = new T[ogCap * SCALE_FACTOR];
            for(size_t i = 0; i < this->size_; i++) { thingo[i] = this->data_[(front_ + i) % ogCap]; }

            delete[] this->data_;
            this->data_ = thingo;
            this->capacity_ = ogCap * SCALE_FACTOR;

            front_ = 0;
            back_ = size_;

        }

        front_ = (front_ - 1 + capacity_) % capacity_;
        this->data_[front_] = item;
        this->size_++;

    }

    void pushBack(const T& item) override {

        // if(this->capacity_ == 0){

        //     this->data_ = new T[1];
        //     this->data_[1] = item;
        //     this->capacity_ = 1;
        //     // this->size_++;
            
        // } else 
        
        if(this->size_ >= this->capacity_) {

            size_t ogCap = this->capacity_;
            T* thingo = new T[ogCap * SCALE_FACTOR];

            for(size_t i = 0; i < this->size_; i++) { thingo[i] = this->data_[(front_ + i) % ogCap]; }
            delete[] this->data_;
            
            this->capacity_ = ogCap * SCALE_FACTOR;
            this->data_ = thingo;

            front_ = 0;
            back_ = size_;

        }

        this->data_[back_] = item;
        this->back_ = (back_ + 1 + capacity_) % capacity_;
        this->size_++;

    }

    // Deletion
    T popFront() override {

        if(size_ == 0 || capacity_ == 0) { throw std::runtime_error("outta bounds"); }

        T thingo = this->data_[front_];
        // this->data_[0] = NULL;
        size_--;
        front_ = (front_ + 1) % capacity_;
        shrinkIfNeeded();

        return thingo;

    }

    T popBack() override {

        if(size_ == 0 || capacity_ == 0) { throw std::runtime_error("outta bounds"); }

        T thingo = this->data_[(back_ - 1 + capacity_) % capacity_];
        // this->data_[this->size_ - 1] = NULL;
        size_--;
        back_ = (back_ - 1 + capacity_) % capacity_;
        shrinkIfNeeded();

        return thingo;

    }

    // Access
    const T& front() const override { 
        
        if(size_ == 0) { throw std::runtime_error("outta bounds"); }
        return this->data_[front_]; 
    
    }

    const T& back() const override { 
        
        if(size_ == 0) { throw std::runtime_error("outta bounds"); }
        return this->data_[(back_ - 1 + capacity_) % capacity_]; 
    
    }

    // Getters
    std::size_t getSize() const noexcept override { return this->size_; }

    void shrinkIfNeeded() {

        if(size_ <= capacity_ / 4 && capacity_ > 1) {

            size_t newCapacity = capacity_ / SCALE_FACTOR;
            T* newData = new T[newCapacity];
            
            for(size_t i = 0; i < size_; i++) { newData[i] = this->data_[(front_ + i) % capacity_]; }
            
            delete[] this->data_;
            this->data_ = newData;
            this->capacity_ = newCapacity;
            this->front_ = 0;
            this->back_ = size_;

        }

    }

    private:
    T* data_;                 // underlying dynamic array
    std::size_t capacity_;    // total allocated capacity
    std::size_t size_;        // number of stored elements
    std::size_t front_;       // index of front element
    std::size_t back_;        // index after the last element (circular)

    static constexpr std::size_t SCALE_FACTOR = 2;

};
