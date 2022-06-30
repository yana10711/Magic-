#include <iostream>
template <class T>

class List {
	template <class T>
	struct Node {
		T value;
		Node* next;
		Node(T value = T(), Node* next = nullptr) {
			this->value = value;
			this->next = next;
		}
		
	};
	std::size_t size = 0;
	Node<T>* head;
public:
	void push_back(T value) {
		if (head == nullptr)
			head = new Node<T>(value);
		else {
			Node <T>*current = this->head;
			while (current->next != nullptr) {
				current = current->next;
			}
			current->next = new Node<T>(value);
		}
		size++;

	}
	void push_front(T value) {
		head = new Node<T>(value, head);
		size++;

	}
	void clear() {
		while (size) {
			Node<T>* temp = head;
			head = head->next;
			delete temp;
			size--;
		}
	
	}
	void insert(T value,int index){
		if (index == 0)
			push_front(value);
		else {
			Node<T>* pr = this->head;
			for (int i = 0; i < index - 1; ++i) {
				pr = pr->next;
			}
			Node<T>* newnode = new Node<T>(value, pr->next);
			pr->next = newnode;
			size++;
		}
	
	}
	void print() {
		if (size == 0) std::cout << "list empty\n";
		else {

			Node<T>* temp = head;
			while (temp != nullptr) {
				std::cout << temp->value << " ";
				temp = temp->next;
			}
			std::cout << "\n";
		}
	
	}
	std::size_t Size() { return size; }
	~List() { clear(); }
};
int main() {
	List<int> lst;
	lst.push_back(4);
	lst.push_back(5);
	lst.print();
	lst.push_front(10);
	lst.push_front(20);
	lst.print();
	lst.push_back(1);
	lst.print();
	lst.insert(90, 2);
	lst.print();
	lst.clear();
	lst.print();

	
}