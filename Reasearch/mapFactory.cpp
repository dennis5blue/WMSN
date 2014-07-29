#include "mapFactory.h"
#include "utility.h"
#include <cstdio>

MapFactory::MapFactory (
    const string& posFileName,
    const string& indepFileName,
    const string& corrFileName,
    const int numCameras):
  m_numCameras(numCameras),
  m_ptrMap(0)
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
  // load cameras' position
  fstream posFile;
  posFile.open (m_posFileName.c_str (), fstream::in);
  string posStrLine;
  while (getline (posFile, posStrLine)){
    vector <string> posTokens = split (posStrLine, ' ');
    stringstream ss (posStrLine);
    double x, y;
    ss >> x >> y;
    m_vecPairTransientPos.push_back (make_pair (x,y));
  }
  std::size_t unsignCaneraNum = m_numCameras;
  if (m_vecPairTransientPos.size () != unsignCaneraNum){
    cerr << "Error: dimension of cameras postion does not match " << endl;
    return NULL;
  }
  posFile.close ();
  m_ptrMap = new Map (m_numCameras);
  m_ptrMap -> SetPosition (m_vecPairTransientPos);

  // load the correlation matrix of each cameras
  // ----------------------------------------
  // |   H(X_1)    H(X_1|X_2) ... H(X_1|X_N)|
  // | H(X_2|X_1)    H(X_2)   ... H(X_2|X_N)|
  // |      .           .              .    |
  // |      .           .              .    |
  // |      .           .              .    |
  // | H(X_N|X_1)  H(X_N_X_2) ...   H(X_N)  |
  // ----------------------------------------
  fstream indepFile;
  indepFile.open (m_indepFileName.c_str (), fstream::in);
  string indepStrLine;
  while (getline (indepFile, indepStrLine)){
    stringstream ss (indepStrLine);
    int h;
    ss >> h;
    m_vecIndepByte.push_back (h);
  }
  indepFile.close ();
  fstream corrFile;
  corrFile.open (m_corrFileName.c_str (), fstream::in);
  string corrStrLine;
  while (getline (corrFile, corrStrLine)){
    vector <string> corrTokens = split (corrStrLine, ' ');
    for (std::size_t j=0; j!=corrTokens.size (); ++j){
      stringstream ss (corrTokens.at (j));
      int h;
      ss >> h;
      m_vecTempCorrByte.push_back (h); 
    }
    m_vecVecCorrByte.push_back (m_vecTempCorrByte);
    if (m_vecTempCorrByte.size () != unsignCaneraNum){
      cerr << "Error: dimension of cameras correlation matrix does not match " << endl;
      return NULL;
    }
    else if (m_vecTempCorrByte.size () == unsignCaneraNum){
      m_vecTempCorrByte.clear ();
    }
  }
  m_ptrMap -> SetCorrelation (m_vecIndepByte, m_vecVecCorrByte);

  return m_ptrMap;
}

