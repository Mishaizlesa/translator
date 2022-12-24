
#ifndef solve_expr_h
#define solve_expr_h
#include "state.h"
#include "queue.h"
#include "stack.h"
#include "expression_check.h"
std::pair<double,bool> solve(std::string str){
    queue<State>inf;
    queue<State>post;
    std::map<std::string,double>var;
    std::pair<double, bool>res;
    if (!check_str(str,inf,var)) return {0,1};
    for(auto& el: var){
        std::cout<<el.first<<" = ";
        std::cin>>el.second;
    }
    if (!check_infix(inf,post)){
        return {0,1};
    }
    if (!check_post(post,res,var)) return {0,1};
    return res;
}
#endif /* solve_expr_h */
