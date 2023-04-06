#include "stdvector.h"
typedef long long ll;
template <class T,class fict=std::string> class my_unordered_map{
private:
    ll mod;
    ll load_factor=7;
    ll size_=0;
    struct sub{
        bool valid;
        bool used;
        sub(){
            valid=0;
        }
    };
    struct elem{
        std::string first;
        T second;
        sub th;
        elem(){
            th=sub();
        }
    };
    stdvector<elem>data;
    void repack(int size){
        stdvector<elem>tmp(data);
        data=stdvector<elem>(size);
        mod=size;
        for(int i=0;i<mod;++i){
            data[i].th.valid=0;
            data[i].th.used=0;
        }
        for(auto a: tmp){
            insert({a.first,a.second});
        }
    }
public:
    using iterator = typename stdvector<elem>::iterator;
    ll k=7;
    my_unordered_map(ll val=1e5){
        mod=val;
        data=stdvector<elem>(mod);
        for(int i=0;i<mod;++i){
            data[i].th.valid=0;
            data[i].th.used=0;
        }
    }
    my_unordered_map(std::initializer_list<std::pair<std::string,T>> init){
        if (init.size()*ll(10)>mod*load_factor) repack(init.size()*3LL);
        size_=init.size();
        mod=1e5;
        data.resize(mod);
        for(auto el: init){
            data[hash(el.first)]={el,1,0};
        }
    }
    void insert(const std::pair<std::string,T>& elem){
        ll tmp=hash(elem.first);
        ll cnt=1;
        while (data[tmp].th.valid) {
            tmp+=(tmp+cnt*cnt*k)%mod;
            cnt++;
        }
        data[tmp].second=elem.second;
        data[tmp].first=elem.first;
        data[tmp].th.valid=1;
        size_++;
        if (size_*10LL>mod*load_factor) repack(size_*5LL);
    }
    std::pair<T&,bool> find(const std::string& key){
        ll tmp=hash(key);
        ll cnt=1;
        while ((data[tmp].th.valid || data[tmp].th.used) && data[tmp].first!=key) {
            tmp+=(tmp+cnt*cnt*k)%mod;
        }
        return {data[tmp].second, data[tmp].th.valid};
    }
    void erase(const std::string& key){
        size_--;
        if (!(find(key).second)) return;
        ll tmp=hash(key);
        ll cnt=1;
        while (data[tmp].first!=key) {
            tmp+=(tmp+cnt*cnt*k)%mod;
        }
        data[tmp].th.used=1;
        data[tmp].th.valid=0;
    }
    ll hash(std::string key){
        ll res=0;
        for(int i=0;i<key.size();++i) res=(res+key[i])%mod;
        return res;
    }
    ll size(){return size_;}
    T& operator [](const std::string& key){
        auto p = find(key);
        if (p.second){
            return p.first;
        }else{
            size_++;
            if (size_*10LL>mod*load_factor) repack(size_*3LL);
            insert({key,T()});
            return find(key).first;
        }
    }
    iterator begin(){
        return data.begin();
    }
    iterator end(){
        return data.end();
    }
};
