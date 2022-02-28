#ifndef MONOPOLES_CPP
#define MONOPOLES_CPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <vector>
#include <algorithm>

#include "monopoles.hpp"
using namespace std;

monopole::monopole(int x0, int y0, int z0, int subg0, int type0)
{
  coords aux(x0,y0,z0);
  loc=aux;
  
  subg=subg0;
  type=type0;
}

//read monopoles from file. NOT SUITABLE FOR MULTI-CONF FILES
vector<monopole> allmono_from_file(string filename)
{
  vector<monopole> res;
  fstream myfile(filename, ios_base::in);
  int pos[3],subg0,type0;
  int timeslice;

  while (myfile>>timeslice)
    {
      for (int i = 0; i < 3; i++)
	  myfile >> pos[i];
      
      myfile >> subg0;
      myfile >> type0;
      monopole tmp(pos[0],pos[1],pos[2],subg0,type0);
      
      res.push_back(tmp);
    }
  myfile.close();
  
  sort(res.begin(),res.end());
  return res;
}

//group read monopoles in different vectors for different confs
vector<vector<monopole>> allmono_from_all_confs(string filename)
{
  vector<vector<monopole>> res;
  vector<monopole> mc;
  string line;

  fstream fin(filename, ios_base::in);  
  getline(fin,line);
  if(line[0]!='#')
      cerr<<"Invalid start of input file"<<endl;
  while(getline(fin,line))
    {
      if(line[0]=='#')
	{
	  sort(mc.begin(),mc.end());
	  res.push_back(mc);
	  mc.clear();
	  continue;
	}

      int subg,type,pos[3];
      stringstream stream(line);
      
      for(int i = 0; i <3; i++)
	  stream>>pos[i];
      stream>>subg;
      stream>>type;

      monopole tmp(pos[0],pos[1],pos[2],subg,type);
      mc.push_back(tmp);
            
    }
  sort(mc.begin(),mc.end());
  res.push_back(mc);
  mc.clear();
  fin.close();
  
  return res;
}

bool monopole::operator <(monopole const &other) const
{
  bool res;
  res=subg<other.subg;

  if(!res)
      res=type<other.type;
  
  return res;
}

bool monopole::operator >(monopole const &other) const
{
  bool res;
  res=subg>other.subg;

  if(!res)
      res=type>other.type;
  
  return res;
}

bool monopole::operator ==(monopole const &other) const
{
  bool res;
  res = subg==other.subg && type==other.type;

  return res;
}

void sort_monopoles(vector<monopole> &monovect)
{
  sort(monovect.begin(),monovect.end());
}

//works only if monopoles are sorted according to type and subg
vector<coords> distances(vector<monopole> &monovect, int subg_0, int type_0, int subg_1, int type_1)
{
  vector<coords> res;
  int i=0;
  while(!(monovect[i].subg == subg_0 && monovect[i].type == type_0))
      i++;
  int s0=i;
  while(monovect[i].subg == subg_0 && monovect[i].type == type_0)
      i++;
  int e0=i;

  if(subg_0!=subg_1 || type_0!=type_1){
    i=0;
    while(!(monovect[i].subg == subg_1 && monovect[i].type == type_1))
	i++;
    int s1=i;
    while(monovect[i].subg == subg_1 && monovect[i].type == type_1)
	i++;
    int e1=i;
    for (int j = s0; j<e0; j++)
	for(int k = s1; k<e1; k++)
	    res.push_back(min_distance(monovect[k].loc,monovect[j].loc));
  }
  else{
    for (int j = s0; j<e0; j++)
	for (int k = s0; k<e0; k++)
	    if(k!=j)
		res.push_back(min_distance(monovect[k].loc,monovect[j].loc));
  }

  return res;
}

vector<vector<coords>> distances_multi_conf(vector<vector<monopole>> &monovect, int subg_0, int type_0, int subg_1, int type_1)
{
  vector<vector<coords>> res;
  for(auto &a:monovect)
      res.push_back(distances(a,subg_0,type_0,subg_1,type_1));
  return res;
}

#endif
