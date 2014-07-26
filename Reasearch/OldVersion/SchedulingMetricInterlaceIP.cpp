#include <iostream>
#include <cmath>
#include <vector>
#include "SchedulingMetricInterlaceIP.h"

using namespace std;
SchedulingMetricInterlaceIP::SchedulingMetricInterlaceIP(int numCameras, vector< pair<double,double> > positions, vector< vector<int> > overhearTopology):
	m_numCameras(numCameras),
	m_positions(positions),
	m_overhearTopology(overhearTopology)
{
	requiredTime = CalRequiredTime();
	vector<int> m_transSchedule = GenerateSchedule();
}

vector<int> SchedulingMetricInterlaceIP::GenerateSchedule()
{
	vector<int> nonScheduled;
	nonScheduled.push_back(m_numCameras-1);
	while (nonScheduled.back() != 0)
		nonScheduled.push_back ( nonScheduled.back() -1 ); //Initialize vector nonScheduled 23,22,...,0
		
	for (int j=0; j!=m_numCameras; ++j)
	{
		double metricTemp = MetricCal( nonScheduled, nonScheduled.at(0) );	
		int nextCamera = nonScheduled.at(0);
		for (int k=1; k!=nonScheduled.size(); ++k)
		{
			double metricTemp2 = MetricCal( nonScheduled, nonScheduled.at(k) );
			if (metricTemp2 < metricTemp)
			{
				metricTemp = metricTemp2;
				nextCamera = nonScheduled.at(k); 
			}
		}
		transSchedule.push_back(nextCamera);
		if (nonScheduled.size() > 0)
			nonScheduled.erase ( nonScheduled.begin()+ScheduledCameraPosition(nonScheduled, nextCamera) );
	}
	return transSchedule;
}

vector< vector<double> > SchedulingMetricInterlaceIP::CalRequiredTime()
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

double SchedulingMetricInterlaceIP::CapacityToAggregatorCal(double m_x, double m_y)
{
	double dx = m_x-xA;
	double dy = m_y-yA;
	double G = pow(10.0,(-13.11-4.281*log10(sqrt(dx*dx+dy*dy)/1000.0)));
	double C = bandwidth*log2(1+(power*G)/bandwidth/N0);
	return C;
}

//Calculate \Delta R(i,j) = \Delta R(cam1,cam2)
double SchedulingMetricInterlaceIP::ResourceDifferenceCal(int cam1, int cam2)
{
	double difference = 0.0;
	if (transSchedule.size() > 0)
	{
        if (transSchedule.size () % 2 == 1) // the previous one is I-frame
		{
            int referenceCamera = transSchedule.back();
            difference = requiredTime.at(cam1).at(referenceCamera) - requiredTime.at(cam2).at(referenceCamera);
        }
        else if (transSchedule.size () % 2 == 0)
        // the previous one is P-frame, so cam1 or cam2 must be I
        {
            int referenceCamera = transSchedule.back();
            difference = requiredTime.at(cam1).at(cam1) - requiredTime.at(cam2).at(cam2);
        }
	}
	else if (transSchedule.size () == 0)
		difference = requiredTime.at(cam1).at(cam1) - requiredTime.at(cam2).at(cam2);
	return difference;
}

//Calculate scheduling metric
double SchedulingMetricInterlaceIP::MetricCal(vector<int> m_nonScheduled, int m_targetCam)
{
	double m_metric = 0.0;
	double omega = 0.0;
	if (m_nonScheduled.size() > 0)
	{
		for (int i=0; i!=m_nonScheduled.size(); ++i)
		{
			omega = ResourceDifferenceCal( m_targetCam, m_nonScheduled.at(i) );
			if (omega > m_metric)
				m_metric = omega;
		}
	}
	return m_metric;
}

int SchedulingMetricInterlaceIP::ScheduledCameraPosition(vector<int> m_nonScheduled, int m_eraseCam)
{
	int pos = 0;
	for (int i=0; i!=m_nonScheduled.size(); ++i)
	{
		if (m_nonScheduled.at(i) == m_eraseCam)
			pos = i;
	}
	return pos;
}

void SchedulingMetricInterlaceIP::PrintSchedule()
{
	cout << "Transmission Schedule: ";
	for (int i=0; i!=transSchedule.size(); ++i)
		cout << transSchedule.at(i) << " ";
	cout << endl;
}

void SchedulingMetricInterlaceIP::PrintIntVector(vector<int> &targetVector)
{
	for (int i=0; i!=targetVector.size(); ++i)
		cout << targetVector.at(i) << " ";
	cout << endl;
}
void SchedulingMetricInterlaceIP::PrintDoubleVector(vector<double> &targetVector)
{
	for (int i=0; i!=targetVector.size(); ++i)
		cout << targetVector.at(i) << " ";
	cout << endl;
}
