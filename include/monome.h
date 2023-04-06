#include <string>
#include <exception>
#include <iostream>
//#include "expression_check.h"
//#pragma once
class monome{
private:
    double coef;
    int x;
    int y;
    int z;
public:
    monome()=default;
    monome(double coef_, int x_, int y_, int z_){
        coef=coef_;
        x=x_;
        y=y_;
        z=z_;
    }
    bool operator > (const monome& b){
        if (x==b.x){
            if (y==b.y){
                return z>b.z;
            }else return y>b.y;
        }else return x>b.x;
    }
    monome(std::string str){
        int ptr=0;
        int cnt=0;
        char symb[3]={'x','y','z'};
        std::string tmp;
        tmp+=str[0];
        while (ptr<str.size()) {
            tmp="";
            for(;str[ptr]!=symb[cnt] && ptr<str.size();++ptr) tmp+=str[ptr];
            if (ptr==str.size()){
                z=std::stod(tmp);
            }else{
                if (cnt==0) coef=std::stod(tmp);
                else if (cnt==1) x=std::stod(tmp);
                else if (cnt==2) y=std::stod(tmp);
            }
            cnt++;
            ptr++;
        }
    }
    //bool operator == (monome b){
    //    return x==b.x && y==b.y && z==b.z;
    //}

    bool operator ^ (const monome& b) {
        return x==b.x && y==b.y && z==b.z;
    }

    bool operator == (const monome& b)
    {
        return *this ^ b && abs(coef - b.coef) < 1e-7;
    }

    bool operator != (const monome& b) { return !(*this == b); }
    monome operator + (const monome& b){
        if (abs(coef+b.coef)<1e-7) return monome(0,0,0,0);
        return monome(coef+b.coef,x,y,z);
    }
    monome operator - (const monome& b){
        if (abs(coef-b.coef)<1e-7) return monome(0,0,0,0);
        return monome(coef-b.coef,x,y,z);
    }
    monome operator * (const monome& b){
        if (abs(coef*b.coef)<1e-7) return monome(0,0,0,0);
        return monome(coef*b.coef, x+b.x, y+b.y, z+b.z);
    }
    
    monome operator /(const monome& b){
        return monome(coef/b.coef, x-b.x, y-b.y, z-b.z);
    }
    
    monome operator * (double b){
        if (abs(b)<1e-7) return monome(0,0,0,0);
        return monome(coef*b, x, y, z);
    }
    
    monome operator /(double b){
        return monome(coef/b, x, y, z);
    }
    double getc() {return coef;}
    int getx() {return x;}
    int gety() {return y;}
    int getz() {return z;}
    monome difx(){
        if (x==0) return monome(0,0,0,0);
        return monome(coef*(x),(x>0?x-1:0),y,z);
    }
    monome dify(){
        if (y==0) return monome(0,0,0,0);
        return monome(coef*(y),x,(y>0?y-1:0),z);
    }
    monome difz(){
        if (z==0) return monome(0,0,0,0);
        return monome(coef*(z),x,y,(z>0?z-1:0));
    }
    monome intx(){
        return monome((coef/(x+1)),x+1,y,z);
    }
    monome inty(){
        return monome((coef/(y+1)),x,y+1,z);
    }
    monome intz(){
        return monome((coef/(z+1)),x,y,z+1);
    }
    friend std::ostream& operator << (std::ostream& o, monome a){
        if (abs(a.coef)<1e-7){
            return o;
        }
        if (a.coef>0)o<<"+ ";
        else o<<"- ";
        o<<abs(a.coef)<<'x'<<a.x<<'y'<<a.y<<'z'<<a.z;
        return o;
    }
};
