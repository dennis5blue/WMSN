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
	double GetOverTransTimeListenOneBefore() const {return totalOverTransTimeListenOneBefore; }
	double GetMinimumTransTime() const {return totalMinimumTransTime; }
	int GetOverTransByte() const {return totalOverTransByte; }
	int GetIndepTransByte() const {return totalIndepTransByte; }
	int GetMinimumTransByte() const {return totalMinimumTransByte; }

private:
	int m_numCameras;
	vector< vector<int> > m_overhearTopology;
	vector<int> m_cameraSchedule;
	vector<double> m_channelCapacity;
	vector<int> indepRequiredBytes;
	vector< vector<double> > requiredTime;
	double totalOverTransTime;
	double totalOverTransTimeListenOneBefore;
	double totalIndepTransTime;
	double totalMinimumTransTime;
	int totalOverTransByte;
	int totalIndepTransByte;
	int totalMinimumTransByte;
	double IndepTimeCalculator();
	double OverTimeCalculator();
	double OverTimeCalculatorListenOneBefore();
	double MinimumTimeCalculator();
	int OverByteCalculator();
	int IndepByteCalculator();
	int MinimumByteCalculator();
	vector< vector<double> > CalRequiredTime();
};

#endif //SIMULATION_FACTORY_H
