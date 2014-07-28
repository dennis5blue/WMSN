#include "map.h"

Map::Map (const int numCameras):
  m_numCameras (numCameras)
{
  m_corrMatrix = Eigen::MatrixXd::Zero (m_numCameras, m_numCameras);  
}

Map::~Map ()
{

}

void
Map::SetCorrMatrix ()
{

}

void
Map::SetPosition (const vector<pair<double,double> >& cameraPos)
{
  for (int i=0; i!=m_numCameras; ++i){
    m_vecPairPos.push_back (cameraPos.at (i)); 
  }
  cout << "Finish postion settings" << endl;
  for (int i=0; i!=m_numCameras; ++i){
    cout << m_vecPairPos.at(i).first << " " << m_vecPairPos.at(i).second << endl;
  }
}
