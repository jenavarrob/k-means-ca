/******************************************************************* -*- C++ -*-
 *
 * author: Jesus Emeterio Navarro Barrientos.
 * web: https://sites.google.com/site/jenavarrob/
 * date: 2017-01-03
 *******************************************************************************/

#include <iostream>
#include <ctime>

#include "clusteranalysis.h"

#include "datapoint.h"
#include "centroid.h"
#include "cluster.h"

#define DEBUG  //for debugging

using namespace std;

clusterAnalysis::clusterAnalysis(int k, int iter, vector<DataPoint> dataPoints)
{
  for (int i = 0; i < k; i++) {
    Cluster clus1=Cluster("Cluster" + to_string(i));
    clusters.push_back(clus1);

#ifdef DEBUG
    cout << "push_back cluster: " << clusters.at(i).getName() << endl;
#endif
  }

  miter = iter;
  mDataPoints = dataPoints;
}

void clusterAnalysis::calcSWCSS()
{
  double temp = 0;

  for (int i = 0; i < clusters.size(); i++)
    temp = temp + clusters[i].getSumSqr();

  mSWCSS = temp;

#ifdef DEBUG
  cout << "clusterAnalysis::calcSWCSS(): " << mSWCSS << endl;
#endif
}

Cluster clusterAnalysis::getCluster(int pos)
{
  return clusters[pos];
}

vector<vector<DataPoint> > clusterAnalysis::getClusterOutput()
{
  vector<vector<DataPoint> > dpsOutput;

  for (int i = 0; i < clusters.size(); i++) {
    dpsOutput.push_back(clusters[i].getDataPoints());
  }

  return dpsOutput;
}

double clusterAnalysis::getMaxXValue()
{
  double temp;
  temp = ((DataPoint) mDataPoints.at(0)).getX();

  for (int i = 0; i < mDataPoints.size(); i++) {
    DataPoint dp = (DataPoint) mDataPoints.at(i);
    temp = (dp.getX() > temp) ? dp.getX() : temp;
  }
  return temp;
}

double clusterAnalysis::getMaxYValue()
{
  double temp = 0;
  temp = ((DataPoint) mDataPoints.at(0)).getY();

  for (int i = 0; i < mDataPoints.size(); i++) {
    DataPoint dp = (DataPoint) mDataPoints.at(i);
    temp = (dp.getY() > temp) ? dp.getY() : temp;
  }
  return temp;
}

double clusterAnalysis::getMinXValue()
{
  double temp = 0;
  temp = ((DataPoint) mDataPoints.at(0)).getX();

  for (int i = 0; i < mDataPoints.size(); i++) {
    DataPoint dp = (DataPoint) mDataPoints.at(i);
    temp = (dp.getX() < temp) ? dp.getX() : temp;
  }
  return temp;
}

double clusterAnalysis::getMinYValue()
{
  double temp = 0;
  temp = ((DataPoint) mDataPoints.at(0)).getY();

  for (int i = 0; i < mDataPoints.size(); i++) {
    DataPoint dp = (DataPoint) mDataPoints.at(i);
    temp = (dp.getY() < temp) ? dp.getY() : temp;
  }
  return temp;
}

int clusterAnalysis::getIterations()
{
  return miter;
}

int clusterAnalysis::getKValue()
{
  return clusters.size();
}

double clusterAnalysis::getSWCSS()
{
  return mSWCSS;
}


int clusterAnalysis::getTotalDataPoints()
{
  return mDataPoints.size();
}

void clusterAnalysis::setInitialCentroids(bool randomC)
{
  //kn = (round((max-min)/k)*n)+min where n is from 0 to (k-1).
  double cx, cy;

  std::srand(std::time(0)); // use current time as seed for random generator
  double mValsX = (getMaxXValue() - getMinXValue())/ RAND_MAX;
  double mValsY = (getMaxYValue() - getMinYValue() ) / RAND_MAX;
  for (int n = 1; n <= clusters.size(); n++) {
    if(randomC){
      cx = mValsX * std::rand() + getMinXValue(); 
      cy = mValsY * std::rand() + getMinYValue();
    }
    else{
      cx = (((getMaxXValue() - getMinXValue()) / (clusters.size() + 1)) * n) + getMinXValue();
      cy = (((getMaxYValue() - getMinYValue()) / (clusters.size() + 1)) * n) + getMinYValue();
    }
      
#ifdef DEBUG
    cout << "set initial centroid:" << cx << "," << cy << " to cluster" << clusters[n - 1].getName() << endl;
#endif	

    Centroid* c1 = new Centroid(cx, cy);
    clusters[n - 1].setCentroid(c1);
    c1->setCluster(&clusters[n - 1]);
  }
}

void clusterAnalysis::assignDPsToClusters()
{
  int n = 0;

  while (true) {
#ifdef DEBUG
    cout << "clusterAnalysis::startAnalysis(): clusters.size(): " << clusters.size() << endl;
    cout << "clusterAnalysis::startAnalysis(): mDataPoints.size(): " << mDataPoints.size() << endl;
#endif
    for (int l = 0; l < clusters.size(); l++) {
#ifdef DEBUG
      cout << "clusterAnalysis::startAnalysis(): cluster: " << l << endl;
      cout << "clusterAnalysis::startAnalysis(): counter data points: " << n << endl;
#endif

      clusters[l].addDataPoint((DataPoint)mDataPoints.at(n));
      n++;
      if (n >= mDataPoints.size())
	return;
    }
  }
}

