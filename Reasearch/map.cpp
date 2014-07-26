#include "map.h"
using std::cout;
using std::endl;

Map::Map (const int numCameras):
  m_numCameras (numCameras)
{
  m_corrMatrix = Eigen::MatrixXd::Zero (m_numCameras, m_numCameras);  
}
