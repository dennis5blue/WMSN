#include <iostream>
#include <cmath>
#include <vector>
#include "ScheduleFactory.h"

using namespace std;

ScheduleFactory::ScheduleFactory(int numCameras, vector< vector<int> > overhearTopology):
	m_numCameras(numCameras),
	m_overhearTopology(overhearTopology)
{
	m_schedule.assign(m_numCameras,1);
	FindBestReference(m_numCameras, m_overhearTopology);
}

/*vector<int> ScheduleFactory::FindBestReference(int m_numCameras, vector< vector<int> > m_overhearTopology)
{
	vector<int> vec_bestRef;
	for(int i=0; i!=m_numCameras; ++i)
	{
		//Initial is the independent transmission bytes
		int tempMin = m_overhearTopology.at(i).at(i);
		int tempBestRef = i;
		
		for(int j=0; j!=m_numCameras; ++j)
		{
			if(m_overhearTopology.at(i).at(j) > 0 && m_overhearTopology.at(i).at(j) < tempMin)
			{
				tempMin = m_overhearTopology.at(i).at(j);
				tempBestRef = j;
			}
		}
		vec_bestRef.push_back(tempBestRef);
	}
	cout << "Best Reference for each cameras: " << endl;
	for(int k=0; k!=vec_bestRef.size(); ++k)
		cout << vec_bestRef.at(k) << " ";
	cout << endl;
	return vec_bestRef;
}*/
vector<int> ScheduleFactory::GenerateSchedule(int m_numCameras, const vector< vector<int> > m_overhearTopology);
{
	//Find the first transmitted camera (smallest m_overhearTopology[i][i])
	for (int i=0; i!=m_numCameras)
}

int ScheduleFactory::FindBestReference(int m_numCameras, int m_targetCamera, const vector< vector<int> > m_overhearTopology);
{
	int tempMin = m_overhearTopology.at(m_targetCamera).at(m_targetCamera);
	int tempBestRef = m_targetCamera;
	for(int i=0; i!=m_numCameras; ++i)
	{
		if(m_overhearTopology.at(m_targetCamera).at(i) > 0 && m_overhearTopology.at(m_targetCamera).at(i) < tempMin)
		{
			tempMin = m_overhearTopology.at(m_targetCamera).at(i);
			tempBestRef = i;
		}
	}
	return tempBestRef;
}

void ScheduleFactory::PrintSchedule()
{
	cout << "Transmission schedule: " << endl;
	for (int i=0; i!=m_schedule.size(); ++i)
		cout << m_schedule.at(i) << " ";
	cout << endl;
}
