#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>
#include <stdlib.h>

#define CAMERA_NUM 30
#define INPUT_CORR (char*)("./Topology/paper720_30cam_corrMatrix.txt")
#define INPUT_INDEP (char*)("./Topology/paper720_30cam_indepByte.txt")
#define INPUT_POS (char*)("./Topology/paper720_30cam_pos.txt")

#include "TopologyFactory.h"
#include "ScheduleFactory.h"
#include "SchedulingMetric.h"
#include "SchedulingMetricConsiderByte.h"
#include "SchedulingMetricInterlaceIPConsiderByte.h"
#include "SimulationFactory.h"
#include "SinrScheduling.h"
#include "SAFactory.h"
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
	cout << endl;

	TopologyFactory myTopology( CAMERA_NUM, position, mycorrTopology );
	myTopology.PrintTopology();

	cout << "Graph: ";
	ScheduleFactory mySchedule( CAMERA_NUM, position, myTopology.GetTopology() );
	mySchedule.PrintSchedule();
	SimulationFactory mySimulation( CAMERA_NUM, myTopology.GetTopology(),
		mySchedule.GetSchedule(), mySchedule.GetCapacity());
	cout << endl;

	cout << "Scheduling metric: ";
	//SchedulingMetric anotherSchedule( CAMERA_NUM, position, myTopology.GetTopology() );	
	SchedulingMetricConsiderByte anotherSchedule( CAMERA_NUM, position, myTopology.GetTopology() );
	anotherSchedule.PrintSchedule();
	SimulationFactory anotherSimulation( CAMERA_NUM, myTopology.GetTopology(),
		anotherSchedule.GetSchedule(), anotherSchedule.GetCapacity());
	cout << endl;
    
    /*cout << "Scheduling metric with interlace IP frame: ";
    SchedulingMetricInterlaceIPConsiderByte interlaceIPSchedule (CAMERA_NUM, position, myTopology.GetTopology ());
    interlaceIPSchedule.PrintSchedule ();
    SimulationFactory interlaceIPSimulation ( CAMERA_NUM, myTopology.GetTopology(),                                             interlaceIPSchedule.GetSchedule(), interlaceIPSchedule.GetCapacity());
    cout << endl;*/
	
	//cout << "Using SA: ";
	//SAFactory saSchedule( CAMERA_NUM, position, myTopology.GetTopology(), anotherSchedule.GetSchedule() );
	//SimulationFactory saSimulation( CAMERA_NUM, myTopology.GetTopology(), saSchedule.GetSchedule(), saSchedule.GetCapacity());
	//cout << endl;
	
	/*cout << "Largest entropy first: ";
	SinrScheduling sinrSchedule( CAMERA_NUM, position, myTopology.GetTopology() );
	sinrSchedule.PrintSchedule();
	SimulationFactory sinrSimulation( CAMERA_NUM, myTopology.GetTopology(),
		sinrSchedule.GetSchedule(), sinrSchedule.GetCapacity());	
	
	cout << endl;	
	cout << "Smallest entropy first: ";
	sinrSchedule.PrintSchedule2();
	SimulationFactory sinrSimulation2( CAMERA_NUM, myTopology.GetTopology(),
		sinrSchedule.GetSchedule2(), sinrSchedule.GetCapacity());	
	cout << endl;*/

	/*vector<int> testSchedule;
	for (int eve=0; eve!=CAMERA_NUM; ++eve)
		testSchedule.push_back(eve);
	SimulationFactory testSimulation( CAMERA_NUM, myTopology.GetTopology(),testSchedule , anotherSchedule.GetCapacity());	*/

	/*
	cout << "Indepent transmission time = " << anotherSimulation.GetIndepTransTime() << endl;
	cout << "Graph: ";	
	cout << "Trans time = " << mySimulation.GetOverTransTimeListenOneBefore() << "; ";
	cout << "Improvement ratio = " << 100*( mySimulation.GetIndepTransTime()-
		mySimulation.GetOverTransTime() )/mySimulation.GetIndepTransTime() << " %" <<endl;
	cout << "Scheduling Metric: ";
	cout << "Trans time = " << anotherSimulation.GetOverTransTime() << "; ";
	cout << "Improvement ratio = " << 100*( anotherSimulation.GetIndepTransTime()-
		anotherSimulation.GetOverTransTime() )/anotherSimulation.GetIndepTransTime() << " %" <<endl;
	cout << "Largest entropy first: ";
	cout << "Trans time = " << sinrSimulation.GetOverTransTimeListenOneBefore() << "; ";
	cout << "Improvement ratio = " << 100*( sinrSimulation.GetIndepTransTime()-
		sinrSimulation.GetOverTransTime() )/sinrSimulation.GetIndepTransTime() << " %" <<endl;	
	cout << "Smallest entropy first: ";
	cout << "Trans time = " << sinrSimulation2.GetOverTransTimeListenOneBefore() << "; ";
	cout << "Improvement ratio = " << 100*( sinrSimulation2.GetIndepTransTime()-
		sinrSimulation2.GetOverTransTime() )/sinrSimulation2.GetIndepTransTime() << " %" <<endl;	
	cout << "Minimum transmission time = " << mySimulation.GetMinimumTransTime() << " (second)" << endl;
	cout << "Maximum ratio = " << 100*( mySimulation.GetIndepTransTime()-mySimulation.GetMinimumTransTime() )/mySimulation.GetIndepTransTime() << " %" <<endl;
	*/
	
	
	cout << "Indepent transmission byte = " << anotherSimulation.GetIndepTransByte() << endl;
	//cout << "Graph: ";
	//cout << "Trans byte = " << mySimulation.GetOverTransByte() << "; ";
	//cout << "Improvement ratio = " << 100*( mySimulation.GetIndepTransByte()-
	//	mySimulation.GetOverTransByte() )/mySimulation.GetIndepTransByte() << " %" <<endl;
	cout << "Scheduling Metric: ";
	cout << "Trans byte = " << anotherSimulation.GetOverTransByte() << "; ";
	cout << "Improvement ratio = " << 100*( anotherSimulation.GetIndepTransByte()-
		anotherSimulation.GetOverTransByte() )/anotherSimulation.GetIndepTransByte() << " %" <<endl;
    //cout << "Scheduling Metric with interlace IP frame: ";
	//cout << "Trans byte = " << interlaceIPSimulation.GetOverTransByteInterlacedIP() << "; ";
	//cout << "Improvement ratio = " << 100*( interlaceIPSimulation.GetIndepTransByte()-
    //                                       interlaceIPSimulation.GetOverTransByteInterlacedIP() )/interlaceIPSimulation.GetIndepTransByte() << " %" <<endl;
	//cout << "Largest entropy first: ";
	//cout << "Trans byte = " << sinrSimulation.GetOverTransByte() << "; ";
	//cout << "Improvement ratio = " << 100*( sinrSimulation.GetIndepTransByte()-
	//	sinrSimulation.GetOverTransByte() )/sinrSimulation.GetIndepTransByte() << " %" <<endl;
	//cout << "Just for test: ";
	//cout << "Trans byte = " << testSimulation.GetOverTransByte() << "; ";
	//cout << "Improvement ratio = " << 100*( testSimulation.GetIndepTransByte()-
	//	testSimulation.GetOverTransByte() )/testSimulation.GetIndepTransByte() << " %" <<endl;

	cout << "Minimum transmission byte = " << mySimulation.GetMinimumTransByte() << " (bytes)" << endl;
	cout << "Maximum ratio = " << 100*( mySimulation.GetIndepTransByte()-mySimulation.GetMinimumTransByte() )/mySimulation.GetIndepTransByte() << " %" <<endl;
	
}


