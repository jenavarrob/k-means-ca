/******************************************************************* -*- C++ -*-
*
* author: Jesus Emeterio Navarro Barrientos.
* web: https://sites.google.com/site/jenavarrob/
* date: 2017-01-03
*******************************************************************************/

//#include <stdio.h>

#include <algorithm>
#include <cstdlib>
#include <list>


class DataPoint;

#include "centroid.h"
#include "cluster.h"
#include "datapoint.h"
#include "clusteranalysis.h"

#define DEBUG

using namespace std;

int main(int argc, char *argv[])
{
  list<DataPoint> dataPoints;

// test1()
//    dataPoints.append(DataPoint(22,21,"a1"));
//    dataPoints.append(DataPoint(19,20,"a2"));
//    dataPoints.append(DataPoint(18,22,"a3"));
//    dataPoints.append(DataPoint(1,3,"b1"));
//    dataPoints.append(DataPoint(30,20,"c1"));

      //clusterAnalysis ca(3,10,dataPoints);
  
// test2()
    dataPoints.append( DataPoint(19,20,"a2"));
    dataPoints.append( DataPoint(18,22,"a3"));
    dataPoints.append( DataPoint(1,1,"b1"));
    dataPoints.append( DataPoint(40,40,"c1"));
    dataPoints.append( DataPoint(10,2,"d1"));
    dataPoints.append( DataPoint(9,1,"d2"));
    dataPoints.append( DataPoint(7,5,"e1"));
    dataPoints.append( DataPoint(8,6,"e2"));
    dataPoints.append( DataPoint(6,7,"e3"));
    dataPoints.append( DataPoint(22,21,"a1"));

    //show input
    cout << "\nInput data:" << endl;
    for(DataPoint dp : dataPoints)
        cout << dp.getObjName();

    //constructor calling clusteranalysis(k_number_of_cluster, iterations, data);

    clusterAnalysis ca(5,10,dataPoints);

    ca.startAnalysis();

    list<list<DataPoint> > dpOutput = ca.getClusterOutput();

#ifdef DEBUG
    cout << "Number of clusters obtained: " << dpOutput.size() << endl;
#endif

    int i=0;
    for(list<DataPoint> dps : dpOutput) {
        i++;
        cout << "-----------Cluster" << i << ", size: "<< dps.size() << "---------" << endl;

        for(DataPoint dp : dps)
	  cout << dp.getObjName() << "[" << dp.getX() << "," << dp.getY() << "]" << endl;
    }

    return 0;
}
