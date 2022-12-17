//#include "queue.h"
bool check_lex(std::string str){
    if (!str.size() || str[0]=='(' || str[0]==')' || str[0]=='+' || str[0]=='-' || str[0]=='/' || str[0]=='*'){
            if (str.size()>1 && (str[0]=='-' || str[0]==')' || str[0]=='(' || str[0]=='+' || str[0]=='/' || str[0]=='*')) return false;
            return true;
        }
    else if (str[0]<='9' && str[0]>='0'){
        int dot_use=1;
        for(int i=1;i<str.size();++i){
            if (!isdigit(str[i]) && !(str[i]=='.' && dot_use)) return false;
            if (str[i]=='.') dot_use=0;
        }
        return true;
    }else return false;
}
bool check_str(std::string str, queue<State>& expr){
    if (!str.size()) return false;
    str+=' ';
    std::size_t pos = str.find(' ');
    State prev;
    while (pos < str.size()){
        auto tmp_str=str.substr(0, pos);
        if (!check_lex(tmp_str)) return false;
        auto tmp=State(str.substr(0, pos));
        if (prev.type_==State::NUMBER && str.substr(0, pos)[0]=='-') expr.push(State("+"));
        if (tmp.type_!=State::IGNORE){
            expr.push(tmp);
        }
        if (str.substr(0,pos)[0]=='-'){
            expr.push(State("*"));
        }
        prev=tmp;
        str = str.substr(pos + 1);
        pos = str.find(' ');
    }
    return true;
}
bool check_infix(queue<State>& expr, queue<State>& post){
    stack<State>tmp;
    while (expr.get_size()) {
        auto cur=expr.front();
        expr.pop();
        //std::cout<<cur.data<<"\n";
        switch (cur.type_) {
            case State::OPEN_BRACKET:
                tmp.push(cur);
                break;
            case State::CLOSE_BRACKET:
                cur = tmp.top();
                tmp.pop();
                while (cur.type_ != State::OPEN_BRACKET){
                    post.push(cur);
                    cur = tmp.top();
                    tmp.pop();
                    if (tmp.empty()){
                        return false;
                    }
                }
                break;
            case State::NUMBER:
                post.push(cur);
                break;
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
        if (tmp.top().type_ != State::OPERATION){
            return false;
        }
        post.push(tmp.top());
        tmp.pop();
    }
    return true;
}
bool check_post(queue<State>& expr, std::pair<double,bool>& res){
    if (expr.get_size() == 1 && expr.front().type_ == State::NUMBER){
        res=std::make_pair(std::stod(expr.front().data),0);
        return true;
    }
    stack< double > tmp;
    while (!expr.empty()){
        auto cur = expr.front();
        expr.pop();
        if (cur.type_ == State::NUMBER){
            tmp.push(std::stod(cur.data));
        }
        else{
            char operand = cur.data[0];
            if (tmp.get_size() < 2){
                return false;
            }
            double b = tmp.top();
            tmp.pop();
            double a = tmp.top();
            tmp.pop();
            switch (operand){
                case '+':
                    tmp.push(a + b);
                    break;
                case '-':
                    tmp.push(a - b);
                    break;
                case '*':
                    tmp.push(a * b);
                    break;
                case '/':
                    if (b==0) return false;
                    tmp.push(float(a) / b);
                    break;
            }
        }
    }
    if (tmp.get_size() != 1)
    {
        return false;
    }
    res={tmp.top(),0};
    return true;
}
