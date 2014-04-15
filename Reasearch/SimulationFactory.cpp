#include <iostream>
#include <cmath>
#include <vector>
#include "SimulationFactory.h"

using namespace std;

SimulationFactory::SimulationFactory(int numCameras, vector< vector<int> > overhearTopology, vector<int> cameraSchedule, vector<double> channelCapacity):
	m_numCameras(numCameras),
	m_overhearTopology(overhearTopology),
	m_cameraSchedule(cameraSchedule),
	m_channelCapacity(channelCapacity)
{
	totalIndepTransTime = IndepTimeCalculator(m_numCameras, m_overhearTopology, m_channelCapacity);
	totalOverTransTime = OverTimeCalculator(m_numCameras, m_overhearTopology, m_channelCapacity, m_cameraSchedule);
	totalMinimumTransTime = MinimumTimeCalculator(m_numCameras, m_overhearTopology, m_channelCapacity);
}

double SimulationFactory::IndepTimeCalculator( int m_numCameras, vector< vector<int> > m_overhearTopology, vector<double> m_channelCapacity )
{
	double m_totalIndepTransTime = 0.0;
	for (int i=0; i!=m_numCameras; ++i)
		m_totalIndepTransTime += 8*m_overhearTopology.at(i).at(i) / m_channelCapacity.at(i) ;
	return m_totalIndepTransTime;
}

double SimulationFactory::OverTimeCalculator( int m_numCameras, vector< vector<int> > m_overhearTopology, vector<double> m_channelCapacity, vector<int> m_cameraSchedule )
{
	int firstCamera = m_cameraSchedule.at(0);
	double m_totalOverTransTime = 8*m_overhearTopology.at(firstCamera).at(firstCamera) / m_channelCapacity.at(firstCamera);
	for (int i=1; i!=m_numCameras; ++i)
	{
		int refCamera = m_cameraSchedule.at(i-1);		
		int encodeCamera = m_cameraSchedule.at(i);
		if ( m_overhearTopology.at(encodeCamera).at(refCamera) != -1 )
			m_totalOverTransTime += 8*m_overhearTopology.at(encodeCamera).at(refCamera) / m_channelCapacity.at(encodeCamera);
		else
			m_totalOverTransTime += 8*m_overhearTopology.at(encodeCamera).at(encodeCamera) / m_channelCapacity.at(encodeCamera);
	}
	return m_totalOverTransTime;
}

double SimulationFactory::MinimumTimeCalculator( int m_numCameras, vector< vector<int> > m_overhearTopology, vector<double> m_channelCapacity )
{
	vector<double> zerosVector(m_numCameras,0.0);
	vector< vector<double> > transTimeMatrix(m_numCameras, zerosVector);
	for (int p=0; p!=m_numCameras; ++p)
	{
		//cout << "Camera " << p << ": " << endl;
		for (int q=0; q!=m_numCameras; ++q)
		{
			transTimeMatrix.at(p).at(q) = 8*m_overhearTopology.at(p).at(q) / m_channelCapacity.at(p);
			//cout << transTimeMatrix.at(p).at(q) << " ";
		}
		//cout << endl;
	}
	
	double m_totalMinimumTransTime = 0.0;
	for (int i=0; i!=m_numCameras; ++i)
	{
		double tempMinTime = transTimeMatrix.at(i).at(i);
		for (int j=0; j!=m_numCameras; ++j)
		{
			if (transTimeMatrix.at(i).at(j) < tempMinTime && transTimeMatrix.at(i).at(j)>0)
				tempMinTime = transTimeMatrix.at(i).at(j);
		}
		//cout << "Camera " << i << "tempMinTime= " << tempMinTime << endl;
		m_totalMinimumTransTime += tempMinTime;
	}

	return m_totalMinimumTransTime;
}
