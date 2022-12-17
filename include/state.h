
#ifndef state_h
#define state_h
#include <string>
#include <exception>
struct State{
    int type_;
    std::string data;
    enum Type{
      OPEN_BRACKET,
      CLOSE_BRACKET,
      NUMBER,
      OPERATION,
      IGNORE
    };
    State ()=default;
    State (const std::string& str){
        data=str;
        if (str[0]=='('){
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
        }
        else if (!str.size()) {
            type_=IGNORE;
        }
    }
    int priority(){
        if (data[0]=='+' || data[0]=='-') return 2;
        else if (data[0]=='*' || data[0]=='/') return 3;
        else if (data[0]==')' || data[0]=='(') return 1;
        else return 0;
    }
    
};
#endif /* state_h */
