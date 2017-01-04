/******************************************************************* -*- C++ -*-
 *
 * author: Jesus Emeterio Navarro Barrientos.
 * web: https://sites.google.com/site/jenavarrob/
 * date: 2017-01-04
 *******************************************************************************/

#include <algorithm>
#include <cstdlib>
#include <vector>
#include <iostream>

class DataPoint;

#include "centroid.h"
#include "cluster.h"
#include "datapoint.h"
#include "clusteranalysis.h"

#define DEBUG

using namespace std;

vector<DataPoint> testData1();
vector<DataPoint> testData2();
void showInput(vector<DataPoint> );
void findClusters(int k, int numIter, vector<DataPoint> dataPoints);

int main(int argc, char *argv[])
{
  vector<DataPoint> dataPoints;
  
  dataPoints = testData1();
  showInput(dataPoints);
  findClusters(3, 5, dataPoints);

  dataPoints = testData2();
  showInput(dataPoints);
  findClusters(5, 10, dataPoints);
  
  return 0;
}

vector<DataPoint> testData1()
{
  vector<DataPoint> dataPoints;
  
  dataPoints.push_back(DataPoint(22,21,"a1"));
  dataPoints.push_back(DataPoint(19,20,"a2"));
  dataPoints.push_back(DataPoint(18,22,"a3"));
  dataPoints.push_back(DataPoint(1,3,"b1"));
  dataPoints.push_back(DataPoint(30,40,"c1"));

  return dataPoints;
}

vector<DataPoint> testData2()
{
  vector<DataPoint> dataPoints;
  
  dataPoints.push_back( DataPoint(19,20,"a2"));
  dataPoints.push_back( DataPoint(18,22,"a3"));
  dataPoints.push_back( DataPoint(1,1,"b1"));
  dataPoints.push_back( DataPoint(40,40,"c1"));
  dataPoints.push_back( DataPoint(10,2,"d1"));
  dataPoints.push_back( DataPoint(9,1,"d2"));
  dataPoints.push_back( DataPoint(7,5,"e1"));
  dataPoints.push_back( DataPoint(8,6,"e2"));
  dataPoints.push_back( DataPoint(6,7,"e3"));
  dataPoints.push_back( DataPoint(22,21,"a1"));

  return dataPoints;
}

void showInput(vector<DataPoint> dataPoints)
{
  //show input
  cout << "\nInput data:" << endl;
  for(DataPoint dp : dataPoints)
    cout << dp.getObjName() << ": (" << dp.getX() << "," << dp.getY() << ")" <<  endl;
}

void findClusters(int k, int numIter, vector<DataPoint> dataPoints)
{
  // constructor calling clusteranalysis(k_number_of_cluster, iterations, data);
  clusterAnalysis ca(k, numIter, dataPoints); 
  ca.startAnalysis();

  vector<vector<DataPoint> > dpOutput = ca.getClusterOutput();

#ifdef DEBUG
  cout << "Number of clusters obtained: " << dpOutput.size() << endl;
#endif

  int i = 0;
  for(vector<DataPoint> dps : dpOutput) {
    i++;
    cout << "-----------Cluster " << i << ", size: "<< dps.size() << "---------" << endl;

    for(DataPoint dp : dps)
      cout << dp.getObjName() << "[" << dp.getX() << "," << dp.getY() << "]" << endl;
  }
}
