#include <iostream>
#include <memory>

template<typename T>
class Queue {
public:
	Queue() : head{nullptr}, tail{head}, size{0} {};

	void Push(const T& val) {
		if (!head) {
			head = std::make_shared<Node>(val);
			tail = head;
		}
		else {
			std::shared_ptr<Node> newElem = std::make_shared<Node>(val);
			newElem->prev.lock() = tail.lock();
			tail.lock()->next = newElem;
			tail = newElem;
		}
		size++;
	}

	void Pop() {
		head = head->next;
		size--;
	}

	void Print() {
		std::shared_ptr<Node> iterator = this->head;
		for (int i = 0; i < size; i++) {
			std::cout << iterator->value;
			if (i != size - 1) {
				std::cout << " -> ";
			}
			iterator = iterator->next;
		}
		std::cout << "\n";
	}

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
private:
	std::shared_ptr<Node> head;
	std::weak_ptr<Node> tail;
	size_t size;
};

int main() {
	Queue<int> q;
	q.Push(1);
	q.Push(2);
	q.Push(3);
	q.Pop();
	q.Pop();
	q.Pop();
	q.Print();
	return 0;
}