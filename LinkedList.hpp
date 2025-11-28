#pragma once
#include <iostream>
using namespace std;

template <typename T>
class LinkedList {

public:

	// Behaviors
	void printForward() const {

		Node* currentNode = this->head;

		while(currentNode != nullptr) {
		
			std::cout << currentNode->data << std::endl;
			currentNode = currentNode->next; 

		}

	}
	
	void printReverse() const {

		Node* currentNode = this->tail;

		while(currentNode != nullptr) {
		
			std::cout << currentNode->data << std::endl;
			currentNode = currentNode->prev; 

		}

	}

	// Accessors
	[[nodiscard]] unsigned int getCount() const { return this->count; }

	Node* getHead() { 

		if(this->head == nullptr) { throw std::runtime_error(); }
		return this->head; 
	
	} 

	const Node* getHead() const { 
		
		if(this->head == nullptr) { throw std::runtime_error(); }
		return this->head;
	
	}

	Node* getTail() { 
		
		if(this->head == nullptr) { throw std::runtime_error(); }
		return this->tail; 
	
	}

	const Node* getTail() const { 

		if(this->head == nullptr) { throw std::runtime_error(); }
		return this->tail; 

	}

	// Insertion
	void addHead(const T& data) {

		Node* newThingy = new Node(nullptr, this->head, data);

		if(this->head == nullptr) { 
			this->head = this->tail = newThingy; 
		}
		else{ 
			this->head->prev = newThingy; 
			newThingy->next = this->head;
			this->head = newThingy;  
		}

		count++;

	}

	void addTail(const T& data) {

		Node* newThingo = new Node(this->tail, nullptr, data);

		if(this->head == nullptr) { 
			this->head = this->tail = newThingo; 
		}
		else { 
			this->tail->next = newThingo; 
			newThingo->prev = this->tail;
			this->tail = newThingo;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
		}

		count++;

	}

	// Removal
	bool removeHead() {

		if(this->head == nullptr) { 
			return false;
		} 

		if(this->head == this->tail) {

			delete this->head;
			this->head = this->tail = nullptr;

			count--;

			return true;
			
		}

		this->head = this->head->next;
		delete this->head->prev;
		this->head->prev = nullptr;

		count--;

		return true;

	}

	bool removeTail() {

		if(this->head == nullptr) { 
			return false; 
		}

		if(this->head == this->tail) {

			delete this->tail;
			this->head = this->tail = nullptr;

			count--;

			return true;

		}

		this->tail = this->tail->prev;
		delete this->tail->next;
		this->tail->next = nullptr;

		count--;		

		return true;

	}

	void Clear() {

		Node* currentNode = this->head;
		Node* thingo;

		while(currentNode != nullptr) {
		
			thingo = currentNode->next;
			delete currentNode;
			currentNode = thingo;

		}

		this->head = this->tail = nullptr;
        this->count = 0;

	}

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept {

		if(this == &other) { return *this; }

		this->Clear();

		head = other.head;
		tail = other.tail;
		count = other.count;

		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;

		return *this;

	}

	LinkedList<T>& operator=(const LinkedList<T>& rhs) {

		if(this == &rhs) { return *this; }

		this->Clear();
		
		Node* thingo = rhs.head;

		while (thingo != nullptr) {

			this->addTail(thingo->data);
			thingo = thingo->next;

		}

		return *this;

	}

	// Construction/Destruction
	LinkedList() {

		head = nullptr;
		tail = nullptr;
		count = 0;

	}

	LinkedList(Node* head, Node* tail, unsigned int count) {

		this->head = head;
		this->tail = tail;
		this->count = count;

	}
	
	LinkedList(const LinkedList<T>& list) {

		// this->head = new Node(nullptr, nullptr, T(list.head->data));
		// head->next = new Node{head,nullptr,list.head->next->data};

		this->head = nullptr;
		this->tail = nullptr;
		this->count = 0;

		Node* currentNode = list.head;

		while(currentNode != nullptr) {

			this->addTail(currentNode->data);
			currentNode = currentNode->next;

		}

	}

	LinkedList(LinkedList<T>&& other) noexcept {

		this->head = other.head;
		this->tail = other.tail;
		this->count = other.count;

		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0; 

	}

	~LinkedList() {

		Node* currentNode = this->head;
		Node* next;

		while(currentNode != nullptr) {
			next = currentNode->next;
			delete currentNode;
			currentNode = next;
		} 

	}

private:

	struct Node {

		Node* prev;
		Node* next;
		T data;

		T getData() { return this->data; }
		const T getData() { return this->data; }

		// Node() : prev(nullptr), next(nullptr), data(NULL) {}
		Node(const T& data) : prev(nullptr), next(nullptr), data(data) {}
		Node(Node* previous, Node* next, const T& data) : prev(previous), next(next), data(data) {}
		// ~Node() { delete data; }

	};

	// Stores pointers to first and last nodes and count
	Node* head;
	Node* tail;
	unsigned int count;

};