#include <iostream>
#include <cmath>
#include <vector>
#include "SinrScheduling.h"

using namespace std;
SinrScheduling::SinrScheduling(int numCameras, vector< pair<double,double> > positions, vector< vector<int> > overhearTopology):
	m_numCameras(numCameras),
	m_positions(positions),
	m_overhearTopology(overhearTopology)
{
	indepRequiredTime = CalIndepRequiredTime();
	transSchedule = GenerateScheduleMostFirst();
	transSchedule2 = GenerateScheduleLeastFirst();
}

vector<int> SinrScheduling::GenerateScheduleMostFirst()
{
	vector<int> m_transSchedule;
	vector<double> m_capacityToAggregator = capacityToAggregator;
	vector<double> m_indepRequiredTime = indepRequiredTime;
	vector<int> m_indepTransByte;
	for (int k=0; k!=m_numCameras; ++k)
		m_indepTransByte.push_back( m_overhearTopology.at(k).at(k) );
	
	for (int i=0; i!=m_numCameras; ++i)
	{
		int nextCamera = 0;
		for (int j=1; j!=m_numCameras; ++j)
		{
			if ( m_indepTransByte.at(j) > m_indepTransByte.at(j-1) )
				nextCamera = j;
		}
		m_indepTransByte.at(nextCamera) = 0; //set it to zero, indicates that we have scheduled this camera 
		m_transSchedule.push_back(nextCamera);	
	}	
	return m_transSchedule;
}

vector<int> SinrScheduling::GenerateScheduleLeastFirst()
{
	vector<int> m_transSchedule;
	for (int i=0; i!=m_numCameras; ++i)
	{
		m_transSchedule.push_back( transSchedule.at(m_numCameras-i-1) );
	}	
	return m_transSchedule;
}

vector<double> SinrScheduling::CalIndepRequiredTime()
{
	power = 0.125; // Watt
	bandwidth = 5000000.0; // Hz
	N0 = 0.000000000000001; // W/kHz ( calculate by pow(10.0,-12.0)/1000.0 )
	xA = m_positions.at(0).first; //Aggregator's position
	yA = m_positions.at(0).second; //Aggregator's position
	for (int cam=0; cam!=m_numCameras; ++cam) //Note that position.at(0) is the aggregator
		capacityToAggregator.push_back( CapacityToAggregatorCal(m_positions.at(cam+1).first,
			m_positions.at(cam+1).second) );
	
	vector<double> m_indepRequiredTime;
	for (int i=0; i!=m_numCameras; ++i)
	{
		double indepTime = 8*m_overhearTopology.at(i).at(i) / capacityToAggregator.at(i);
		m_indepRequiredTime.push_back(indepTime);
	}
	return m_indepRequiredTime;
}

double SinrScheduling::CapacityToAggregatorCal(double m_x, double m_y)
{
	double dx = m_x-xA;
	double dy = m_y-yA;
	double G = pow(10.0,(-13.11-4.281*log10(sqrt(dx*dx+dy*dy)/1000.0)));
	double C = bandwidth*log2(1+(power*G)/bandwidth/N0);
	return C;
}

void SinrScheduling::PrintSchedule()
{
	cout << "Transmission Schedule: ";
	for (int i=0; i!=transSchedule.size(); ++i)
		cout << transSchedule.at(i) << " ";
	cout << endl;
}

void SinrScheduling::PrintSchedule2()
{
	cout << "Transmission Schedule: ";
	for (int i=0; i!=transSchedule2.size(); ++i)
		cout << transSchedule2.at(i) << " ";
	cout << endl;
}

void SinrScheduling::PrintIntVector(vector<int> &targetVector)
{
	for (int i=0; i!=targetVector.size(); ++i)
		cout << targetVector.at(i) << " ";
	cout << endl;
}
void SinrScheduling::PrintDoubleVector(vector<double> &targetVector)
{
	for (int i=0; i!=targetVector.size(); ++i)
		cout << targetVector.at(i) << " ";
	cout << endl;
}
