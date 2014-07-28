#include "mapFactory.h"
#include "utility.h"
#include <cstdio>

MapFactory::MapFactory (
    const string& posFileName,
    const string& indepFileName,
    const string& corrFileName,
    const int numCameras):
  m_ptrMap(0),
  m_numCameras(numCameras)
{
  m_posFileName = posFileName;
  m_indepFileName = indepFileName;
  m_corrFileName = corrFileName;
}

MapFactory::~MapFactory ()
{
  if (m_ptrMap != 0){
    delete m_ptrMap;
  }
}

Map* MapFactory::CreateMap ()
{
  fstream posFile;
  posFile.open (m_posFileName.c_str (), fstream::in);
  string posStrLine;
  while (getLine (posFile, posStrLine)){
    vector <string> posTokens = split (posStrLine, ' ');
    stringstream ss (posStrLine);
    double x, y;
    ss >> x >> y;
    m_vecPairTransientPos.push_back (make_pair (x,y));
  }
  if (m_vecPairTransientPos.size () != m_numCameras){
    cerr << "Error: dimension of cameras postion does not match " << endl;
    return NULL;
  }
  posFile.close ();
  m_ptrMap = new Map (m_numCameras);
  m_ptrMap -> SetPosition (m_vecPairTransientPos);
  return m_ptrMap;
}

