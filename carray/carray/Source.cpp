#include <iostream>
#include <initializer_list>
#include <algorithm>

template <typename T, std::size_t  N>
class Array {
	T arr[N];
public:
	Array() = default;
	Array(const std::initializer_list<T>& l)  {
		auto first =arr;
		auto last =arr + N;
		auto it = l.begin();
		auto end = l.end();
		for (; first != last; ++first) {
			if (it != end) {
				*first = *it;
				++it;
			}
			else *first = 0; 
		}
	}

	class Iterator;

	friend std::ostream& operator<<(std::ostream&, const Array<T,N>& n);

	Iterator begin() { return arr; }
	Iterator end() { return arr + N; }

	class Iterator {
		T* current;
	public:
		Iterator(T* first) : current(first) {}

		T& operator+ (int n) { return *(current + n); }
		T& operator- (int n) { return *(current - n); }

		T& operator++ (int) { return *current++; }
		T& operator-- (int) { return *current--; }

		T& operator++ () { return *++current; }
		T& operator-- () { return *--current; }

		bool operator!= (const Iterator it) { return current != it.current; }
		bool operator== (const Iterator it) { return current == it.current; }
		T& operator* () { return *current; }
	};
	std::size_t size() {
		return N;
	}

	T& front() {
		return *(arr);
	}

	T& back() {
		return *(arr+(N-1));
	}

	T& operator[](const int& n) {
		if (n > 0 && n < N)
			return arr[n];
		return arr[0];
	}

	T& at(size_t n) {
		if (n >= N)
			throw std::out_of_range("...");
		return arr[n];
	 }

	void fill(const T& value) {
		auto first = arr;
		auto last = arr+N;
		for (; first != last; ++first) {
			*first = value;
		}
	}

	void print() {
		for (auto& i : arr)
			std::cout << i << " ";
		std::cout << "\n";
	}

	void sort () {
		std::sort(arr,arr+N);
	}

	auto& max() {
	 auto result = std::ranges::max_element(arr, arr + N);
	 return *result;
	}

	auto& min() {
		auto result = std::ranges::min_element(arr, arr + N);
		return *result;
	}

};

template <typename T, std::size_t N>
std::ostream operator<<(std::ostream out, const Array<T, N>& n) {
	out << Array<T,N>::arr[n];
	return out;
}
int main() {
	Array<int, 4> arr = { 5,8,7,9};
	Array<double, 3> arr1; 
	arr1.fill(5.01);
	arr1.print();
	auto it = Array<int, 4>::Iterator(arr.begin());
	std::cout << ++it << "\n";
	arr.sort();
	arr.print();
	std::cout << "max:" << arr.max() << "\n";
	std::cout << "min:" << arr.min() << "\n";

 }