#include "solve_expr.h"
using namespace std;
void print(stdvector<pair<polynome,bool>> arr){
    
    std::cout<<"hash_table_open_adr:\n";
    if (!arr[0].second) std::cout<<"no result(\n";
    else std::cout<<arr[0].first<<"\n";
    
    
    std::cout<<"tree_avl:\n";
    if (!arr[1].second) std::cout<<"no result(\n";
    else std::cout<<arr[1].first<<"\n";
    
    
    std::cout<<"ordered_table:\n";
    if (!arr[2].second) std::cout<<"no result(\n";
    else std::cout<<arr[2].first<<"\n";
    
    
    std::cout<<"hash_table_list:\n";
    if (!arr[3].second) std::cout<<"no result(\n";
    else std::cout<<arr[3].first<<"\n";
    
    
    std::cout<<"red-black tree:\n";
    if (!arr[4].second) std::cout<<"no result(\n";
    else std::cout<<arr[4].first<<"\n";
    
    std::cout<<"unordered_table:\n";
    if (!arr[5].second) std::cout<<"no result(\n";
    else std::cout<<arr[5].first<<"\n";
}
int main() {
    stdvector<polynome>a;
    cout<<"terms of use:\n1 enter all operators and numbers separately by space (it can be more than 1)\n2 integers and decimals are supported\n3 addition, substraction, multiplication and division are supported\n4 Variables are supported\5 Variables must start with latin letter or with _\n6 Variables can consist latin letters, '_' and numbers\n";
    string res;
    while (true) {
        cout<<"enter the expression:\n";
        getline(cin, res);
        auto tmp=solve(res,a);
        if (!tmp.get_size()) cout<<"INCORRECT EXPRESSION\n";
        else print(tmp);
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

