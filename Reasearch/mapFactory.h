#ifndef _MAPFACTORY_
#define _MAPFACTORY_
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "map.h"

using std::string;
using std::cout;
using std::endl;
using std::cerr;
using std::pair;
using std::vector;
using std::fstream;
using std::stringstream;
using std::make_pair;

class MapFactory
{
  public:
    MapFactory (
        const string& posFileName,
        const string& indepFileName,
        const string& corrFileName,
        const int numCameras);
    ~MapFactory ();
    Map* CreateMap ();
  
  private:
    string m_posFileName;
    string m_indepFileName;
    string m_corrFileName;
    const int m_numCameras;
    vector< pair<double,double> > m_vecPairTransientPos;
    Map* m_ptrMap;
};
#endif
