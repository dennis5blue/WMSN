#include "map.h"

Map::Map (const int numCameras):
  m_printOrNot (0),
  m_numCameras (numCameras)
{
  m_corrMatrix = Eigen::MatrixXd::Zero (m_numCameras, m_numCameras);  
}

Map::~Map ()
{

}

void
Map::SetCorrelation (const vector <int>& indepByte, const vector <vector <int> >& corrByte)
{
  for (std::size_t i=0; i!=indepByte.size (); ++i){
    m_corrMatrix (i, i) = indepByte.at (i);
  }
  for (std::size_t i=0; i!=corrByte.size (); ++i){
    for (std::size_t j=0; j!=corrByte.at (i).size (); ++j){
      if (i!=j){
        m_corrMatrix (i, j) = corrByte.at (i). at(j);
      }
    }
  }
  if (m_printOrNot == 1){
    cout << "Finish correlation matrix settings" << endl;
    for (int i=0; i!=m_numCameras; ++i){
      for (int j=0; j!=m_numCameras; ++j)
        cout << m_corrMatrix (i, j) << " ";
      cout << endl;
    }
  }
}

void
Map::SetPosition (const vector<pair<double,double> >& cameraPos)
{
  for (int i=0; i!=m_numCameras; ++i){
    m_vecPairPos.push_back (cameraPos.at (i)); 
  }
  if (m_printOrNot == 1){
    cout << "Finish postion settings" << endl;
    for (int i=0; i!=m_numCameras; ++i){
      cout << m_vecPairPos.at(i).first << " " << m_vecPairPos.at(i).second << endl;
    }
  }
}
