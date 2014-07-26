#include <iostream>
#include <cmath>
#include <vector>
#include "SchedulingMetricInterlaceIPConsiderByte.h"

using namespace std;
SchedulingMetricInterlaceIPConsiderByte::SchedulingMetricInterlaceIPConsiderByte(int numCameras, vector< pair<double,double> > positions, vector< vector<int> > overhearTopology):
	m_numCameras(numCameras),
	m_positions(positions),
	m_overhearTopology(overhearTopology)
{
	requiredTime = CalRequiredTime();
	/*
	cout << "requiredTime: " << endl;
	for (int i=0; i!=m_numCameras; ++i)
	{	for (int j=0; j!=m_numCameras; ++j)
			cout << requiredTime.at(i).at(j) << " ";
		cout << endl;
	}
	cout << endl;
	*/
	//PrintTopology();
	
	vector<int> m_transSchedule = GenerateSchedule();
}

vector<int> SchedulingMetricInterlaceIPConsiderByte::GenerateSchedule()
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

vector< vector<double> > SchedulingMetricInterlaceIPConsiderByte::CalRequiredTime()
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
			{
				m_requiredTime.at(i).at(j) = m_overhearTopology.at(i).at(i)/capacityToAggregator.at(i);
				m_overhearTopology.at(i).at(j) = m_overhearTopology.at(i).at(i); //change the overhearTopology
			}
		}
	}
	return m_requiredTime;
}

double SchedulingMetricInterlaceIPConsiderByte::CapacityToAggregatorCal(double m_x, double m_y)
{
	double dx = m_x-xA;
	double dy = m_y-yA;
	double G = pow(10.0,(-13.11-4.281*log10(sqrt(dx*dx+dy*dy)/1000.0)));
	double C = bandwidth*log2(1+(power*G)/bandwidth/N0);
	return C;
}

//Calculate \Delta R(i,j) = \Delta R(cam1,cam2)
int SchedulingMetricInterlaceIPConsiderByte::ResourceDifferenceCal(int cam1, int cam2)
{
	int difference = 0;
	if (transSchedule.size() > 0)
	{
        if (transSchedule.size () % 2 == 1) // the previous one is I-frame
        {
		int referenceCamera = transSchedule.back();
		difference = m_overhearTopology.at(cam1).at(referenceCamera) - m_overhearTopology.at(cam2).at(referenceCamera);
        }
        else if (transSchedule.size () % 2 == 0)
            // the previous one is P-frame, so cam1 or cam2 must be I
        {
            difference = m_overhearTopology.at(cam1).at(cam1) - m_overhearTopology.at(cam2).at(cam2);
        }
	}
	else if (transSchedule.size() == 0)
		difference = m_overhearTopology.at(cam1).at(cam1) - m_overhearTopology.at(cam2).at(cam2);
	return difference;
}

//Calculate scheduling metric
int SchedulingMetricInterlaceIPConsiderByte::MetricCal(vector<int> m_nonScheduled, int m_targetCam)
{
	int m_metric = 0;
	int omega = 0;
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

int SchedulingMetricInterlaceIPConsiderByte::ScheduledCameraPosition(vector<int> m_nonScheduled, int m_eraseCam)
{
	int pos = 0;
	for (int i=0; i!=m_nonScheduled.size(); ++i)
	{
		if (m_nonScheduled.at(i) == m_eraseCam)
			pos = i;
	}
	return pos;
}

void SchedulingMetricInterlaceIPConsiderByte::PrintSchedule()
{
	cout << "Transmission Schedule: ";
	for (int i=0; i!=transSchedule.size(); ++i)
		cout << transSchedule.at(i) << " ";
	cout << endl;
}

void SchedulingMetricInterlaceIPConsiderByte::PrintTopology()
{
	cout << "m_overhearTopology: " << endl;
	for (int i=0; i!=m_numCameras; ++i)
	{	for (int j=0; j!=m_numCameras; ++j)
			cout << m_overhearTopology.at(i).at(j) << " ";
		cout << endl;
	}
	cout << endl;
}

void SchedulingMetricInterlaceIPConsiderByte::PrintIntVector(vector<int> &targetVector)
{
	for (int i=0; i!=targetVector.size(); ++i)
		cout << targetVector.at(i) << " ";
	cout << endl;
}
void SchedulingMetricInterlaceIPConsiderByte::PrintDoubleVector(vector<double> &targetVector)
{
	for (int i=0; i!=targetVector.size(); ++i)
		cout << targetVector.at(i) << " ";
	cout << endl;
}
