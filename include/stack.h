#include "stdvector.hpp"
#include "iostream"

template <typename T> class stack: public stdvector<T>{
public:
    stack(int n=100000): stdvector<T>(n){
        this->size=0;
    }
    
    void resize(int n_size)=delete;
    
    void set_cap(int n_cap)=delete;
    
    
    void insert(int id,T val)=delete;
    
    bool empty() {return (this->size==0);}
    
    
    T top(){
        if (this->size==0) throw std::out_of_range("stack is empty");
        return this->data[this->size-1];
    }
    void push(T a){
        this->push_back(a);
    }
    void pop(){
        if (this->size==0) throw std::out_of_range("stack is empty");
        this->pop_back();
    }
    int get_size(){
        return this->size;
    }
    
};
