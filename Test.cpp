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

int ans_int=0;
string ans_str="";
double ans_d=0.0;

TEST_CASE("Range Tests")
{
    CHECK_NOTHROW(range(0,0)); //1
    ans_int=-1;
    for(int i: range(0,0))
     CHECK(i == ans_int + 1); //2
    
     ans_int=0;
    for(int i: range(1,2))
    CHECK(i == ans_int + 1); //3
    
     ans_int=0;
    for(int i: range(1,4))
      CHECK(i == ans_int + 1); //4
    
    CHECK_NOTHROW(range(-1,1)); //5
     ans_int=-2;
    for(int i: range(-1,1))
     CHECK(i == ans_int + 1);
    
    CHECK_THROWS(range(2,1)); //7
    CHECK_THROWS(range(-1,-3)); //49
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
     //CHECK_NOTHROW(accumulate(vecInt)); //8
   //  CHECK_NOTHROW(accumulate(singleVecInt)); //9
   //  CHECK_THROWS(accumulate(emptyVecInt)); //10
   //  CHECK_NOTHROW(accumulate(vecString)); //11
   //  CHECK_NOTHROW(accumulate(vecDouble)); //12
   //  CHECK_NOTHROW(accumulate(a)); //13
   //  CHECK_NOTHROW(accumulate(l)); //14
   //  CHECK_NOTHROW(accumulate(r)); //15
  //   CHECK_NOTHROW(accumulate(accumulate(vecInt))); //22
     
     
       ans_int=0;
     for(int i: accumulate(vecInt))
     ans_int+=i;
    CHECK(ans_int == 10); //16
    
      ans_int=0;
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
     
      ans_int=0;
     for(int i:accumulate(a))
     ans_int+=i;
     CHECK(ans_int == -10); //20
     
     ans_str = "";
     for(string i: accumulate(l))
     ans_str+=i;
     CHECK(ans_str == "VeryVeryGood"); //21
    
      ans_int=0;
    for(int i: accumulate(r))
     ans_int+=i;
     CHECK(ans_int == 4); //23
     
       ans_int=0;
     for(int i: accumulate(accumulate(vecInt)))
     ans_int+=i;
     CHECK(ans_int == 10); // 24
     
       ans_int=0;
     for(int i: accumulate(accumulate(accumulate(vecInt))))
     ans_int+=i;
     CHECK(ans_int == 15); // 25
     
}

