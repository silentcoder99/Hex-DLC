#pragma once

template <class Type>
class SuperArray {
	int length;
	Type* arrayPointer;

public:
	SuperArray(int size) {
		length = size;
		arrayPointer = new Type[size];
	}

	~SuperArray() {
		delete[] arrayPointer;
	}

	Type get(int index) {
		return arrayPointer[index];
	}

	void set(int index, Type value) {
		arrayPointer[index] = value;
	}

	int size() {
		return length;
	}

};