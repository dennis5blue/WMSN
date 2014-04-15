#ifndef SCHEDULE_FACTORY_H
#define SCHEDULE_FACTORY_H

#include <vector>
#include <utility>
using std::vector;
using std::pair;

class ScheduleFactory
{
public:
	ScheduleFactory(int numCameras, vector< pair<double,double> > positions, vector< vector<int> > overhearTopology);
	int m_numCameras;
	vector< vector<int> > m_overhearTopology;
	vector< pair<double,double> > m_positions;
	vector<int> GetSchedule() const {return transSchedule; }
	void PrintSchedule();

private:
	double power;
	double bandwidth;
	double N0;
	double xA;
	double yA;
	vector<int> transSchedule;
	vector<int> indepRequiredBytes;
	vector<double> capacityToAggregator;
	vector<int> GenerateSchedule(int m_numCameras, const vector< vector<int> > m_overhearTopology);	
	int FindBestReference(int m_numCameras, int m_targetCamera, const vector< vector<int> > m_overhearTopology);
	int FindBestRefTo(int m_numCameras, int m_targetCamera, const vector<int> m_indepRequiredBytes, const vector< vector<int> > m_overhearTopology, const vector<int> m_searchRange);
	double CapacityToAggregatorCal(double m_xA, double m_yA, double m_x, double m_y, double m_power, double m_bandwidth, double m_N0);	
};

#endif //SCHEDULE_FACTORY_H