TEST_CASE("Accumulate With Binary Operator")
{
//      CHECK_NOTHROW(accumulate(vecInt,[](int x, int y){return x+y;})); //26
//      CHECK_NOTHROW(accumulate(singleVecInt,[](int x, int y){return x*y;})); //27
//      CHECK_THROWS(accumulate(emptyVecInt,[](int x, int y){return x+y;})); //28
//      CHECK_NOTHROW(accumulate(vecString,[](string x, string y){return x+y;}));//29
//      CHECK_THROWS(accumulate(vecString,[](string x, string y){return x*y;}));//30
//      CHECK_NOTHROW(accumulate(vecDouble,[](double x, double y){return x/y;})); //31
//      CHECK_NOTHROW(accumulate(a,[](int x, int y){return x-y;})); //32
//      CHECK_NOTHROW(accumulate(l,[](string x, string y){return x+y;})); //33
//      CHECK_NOTHROW(accumulate(r,[](int x, int y){return x+y;})); //34
//      CHECK_NOTHROW(accumulate(accumulate(vecInt),[](int x, int y){return x+y;})); //35
//      CHECK_THROWS(accumulate(accumulate(vecString,[](string x, string y){return x/y;}))); //97
     
      ans_int=0;
     for(int i: accumulate(vecInt,[](int x, int y){return x+y;}))
     ans_int+=i;
    CHECK(ans_int == 10); //36
    
     ans_int=0;
     for(int i: accumulate(vecInt,[](int x, int y){return x*y;}))
     ans_int+=i;
    CHECK(ans_int == 9); //51
    
     ans_int=0;
     for(int i: accumulate(vecInt,[](int x, int y){return x-y;}))
     ans_int+=i;
    CHECK(ans_int == -4); //52
    
      ans_int=0;
     for(int i: accumulate(singleVecInt,[](int x, int y){return x*y;}))
     ans_int+=i;
     CHECK(ans_int == 1); //37
    
    ans_str = "";
     for(string i: accumulate(vecString,[](string x, string y){return x+y;}))
     ans_str+=i;
     CHECK(ans == "ThisThisIsThisIsWorking"); //38
     
     ans_d = 0.0;
     for(double i: accumulate(vecDouble,[](double x, double y){return x/y;}))
     ans_d+=i;
     CHECK(ans == 0.2); //39
     
     ans_int=0;
     for(int i:accumulate(a,[](int x, int y){return x-y;}))
     ans_int+=i;
     CHECK(ans_int == 4); //40
     
     ans_str = "";
     for(string i: accumulate(l,[](string x, string y){return x+y;}))
     ans_str+=i;
     CHECK(ans_str == "VeryVeryGood"); //41
    
     ans_int=0;
    for(int i: accumulate(r,[](int x, int y){return x+y;}))
     ans_int+=i;
     CHECK(ans_int == 4); //42
     
     ans_int=0;
     for(int i: accumulate(accumulate(vecInt ,[](int x, int y){return x+y;}),[](int x, int y){return x+y;}))
     ans_int+=i;
     CHECK(ans_int == 15); // 43
     
      ans_int=0;
     for(int i: accumulate(accumulate(accumulate(vecInt,[](int x, int y){return x+y;}),[](int x, int y){return x+y;}),[](int x, int y){return x+y;}))
     ans_int+=i;
     CHECK(ans_int == 21); // 44
     
//      CHECK_THROWS(accumulate(vecString,[](string x, string y){return x/y;})); //45
//      CHECK_THROWS(accumulate(vecString,[](string x, string y){return x%y;})); //46
//      CHECK_THROWS(accumulate(vecString,[](string x, string y){return x-y;})); //47
     
}

struct lessThan3{
 bool oerator()(int i) const {return i<3;}
};

struct moreThan2{
 bool oerator()(int i) const {return i>2;}
};

struct equal2{
 bool oerator()(int i) const {return i==2;}
};


