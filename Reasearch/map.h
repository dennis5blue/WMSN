#ifndef _MAP_
#define _MAP_
#include <vector>
#include <iostream>
#include <eigen3/Eigen/Core>

using std::vector;
using std::pair;
using std::cout;
using std::endl;
using std::string;

class Map
{
  public:
    Map (const int numCameras);
    ~Map ();
    void SetCorrelation (const vector <int>& indepByte, const vector <vector <int> >& corrByte);
    void SetPosition (const vector <pair <double,double> >& cameraPos);
  private:
    bool m_printOrNot;
    const int m_numCameras;
    Eigen::MatrixXd m_corrMatrix;
    vector< pair<double,double> > m_vecPairPos;
};
#endif
