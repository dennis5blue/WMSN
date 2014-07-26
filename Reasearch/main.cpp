#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>
#include <stdlib.h>
#include <boost/program_options.hpp>

#define CAMERA_NUM 100
#define INPUT_CORR (char*)("./Topology/city2000_res720_cam100_corrMatrix.txt")
#define INPUT_INDEP (char*)("./Topology/city2000_res720_cam100_indepByte.txt")
#define INPUT_POS (char*)("./Topology/city2000_res720_cam100_pos.txt")

namespace po = boost::program_options;
using namespace std;

int main (int argc, char *argv[])
{
  double powerMaxDbm;
  string scheAlgorithm;
  po::options_description desc ("Allowed options");
  desc.add_options ()
    ("help,h", "Print help messages")
    ("power,p", po::value<double> (), "Maximum power(dbm)")
    ("algorithm,A", po::value<string> (), "Scheduling algorithm");
  po::variables_map vm;
  po::store (po::parse_command_line (argc, argv, desc), vm);
  po::notify (vm);

  if (vm.size () == 0 || vm.count ("help")){
    cout << desc << "\n";
    return 0;
  }else if (vm.size () == 2){
    powerMaxDbm = vm["power"].as<double> ();
    scheAlgorithm = vm["algorithm"].as<string> ();  
  }
  cout << "scheduling algorithm is: " << scheAlgorithm << endl;
}
