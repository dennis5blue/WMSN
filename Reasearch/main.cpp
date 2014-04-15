#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>
#include <stdlib.h>

#define CAMERA_NUM 24
#define INPUT_CORR (char*)("corrMatrix.txt")
#define INPUT_INDEP (char*)("indepByte.txt")
#define INPUT_POS (char*)("pos.txt")

#include "TopologyFactory.h"
#include "ScheduleFactory.h"
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
	//vector< vector<int> > *ptr_mycorrTopology = new vector< vector<int> > (CAMERA_NUM, zeroVector);
	//vector< vector<int> > *ptr_mycorrTopology = &mycorrTopology;
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

	TopologyFactory myTopology( CAMERA_NUM, position, mycorrTopology );
	myTopology.PrintTopology();
	
	ScheduleFactory mySchedule( CAMERA_NUM, position, myTopology.GetTopology() );
	mySchedule.PrintSchedule();
}


