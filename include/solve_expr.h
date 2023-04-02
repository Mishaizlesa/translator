
#ifndef solve_expr_h
#define solve_expr_h
#include "state.h"
#include "queue.h"
#include "stack.h"
#include "expression_check.h"
#include "tree.h"
#include "table.h"
#include "hash_table.h"
#include "HashTable.h"
#include "TreeT.h"
#include "TableT.h"
stdvector<std::pair<polynome,bool>> solve(std::string str, stdvector<polynome>& test){
    stdvector<std::pair<polynome,bool>> err(0);
    stdvector<std::pair<polynome,bool>> res(0);
    queue<State>inf;
    queue<State>post;
    my_unordered_map<polynome>tmp_var;
    my_unordered_map<polynome>var_hash;
    Tree<std::string,polynome>var_tree;
    Table<std::string,polynome>var_table;
    HashTable<polynome>var_hash_list;
    TreeT<std::string, polynome>var_tree_rb;
    TableT<std::string, polynome>var_table_unord;
    if (!check_str(str,inf,tmp_var)) return err;
    if (test.get_size()){
        int i=0;
        for(auto& el:tmp_var){
            el.second=test[i];
            i++;
        }
    }
    else{
        for(auto& el: tmp_var){
            if (!el.first.size()) continue;
            polynome pol;
            std::cout<<el.first<<" = ";
            std::string str;getline(std::cin,str);
            if (!str.size()) return err;
            str+=' ';
            std::size_t pos = str.find(' ');
            State prev;
            bool neg=0;
            while (pos < str.size()){
                auto tmp_str=str.substr(0, pos);
                if (tmp_str!="-" && tmp_str!="+" && tmp_str!=" "){
                    if (!checkmonome(tmp_str)){
                        return err;
                    }
                    monome mon(tmp_str);
                    if (neg){
                        mon=mon*-1;
                        neg=0;
                    }
                    pol.insert(mon);
                }else{
                    if (tmp_str=="-") neg=1;
                }
                str = str.substr(pos + 1);
                pos = str.find(' ');
            }
            el.second=pol;
        }
    }
    for(auto& el: tmp_var){
        if (!el.first.size()) continue;
        var_hash[el.first]=el.second;
        var_tree[el.first]=el.second;
        var_table[el.first]=el.second;
        var_hash_list[el.first]=el.second;
        var_tree_rb[el.first]=el.second;
        var_table_unord[el.first]=el.second;
    }
    if (!check_infix(inf,post)){
        return err;
    }
    //std::cout<<var_tree["a"]<<"\n";
    auto cop=post;
    if (!check_post(post,res,var_hash)) res.push_back({polynome(),false});
    post=cop;
    if (!check_post(post,res,var_tree)) res.push_back({polynome(),false});
    post=cop;
    if (!check_post(post,res,var_table)) res.push_back({polynome(),false});
    post=cop;
    if (!check_post(post,res,var_hash_list)) res.push_back({polynome(),false});
    post=cop;
    if (!check_post(post,res,var_tree_rb)) res.push_back({polynome(),false});
    post=cop;
    if (!check_post(post,res,var_table_unord)) res.push_back({polynome(),false});
    return res;
}
#endif /* solve_expr_h */
