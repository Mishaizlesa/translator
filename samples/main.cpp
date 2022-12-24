#include "solve_expr.h"
using namespace std;
int main() {
    cout<<"terms of use:\n1 enter all operators and numbers separately by space (it can be more than 1)\n2 integers and decimals are supported\n3 addition, substraction, multiplication and division are supported\n4 Variables are supported\5 Variables must start with latin letter or with _\n6 Variables can consist latin letters, '_' and numbers\n";
    string res;
    while (true) {
        cout<<"enter the expression:\n";
        getline(cin, res);
        auto tmp=solve(res);
        if (tmp.second) cout<<"INCORRECT EXPRESSION\n";
        else cout<<tmp.first<<"\n";
        string ans="1";
        //cin.ignore();
        while (ans!="y" && ans!="n") {
            cout<<"do you want to continue working with programm? (y/n) ";
            cin>>ans;
            //cin.ignore(INT_MAX);
        }
        if (ans=="n") break;
        cin.ignore();
    }
}
