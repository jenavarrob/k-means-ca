/******************************************************************* -*- C++ -*-
 *
 * author: Jesus Emeterio Navarro Barrientos.
 * web: https://sites.google.com/site/jenavarrob/
 * date: 2017-01-04
 *******************************************************************************/

#include <algorithm>

#include "cluster.h"
#include "datapoint.h"

using namespace std;

Cluster::Cluster()
{
  mName = "";
  mCentroid = 0; //will be set by calling setCentroid()
}

Cluster::Cluster(string name)
{
  mName = name;
  mCentroid = 0; //will be set by calling setCentroid()
}

void Cluster::addDataPoint(DataPoint dp)
{ //called from CAInstance
  dp.setCluster(this); //initiates a inner call to calcEuclideanDistance() in DP.
  this->mDataPoints.push_back(dp);
  calcSumOfSquares();
}

Centroid* Cluster::getCentroid()
{
  return mCentroid;
}

DataPoint Cluster::getDataPoint(int pos)
{
  return (DataPoint) this->mDataPoints.at(pos);
}

void Cluster::calcSumOfSquares()
{ //called from Centroid
  int size = this->mDataPoints.size();
  double temp = 0;
  for (int i = 0; i < size; i++) {
    temp = temp + ((DataPoint) this->mDataPoints.at(i)).getCurrentEuDt();
  }

  this->mSumSqr = temp;
}

vector<DataPoint> Cluster::getDataPoints()
{
  return this->mDataPoints;
}

int Cluster::getNumDataPoints()
{
  return this->mDataPoints.size();
}

string Cluster::getName()
{
  return this->mName;
}

double Cluster::getSumSqr()
{
  return this->mSumSqr;
}

void Cluster::removeDataPoint(DataPoint dp)
{
  auto it = std::find(mDataPoints.begin(),mDataPoints.end(), dp);
  if (it != mDataPoints.end()) {
    mDataPoints.erase(it);
  }
  
  //this is not working because is erasing all dps with value dp
  // this->mDataPoints.erase(std::remove(mDataPoints.begin(), mDataPoints.end(), dp), mDataPoints.end());

  calcSumOfSquares();
}

void Cluster::setCentroid(Centroid* c)
{
  mCentroid = c;
}
