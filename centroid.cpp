/******************************************************************* -*- C++ -*-
 *
 * author: Jesus Emeterio Navarro Barrientos.
 * web: https://sites.google.com/site/jenavarrob/
 * date: 2017-01-04
 *******************************************************************************/

#include "centroid.h"

#include "cluster.h"
#include "datapoint.h"

Centroid::Centroid(double cx, double cy)
{
  this->mCx = cx;
  this->mCy = cy;
}

void Centroid::calcCentroid()
{ //only called by CAInstance
  int numDP = mCluster->getNumDataPoints();
  double tempX = 0, tempY = 0;
  int i;

  //calculating the new Centroid
  for (i = 0; i < numDP; i++) {
    tempX = tempX + mCluster->getDataPoint(i).getX();
    //total for x
    tempY = tempY + mCluster->getDataPoint(i).getY();
    //total for y
  }

  this->mCx = tempX / numDP;
  this->mCy = tempY / numDP;

#ifdef DEBUG
  cout << "set new centroid:" << mCx << "," << mCy << " to cluster" << mCluster->getName() << endl;
#endif
	
  //calculating the new Euclidean Distance for each Data Point
  tempX = 0;
  tempY = 0;

  for (i = 0; i < numDP; i++) {
    mCluster->getDataPoint(i).calcEuclideanDistance();
  }
  //calculate the new Sum of Squares for the Cluster
  mCluster->calcSumOfSquares();
}

Cluster* Centroid::getCluster()
{
  return mCluster;
}

double Centroid::getCx()
{
  return mCx;
}

double Centroid::getCy()
{
  return mCy;
}

void Centroid::setCluster(Cluster* c)
{
  mCluster = c;
}
