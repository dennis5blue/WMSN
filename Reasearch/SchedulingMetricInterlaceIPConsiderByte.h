#ifndef SCHEDULING_METRIC_INTERLACE_IP_CONSIDER_BYTE_H
#define SCHEDULING_METRIC_INTERLACE_IP_CONSIDER_BYTE_H

#include <vector>
#include <utility>
using std::vector;
using std::pair;

class SchedulingMetricInterlaceIPConsiderByte
{
public:
	SchedulingMetricInterlaceIPConsiderByte(int numCameras, vector< pair<double,double> > positions, vector< vector<int> > overhearTopology);
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
	vector< vector<double> > CalRequiredTime(); //note that in this function, we change the overTopology for convenient
	vector<int> GenerateSchedule();
	double CapacityToAggregatorCal(double m_x, double m_y);
	int ResourceDifferenceCal(int cam1, int cam2);
	int MetricCal(vector<int> m_nonScheduled, int m_targetCam);
	int ScheduledCameraPosition(vector<int> m_nonScheduled, int m_eraseCam);
	void PrintIntVector(vector<int> &targetVector);
	void PrintDoubleVector(vector<double> &targetVector);
	void PrintTopology();
};

#endif //SCHEDULING_METRIC_INTERLACE_IP_CONSIDER_BYTE_H
