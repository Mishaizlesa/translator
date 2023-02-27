#include "stdvector.hpp"
template <typename T> class queue: public stdvector<T>{
private:
    T* head, *tail;
public:
    queue(int n=100000): stdvector<T>(n){
        this->size=0;
        head=this->data;
        tail=this->data;
    }
    void resize(int n_size)=delete;
    
    
    T& operator [](int i)=delete;
    
    void insert(int i,T val)=delete;
    
    bool empty() {return (this->size==0);}
    
    T front(){
        if (this->empty()) throw std::out_of_range("queue is empty");
        return *head;
    }
    void push(T a){
        if (tail==head){
            this->set_cap(this->capacity*2);
            head = this->data;
            tail = this->data + this->size;
        }
        *tail = a;
        tail = this->data + (tail - this->data + 1) % this->capacity;
        this->size++;
    }
    void pop(){
        if (this->empty()) throw std::out_of_range("queue is empty");
        head = this->data+(head - this->data + 1)%this->capacity;
        this->size--;
    }
    int get_size() {return this->size;}
};
