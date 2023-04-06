#include <stack>
template <class A, class B>class Tree{
private:
    struct node{
        node* l;
        node* r;
        int height;
        A key;
        B val;
        node(A key_, B val_){
            l=nullptr;
            r=nullptr;
            key=key_;
            val=val_;
            height=1;
        }
    };
    node * root=nullptr;
public:
    class iterator{
    private:
        node* data_it;
        node* root;
        iterator ()= default;
    public:
        
        explicit iterator(const Tree& t): root(t.root){};
        iterator(node* _node, node* root_) { data_it = _node; root=root_;}
        iterator(const iterator& it) { data_it = it.data_it; root=it.root; }
        bool operator ==(const iterator& it) { return data_it == it.data_it; }
        bool operator !=(const iterator& it) { return !(data_it==it.data_it); }
        std::pair<A,B&> operator*() { return {data_it->key, data_it->val}; }
        iterator& operator ++(){
            auto tmp=root;
            std::stack<node*>stack;
            while (tmp && tmp->key!=data_it->key) {
                stack.push(tmp);
                if (tmp->key>data_it->key) tmp=tmp->l;
                else tmp=tmp->r;
            }
            if (data_it->r){
                auto n=data_it->r;
                while (n->l) {
                    n=n->l;
                }
                data_it=n;
                return *this;
            }
            auto prev=data_it;
            while (stack.size() && (stack.top()->r && stack.top()->r->key==prev->key)) {
                prev=stack.top();
                stack.pop();
            }
            if (!stack.size()) data_it=nullptr;
            else data_it=stack.top();
            return *this;
        }
    };
    Tree() { root = nullptr; }
    void delete_node(node* node)
    {
        if (!node) return;
        delete_node(node->l);
        delete_node(node->r);
        delete node;
    }
    void clear() { delete_node(root); root = nullptr; }
    ~Tree() { clear(); }

    node* find(A key, node* t){
        if (!t || t->key==key) return t;
        if (t->key>key) return find(key, t->l);
        else{
            return find(key, t->r);
        }
    }
    void insert(std::pair<A, B> pa){
        root=insert_real(pa.first, pa.second, root);
    }
    node* insert_real(A key_, B val_, node* t){
        if (!t){
            t=new node(key_,val_);
        }
        else if (t->key>key_){
            t->l=insert_real(key_, val_, t->l);
        }else if (t->key<key_){
            t->r=insert_real(key_, val_, t->r);
        }else{
            t->val=val_;
        }
        return balance(t);
    }
    node* balance(node* t){
        overhight(t);
        if (hdif(t)==2){
            if (hdif(t->r)<0) t->r=rightrot(t->r);
            return leftrot(t);
        }else if (hdif(t)==-2){
            if (hdif(t->l)>0) t->l=leftrot(t->l);
            return rightrot(t);
        }
        return t;
    }
    void overhight(node* t){
        int left=height(t->l);
        int right=height(t->r);
        t->height=(left>right?left:right);
    }
    int height(node* t){
        if (t) return t->height;
        return 0;
    }
    int hdif(node *t){
        return height(t->r)-height(t->l);
    }
    node* rightrot(node* t){
        auto left=t->l;
        t->l=left->r;
        left->r=t;
        overhight(t);
        overhight(left);
        return left;
        
    }
    node* leftrot(node* t){
        auto right=t->r;
        right->r=t->l;
        t->l=right;
        overhight(right);
        overhight(t);
        return t;
    }
    node* erase(node* t, A key){
        if (!t) return t;
        if (t->key>key) t->l=erase(t->l, key);
        else if (t->key<key) t->r=erase(t->r,key);
        else{
            node* mmax=max(t->l);
            node* left;
            node* right;
            if (!mmax){
                right=t->r;
                if (t == root)
                    root = nullptr;
                delete t;
                return right;
            }
            left=t->l;
            right=t->r;
            if (t == root)
                root = nullptr;
            delete t;
            mmax->r=right;
            mmax->l=erasemax(left);
            return mmax;
        }
        t=balance(t);
        return t;
    }

    node* erasemax(node* t){
        if (t->r){
            t->r=erasemax(t->r);
            t=balance(t);
            return t;
        }
        return t->l;
    }
    node* max(node* t){
        if (t && t->r) return max(t->r);
        else return t;
    }
    node* min(node* t){
        if (t && t->l) return min(t->l);
        else return t;
    }
    node* findprev(node* t){
        return max(t->l);
    }
    void inordered_pass(node* t){
        if (!t) return;
        inordered_pass(t->l);
        std::cout<<t->key<<" ";
        inordered_pass(t->r);
    }
    iterator begin(){
        auto tmp=root;
        while (tmp && tmp->l) {
            tmp=tmp->l;
        }
        return iterator(tmp,root);
    }
    iterator end(){
        return iterator(nullptr,root);
    }
    B& operator []( const A& key){
        node* it;
        if (it=find(key,root)){
            return it->val;
        }else{
            insert(std::make_pair(key, B()));
            return find(key,root)->val;
        }
    }
    bool isbal(node* t){
        return abs(t->l->height-t->r->height)<2;
    }
    node* getroot(){return root;}

    void erase(const A& key)
    {
        erase(root, key);
    }
};
