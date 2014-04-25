#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>
#include <stdlib.h>

#define CAMERA_NUM 24
#define INPUT_CORR (char*)("./Topology/test5_corrMatrix.txt")
#define INPUT_INDEP (char*)("./Topology/test5_indepByte.txt")
#define INPUT_POS (char*)("pos.txt")

#include "TopologyFactory.h"
#include "ScheduleFactory.h"
#include "SchedulingMetric.h"
#include "SimulationFactory.h"
using namespace std;

int main(int argc, char *argv[])
{
	//**********************************************************************************************//	
	//***Load the file into corrTopology, record the required transmission bytes for each cameras***//
	//***	[i][i] means camera i indep. coding, [i][j] means camera i reference from camera j	 ***//
	//***	 Also load the position of each cameras (position[0] is the aggregator at (0,0))	 ***//
	//**********************************************************************************************//	
	vector<int> zeroVector(CAMERA_NUM, 0);	
	vector< vector<int> > mycorrTopology(CAMERA_NUM, zeroVector);
	ifstream input(INPUT_CORR, ios::in);
    for (int i=0; i!=CAMERA_NUM; ++i)
        for (int j=0; j!=CAMERA_NUM; ++j)
            input >> mycorrTopology.at(i).at(j);	
    input.close();
	ifstream input2(INPUT_INDEP, ios::in);
	for (int k=0; k!=CAMERA_NUM; ++k)
		input2 >> mycorrTopology.at(k).at(k);
	input2.close();
	
	vector< pair<double,double> > position(CAMERA_NUM+1, make_pair(0.0,0.0));
	ifstream inputPos(INPUT_POS, ios::in);
	double tempX, tempY;	
	for (int l=0; l!=CAMERA_NUM; ++l)
	{
		inputPos >> tempX;
		inputPos >> tempY;
		position.at(l+1) = make_pair(tempX,tempY);
	}
	inputPos.close();

	//print the input matrix for transmission time and cameras position
	/*cout << "Required transmission bytes: " << endl;    
	for (int i=0; i!=CAMERA_NUM; ++i)
    {
        for (int j=0; j!=CAMERA_NUM; ++j)
            cout << mycorrTopology[i][j] << " ";
        cout << endl;
    }
    cout << endl;
	cout << "Camera positions: " << endl;
	for (int k=0; k!=CAMERA_NUM+1; ++k)
		cout << position[k].first << " " << position[k].second << endl;
	*/
	cout << "Input File is: " << INPUT_CORR << endl;

	TopologyFactory myTopology( CAMERA_NUM, position, mycorrTopology );
	//myTopology.PrintTopology();
	
	ScheduleFactory mySchedule( CAMERA_NUM, position, myTopology.GetTopology() );
	mySchedule.PrintSchedule();
	SchedulingMetric anotherSchedule( CAMERA_NUM, position, myTopology.GetTopology() );	
	anotherSchedule.PrintSchedule();
	
	SimulationFactory mySimulation( CAMERA_NUM, myTopology.GetTopology(),
		mySchedule.GetSchedule(), mySchedule.GetCapacity());
	SimulationFactory anotherSimulation( CAMERA_NUM, myTopology.GetTopology(),
		anotherSchedule.GetSchedule(), anotherSchedule.GetCapacity());
	//cout << "Independent transmission time = " << mySimulation.GetIndepTransTime() << " (second)" << endl;
	//cout << "Overhearing transmission time = " << mySimulation.GetOverTransTime() << " (second)" << endl;
	cout << "Greedy: " << endl;	
	cout << "Improvement ratio = " << 100*( mySimulation.GetIndepTransTime()-
		mySimulation.GetOverTransTime() )/mySimulation.GetIndepTransTime() << " %" <<endl;
	cout << "Scheduling Metric: " << endl;	
	cout << "Improvement ratio = " << 100*( anotherSimulation.GetIndepTransTime()-
		anotherSimulation.GetOverTransTime() )/anotherSimulation.GetIndepTransTime() << " %" <<endl;
	//cout << "Minimum transmission time = " << mySimulation.GetMinimumTransTime() << " (second)" << endl;
	cout << "Maximum ratio = " << 100*( mySimulation.GetIndepTransTime()-mySimulation.GetMinimumTransTime() )/mySimulation.GetIndepTransTime() << " %" <<endl;
}


