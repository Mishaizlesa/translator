
#ifndef state_h
#define state_h
#include <string>
#include <exception>
#include <map>
#include "polynome.h"
struct State{
    int type_;
    std::string data;
    enum Type{
        OPEN_BRACKET,
        CLOSE_BRACKET,
        NUMBER,
        OPERATION,
        IGNORE,
        VARIABLE,
        FUNC
    };
    State ()=default;
    State (const std::string& str){
        data=str;
        std::string str_cop(str);
        for (char& c : str_cop)
            c = tolower(c);
        if (str_cop=="difx" || str_cop=="dify" || str_cop == "difz" || str_cop=="intx" || str_cop=="inty" || str_cop=="intz") type_=FUNC;
        else if (str[0]=='('){
            type_=OPEN_BRACKET;
        }
        else if (str[0] == ')'){
            type_ = CLOSE_BRACKET;
        }
        else if ((str[0] >= '0' && str[0] <= '9' ) || str[0]=='-'){
            type_ = NUMBER;
            if (str[0]=='-'){
                data="-1";
            }
        }
        else if (str[0] == '+'  || str[0] == '*' || str[0] == '/'){
            type_ = OPERATION;
        }else if ((str[0]-'a'>=0 && str[0]-'a'<26) || str[0]=='_' || (str[0]-'A'>=0 && str[0]-'A'<26)){
            type_=VARIABLE;
        }
        else if (!str.size()) {
            type_=IGNORE;
        }
    }
    int priority(){
        if (data[0]=='+' || data[0]=='-') return 2;
        else if (data[0]=='*' || data[0]=='/') return 3;
        else if (data[0]==')' || data[0]=='(') return 1;
        else if (type_ == FUNC) return 4;
        else return 0;
    }
    
};
#endif /* state_h */
