#ifndef MONOPOLES_HPP
#define MONOPOLES_HPP

#include <vector>

#include "coords.hpp"

class monopole{
private:
  coords loc;
  int subg, type;

  friend std::vector<monopole> allmono_from_file(std::string filename);
  friend std::vector<std::vector<monopole>> allmono_from_all_confs(std::string filename);
  friend void sort_monopoles(std::vector<monopole> &monovect);
  friend std::vector<coords> distances(std::vector<monopole> &monovect, int subg_0, int type_0, int subg_1, int type_1);
  friend std::vector<std::vector<coords>> distances_multi_conf(std::vector<std::vector<monopole>> &monovect, int subg_0, int type_0, int subg_1, int type_1);

public:
  monopole(){};
  monopole(int x0, int y0, int z0, int subg0, int type0);

  bool operator <(monopole const &other) const;
  bool operator >(monopole const &other) const;
  bool operator ==(monopole const &other) const;

  ~monopole(){};
};

#endif
