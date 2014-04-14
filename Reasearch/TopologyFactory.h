#ifndef TOPOLOGYFACTORY_H
#define TOPOLOGYFACTORY_H

#include <vector>
#include <utility>
using std::vector;
using std::pair;
class TopologyFactory
{
public:
	TopologyFactory(int numCameras, vector< pair<double,double> > positions, vector< vector<int> > corrTopology);
	int m_numCameras;
	vector< pair<double,double> > m_positions; // the first pair is the aggregator position
	vector< vector<int> > m_corrTopology;
	vector< vector<int> > GetTopology() const {return m_corrTopology; }

private:
	//double m_power = 0.125; // Watt
	//double m_bandwidth = 5000000.0; // Hz
	//double m_N0 = 0.000000000000001; // W/kHz ( calculate by pow(10.0,-12.0)/1000.0 )
	double m_power; // Watt
	double m_bandwidth; // Hz
	double m_N0; // W/kHz ( calculate by pow(10.0,-12.0)/1000.0 )
	int CheckOverhear(vector< pair<double,double> > positions, vector< vector<int> > *m_corrTopology);
	double CapacityCal(double x0, double y0, double x1, double y1, double m_power, double m_bandwidth, double m_N0);
	
};

#endif //TOPOLOGYFACTORY_H
