#ifndef TOOLS_HPP
#define TOOLS_HPP

#include <vector>

extern int NL;

long int cart_to_lex(int x, int y, int z);
long int cartdist_to_lexhhh(int x, int y, int z);
std::vector<int> lexhhhdist_to_cart(long int lexhhh);
double avg(std::vector<double> v);
#endif
