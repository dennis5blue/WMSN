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
	requiredTime = CalRequiredTime();	
	totalIndepTransTime = IndepTimeCalculator();
	totalOverTransTime = OverTimeCalculator();
	totalOverTransTimeListenOneBefore = OverTimeCalculatorListenOneBefore();
	totalMinimumTransTime = MinimumTimeCalculator();
	totalOverTransByte = OverByteCalculator(); //Listen only one before
	totalIndepTransByte = IndepByteCalculator();
	totalMinimumTransByte = MinimumByteCalculator();
}

vector< vector<double> > SimulationFactory::CalRequiredTime()
{
	vector<double> tempZero(m_numCameras, 0);
	vector< vector<double> > m_requiredTime(m_numCameras, tempZero);
	for (int i=0; i!=m_numCameras; ++i)
	{
		for (int j=0; j!=m_numCameras; ++j)
		{
			if (m_overhearTopology.at(i).at(j)>0)
				m_requiredTime.at(i).at(j) = 8*m_overhearTopology.at(i).at(j)/m_channelCapacity.at(i);
			else if (m_overhearTopology.at(i).at(j)==-1)
				m_requiredTime.at(i).at(j) = 8*m_overhearTopology.at(i).at(i)/m_channelCapacity.at(i);
		}
	}
	return m_requiredTime;
}

double SimulationFactory::IndepTimeCalculator()
{
	double m_totalIndepTransTime = 0.0;
	for (int i=0; i!=m_numCameras; ++i)
		m_totalIndepTransTime += requiredTime.at(i).at(i);
	return m_totalIndepTransTime;
}

double SimulationFactory::OverTimeCalculator()
{
	int firstCamera = m_cameraSchedule.at(0);
	double m_totalOverTransTime = requiredTime.at(firstCamera).at(firstCamera);
	for (int i=1; i!=m_numCameras; ++i)
	{
		int encodeCamera = m_cameraSchedule.at(i);
		int refCamera = m_cameraSchedule.at(i-1);
		for (int j=0; j!=i-1; ++j)
		{
			if (requiredTime.at(encodeCamera).at(m_cameraSchedule.at(j)) < requiredTime.at(encodeCamera).at(refCamera))
				refCamera = m_cameraSchedule.at(j);
		}
		m_totalOverTransTime += requiredTime.at(encodeCamera).at(refCamera);
	}
	return m_totalOverTransTime;
}

double SimulationFactory::OverTimeCalculatorListenOneBefore()
{
	int firstCamera = m_cameraSchedule.at(0);
	double m_totalOverTransTime = requiredTime.at(firstCamera).at(firstCamera);
	for (int i=1; i!=m_numCameras; ++i)
	{
		int encodeCamera = m_cameraSchedule.at(i);
		int refCamera = m_cameraSchedule.at(i-1);
		m_totalOverTransTime += requiredTime.at(encodeCamera).at(refCamera);
	}
	return m_totalOverTransTime;
}

double SimulationFactory::MinimumTimeCalculator()
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

int SimulationFactory::IndepByteCalculator()
{
	int m_totalIndepTransByte = 0;
	cout << "Independent required bytes: " << endl;
	for (int i=0; i!=m_numCameras; ++i)
	{
		m_totalIndepTransByte += m_overhearTopology.at(i).at(i);
		cout << m_overhearTopology.at(i).at(i) << " ";
	}
	cout << endl;
	return m_totalIndepTransByte;
}

int SimulationFactory::OverByteCalculator()
{
	/*for (int a=0; a!=m_numCameras; ++a)
	{
		for (int b=0; b!=m_numCameras; ++b)
			cout << m_overhearTopology.at(a).at(b) << " ";
		cout << endl;
	}*/
    std::vector <int> beta; // 1 is broadcaster, 0 is listener
	cout << "Overhearing required bytes: " << endl;
	int firstCamera = m_cameraSchedule.at(0);
	int m_totalOverTransByte = m_overhearTopology.at(firstCamera).at(firstCamera);
    beta.push_back (1);
	cout << m_overhearTopology.at(firstCamera).at(firstCamera) << " ";
	for (int i=1; i!=m_numCameras; ++i)
	{
		int encodeCamera = m_cameraSchedule.at(i);
		int refCamera = m_cameraSchedule.at(i-1);
        int tempRequiredByte = 0;
		
		// use to check if the previous camera can be overheard
		// need to check all the adjacent cameras is the previous camera is P-frame encoded
		if (beta.at (i-1) == 1) // if the previous one is broadcaster, just reference it
        {
            tempRequiredByte = m_overhearTopology.at(encodeCamera).at(refCamera);
            m_totalOverTransByte += tempRequiredByte;
            beta.push_back (0);
            cout << tempRequiredByte;
            cout << "P ";
        }
        else if (beta.at (i-1) == 0)
        {
            int originalI = i-1;
            int jumpOut = i-1;
            while (jumpOut >= 0)
            {
                if (beta.at (jumpOut) == 1)
                {
                    originalI = jumpOut;
                    jumpOut = -1;
                }
                -- jumpOut;
            }
            if (m_overhearTopology.at (encodeCamera).at (originalI) != -1)
            {
                tempRequiredByte = m_overhearTopology.at(encodeCamera).at(refCamera);
                m_totalOverTransByte += tempRequiredByte;
                beta.push_back (0);
                cout << tempRequiredByte;
                cout << "P ";
            }
            else if (m_overhearTopology.at (encodeCamera).at (originalI) == -1)
            {
                tempRequiredByte = m_overhearTopology.at (encodeCamera).at (encodeCamera);
                m_totalOverTransByte += tempRequiredByte;
                beta.push_back (1);
                cout << tempRequiredByte;
                cout << "I ";
            }
        }
    }
	cout << endl;
	return m_totalOverTransByte;
}

int SimulationFactory::MinimumByteCalculator()
{
	int m_totalMinimumTransByte = 0;
	cout << "Minimum required bytes: " << endl;
	for (int i=0; i!=m_numCameras; ++i)
	{
		int tempMinByte = m_overhearTopology.at(i).at(i);
		for (int j=0; j!=m_numCameras; ++j)
		{
			if (m_overhearTopology.at(i).at(j) < tempMinByte && m_overhearTopology.at(i).at(j)>0)
				tempMinByte = m_overhearTopology.at(i).at(j);
		}
		cout << tempMinByte << " ";
		m_totalMinimumTransByte += tempMinByte;
	}
	cout << endl;
	return m_totalMinimumTransByte;
}

/*
int SimulationFactory::PrintTransTimeEachCamera();
{

	return 1;
}
*/
