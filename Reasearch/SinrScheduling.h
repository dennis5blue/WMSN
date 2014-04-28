#ifndef SINR_SCHEDULING_H
#define SINR_SCHEDULING_H

#include <vector>
#include <utility>
using std::vector;
using std::pair;

class SinrScheduling
{
public:
	SinrScheduling(int numCameras, vector< pair<double,double> > positions, vector< vector<int> > overhearTopology);
	vector<int> GetSchedule() const {return transSchedule; }
	vector<int> GetSchedule2() const {return transSchedule2; }
	vector<double> GetCapacity() const {return capacityToAggregator; }	
	void PrintSchedule();
	void PrintSchedule2();

private:
	int m_numCameras;
	vector< vector<int> > m_overhearTopology;
	vector< pair<double,double> > m_positions;
	vector<double> indepRequiredTime;
	vector<double> indepRequiredTime2;
	double power;
	double bandwidth;
	double N0;
	double xA;
	double yA;
	vector<int> transSchedule;	// Most time first
	vector<int> transSchedule2; // Least time first
	vector<double> capacityToAggregator;
	vector<double> CalIndepRequiredTime();
	vector<int> GenerateScheduleMostFirst();
	vector<int> GenerateScheduleLeastFirst();		
	double CapacityToAggregatorCal(double m_x, double m_y);
	void PrintIntVector(vector<int> &targetVector);
	void PrintDoubleVector(vector<double> &targetVector);
};

#endif //SINR_SCHEDULING_H
