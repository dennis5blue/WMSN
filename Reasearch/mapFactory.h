#ifndef _MAPFACTORY_
#define _MAPFACTORY_
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "map.h"

class MapFactory
{
  public:
    MapFactory (const int numCameras);
    ~MapFactory ();
    Map* CreateMap ();
  
  private:
    string m_mapFileName;
    const int m_numCameras;
    Map* m_ptrMap;
};
#endif
