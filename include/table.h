#include "stdvector.h"
template<class A, class B> typename stdvector<std::pair<A, B>>::iterator my_upper_bound(typename stdvector<std::pair<A, B>>::iterator l, typename stdvector<std::pair<A, B>>::iterator r, const A& val){
    int mid=0;
    int ri=r-l;
    int li=0;
    while (li<ri) {
        mid=(li+ri)/2;
        if (val>=(*(l+mid)).first) li=mid+1;
        else ri=mid;
    }
    mid=(li+ri)/2;
    return l+mid;
}



template <class A, class B> class Table{
private:
    stdvector<std::pair<A,B>>data;
    
public:
    using iterator = typename stdvector<std::pair<A,B>>::iterator;
    Table()=default;
    Table (std::initializer_list<std::pair<A, B>> list){
        for(auto el: list){
            insert(el);
        }
    }
    void insert(const std::pair<A,B>& el){
        auto it = my_upper_bound<A, B>(data.begin(), data.end(), el.first);
        auto cop=it;
        if ((*(--cop)).first==el.first) return;
        data.insert(it-data.begin(), el);
    }
    void erase_it(iterator it){
        data.erase(it-data.begin());
    }
    void erase(const A& val){
        if (search(val)){
            auto it = my_upper_bound<A, B>(data.begin(), data.end(), val);
            erase_it(--it);
        }
    }
    bool search(const A& el){
        //cout<<data.end()-data.begin()<<"\n";
        auto it = my_upper_bound<A,B>(data.begin(), data.end(), el);
        if (it==data.begin()) return false;
        
        return ((*(--it)).first==el);
    }
    B& operator [](const A& el){
        if (search(el)){
            return ((*(--my_upper_bound<A,B>(data.begin(), data.end(), el))).second);
        }else{
            insert({el,B()});
            return ((*(--my_upper_bound<A,B>(data.begin(), data.end(), el))).second);
        }
    }
    int size() {return data.get_size();}
    iterator begin(){return data.begin();}
    iterator end(){return  data.end();}
};
