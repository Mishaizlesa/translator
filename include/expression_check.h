//#include "queue.h"
bool check_num(std::string str){
    int dot_use=1;
    for(int i=0;i<str.size();++i){
        if (!isdigit(str[i]) && !(str[i]=='.' && dot_use)) return false;
        if (str[i]=='.') dot_use=0;
    }
    return true;
}
bool checkmonome(std::string str){
    if (!str.size()) return false;
    int ptr=0;
    int cnt=0;
    char symb[3]={'x','y','z'};
    std::string tmp;
    while (ptr<str.size()) {
        tmp="";
        for(;check_num(std::string(1,str[ptr])) && ptr<str.size() ;++ptr) tmp+=str[ptr];
        if (ptr==str.size()){
            if (cnt!=3) return false;
        }
        else if (str[ptr]!=symb[cnt]) return false;
        if (cnt==3 && ptr!=str.size()) return false;
        cnt++;
        ptr++;
    }
    return true;
}
bool check_var(std::string str){
    for(auto el: str){
        if ((el-'a'<0 || el-'a'>=26) && (el!='_') && (el-'0'<0 || el-'0'>9) && (el-'A'<0 || el-'A'>25)) {
            return false;
        }
    }
    return true;
}
bool check_func(std::string str){
    for (char& c : str)
        c = tolower(c);
    return (str=="difx" || str=="dify" || str == "difz" || str=="intx" || str=="inty" || str=="intz");
}
bool check_lex(std::string str){
    if (check_func(str)) return true;
    if (!str.size() || str[0]=='(' || str[0]==')' || str[0]=='+' || str[0]=='-' || str[0]=='/' || str[0]=='*'){
        if (str.size()>1 && (str[0]=='-' || str[0]==')' || str[0]=='(' || str[0]=='+' || str[0]=='/' || str[0]=='*')) return false;
        return true;
    }
    else if (str[0]<='9' && str[0]>='0'){
        return check_num(str);
    }else if ((str[0]-'a'>=0 && str[0]-'a'<26) || str[0]=='_' || (str[0]-'A'>=0 && str[0]-'A'<26)) return check_var(str);
    else return false;
}
template <class arr>bool check_str(std::string str, TDynamicQueue<State>& expr, arr& var){
    if (!str.size()) return false;
    str+=' ';
    std::size_t pos = str.find(' ');
    State prev;
    while (pos < str.size()){
        auto tmp_str=str.substr(0, pos);
        if (!check_lex(tmp_str)) return false;
        auto tmp=State(str.substr(0, pos));
        if ((prev.type_==State::NUMBER || prev.type_==State::VARIABLE) && str.substr(0, pos)[0]=='-') expr.push(State("+"));
        if (tmp.type_!=State::IGNORE){
            expr.push(tmp);
        }
        if (str.substr(0,pos)[0]=='-'){
            expr.push(State("*"));
        }
        if (tmp.type_==State::VARIABLE){
            var[tmp.data];
        }
        prev=tmp;
        str = str.substr(pos + 1);
        pos = str.find(' ');
    }
    return true;
}
bool check_infix(TDynamicQueue<State>& expr, TDynamicQueue<State>& post){
    stack<State>tmp;
    while (expr.size()) {
        auto cur=expr.front();
        expr.pop();
        //std::cout<<cur.data<<"\n";
        switch (cur.type_) {
            case State::OPEN_BRACKET:
                tmp.push(cur);
                break;
            case State::CLOSE_BRACKET:
                if (tmp.empty()) return false;
                cur = tmp.top();
                tmp.pop();
                while (cur.type_ != State::OPEN_BRACKET){
                    post.push(cur);
                    if (tmp.empty()){
                        return false;
                    }
                    cur = tmp.top();
                    tmp.pop();
                }
                break;
            case State::NUMBER:
                post.push(cur);
                break;
            case State::VARIABLE:
                post.push(cur);
                break;
            case State::FUNC:
                post.push(State("0"));
            case State::OPERATION:
                while (!tmp.empty() && tmp.top().priority() >= cur.priority()){
                    post.push(tmp.top());
                    tmp.pop();
                }
                tmp.push(cur);
                break;
        }
    }
    while (!tmp.empty()){
        if (tmp.top().type_ != State::OPERATION && tmp.top().type_!=State::FUNC){
            return false;
        }
        post.push(tmp.top());
        tmp.pop();
    }
    return true;
}
template <class arr> bool check_post(TDynamicQueue<State>& expr, stdvector<std::pair<polynome,bool>>& res,arr& var){
    if (expr.size() == 1){
        if (expr.front().type_==State::VARIABLE){
            res.push_back({var[expr.front().data],0});
        }else if (expr.front().type_==State::NUMBER){
            polynome pol;
            monome tmp(std::stod(expr.front().data),0,0,0);
            pol.insert(tmp);
            res.push_back({pol,0});
        }
    }
    stack< polynome > tmp;
    while (!expr.empty()){
        auto cur = expr.front();
        expr.pop();
        if (cur.type_ == State::NUMBER){
            polynome pol;
            monome tmp_m(std::stod(cur.data),0,0,0);
            pol.insert(tmp_m);
            tmp.push(pol);
        }else if (cur.type_==State::VARIABLE){
            tmp.push(var[cur.data]);
        }else if (cur.type_==State::FUNC){
            if (tmp.get_size()==0) return false;
            auto b=tmp.top();
            tmp.pop();
            auto a=tmp.top();
            tmp.pop();
            polynome c;
            auto tmp_str = cur.data;
            for (char& ch : tmp_str)
                ch = tolower(ch);
            if (tmp_str == "difx") c = b.difx();
            if (tmp_str == "dify") c = b.dify();
            if (tmp_str == "difz") c = b.difz();
            if (tmp_str == "intx") c = b.intx();
            if (tmp_str == "inty") c = b.inty();
            if (tmp_str == "intz") c = b.intz();
            tmp.push(c);
        }
        else{
            char operand = cur.data[0];
            if (tmp.get_size() < 2){
                return false;
            }
            auto b = tmp.top();
            tmp.pop();
            auto a = tmp.top();
            tmp.pop();
            switch (operand){
                case '+':
                    tmp.push(a + b);
                    break;
                case '-':{
                    b= b*-1;
                    tmp.push(a + b);
                    break;}
                case '*':
                    tmp.push(a * b);
                    break;
                case '/':
                    if (b.check_zero()) return false;
                    tmp.push(a / b);
                    break;
            }
        }
    }
    if (tmp.get_size() != 1)
    {
        return false;
    }
    res.push_back({tmp.top(),1});
    return true;
}