TEST_CASE("Filter False")
{
//   CHECK_NOTHROW(filterfalse(lessThan3{}, vecInt)); //53
//   CHECK_NOTHROW(filterfalse(moreThan2{}, vecInt)); //54
//   CHECK_NOTHROW(filterfalse(equal2{}, vecInt)); //55
//   CHECK_NOTHROW(filterfalse([](int i){return i%2==0},r)); //56
//   CHECK_NOTHROW(filterfalse([](int i){return i+i==2},r)); //57
//   CHECK_NOTHROW(filterfalse([](string i){return i+"Good"=="VeryGood"},l)); //58
//   CHECK_NOTHROW(filterfalse(moreThan2{}, accumulate(r))); //59
//   CHECK_NOTHROW(filterfalse(moreThan2{}, accumulate(vecInt,[](int x, int y){return x*y;}))); //60
//   CHECK_THROWS(filterfalse([](double i){return i/2.0==0.0}, accumulate(vecDouble))); //61
//   CHECK_NOTHROW(filterfalse([](string i){return i.size()==4},l)); //62
  
//   CHECK_THROWS(filterfalse([](int i){return i/2==0.5},vecInt)); //63
//   CHECK_THROWS(filterfalse([](int i){return i.size()==4},vecString)); //64
//   CHECK_THROWS(filterfalse([](string i){return i%2==0},vecString)); //65
//   CHECK_THROWS(filterfalse([](int i){return i%2==0},emptyVecInt)); //66
//   CHECK_THROWS(filterfalse([](string i){return i+i==2},vecString); //98
  
  ans_str ="";
  for(int i: filterfalse(  lessThan3{}, vecInt  ))
    ans_str = ans_str + to_string(i) + " ";
  CHECK(str == "1 2 "); //67
  
   ans_str ="";
  for(int i: filterfalse(  moreThan2{}, vecInt  ))
    ans_str = ans_str + to_string(i) + " ";
  CHECK(str == "3 "); //68
  
  ans_str ="";
  for(int i: filterfalse(  equal2{}, vecInt  ))
    ans_str = ans_str + to_string(i) + " ";
  CHECK(str == "2 "); //69
  
  ans_str ="";
  for(int i: filterfalse(  [](int i){return i%2==0},r  ))
    ans_str = ans_str + to_string(i) + " ";
  CHECK(str == "2 ");
  
  ans_str ="";
  for(int i: filterfalse(  [](int i){return i+i==2},r  ))
    ans_str = ans_str + to_string(i) + " ";
  CHECK(str == "1 "); //70
  
  ans_str ="";
  for(string i: filterfalse(  [](string i){return i+"Good"=="VeryGood"},l  ))
    ans_str = ans_str + to_string(i) + " ";
  CHECK(str == "Very "); //71
  
  ans_str ="";
  for(int i: filterfalse( moreThan2{}, accumulate(r)  ))
    ans_str = ans_str + to_string(i) + " ";
  CHECK(str == "3 "); //72
  
  ans_str ="";
  for(int i: filterfalse(  moreThan2{}, accumulate(vecInt,[](int x, int y){return x*y;})  ))
    ans_str = ans_str + to_string(i) + " ";
  CHECK(str == "6 "); //73
  
  ans_str ="";
  for(double i: filterfalse(  [](double i){return i/2.0==0.0}, accumulate(vecDouble)  ))
    ans_str = ans_str + to_string(i) + " ";
  CHECK(str == ""); //74
  
  ans_str ="";
  for(int i: filterfalse(  [](string i){return i.size()==4},l  ))
    ans_str = ans_str + to_string(i) + " ";
  CHECK(str == "Very "); //75
  
  TEST_CASE("Compress")
{
//   CHECK_NOTHROW(compress(string("abc"), tff)); //76
//   CHECK_NOTHROW(compress(string("abc"), fff)); //77
//   CHECK_NOTHROW(compress(string("abc"), ttt)); //78
//   CHECK_NOTHROW(compress(string("abc"), tft)); //79
//   CHECK_NOTHROW(compress(string("abc"), fft)); //80
//   CHECK_NOTHROW(compress(vecInt, ttt)); //81
//   CHECK_NOTHROW(compress(range(1,4), tff)); //82
//   CHECK_NOTHROW(compress(accumulate(vecInt), tff)); //83
//   CHECK_NOTHROW(compress( accumulate(vecInt,[](int x, int y){return x*y;}), fft) ); //84
//   CHECK_NOTHROW(compress( filterfalse([](int i){return i%2==0},accumulate(vecInt,[](int x, int y){return x*y;})), fft)); //85
//   CHECK_THROWS(compress(string("abc"), tfft)); //86
//   CHECK_THROWS(compress(string("abc"), dft)); //87
//   CHECK_THROWS(compress(string("abcd"), tff)); //88
//   CHECK_THROWS(compress(string("abc"), f ft)); //87
//    CHECK_THROWS(compress(range(1,2),tt); //99
//    CHECK_THROWS(compress(string(""),t)); //100
   
  ans_str ="";
  for(string i: compress(  string("abc"), tff  ))
    ans_str = ans_str + i + " ";
  CHECK(str == "a "); //88
  
  ans_str ="";
  for(string i: compress(  string("abc"), fff  ))
    ans_str = ans_str + i + " ";
  CHECK(str == ""); //89
  
  ans_str ="";
  for(string i: compress(  string("abc"), ttt  ))
    ans_str = ans_str + i + " ";
  CHECK(str == "a b c "); //90
  
  ans_str ="";
  for(string i: compress(  string("abc"), tft  ))
    ans_str = ans_str + i + " ";
  CHECK(str == "a c "); //91
  
  ans_str ="";
  for(int i: compress(  vecInt, ttt  ))
    ans_str = ans_str + to_string(i) + " ";
  CHECK(str == "1 2 3 "); //92
  
  ans_str ="";
  for(int i: compress(  range(1,4), tff  ))
    ans_str = ans_str + to_string(i) + " ";
  CHECK(str == "1 "); //93
  
  ans_str ="";
  for(int i: compress(  accumulate(vecInt), ftf  ))
    ans_str = ans_str + to_string(i) + " ";
  CHECK(str == "3 "); //94
  
  
  
  
  
  
  
  
 
   
  
 
  
  
  
}


