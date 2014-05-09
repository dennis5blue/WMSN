#ifndef SA_FACTORY_H
#define SA_FACTORY_H

#include <vector>
#include <utility>
using std::vector;
using std::pair;

class SAFactory
{
public:
	SAFactory(int numCameras, vector< pair<double,double> > positions, vector< vector<int> > overhearTopology, vector<int> initialSchedule);
	vector<int> GetSchedule() const {return transScheduleAfterSA; }
	vector<double> GetCapacity() const {return capacityToAggregator; }	

private:
	int m_numCameras;
	vector< vector<int> > m_overhearTopology;
	vector< pair<double,double> > m_positions;
	vector< vector<double> > requiredTime;
	vector<int> m_initialSchedule;
	vector<int> transScheduleAfterSA;
	double power;
	double bandwidth;
	double N0;
	double xA;
	double yA;
	vector<double> capacityToAggregator;
	vector< vector<double> > CalRequiredTime();
	double CapacityToAggregatorCal(double m_x, double m_y);
};

#endif //SA_FACTORY_H
