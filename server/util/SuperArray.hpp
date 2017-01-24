#pragma once

template <class Type>
class Array {
	int length = 0;
	Type* arrayPointer = nullptr;

public:
	Array(int size) {
		if (size != 0) {
			length = size;
			arrayPointer = new Type[size];
		}
	}

	Array(const std::initializer_list<Type> list) {
		if (list.size() != 0) {
			length = list.size();
			arrayPointer = new Type[length];

			int elementIndex = 0;
			for (const Type& element : list) {
				arrayPointer[elementIndex] = element;
				elementIndex++;
			}
		}
	}

	Array() {
	}

	Array(const Array& other) {
		if (other.length != 0) {
			length = other.length;
			arrayPointer = new Type[length];
			for (int i = 0; i < length; i++) {
				arrayPointer[i] = other.arrayPointer[i];
			}
		}
	}

	void operator=(const Array& other) {
		if (other.length != 0) {
			length = other.length;
			delete[] arrayPointer;
			arrayPointer = new Type[length];
			for (int i = 0; i < length; i++) {
				arrayPointer[i] = other.arrayPointer[i];
			}
		}
	}

	~Array() {
		if(length != 0)
			delete[] arrayPointer;
	}

	Type& get(int index) const {
		return arrayPointer[index];
	}

	void copy(Array<Type> other) {
		if (other.size() <= size()) {
			for (int i = 0; i < other.size(); i++) {
				arrayPointer[i] = other[i];
			}
		}
	}

	void set(int index, const Type& value) {
		arrayPointer[index] = value;
	}

	int size() {
		return length;
	}

	Type& operator[](int index) {
		return get(index);
	}
};