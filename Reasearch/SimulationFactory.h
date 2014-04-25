#ifndef SIMULATION_FACTORY_H
#define SIMULATION_FACTORY_H

#include <vector>
#include <utility>
using std::vector;
using std::pair;

class SimulationFactory
{
public:
	SimulationFactory(int numCameras, vector< vector<int> > overhearTopology, vector<int> cameraSchedule, vector<double> channelCapacity);
	double GetIndepTransTime() const {return totalIndepTransTime; }
	double GetOverTransTime() const {return totalOverTransTime; }
	double GetMinimumTransTime() const {return totalMinimumTransTime; }

private:
	int m_numCameras;
	vector< vector<int> > m_overhearTopology;
	vector<int> m_cameraSchedule;
	vector<double> m_channelCapacity;
	vector<int> indepRequiredBytes;
	vector< vector<double> > requiredTime;
	double totalOverTransTime;
	double totalIndepTransTime;
	double totalMinimumTransTime;
	double IndepTimeCalculator();
	double OverTimeCalculator();
	double MinimumTimeCalculator();
	vector< vector<double> > CalRequiredTime();
};

#endif //SIMULATION_FACTORY_H
