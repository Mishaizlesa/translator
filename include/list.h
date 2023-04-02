#ifndef __TDynamicList_H__
#define __TDynamicList_H__

#include<algorithm>
#include<stdexcept>
template<typename T>
class TDynamicList
{

private:
    
    struct TNode
    {
        TNode* next = nullptr;
    public:
        T value;
        TNode(const T& _value)
        {
            next = nullptr;
            value = _value;
        }
    };

    


    TNode* first = nullptr;
    TNode* last = nullptr;
    size_t sz;

public:

    struct iterator
    {
        TNode* node;
        iterator() = default;
        iterator(TNode* _node)
        {
            node = _node;
        }

        bool operator ==(const iterator& it) { return node == it.node; }
        bool operator !=(const iterator& it) { return node != it.node; }
        iterator& operator ++()
        {
            if (!node)
                throw std::logic_error("out of range");
            node = node->next;
            return *this;
        }

        T& operator*() { return node->value; }
    };

    iterator begin() { return iterator(first); }
    iterator end() { return iterator(nullptr); }
    iterator back() const noexcept { return iterator(last); }
    void clear() noexcept
    {
        while (first)
        {
            TNode* temp = first;
            first = first->next;
            delete temp;
        }
        sz = 0;
        last = nullptr;
    }

    ~TDynamicList() noexcept { clear(); }
    size_t size() const noexcept { return sz; }
    bool empty() const noexcept { return sz == 0; }

    friend void swap(TDynamicList& l1, TDynamicList& l2) noexcept
    {
        std::swap(l1.first, l2.first);
        std::swap(l1.last, l2.last);
        std::swap(l1.sz, l2.sz);
    }

    void push_back(const T& v)
    {
        if (!first)
        {
            first = new TNode(v);
            last = first;
        }
        else
        {
            last->next = new TNode(v);
            last = last->next;
        }
        sz++;
    }

    TDynamicList(const TDynamicList& other)
    {
        TDynamicList tmp;
        TNode* tmp_first = other.first;
        while (tmp_first)
        {
            tmp.push_back(tmp_first->value);
            tmp_first = tmp_first->next;
        }
        swap(*this, tmp);
    }

    TDynamicList()
    {
        first = nullptr;
        last = nullptr;
        sz = 0;
    }

    void push_front(const T& v)
    {
        TNode* tmp = first;
        first = new TNode(v);
        first->next = tmp;
        sz++;
    }

    void pop_front()
    {
        if(!first)
            throw std::logic_error("list is empty");

        TNode* tmp = first->next;
        delete first;
        first = tmp;
        sz--;
    }

    void erase_after(const iterator& it)
    {
        TNode* node = it.node;
        if(!node || !node->next)
            throw std::logic_error("invalid node");

        TNode* er_el = node->next;
        node->next = er_el ? er_el->next : nullptr;
        delete er_el;
        sz--;
    }


    void insert_after(const iterator& it, const T& value)
    {
        TNode* node = it.node;
        if (!node)
            throw std::logic_error("invalid node");

        if (node == last)
        {
            push_back(value);
            return;
        }

        TNode* tmp = node->next;
        node->next = new TNode(value);
        node->next->next = tmp;
        sz++;
    }


    TDynamicList& operator = (const TDynamicList& other)
    {
        if (this == &other)
        {
            return *this;
        }
        TDynamicList<T> tmp (other);
        swap(*this, tmp);
        return *this;
    }

    /*TDynamicList&& operator = (TDynamicList&& other)
    {
        swap(*this, other);
        return *this;
    }*/
};


#endif
