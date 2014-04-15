#include <iostream>
#include <cmath>
#include <vector>
#include "ScheduleFactory.h"

using namespace std;

ScheduleFactory::ScheduleFactory(int numCameras, vector< pair<double,double> > positions, vector< vector<int> > overhearTopology):
	m_numCameras(numCameras),
	m_positions(positions),
	m_overhearTopology(overhearTopology)
{
	power = 0.125; // Watt
	bandwidth = 5000000.0; // Hz
	N0 = 0.000000000000001; // W/kHz ( calculate by pow(10.0,-12.0)/1000.0 )
	xA = m_positions.at(0).first; //Aggregator's position
	yA = m_positions.at(0).second; //Aggregator's position
	
	//Initialize Required bytes and Channel capacity
	for (int cam=0; cam!=m_numCameras; ++cam)
	{
		indepRequiredBytes.push_back( m_overhearTopology.at(cam).at(cam) );
		capacityToAggregator.push_back( CapacityToAggregatorCal(xA, yA, m_positions.at(cam+1).first, m_positions.at(cam+1).second, power, bandwidth, N0) );
	}

	// Generate the schedule order 
	GenerateSchedule(m_numCameras, m_overhearTopology);
}

vector<int> ScheduleFactory::GenerateSchedule(int m_numCameras, const vector< vector<int> > m_overhearTopology)
{
	//Initialize the serach range for scheduling algorithm
	vector<int> searchRange;
	for(int j=0; j!=m_numCameras; ++j)
		searchRange.push_back(j);
	
	//Find the first transmitted camera ( smallest transmission time m_overhearTopology[i][i]/capacityToAggregator[i] )
	int firstTrans = 0;
	double tempIndepTime = indepRequiredBytes.at(0)/capacityToAggregator.at(0);	
	for (int i=1; i!=m_numCameras; ++i)
	{
		if ( indepRequiredBytes.at(i)/capacityToAggregator.at(i) < indepRequiredBytes.at(i-1)/capacityToAggregator.at(i-1) )
		{
			firstTrans = i;
			tempIndepTime = indepRequiredBytes.at(i)/capacityToAggregator.at(i);
		}
	}
	transSchedule.push_back(firstTrans);
	searchRange.at(firstTrans) = -1; // -1 means we have already scheduled this camera
	
	for (int k=1; k!=m_numCameras; ++k)
	{
		int nextCamera = FindBestRefTo(m_numCameras, transSchedule.at(k-1), indepRequiredBytes, m_overhearTopology, searchRange);		
		// If 'nextCamera' is already scheduled, choose the camera with the smallest indep. transmission time
		if (searchRange.at(nextCamera) == -1)
		{
			tempIndepTime = 100000000;
			for (int p=0; p!=searchRange.size(); ++p)
			{
				if ( searchRange.at(p)!=-1 && indepRequiredBytes.at(p)/capacityToAggregator.at(p) < tempIndepTime)
				{
					tempIndepTime = indepRequiredBytes.at(p)/capacityToAggregator.at(p);
					nextCamera = p;
				}
			}
		}	
		
		transSchedule.push_back(nextCamera);
		searchRange.at(nextCamera) = -1;
	}	
	return transSchedule;
}

//Find camera j for camera i to reference from, so that camera i requires the least transmission bytes
//Therefore, search for the ith row of overhearTopology and find the smallest column
int ScheduleFactory::FindBestReference(int m_numCameras, int m_targetCamera, const vector< vector<int> > m_overhearTopology)
{
	int tempMin = m_overhearTopology.at(m_targetCamera).at(m_targetCamera);
	int tempBestRef = m_targetCamera;
	for (int j=0; j!=m_numCameras; ++j)
	{
		if (m_overhearTopology.at(m_targetCamera).at(j) > 0 && m_overhearTopology.at(m_targetCamera).at(j) < tempMin)
		{
			tempMin = m_overhearTopology.at(m_targetCamera).at(j);
			tempBestRef = j;
		}
	}
	return tempBestRef;
}

//Find camera j for camera i to reference to, that is, camera j can reduce the most transmission time by overhearing camera i 
int ScheduleFactory::FindBestRefTo(int m_numCameras, int m_targetCamera, const vector<int> m_indepRequiredBytes, const vector< vector<int> > m_overhearTopology, const vector<int> m_searchRange)
{
	double tempReducedTime = ( m_indepRequiredBytes.at(m_targetCamera) - m_overhearTopology.at(m_targetCamera).at(m_targetCamera) ) / capacityToAggregator.at(m_targetCamera);
	int tempBestRefTo = m_targetCamera;
	for (int j=0; j!=m_numCameras; ++j)
	{
		if ( m_overhearTopology.at(j).at(m_targetCamera) != -1 )
		{
			double ReducedTimeForj = ( m_indepRequiredBytes.at(j) - m_overhearTopology.at(j).at(m_targetCamera) ) / capacityToAggregator.at(j);
			if ( ReducedTimeForj > tempReducedTime && m_searchRange.at(j)!=-1 ) //only compare the un-scheduled cameras
			{
				tempReducedTime = ReducedTimeForj;
				tempBestRefTo = j;
			}
		}
	}
	
	return tempBestRefTo;
}

double ScheduleFactory::CapacityToAggregatorCal(double m_xA, double m_yA, double m_x, double m_y, double m_power, double m_bandwidth, double m_N0)
{
	double dx = m_x-m_xA;
	double dy = m_y-m_yA;
	double G = pow(10.0,(-13.11-4.281*log10(sqrt(dx*dx+dy*dy)/1000.0)));
	double C = m_bandwidth*log2(1+(m_power*G)/m_bandwidth/m_N0);
	return C;
}

void ScheduleFactory::PrintSchedule()
{
	cout << "Transmission schedule: " << endl;
	for (int i=0; i!=transSchedule.size(); ++i)
		cout << transSchedule.at(i) << " ";
	cout << endl;
}
