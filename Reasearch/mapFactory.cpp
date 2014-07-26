#include "mapFactory.h"

MapFactory::MapFactory (
    const string& mapFileName,
    const int numCameras):
  m_ptrMap(0),
  m_numCameras(numCameras)
{
  m_mapFileName = mapFileName;
}

MapFactory::~MapFactory ()
{
  if (m_ptrMap != 0){
    delete m_ptrMap;
  }
}

Map* MapFactory::CreateMap ()
{
  
}

