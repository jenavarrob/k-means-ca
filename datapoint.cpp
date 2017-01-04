/******************************************************************* -*- C++ -*-
 *
 * author: Jesus Emeterio Navarro Barrientos.
 * web: https://sites.google.com/site/jenavarrob/
 * date: 2017-01-03
 *******************************************************************************/

#include "datapoint.h"

#include "cluster.h"
#include "centroid.h"

using namespace std;

DataPoint::DataPoint(double x, double y, string name)
{
  mX = x;
  mY = y;
  mObjName = name;
  mCluster = 0;
}

void DataPoint::calcEuclideanDistance()
{
  //called when DP is added to a cluster or when a Centroid is recalculated.
  mEuDt = sqrt(pow((mX - mCluster->getCentroid()->getCx()),
		   2) + pow((mY - mCluster->getCentroid()->getCy()), 2));
}

Cluster* DataPoint::getCluster()
{
  return mCluster;
}

double DataPoint::getCurrentEuDt()
{
  return mEuDt;
}

string DataPoint::getObjName()
{
  return mObjName;
}

double DataPoint::getX()
{
  return mX;
}

double DataPoint::getY()
{
  return mY;
}

void DataPoint::setCluster(Cluster* cluster)
{
  mCluster = cluster;
  calcEuclideanDistance();
}

double DataPoint::testEuclideanDistance(Centroid* c)
{
  return sqrt(pow((mX - c->getCx()), 2) + pow((mY - c->getCy()), 2));
}

bool DataPoint::operator ==(DataPoint dp1)
{
  if(dp1.getX()!=this->getX())
    return false;
  if(dp1.getY()!=this->getY())
    return false;
  if(dp1.getObjName()!=this->getObjName())
    return false;

  return true;
}