void clusterAnalysis::startAnalysis()
{
#ifdef DEBUG
  cout << "Entering clusterAnalysis::startAnalysis(): " << endl;
#endif

  //set Starting centroid positions - Start of Step 1
  setInitialCentroids(true); //set true for random initial centroids

#ifdef DEBUG
  cout << "clusterAnalysis::startAnalysis(): assign DataPoint to clusters" << endl;
#endif

  //assign DataPoint to clusters
  assignDPsToClusters();

#ifdef DEBUG
  for(Cluster clus : clusters) {
    cout << "-----------Cluster " << clus.getName() << ", size: "<< clus.getNumDataPoints() << "---------" << endl;

    for(DataPoint dp : clus.getDataPoints())
      cout << dp.getObjName() << "[" << dp.getX() << "," << dp.getY() << "]" << endl;
  }
  cout << "clusterAnalysis::startAnalysis(): calculate E for all the clusters" << endl;
#endif

  //calculate E for all the clusters
  calcSWCSS();

#ifdef DEBUG
  cout << "clusterAnalysis::startAnalysis(): recalculate Cluster centroids - Start of Step 2" << endl;
#endif

  //recalculate Cluster centroids - Start of Step 2
  for (int i = 0; i < clusters.size(); i++)
    clusters[i].getCentroid()->calcCentroid();

#ifdef DEBUG
  cout << "clusterAnalysis::startAnalysis(): recalculate E for all the clusters" << endl;
#endif

  //recalculate E for all the clusters
  calcSWCSS();

#ifdef DEBUG
  for(Cluster clus : clusters) {
    cout << "-----------Cluster " << clus.getName() << ", size: "<< clus.getNumDataPoints() << "---------" << endl;

    for(DataPoint dp : clus.getDataPoints())
      std::cout << dp.getObjName() << "[" << dp.getX() << "," << dp.getY() << "]" << endl;
  }
  cout << "clusterAnalysis::startAnalysis(): entering loop for miterations" << endl;
#endif

  for (int i = 0; i < miter; i++) {
      
#ifdef DEBUG
    for(Cluster clus : clusters) {
      cout << "-----------Cluster " << clus.getName() << ", size: "<< clus.getNumDataPoints() << "---------" << endl;

      for(DataPoint dp: clus.getDataPoints())
	cout << dp.getObjName() << "[" << dp.getX() << "," << dp.getY() << "]" << endl;
    }
    cout << "clusterAnalysis::startAnalysis(): iteration: " << i << endl;
#endif

    for (int j = 0; j < clusters.size(); j++) {
#ifdef DEBUG
      cout << "number of clusters: " << clusters.size() << endl;
#endif
      for (int k = 0; k < clusters[j].getNumDataPoints(); k++) {
#ifdef DEBUG
	cout << "cluster: " << j << ", size: " << clusters[j].getNumDataPoints() << endl;
#endif
	//pick the first element of the first cluster
	//get the current Euclidean distance
	double tempEuDt = clusters[j].getDataPoint(k).getCurrentEuDt();

#ifdef DEBUG
	cout << "current Euclidean distance: " << tempEuDt << endl;
#endif

	Cluster* tempCluster=0;
	bool matchFoundFlag = false;

	//testEuclidean distance for all clusters
	for (int l = 0; l < clusters.size(); l++) {
	  //if testEuclidean < currentEuclidean then
	  if (tempEuDt > clusters[j].getDataPoint(k).testEuclideanDistance(clusters[l].getCentroid())) {

	    tempEuDt = clusters[j].getDataPoint(k).testEuclideanDistance(clusters[l].getCentroid());
	    tempCluster = &clusters[l];
	    matchFoundFlag = true;

#ifdef DEBUG
	    cout << "testEuclidean distance < current Euclidean distance: tempEuDt: " << tempEuDt << ", tempCluster: " << tempCluster->getName() << endl;
#endif

	  } // if statement - Check whether the Last EuDt is > Present EuDt
	}
	//for variable 'l' - Looping between different Clusters for matching a Data Point.
	//add DataPoint to the cluster and calcSWCSS

	if (matchFoundFlag) {
#ifdef DEBUG 
	  cout << "matchFound, adding dp " << clusters[j].getDataPoint(k).getObjName() << " to cluster " << tempCluster->getName() << " with current cluster size: " << tempCluster->getNumDataPoints() << endl;
#endif

	  tempCluster->addDataPoint(clusters[j].getDataPoint(k));

#ifdef DEBUG 
	  cout << "Cluster " << tempCluster->getName() << " has new cluster size: " << tempCluster->getNumDataPoints() << endl;
	  cout << "removing dp " << clusters[j].getDataPoint(k).getObjName() << " from cluster " << clusters[j].getName() << endl;
#endif
		    		  
	  clusters[j].removeDataPoint(clusters[j].getDataPoint(k));
#ifdef DEBUG
	  cout << "Cluster " << clusters[j].getName() << " has a new cluster size: " << clusters[j].getNumDataPoints() << endl;
	  cout << "Computing new centroids" << endl;
#endif
		    
	  for (int m = 0; m < clusters.size(); m++)
	    clusters[m].getCentroid()->calcCentroid();

	  //for variable 'm' - Recalculating centroids for all Clusters
	  calcSWCSS();
	}

	//if statement - A Data Point is eligible for transfer between Clusters.
      }
      //for variable 'k' - Looping through all Data Points of the current Cluster.
    }//for variable 'j' - Looping through all the Clusters.
  }//for variable 'i' - Number of iterations.

#ifdef DEBUG
  cout << "exiting clusterAnalysis::startAnalysis()" << endl << endl;
#endif
}
