
#include <iostream>
#include <math.h>
#include "tools.hpp"
#include "monopoles.hpp"

// using namespace std;
int NL;

std::vector<monopole> allmono_from_file(std::string filename);
std::vector<std::vector<monopole>> allmono_from_all_confs(std::string filename);
std::vector<std::pair<coords,double>> histo(std::vector<double> proto_histo);

int main(int argc, char **argv){
  NL=32;

  std::string mono_file = argv[1];
  std::vector<std::vector<monopole>> monos;

  std::cout<<"0"<<std::endl;
  monos=allmono_from_all_confs(mono_file);

  std::cout<<"1"<<std::endl;
  std::vector<std::vector<coords>> dists;
  dists=distances_multi_conf(monos,0,0,1,0);
  std::cout<<"2"<<std::endl;
  
  std::vector<std::vector<double>> proto_histo;
  proto_histo=prepare_mean_naive_histo(dists,0);
  std::cout<<"3"<<std::endl;

  std::vector<std::pair<coords,double>> com_histo=histo(proto_histo[0]);
  std::cout<<"4"<<std::endl;

  print_naive_histo_car(com_histo,argv[2]);
  print_naive_histo_pol(com_histo,argv[3]);
  print_naive_histo_g_r(com_histo,argv[4]);
  return 0;
}
