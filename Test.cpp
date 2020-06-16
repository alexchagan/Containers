#include "doctest.h"
#include <string>
#include <vector>
#include <array>
#include <iostream>
#include "range.hpp"
#include "accumulate.hpp"
#include "filterfalse.hpp"
#include "compress.hpp"
using namespace std;

int ans_int;
string ans_str;
double ans_d;

TEST_CASE("Range Tests")
{
    CHECK_NOTHROW(range(0,0)); //1
    int ans_int=-1;
    for(int i: range(0,0))
     CHECK(i == ans_int + 1); //2
    
     int ans_int=0;
    for(int i: range(1,2))
    CHECK(i == ans_int + 1); //3
    
     int ans_int=0;
    for(int i: range(1,4))
      CHECK(i == ans_int + 1); //4
    
    CHECK_NOTHROW(range(-1,1)); //5
    int ans_int=-2;
    for(int i: range(-1,1))
     CHECK(i == ans_int + 1);
    
    CHECK_THROWS(range(2,1)); //7
    CHECK_THROWS(range(-1,-3)); //49
    CHECK_THROWS(range("a","c")); //48
    CHECK_THROWS(range(0.5,1)); //50
}

vector<int> vecInt = {1,2,3};
vector<int> singleVecInt {1};
vector<int> emptyVecInt {};
vector<string> vecString = {"This", "Is", "Working"};
vector<double> vecDouble = {0.5, -2.0, 3.0};
array<int, 3> a = {-1,-2,-3};
list<string> l = {"Very" , "Good" };
range r(1,3);


TEST_CASE("Basic Accumulate Tests")
{
     CHECK_NOTHROW(accumulate(vecInt)); //8
     CHECK_NOTHROW(accumulate(singleVecInt)); //9
     CHECK_THROWS(accumulate(emptyVecInt)); //10
     CHECK_NOTHROW(accumulate(vecString)); //11
     CHECK_NOTHROW(accumulate(vecDouble)); //12
     CHECK_NOTHROW(accumulate(a)); //13
     CHECK_NOTHROW(accumulate(l)); //14
     CHECK_NOTHROW(accumulate(r)); //15
     CHECK_NOTHROW(accumulate(accumulate(vecInt))); //22
     
      int ans_int=0;
     for(int i: accumulate(vecInt))
     ans_int+=i;
    CHECK(ans_int == 10); //16
    
     int ans_int=0;
     for(int i: accumulate(singleVecInt))
    ans_int+=i;
     CHECK(ans_int == 1); //17
    
    ans_str = "";
     for(string i: accumulate(vecString))
     ans_str+=i;
     CHECK(ans_str == "ThisThisIsThisIsWorking"); //18
      
     ans_d = 0.0;
     for(double i: accumulate(vecDouble))
     ans_d+=i;
     CHECK(ans_d == 2.5); //19
     
     int ans_int=0;
     for(int i:accumulate(a))
     ans_int+=i;
     CHECK(ans_int == -10); //20
     
     ans_str = "";
     for(string i: accumulate(l))
     ans_str+=i;
     CHECK(ans_str == "VeryVeryGood"); //21
    
     int ans_int=0;
    for(int i: accumulate(r))
     ans_int+=i;
     CHECK(ans_int == 4); //23
     
      int ans_int=0;
     for(int i: accumulate(accumulate(vecInt)))
     ans_int+=i;
     CHECK(ans_int == 10); // 24
     
      int ans_int=0;
     for(int i: accumulate(accumulate(accumulate(vecInt))))
     ans_int+=i;
     CHECK(ans_int == 15); // 25
     
}

TEST_CASE("Accumulate With Binary Operator")
{
     CHECK_NOTHROW(accumulate(vecInt,[](int x, int y){return x+y;})); //26
     CHECK_NOTHROW(accumulate(singleVecInt,[](int x, int y){return x*y;})); //27
     CHECK_THROWS(accumulate(emptyVecInt,[](int x, int y){return x+y;})); //28
     CHECK_NOTHROW(accumulate(vecString,[](int x, int y){return x+y;}));//29
     CHECK_THROWS(accumulate(vecString,[](int x, int y){return x*y;}));//30
     CHECK_NOTHROW(accumulate(vecDouble,[](int x, int y){return x/y;})); //31
     CHECK_NOTHROW(accumulate(a,[](int x, int y){return x-y;})); //32
     CHECK_NOTHROW(accumulate(l,[](int x, int y){return x*y;})); //33
     CHECK_NOTHROW(accumulate(r,[](int x, int y){return x+y;})); //34
     CHECK_NOTHROW(accumulate(accumulate(vecInt),[](int x, int y){return x+y;})); //35
     
      int ans_int=0;
     for(int i: accumulate(vecInt,[](int x, int y){return x+y;}))
     ans_int+=i;
    CHECK(ans_int == 10); //36
    
    int ans_int=0;
     for(int i: accumulate(vecInt,[](int x, int y){return x*y;}))
     ans_int+=i;
    CHECK(ans_int == 9); //51
    
    int ans_int=0;
     for(int i: accumulate(vecInt,[](int x, int y){return x-y;}))
     ans_int+=i;
    CHECK(ans_int == -4); //52
    
     int ans_int=0;
     for(int i: accumulate(singleVecInt,[](int x, int y){return x*y;}))
     ans_int+=i;
     CHECK(ans_int == 1); //37
    
    ans_str = "";
     for(string i: accumulate(vecString,[](int x, int y){return x+y;}))
     ans_str+=i;
     CHECK(ans == "ThisThisIsThisIsWorking"); //38
     
     ans_d = 0.0;
     for(double i: accumulate(vecDouble,[](int x, int y){return x/y;}))
     ans_d+=i;
     CHECK(ans == 0.2); //39
     
      int ans_int=0;
     for(int i:accumulate(a,[](int x, int y){return x-y;}))
     ans_int+=i;
     CHECK(ans_int == 4); //40
     
     ans_str = "";
     for(string i: accumulate(l,[](int x, int y){return x+y;}))
     ans_str+=i;
     CHECK(ans_str == "VeryVeryGood"); //41
    
     int ans_int=0;
    for(int i: accumulate(r,[](int x, int y){return x+y;}))
     ans_int+=i;
     CHECK(ans_int == 4); //42
     
     int ans_int=0;
     for(int i: accumulate(accumulate(vecInt ,[](int x, int y){return x+y;}),[](int x, int y){return x+y;}))
     ans_int+=i;
     CHECK(ans_int == 15); // 43
     
     int ans_int=0;
     for(int i: accumulate(accumulate(accumulate(vecInt,[](int x, int y){return x+y;}),[](int x, int y){return x+y;}),[](int x, int y){return x+y;}))
     ans_int+=i;
     CHECK(ans_int == 21); // 44
     
     CHECK_THROWS(accumulate(vecString,[](int x, int y){return x/y;})); //45
     CHECK_THROWS(accumulate(vecString,[](int x, int y){return x%y;})); //46
     CHECK_THROWS(accumulate(vecString,[](int x, int y){return x-y;})); //47
     
}


