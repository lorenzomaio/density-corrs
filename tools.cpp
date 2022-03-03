#ifndef TOOLS_CPP
#define TOOLS_CPP

#include <iostream>
#include "tools.hpp"

long int cart_to_lex(int x, int y, int z){
  long int lex;

  if(x < NL && y < NL && y < NL)
      lex=(x + NL*y + NL*NL*z);
  else
    {
      std::cerr<<"ERROR: cartesian coordinates out of range\
                (File: "<<__FILE__ <<" line: "<<__LINE__<<")"
	       <<std::endl;
      exit(1);
    }
  return lex;
}

long int cartdist_to_lexhhh(int x, int y, int z){
  int lex;
  
  if(abs(x) < NL/2 && abs(y) < NL/2 && abs(z) < NL/2)
    {
      lex = (NL/2-1+x) + NL*(NL/2-1+y) + NL*NL*(NL/2-1+z);
      if(lex>(NL)*(NL)*(NL))
	{
	  std::cerr<<"ERROR: lexicographic coordinates out of range "
		   <<"(File: \""<<__FILE__ <<"\" Line: "<<__LINE__<<")"
		   <<std::endl;
	  exit(1);
	} 
    }
  else
    {
      std::cerr<<"ERROR: cartesian coordinates out of range "
	       <<"(File: \""<<__FILE__ <<"\" Line: "<<__LINE__<<")"
	       <<std::endl;
      exit(1);
    }
  
  return lex;
}

std::vector<int> lexhhhdist_to_cart(long int lexhhh){
  std::vector<int> cart;

  cart.push_back((lexhhh%NL)-NL/2+1);
  lexhhh/=NL;
  cart.push_back((lexhhh%NL)-NL/2+1);
  cart.push_back((lexhhh/NL)-NL/2+1);
  
  return cart;
}  

double avg(std::vector<double> v){
  double res=0;

  for(auto &a : v)
      res+=a;
  res/=v.size();

  return res;
}

#endif
