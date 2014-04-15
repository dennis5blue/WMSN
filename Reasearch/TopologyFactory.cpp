#include <iostream>
#include <cmath>
#include "TopologyFactory.h"
#define Inf 2147483647
using namespace std;

TopologyFactory::TopologyFactory(int numCameras, vector< pair<double,double> > positions, vector< vector<int> > corrTopology):
	m_numCameras(numCameras),
	m_positions(positions),
	m_corrTopology(corrTopology)
{
	m_power = 0.125; // Watt
	m_bandwidth = 5000000.0; // Hz
	m_N0 = 0.000000000000001; // W/kHz ( calculate by pow(10.0,-12.0)/1000.0 )
	m_corrTopology = CheckOverhear(positions, m_corrTopology);
}

vector< vector<int> > TopologyFactory::CheckOverhear(vector< pair<double,double> > positions, vector< vector<int> > m_corrTopology)
{
	double xAggregator = positions[0].first;
	double yAggregator = positions[0].second;
	int m_cameraNum = m_corrTopology.size();
	for(int i=0; i!= m_corrTopology.size(); ++i)
	{
		for(int j=0; j!=m_corrTopology[i].size(); ++j)
		{
			if(j!=i) // check if camera i can overhear camera j's transmission
			{
				double x0 = positions[i+1].first;
				double y0 = positions[i+1].second;
				double x1 = positions[j+1].first;
				double y1 = positions[j+1].second;
				double capacityToAggregator = CapacityCal(x1,y1,xAggregator,yAggregator,m_power,m_bandwidth,m_N0); // j to aggregator
				double timeToTxIdt = m_corrTopology[j][j]/capacityToAggregator; //transmission time for camera j
				double linkCapacity = CapacityCal(x0,y0,x1,y1,m_power,m_bandwidth,m_N0);
				if(timeToTxIdt*linkCapacity < m_corrTopology[j][j])
					m_corrTopology[i][j] = -1; // -1 means fail to overhear
			}
		}	
	}
	return m_corrTopology;
}

double TopologyFactory::CapacityCal(double x0, double y0, double x1, double y1, double m_power, double m_bandwidth, double m_N0)
{
	double dx = x0-x1;
	double dy = y0-y1;
	if(dx==0 && dy==0)
		dx = 1.0; //prevent from out of log's domain
	double G = pow(10.0,(-13.11-4.281*log10(sqrt(dx*dx+dy*dy)/1000.0)));
	double C = m_bandwidth*log2(1+(m_power*G)/m_bandwidth/m_N0);
	return C;
}
