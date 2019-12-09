#include <iostream>
#include <string>
#include <algorithm>
#include <exception>
#include "queue.h"
#include "triangle.h"
#include "vertex.h"
#include "vector.h"

int main() {
	Queue<Triangle<int>> q;

	std::string cmd;

	std::cout << "Operations: Add/ Remove/ Print/ Front/ Back/ Count_if/ Menu/ Exit" << std::endl;
	std::cout << "______________________________________" << std::endl;
	while (std::cin >> cmd) {
		if (cmd == "Add") {
			std::cout << "______________________________________" << std::endl;
			std::cout << "Add an item to the back of the queue[Push] or to the iterator position[Iter]" << std::endl;
			std::cout << "______________________________________" << std::endl;
			std::cin >> cmd;
			std::cout << "______________________________________" << std::endl;
			if (cmd == "Push") {
				Triangle<int> t;
				std::cout << "Input points: ";
				try {
					std::cin >> t;
				}
				catch (std::exception &e) {
					std::cout << e.what() << std::endl;
					std::cout << "______________________________________" << std::endl;
					continue;
				}
				
				q.Push(t);
				std::cout << "______________________________________" << std::endl;
			}
			else if (cmd == "Iter") {
				Triangle<int> t;
				std::cout << "Input points: ";
				try {
					std::cin >> t;
				}
				catch (std::exception &e) {
					std::cout << e.what() << std::endl;
					std::cout << "______________________________________" << std::endl;
					continue;
				}
				std::cout << "______________________________________" << std::endl;
				std::cout << "Input index: ";
				unsigned int i;
				std::cin >> i;
				std::cout << "______________________________________" << std::endl;
				if (i > q.Size()) {
					std::cout << "The index must be less than the number of elements" << std::endl;
					std::cout << "______________________________________" << std::endl;
					continue;
				}
				Queue<Triangle<int>>::ForwardIterator it = q.Begin();
				for (unsigned int cnt = 0; cnt < i; cnt++) {
					it++;
				}
				q.Insert(it, t);
			}
			else {
				std::cout << "Invalid input" << std::endl;
				std::cin.clear();
				std::cin.ignore(30000, '\n');
				std::cout << "______________________________________" << std::endl;
				continue;
			}
		}
		else if (cmd == "Remove") {
			std::cout << "______________________________________" << std::endl;
			if (q.Empty()) {
				std::cout << "Queue is empty" << std::endl;
				std::cout << "______________________________________" << std::endl;
				continue;
			}
			std::cout << "Delete item from front of queue[Pop] or to the iterator position[Iter]" << std::endl;
			std::cout << "______________________________________" << std::endl;
			std::cin >> cmd;
			std::cout << "______________________________________" << std::endl;
			if (cmd == "Pop") {
				q.Pop();
			}
			else if (cmd == "Iter") {
				std::cout << "Input index: ";
				unsigned int i;
				std::cin >> i;
				std::cout << "______________________________________" << std::endl;
				if (i > q.Size()) {
					std::cout << "The index must be less than the number of elements" << std::endl;
					std::cout << "______________________________________" << std::endl;
					continue;
				}
				Queue<Triangle<int>>::ForwardIterator it = q.Begin();
				for (unsigned int cnt = 0; cnt < i; cnt++) {
					it++;
				}
				q.Erase(it);
			}
			else {
				std::cout << "Invalid input" << std::endl;
				std::cin.clear();
				std::cin.ignore(30000, '\n');
				std::cout << "______________________________________" << std::endl;
				continue;
			}
		}
		else if (cmd == "Print") {
			std::cout << "______________________________________" << std::endl;
			q.Print();
			std::cout << "______________________________________" << std::endl;
		}
		else if (cmd == "Front") {
			std::cout << "______________________________________" << std::endl;
			Triangle<int> value;
			try {
				value = q.Front();
			}
			catch (std::exception &e) {
				std::cout << e.what() << std::endl;
				std::cout << "______________________________________" << std::endl;
				continue;
			}
			std::cout << value << std::endl;
			std::cout << "______________________________________" << std::endl;
		}
		else if (cmd == "Back") {
			std::cout << "______________________________________" << std::endl;
			Triangle<int> value;
			try {
				value = q.Back();
			}
			catch (std::exception &e) {
				std::cout << e.what() << std::endl;
				std::cout << "______________________________________" << std::endl;
				continue;
			};
			std::cout << value << std::endl;
			std::cout << "______________________________________" << std::endl;
		}
		else if (cmd == "Count_if") {
			std::cout << "______________________________________" << std::endl;
			std::cout << "Input area: ";
			double area;
			std::cin >> area;
			std::cout << "______________________________________" << std::endl;
			std::cout << "The number of figures with an area less than a given " << std::count_if(q.Begin(), q.End(), [area](Triangle<int> t){
				return Area(t) < area;
			}) << std::endl;
			std::cout << "______________________________________" << std::endl;
		}
		else if (cmd == "Menu") {
			std::cout << "______________________________________" << std::endl; 
			std::cout << "Operations: Add/ Remove/ Print/ Front/ Back/ Count_if/ Menu/ Exit" << std::endl;
			std::cout << "______________________________________" << std::endl; 
		}
		else if (cmd == "Exit") {
			break;
		}
		else {
			std::cout << "______________________________________" << std::endl; 
			std::cout << "Invalid input" << std::endl;
			std::cin.clear();
			std::cin.ignore(30000, '\n');
			std::cout << "______________________________________" << std::endl; 
		}
	}

	return 0;
} 