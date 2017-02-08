template<class Type>
class Array{
public:
	virtual Type& get(int index);
	virtual void set(Type element, int index); 
	virtual int size();
	virtual Type& operator[](int index){
		get(index);	
	};
};
