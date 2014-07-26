#ifndef SCHEDULING_METRIC_H
#define SCHEDULING_METRIC_H

#include <vector>
#include <utility>
using std::vector;
using std::pair;

class SchedulingMetric
{
public:
	SchedulingMetric(int numCameras, vector< pair<double,double> > positions, vector< vector<int> > overhearTopology);
	vector<int> GetSchedule() const {return transSchedule; }
	vector<double> GetCapacity() const {return capacityToAggregator; }	
	void PrintSchedule();

private:
	int m_numCameras;
	vector< vector<int> > m_overhearTopology;
	vector< pair<double,double> > m_positions;
	vector< vector<double> > requiredTime;
	double power;
	double bandwidth;
	double N0;
	double xA;
	double yA;
	vector<int> transSchedule;
	vector<double> capacityToAggregator;
	vector< vector<double> > CalRequiredTime();
	vector<int> GenerateSchedule();
	double CapacityToAggregatorCal(double m_x, double m_y);
	double ResourceDifferenceCal(int cam1, int cam2);
	double MetricCal(vector<int> m_nonScheduled, int m_targetCam);
	int ScheduledCameraPosition(vector<int> m_nonScheduled, int m_eraseCam);
	void PrintIntVector(vector<int> &targetVector);
	void PrintDoubleVector(vector<double> &targetVector);
};

#endif //SCHEDULING_METRIC_H
