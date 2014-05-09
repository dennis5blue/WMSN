#include <iostream>
#include <cmath>
#include <vector>
#include "SAFactory.h"

using namespace std;
SAFactory::SAFactory(int numCameras, vector< pair<double,double> > positions, vector< vector<int> > overhearTopology, vector<int> initialSchedule):
	m_numCameras(numCameras),
	m_positions(positions),
	m_overhearTopology(overhearTopology),
	m_initialSchedule(initialSchedule)
{
	requiredTime = CalRequiredTime();
}

vector< vector<double> > SAFactory::CalRequiredTime()
{
	power = 0.125; // Watt
	bandwidth = 5000000.0; // Hz
	N0 = 0.000000000000001; // W/kHz ( calculate by pow(10.0,-12.0)/1000.0 )
	xA = m_positions.at(0).first; //Aggregator's position
	yA = m_positions.at(0).second; //Aggregator's position
	for (int cam=0; cam!=m_numCameras; ++cam)
		capacityToAggregator.push_back( CapacityToAggregatorCal(m_positions.at(cam+1).first,
			m_positions.at(cam+1).second) );
	
	vector<double> tempZero(m_numCameras, 0);
	vector< vector<double> > m_requiredTime(m_numCameras, tempZero);
	for (int i=0; i!=m_numCameras; ++i)
	{
		for (int j=0; j!=m_numCameras; ++j)
		{
			if (m_overhearTopology.at(i).at(j)>0)
				m_requiredTime.at(i).at(j) = m_overhearTopology.at(i).at(j)/capacityToAggregator.at(i);
			else
				m_requiredTime.at(i).at(j) = m_overhearTopology.at(i).at(i)/capacityToAggregator.at(i);
		}
	}
	return m_requiredTime;
}

double SAFactory::CapacityToAggregatorCal(double m_x, double m_y)
{
	double dx = m_x-xA;
	double dy = m_y-yA;
	double G = pow(10.0,(-13.11-4.281*log10(sqrt(dx*dx+dy*dy)/1000.0)));
	double C = bandwidth*log2(1+(power*G)/bandwidth/N0);
	return C;
}

