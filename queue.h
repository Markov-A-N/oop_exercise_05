#ifndef QUEUE_H
#define QUEUE_H 1

#include <iostream>
#include <memory>
#include <algorithm>

template<typename T>
class Queue {
	using value_type = T;
	using size_type = size_t;
	using reference = value_type &;
	using const_reference = const value_type &;
	using pointer = value_type *;
	using const_pointer = const value_type *;

private:
	class Node {
	public:
		Node(T val) : next{nullptr}, prev{next}, value{val} {};
		friend class Queue;
	private:
		std::shared_ptr<Node> next;
		std::weak_ptr<Node> prev;
		T value;
	};

public:

	class ForwardIterator {
	public:
		using value_type = T;
	    using reference = T&;
	    using pointer = T*;
	    using difference_type = ptrdiff_t;
	    using iterator_category = std::forward_iterator_tag;
		friend class Queue;

		ForwardIterator(std::shared_ptr<Node> it = nullptr) : ptr{it} {};

		ForwardIterator(const ForwardIterator &other) : ptr{other.ptr} {};

		ForwardIterator operator++() {
			if (ptr.lock() == nullptr) {
				return *this;
			}
			ptr = ptr.lock()->next;
			return *this;
		}

		ForwardIterator operator++(int s) {
			if (ptr.lock() == nullptr) {
				return *this;
			}
			ForwardIterator old{this->ptr.lock()};
			++(*this);
			return old;
		}

		reference operator*() {
			return ptr.lock()->value;
		}

		const_reference operator*() const {
			return ptr.lock()->value;
		}

		std::shared_ptr<Node> operator->() {
			return ptr.lock();
		}

		std::shared_ptr<const Node> operator->() const {
			return ptr.lock();
		}

		bool operator==(const ForwardIterator &rhs) const {
			return ptr.lock() == rhs.ptr.lock();
		}

		bool operator!=(const ForwardIterator &rhs) const {
			return ptr.lock() != rhs.ptr.lock();
		}

		ForwardIterator Next() const {
			if (ptr.lock() == nullptr) 
				return ForwardIterator{};
			return ptr.lock()->next;
		} 

	private:
		std::weak_ptr<Node> ptr;
	};

	Queue() : head{nullptr}, tail{head}, size{0} {};

	void Push(const T& val) {
		if (!head) {
			head = std::make_shared<Node>(val);
			tail = head;
		}
		else {
			std::shared_ptr<Node> newElem = std::make_shared<Node>(val);
			newElem->prev = tail;
			tail.lock()->next = newElem;
			tail = newElem;
		}
		size++;
	}

	ForwardIterator Insert(const ForwardIterator it, const T& val) {
		if (it == ForwardIterator{}) {
			if (tail.lock() == nullptr) {
				Push(val);
				return Begin();
			}
			std::shared_ptr<Node> newElem = std::make_shared<Node>(val);
			newElem->prev = tail;
			tail.lock()->next = newElem;
			tail = newElem;
			size++;
			return newElem;
		}
		if (it == Begin()) {
			std::shared_ptr<Node> newElem = std::make_shared<Node>(val);
			newElem->next = it.ptr.lock();
			it->prev.lock() = newElem;
			head = newElem;
			size++;
			return newElem;
		}
		std::shared_ptr<Node> newElem = std::make_shared<Node>(val);
		newElem->next = it.ptr.lock();
		it->prev.lock()->next = newElem;
		newElem->prev = it->prev;
		it->prev.lock() = newElem;
		size++;
		return newElem;
	}

	void Pop() {
		if (head) {
			head = head->next;
			size--;
		}
	}

	ForwardIterator Erase(const ForwardIterator it) {
		if (it == ForwardIterator{}) { //удаление несуществующего элемента
			return End();
		}
		if (it->prev.lock() == nullptr && head == tail.lock()) { //удаление очереди, состоящей только из одного элемента
			head = nullptr;
			tail = head;
			size = 0;
			return End();
		}
		if (it->prev.lock() == nullptr) { //удаление первого элемента
			it->next->prev.lock() = nullptr;
			head = it->next;
			size--;
			return head;
		}
		ForwardIterator res = it.Next();
		if (res == ForwardIterator{}) { //удаление последнего элемента
			it->prev.lock()->next = nullptr;
			size--;
			return End();
		}
		//удаление элементов в промежутке
		it->next->prev = it->prev;
		it->prev.lock()->next = it->next;
		size--;
		return res;
	}

	reference Front() {
		if (head == nullptr)
			throw std::out_of_range("Empty item");
		return this->head->value;
	}

	const_reference Front() const {
		if (head == nullptr)
			throw std::out_of_range("Empty item");
		return this->head->value;
	}

	reference Back() {
		if (head == nullptr)
			throw std::out_of_range("Empty item");
		return this->tail.lock()->value;
	}

	const_reference Back() const {
		if (head == nullptr)
			throw std::out_of_range("Empty item");
		return this->tail.lock()->value;
	}

	ForwardIterator Begin() {
		return head;
	}

	ForwardIterator End() {
		return ForwardIterator{};
	}

	bool Empty() const {
		return size == 0;
	}

	size_type Size() const {
		return size;
	}

	void Swap(Queue &rhs) {
		std::shared_ptr<Node> temp = head;
		head = rhs.head;
		rhs.head = temp;
	}

	void Clear() {
		head = nullptr;
		tail = head;
		size = 0;
	}

	void Print() {
		ForwardIterator it = Begin();
		std::for_each(Begin(), End(), [it, this](auto e)mutable{
			std::cout << e;
			if (it.Next() != this->End()) {
				std::cout << " <- ";
			}
			it++;
		});
		std::cout << "\n";
	}

private:
	std::shared_ptr<Node> head;
	std::weak_ptr<Node> tail;
	size_t size;
};

#endif //QUEUE_H