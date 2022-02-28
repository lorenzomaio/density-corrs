#include <iostream>
#include <math.h>
#include "tools.hpp"
#include "monopoles.hpp"

// using namespace std;
int NL;

std::vector<monopole> allmono_from_file(std::string filename);
std::vector<std::pair<coords,double>> histo(std::vector<double> proto_histo);

int main(int argc, char **argv){
  NL=48;

  std::string mono_file = argv[1];
  std::vector<monopole> monos;
  monos=allmono_from_file(mono_file);

  std::vector<coords> dist;
  dist=distances(monos,1,0,1,0);

  // for(auto &a:dist){
  //   a.print_mono();
  // }
  
  std::vector<double> proto_histo;
  proto_histo=prepare_naive_histo(dist);
  
  std::vector<std::pair<coords,double>> com_histo=histo(proto_histo);

  print_naive_histo_car(com_histo,argv[2]);
  print_naive_histo_pol(com_histo,argv[3]);
  print_naive_histo_g_r(com_histo,argv[4]);
  return 0;
}
