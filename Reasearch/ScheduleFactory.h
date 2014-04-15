#ifndef SCHEDULE_FACTORY_H
#define SCHEDULE_FACTORY_H

#include <vector>
#include <utility>
using std::vector;
using std::pair;

class ScheduleFactory
{
public:
	ScheduleFactory(int numCameras, vector< vector<int> > overhearTopology);
	int m_numCameras;
	vector< vector<int> > m_overhearTopology;
	vector<int> GetSchedule() const {return m_schedule; }
	void PrintSchedule();

private:
	vector<int> m_schedule;
	//vector<int> FindBestReference(int m_numCameras, vector< vector<int> > m_overhearTopology);
	int FindBestReference(int m_numCameras, int m_targetCamera, const vector< vector<int> > m_overhearTopology);
	vector<int> GenerateSchedule(int m_numCameras, const vector< vector<int> > m_overhearTopology);
};

#endif //SCHEDULE_FACTORY_H
