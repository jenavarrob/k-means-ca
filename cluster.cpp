/******************************************************************* -*- C++ -*-
*
* author: Jesus Emeterio Navarro Barrientos.
* web: https://sites.google.com/site/jenavarrob/
* date: 2017-01-03
*******************************************************************************/

#include "cluster.h"
#include "datapoint.h"

Cluster::Cluster()
{
    mName = "";
    mCentroid = 0; //will be set by calling setCentroid()
}

Cluster::Cluster(QString name)
{
    mName = name;
    mCentroid = 0; //will be set by calling setCentroid()
}

void Cluster::addDataPoint(DataPoint dp)
{ //called from CAInstance
    dp.setCluster(this); //initiates a inner call to calcEuclideanDistance() in DP.
    this->mDataPoints.append(dp);
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

QList<DataPoint> Cluster::getDataPoints()
{
    return this->mDataPoints;
}

int Cluster::getNumDataPoints()
{
    return this->mDataPoints.size();
}

QString Cluster::getName()
{
    return this->mName;
}

double Cluster::getSumSqr()
{
    return this->mSumSqr;
}

void Cluster::removeDataPoint(DataPoint dp)
{
    this->mDataPoints.removeOne(dp);
    calcSumOfSquares();
}

void Cluster::setCentroid(Centroid* c)
{
    mCentroid = c;
}
