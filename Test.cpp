#include "doctest.h"
#include <string>
#include <vector>
#include <array>
#include <list>
#include <iostream>
#include "range.hpp"
#include "accumulate.hpp"
#include "filterfalse.hpp"
#include "compress.hpp"
using namespace std;
using namespace itertools;

TEST_CASE("Range Test")
{
    vector<int> result1 = {1,2,3,4,5};
    int j=0;
    for(int i : range(1,6))
    {
        CHECK(i == result1.at(j));
        ++j;
    }
    CHECK(j == 5);
    CHECK(j != 4);
    CHECK(j != 0);
    CHECK(j != 6);
    
    vector<int> result2 = {-5,-4,-3,-2,-1};
    j=0;
    for(int i : range(-5,0))
    {
        CHECK(i == result2.at(j));
        ++j;
    }
    CHECK(j == 5);
    CHECK(j != 4);
    CHECK(j != 0);
    CHECK(j != 6);
    
    int ans_int=0;
    
    ans_int=-1;
    for(int i: range(0,0))
     CHECK(i == ans_int + 1); 
    
    
     ans_int=0;
    for(int i: range(1,2))
    {
    CHECK(i == ans_int + 1); 
    ++ans_int;
    }
    
     ans_int=0;
    for(int i: range(1,4))
    {
      CHECK(i == ans_int + 1);
      ++ans_int;
    }
    
     ans_int=-2;
    for(int i: range(-1,1))
    {
     CHECK(i == ans_int + 1);
     ++ans_int;
    }
}

TEST_CASE("Test Basic Accumulate")
{
    
vector<int> vecInt = {1,2,3};
vector<int> singleVecInt {1};
vector<string> vecString = {"This", "Is", "Working"};
vector<double> vecDouble = {0.5, -2.0, 3.0};
array<int, 3> a = {-1,-2,-3};
list<string> l = {"Very" , "Good" };
range r(1,3);

int ans_int=0;
string ans_str="";
double ans_d=0.0;

    ans_int=0;
    for(int i: accumulate(vecInt))
    ans_int+=i;
    CHECK(ans_int == 10); 
    
    ans_int=0;
    for(int i: accumulate(singleVecInt))
    ans_int+=i;
    CHECK(ans_int == 1); 
    
     ans_d = 0.0;
     for(double i: accumulate(vecDouble))
     ans_d+=i;
     CHECK(ans_d == 0.5); 
     
      ans_int=0;
     for(int i:accumulate(a))
     ans_int+=i;
     CHECK(ans_int == -10); 
     
      ans_int=0;
    for(int i: accumulate(r))
     ans_int+=i;
     CHECK(ans_int == 4); 
     
       ans_int=0;
     for(int i: accumulate(accumulate(vecInt)))
     ans_int+=i;
     CHECK(ans_int == 37); 
     
       ans_int=0;
     for(int i: accumulate(accumulate(accumulate(vecInt))))
     ans_int+=i;
     CHECK(ans_int == 64); 
     
    vecInt = {1,2,3};
    vector<int> result1 = {1,3,6};
    int j=0;
    for(int i : accumulate(vecInt))
    {
        CHECK(i == result1.at(j));
        ++j;
    }
    CHECK(j == 3);
    CHECK(j != 4);
    CHECK(j != 0);
    CHECK(j != 2);
    
    
    vector<int> result2 = {1};
    j=0;
    for(int i : accumulate(singleVecInt))
    {
        CHECK(i == result2.at(j));
        ++j;
    }
    CHECK(j == 1);
    CHECK(j != 2);
    CHECK(j != 0);
    
    vector<string> result3 = {"This","ThisIs","ThisIsWorking"};
    j=0;
    for(auto i : accumulate(vecString))
    {
        CHECK(i == result3.at(j));
        ++j;
    }
    CHECK(j == 3);
    CHECK(j != 2);
    CHECK(j != 0);
    CHECK(j != 4);
    
    vector<double> result4 = {0.5,1.0,1.5};
    j=0;
    for(double i : accumulate(vector<double>{0.5,0.5,0.5}))
    {
        CHECK(i == result4.at(j));
        ++j;
    }
    CHECK(j == 3);
    CHECK(j != 2);
    CHECK(j != 0);
    CHECK(j != 4);
}

TEST_CASE("Accumulate with binary operator")
{

    vector<int> result1 = {1,3,6};
    int j=0;
    for(int i : accumulate(range(1,4),[](int x, int y){return x+y;}))
    {
        CHECK(i == result1.at(j));
        ++j;
    }
    CHECK(j == 3);
    CHECK(j != 4);
    CHECK(j != 0);
    CHECK(j != 2);
    
     vector<double> result3 = {0.5,1.0,1.5};
     j=0;
    for(double i : accumulate(vector<double>{0.5,0.5,0.5},[](double x, double y){return x+y;}))
    {
        CHECK(i == result3.at(j));
        ++j;
    }
    CHECK(j == 3);
    CHECK(j != 4);
    CHECK(j != 0);
    CHECK(j != 2);


vector<int> result2 = {1,2,6};
     j=0;
    for(int i : accumulate(vector<int>{1,2,3} ,[](int x, int y){return x*y;}))
    {
        CHECK(i == result2.at(j));
        ++j;
    }
    CHECK(j == 3);
    CHECK(j != 4);
    CHECK(j != 0);
    CHECK(j != 2);

vector<string> result4 = {"This","ThisIs","ThisIsWorking"};
     j=0;
    for(string i : accumulate(vector<string>{"This","Is","Working"},[](string x, string y){return x+y;}))
    {
        CHECK(i == result4.at(j));
        ++j;
    }
    CHECK(j == 3);
    CHECK(j != 4);
    CHECK(j != 0);
    CHECK(j != 2);
}

TEST_CASE("Filter False")
{
    vector<int> result1 = {2,4,6};
    int j=0;
    for(int i : filterfalse([](int i){return i%2==0;},range(2,7)))
    {
        CHECK(i == result1.at(j));
        ++j;
    }
    CHECK(j == 3);
    CHECK(j != 4);
    CHECK(j != 0);
    CHECK(j != 2);
    
    vector<int> result2 = {2,2,2};
    j=0;
    for(int i : filterfalse([](int i){return i+i==4;},vector<int>{1,2,3,2,4,2}))
    {
        CHECK(i == result2.at(j));
        ++j;
    }
    CHECK(j == 3);
    CHECK(j != 4);
    CHECK(j != 0);
    CHECK(j != 2);
   
//     vector<string> result3 = {"aaa","bbb","ccc"};
//     j=0;
//     for(auto i : filterfalse([](string i){return i.size()==3;},vector<string>{"aa","aaa","bbb","ccc"}))
//     {
//         CHECK(i == result3.at(j));
//         ++j;
//     }
//     CHECK(j == 3);
//     CHECK(j != 4);
//     CHECK(j != 0);
//     CHECK(j != 2);
    
    vector<double> result4 = {3.2,3.6};
    j=0;
    for(double i : filterfalse([](double i){return i>3;},vector<double>{2.2,3.2,3.6}))
    {
        CHECK(i == result4.at(j));
        ++j;
    }
    CHECK(j == 2);
    CHECK(j != 3);
    CHECK(j != 1);
    CHECK(j != 0);
    
}

    
