#pragma once
/*
 * Array Class:
 * Purely virtual, instanciate subclasses of this. Including:
 *  - FastArray from util/FastArray.h
 *  - SwapArray from util/SwapArray.h
 *
 * Advantages and Disadvantages of these implementations are found
 * In the header files
 */
 

template<class Type>
class Array{
public:
    virtual ~Array() = 0;
	virtual Type& get(int index) const = 0;
	virtual void set(int index, const Type& element) = 0; 
	virtual int size() = 0;
    virtual void swap(int firstIndex, int secondIndex) = 0;
	virtual Type& operator[](int index){
		get(index);	
	};
};
