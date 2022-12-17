
#ifndef solve_expr_h
#define solve_expr_h
#include "state.h"
#include "queue.h"
#include "stack.h"
#include "expression_check.h"
std::pair<double,bool> solve(std::string str){
    queue<State>inf;
    queue<State>post;
    std::pair<double, bool>res;
    if (!check_str(str,inf)) return {0,1};
    if (!check_infix(inf,post)){
        return {0,1};
    }
    if (!check_post(post,res)) return {0,1};
    return res;
}
#endif /* solve_expr_h */
