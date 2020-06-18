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
    vector<int> result1 {1,2,3,4,5};
    int j=0;
    for(int i : range(1,6))
    {
        CHECK(i == result1.at(j));
        ++j;
    }
    CHECK(j == 5);
    
    vector<int> result2 {-5,-4,-3,-2,-1};
    j=0;
    for(int i : range(-5,0))
    {
        CHECK(i == result2.at(j));
        ++j;
    }
    CHECK(j == 5);

    
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
    
vector<int> vecInt {1,2,3};
vector<int> singleVecInt {1};
vector<string> vecString {"This", "Is", "Working"};
vector<double> vecDouble {0.5, -2.0, 3.0};
array<int, 3> a {-1,-2,-3};
list<string> l {"Very" , "Good" };
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
    vector<int> result1 {1,3,6};
    int j=0;
    for(int i : accumulate(vecInt))
    {
        CHECK(i == result1.at(j));
        ++j;
    }
    CHECK(j == 3);

    
    
    vector<int> result2 {1};
    j=0;
    for(int i : accumulate(singleVecInt))
    {
        CHECK(i == result2.at(j));
        ++j;
    }
    CHECK(j == 1);

    
    vector<string> result3 {"This","ThisIs","ThisIsWorking"};
    j=0;
    for(auto i : accumulate(vecString))
    {
        CHECK(i == result3.at(j));
        ++j;
    }
    CHECK(j == 3);

    
    vector<double> result4 {0.5,1.0,1.5};
    j=0;
    for(double i : accumulate(vector<double>{0.5,0.5,0.5}))
    {
        CHECK(i == result4.at(j));
        ++j;
    }
    CHECK(j == 3);

}

TEST_CASE("Accumulate with binary operator")
{

    vector<int> result1 {1,3,6,10,15,21,28,36,45,55};
    int j=0;
    for(int i : accumulate(range(1,11),[](int x, int y){return x+y;}))
    {
        CHECK(i == result1.at(j));
        ++j;
    }
    CHECK(j == 10);

   

vector<int> result2 {1,2,6};
     j=0;
    for(int i : accumulate(vector<int>{1,2,3} ,[](int x, int y){return x*y;}))
    {
        CHECK(i == result2.at(j));
        ++j;
    }
    CHECK(j == 3);

}

TEST_CASE("Filter False")
{
    vector<int> result1 {2,4,6,8,10,12,14,16};
    int j=0;
    for(int i : filterfalse([](int i){return i%2!=0;},range(2,17)))
    {
        CHECK(i == result1.at(j));
        ++j;
    }
    CHECK(j == 8);

    
    vector<int> result2 {3,5,7,9,11,13,15};
    j=0;
    for(int i : filterfalse([](int i){return i%2==0;},range(2,17)))
    {
        CHECK(i == result2.at(j));
        ++j;
    }
    CHECK(j == 7);

   
    vector<int> result3 {3,6,10,15,21,28,36,45,55};
    vector<int> vec{1,2,3,4,5,6,7,8,9,10};
    j=0;
    for(int i : filterfalse([](int i){return i<2;},accumulate(vec)))
    {
        CHECK(i == result3.at(j));
        ++j;
    }
    CHECK(j == 9);

}

TEST_CASE("COMPRESS")
{
 
 vector<bool> tff{true,false,false};
 vector<bool> fff{false,false,false};
 vector<bool> ttt{true,true,true};
 vector<bool> tft{true,false,true};
 vector<bool> fft{false,false,true};
 vector<bool> tfft{true,false,false,true};
  vector<bool> ttf{true,true,false};
 vector<bool> ttfttttftt{true,true,false,true,true,true,true,false,true,true};
  CHECK_NOTHROW(compress(string("abc"), tff)); //76
  CHECK_NOTHROW(compress(string("abc"), fff)); //77
  CHECK_NOTHROW(compress(string("abc"), ttt)); //78
  CHECK_NOTHROW(compress(string("abc"), tft)); //79
  CHECK_NOTHROW(compress(string("abc"), fft)); //80
  
    vector<int> result1{2,4,6};
    int j=0;
    for(auto i : compress(vector<int>{2,4,6},ttt))
    {
        CHECK(i == result1.at(j));
        ++j;
    }
    CHECK(j == 3);

    
    vector<string> result2 = {"Hi","Bye"};
    j=0;
        for(auto i : compress(vector<string>{"Hi","Hello","Bye"},tft))
    {
        CHECK(i == result2.at(j));
        ++j;
    }
    CHECK(j == 2);

   
    vector<int> result3 = {1,2,4,5,6,7,9,10};
    j=0;
    for(int i : compress(range(1,11),ttfttttftt))
    {
        CHECK(i == result3.at(j));
        ++j;
    }
    CHECK(j == 8);
    ///////////////////
    
}

    
