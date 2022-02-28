#ifndef COORDS_HPP
#define COORDS_HPP

#include <vector>
#include <tuple>
  
class coords{
private:
  int x, y, z;           //cartesian coordinates
  double r, theta, phi;  //spherical coordinates
  int subg, type;        //attributes

  friend coords min_distance(coords const &x1,coords const &x0); //min dist in periodic cube
  friend std::vector<double> prepare_naive_histo(std::vector<coords> distances);
  friend std::vector<std::vector<double>> prepare_mean_naive_histo(std::vector<std::vector<coords>> distances, bool comp_err);
  friend std::vector<std::pair<coords,double>> histo(std::vector<double> proto_histo);
  friend void print_naive_histo_car(std::vector<std::pair<coords,double>> histo, char* filename);
  friend void print_naive_histo_pol(std::vector<std::pair<coords,double>> histo, char* filename);
  friend void print_naive_histo_g_r(std::vector<std::pair<coords,double>> histo, char* filename);
public:
  coords(){};
  coords(int x0, int y0, int z0); //initialize all the coordinates
  coords operator -(coords const &x0) const; //distance vector between two
  void print_mono(FILE *file=NULL); //print all the coordinates
  

  ~coords(){};
};

#endif
