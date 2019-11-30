#include <iostream>
#include <memory>

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
		using value_type = T;
		using difference_type = ptrdiff_t;
		using reference = value_type &;
		using const_reference = const value_type &;
		using pointer = T *;
		using const_pointer = const T *;
		using iterator_category = std::forward_iterator_tag;

	public:
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

	reference Front() {
		return this->head->value;
	}

	const_reference Front() const {
		return this->head->value;
	}

	reference Back() {
		return this->tail->value;
	}

	const_reference Back() const {
		return this->tail->value;
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
		for (auto it = Begin(); it != End(); it++) {
			std::cout << *it;
			if (it.Next() != End()) {
				std::cout << " <- ";
			}
		}
		std::cout << "\n";
	}

private:
	std::shared_ptr<Node> head;
	std::weak_ptr<Node> tail;
	size_t size;
};

int main() {
	Queue<int> q;
	q.Push(10);
	q.Push(11);
	q.Push(7);
	q.Print();
	Queue<int>::ForwardIterator it = q.Begin();
	q.Insert(it, 99);
	q.Print();
	std::cout << q.Size() << "\n";
	it = q.End();
	q.Insert(it, 199);
	q.Print();
	std::cout << q.Size() << "\n";
	q.Clear();
	q.Print();
	q.Insert(it, 21);
	q.Print();
	std::cout << q.Size() << "\n";
	it++;
	q.Insert(it, 22);
	q.Print();
	it = q.Insert(it, 23);
	q.Print();
	q.Insert(it, 25);
	q.Print();

	return 0;
}