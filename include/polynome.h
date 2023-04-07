#include "monome.h"
#include "list.h"
#include <forward_list>
class polynome{
private:
    TDynamicList<monome>data;
public:
    polynome()=default;
    void insert(monome& a){
        auto it=data.begin();
        auto prev=it;
        while (it!=data.end() && a>(*it)) {
            prev=it;
            ++it;
        }
        if (it.node){
            if (*it ^ a){
                *it=*it+a;
            }else data.insert_after(it,a);
        }else{
            if (data.begin()==data.end()) data.push_front(a);
            else data.insert_after(prev,a);
        }
    }
    
    polynome operator +(polynome& b){
        polynome tmp;
        auto it=data.begin();
        while (it!=data.end()) {
            auto ins=*it;
            tmp.insert(ins);
            ++it;
        }
        it=b.data.begin();
        while (it!=data.end()) {
            auto ins=*it;
            tmp.insert(ins);
            ++it;
        }
        return tmp;
    }

    polynome operator -(polynome& b) {
        b = b * (-1);
        return *this + b;
    }
    
    polynome operator *(polynome& b){
        polynome tmp;
        auto it=data.begin();
        while(it!=data.end()){
            auto it2=b.data.begin();
            while(it2!=b.data.end()){
                auto tmp_mon1=*it;
                auto tmp_mon2=*it2;
                auto tmp_monres=tmp_mon1*tmp_mon2;
                tmp.insert(tmp_monres);
                ++it2;
            }
            ++it;
        }
        return tmp;
    }
    polynome operator *(double b){
        polynome tmp;
        auto it=data.begin();
        while(it!=data.end()){
            auto ins=*it*b;
            tmp.insert(ins);
            ++it;
        }
        return tmp;
    }
    polynome operator /(double b){
        polynome tmp;
        auto it=data.begin();
        while(it!=data.end()){
            auto ins=*it/b;
            tmp.insert(ins);
            ++it;
        }
        return tmp;
    }
    polynome operator /(polynome& b){
        polynome div;
        auto it=data.begin();
        while(it!=data.end()) {
            auto ins=*it;
            div.insert(ins);
            ++it;
            
        }
        it=div.data.begin();
        auto ptr=b.data.begin();
        polynome res;
        while((*ptr).getx()<=(*it).getx() && (*ptr).gety()<=(*it).gety() && (*ptr).getz()<=(*it).getz()){
            auto m1=*it;
            auto m2=*ptr;
            auto r=m1/m2;
            res.insert(r);
            auto tmp=ptr;
            while (tmp!=b.data.end()) {
                auto ins=*tmp*(r*-1);
                div.insert(ins);
                ++tmp;
            }
            it=div.data.begin();
        }
        return res;
    }
    bool valid(){
        return !(abs((*data.begin()).getc())<1e-7);
    }

    bool operator == (polynome p)
    {
        auto it1 = this->data.begin();
        auto it2 = p.data.begin();

        
        if (data.size() == 1 && p.data.size() == 0 && (*it1) == monome(0.0, 0, 0, 0))
            return true;

        if (data.size() == 0 && p.data.size() == 1 && (*it2) == monome(0.0, 0, 0, 0))
            return true;

        for (; it1 != this->data.end() && it2 != p.data.end(); ++it1, ++it2)
        {
            if ((*it1) != (*it2))
                return false;
        }
        return it1 == this->data.end() && it2 == p.data.end();
    }

    bool operator != (polynome p) { return !(*this == p); }
    polynome difx(){
        polynome res;
        for(auto el: data){
            auto tmp=el.difx();
            res.insert(tmp);
        }
        return res;
    }
    polynome dify(){
        polynome res;
        for(auto el: data){
            auto tmp=el.dify();
            res.insert(tmp);
        }
        return res;
    }
    polynome difz(){
        polynome res;
        for(auto el: data){
            auto tmp=el.difz();
            res.insert(tmp);
        }
        return res;
    }
    polynome intx(){
        polynome res;
        for(auto el: data){
            auto tmp=el.intx();
            res.insert(tmp);
        }
        return res;
    }
    polynome inty(){
        polynome res;
        for(auto el: data){
            auto tmp=el.inty();
            res.insert(tmp);
        }
        return res;
    }
    polynome intz(){
        polynome res;
        for(auto el: data){
            auto tmp=el.intz();
            res.insert(tmp);
        }
        return res;
    }
    friend std::ostream& operator << (std::ostream& o, polynome& a){
        auto it=a.data.begin();
        while (it!=a.data.end()) {
            o<<*it<<" ";
            ++it;
        }
        return o;
    }
    bool check_zero(){
        return abs((*data.begin()).getc())<1e7;
    }
};
