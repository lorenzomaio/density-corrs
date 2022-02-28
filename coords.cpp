#ifndef COORDS_CPP
#define COORDS_CPP

#include <iostream>
#include <math.h>
#include <map>
#include <numeric>
#include "tools.hpp"
#include "coords.hpp"

using namespace std;

coords::coords(int x0, int y0, int z0)
  {
    x = x0;
    y = y0;
    z = z0;

    r = sqrt(x0*x0 + y0*y0 + z0*z0);
    theta = acos(z0/r);
    phi = atan2(y0,x0);
  }

coords coords::operator -(coords const &x0) const
{
  coords xr;
  xr.x = x - x0.x;
  xr.y = y - x0.y;
  xr.z = z - x0.z;

  xr.r = sqrt(xr.x*xr.x + xr.y*xr.y + xr.z*xr.z);
  xr.theta = acos(xr.z/xr.r);
  xr.phi = atan2(xr.y,xr.x);
  return xr;
}


void coords::print_mono(FILE *file)
{
  if( file==NULL ){
    // cout<<x<<" "<<y<<" "<<z<<endl;
    cout<<r<<" "<<theta<<" "<<phi<<endl;
  }
  else{
    fprintf(file,"%d %d %d\n",x,y,z);
  }
}
coords min_distance(coords const &x1,coords const &x0){
  coords aux = x1-x0;
  if(abs(aux.x)>=NL/2)
      aux.x=aux.x/abs(aux.x)*((NL-1)-abs(aux.x));
  if(abs(aux.y)>=NL/2)
      aux.y=aux.y/abs(aux.y)*((NL-1)-abs(aux.y));
  if(abs(aux.z)>=NL/2)
      aux.z=aux.z/abs(aux.z)*((NL-1)-abs(aux.z));

  coords res(aux.x,aux.y,aux.z);
  
  return res;
}

vector<double> prepare_naive_histo(vector<coords> distances){
  vector<double> res((NL-1)*(NL-1)*(NL-1),0);
  double factor = (distances.size())/(double)res.size();
  for (auto &a : distances)
      res[cartdist_to_lexhhh(a.x,a.y,a.z)]+=1.0;
  for (auto &a : res)
      a/=factor;
  return res;
}

//returns two vectors if you comp_err=1
vector<vector<double>> prepare_mean_naive_histo(vector<vector<coords>> distances, bool comp_err=0)
{
  vector<vector<double>> res;
  vector<double> res_c((NL-1)*(NL-1)*(NL-1),0);
  double factor = double(distances.size());
  
  for (auto &a : distances)
    {
      vector<double> tmp = prepare_naive_histo(a);
      for(int i=0;i<res_c.size();i++)
	  res_c[i]+=tmp[i];
    }
  for (auto &a : res_c)
      a/=factor;
  res.push_back(res_c);
  res_c.clear();
  
  if(comp_err)
    {
      for (auto &a : distances)
	{
	  vector<double> tmp = prepare_naive_histo(a);
	  for(int i=0;i<res[0].size();i++)
	      res_c[i]+=(tmp[i]-res[0][i])*(tmp[i]-res[0][i]);
	}
      for(auto &a : res_c)
	  a=sqrt(a)/factor;
      res.push_back(res_c);
    } 

  return res;
}

vector<pair<coords,double>> histo(vector<double> proto_histo){
  vector<pair<coords,double>> res;
  
  for (long int i = 0; i < proto_histo.size(); i++){
    vector<int> tmp=lexhhhdist_to_cart(i);
    coords pos(tmp[0],tmp[1],tmp[2]);
    res.push_back(make_pair(pos, proto_histo[i]));
  }
  
  return res;
}

void print_naive_histo_car(std::vector<std::pair<coords,double>> histo, char* filename){
  FILE * fout=fopen(filename,"w");
  for(auto &a : histo)
    {
      if (a.first.r<=NL/2)
	  fprintf(fout,"%d %d %d %lf\n",a.first.x,a.first.y,a.first.z,a.second);
    }
  fclose(fout);
}

void print_naive_histo_pol(std::vector<std::pair<coords,double>> histo, char* filename){
  map <pair<double,double>,vector<double>> pol_histo;
  for(auto &a : histo)
    {
      if (a.first.r<=NL/2){
	pol_histo[make_pair(a.first.r, a.first.theta)].push_back(a.second);
      }
    }

  FILE * fout=fopen(filename,"w");
  for(map<pair<double,double>, vector<double>>::const_iterator it = pol_histo.begin();
      it != pol_histo.end(); it++)
    {
      fprintf(fout,"%lf %lf %lf\n",it->first.first,it->first.second,avg(it->second));
    }
  fclose(fout);
}

void print_naive_histo_g_r(std::vector<std::pair<coords,double>> histo, char* filename){
  map <double,vector<double>> gr_histo;
  for(auto &a : histo)
    {
      if (a.first.r<=NL/2){
	gr_histo[a.first.r].push_back(a.second);
      }
    }
  
  FILE * fout=fopen(filename,"w");
  for(map<double, vector<double>>::const_iterator it = gr_histo.begin();
      it != gr_histo.end(); it++)
    {
      fprintf(fout,"%lf %lf\n", it->first, avg(it->second));
    }
  fclose(fout);  
}
#endif
