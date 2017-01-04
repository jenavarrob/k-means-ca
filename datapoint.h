/******************************************************************* -*- C++ -*-
*
* author: Jesus Emeterio Navarro Barrientos.
* web: https://sites.google.com/site/jenavarrob/
* date: 2017-01-03
*******************************************************************************/

#ifndef DATAPOINT_H
#define DATAPOINT_H

#include <string>
#include <cmath>

//forward declarations
class Centroid;
class Cluster;

class DataPoint
{
public:
  DataPoint(double x, double y, std::string name);

    void calcEuclideanDistance();        
    Cluster* getCluster();
    double getCurrentEuDt();
    std::string getObjName();
    double getX();
    double getY();
    void setCluster(Cluster* cluster);
    double testEuclideanDistance(Centroid* c);

    //overload operator for removeOne() from vector on Cluster::removeDataPoint(DataPoint dp)
    bool operator==(DataPoint dp1);

private:    
    Cluster* mCluster;
    double mEuDt;
    std::string mObjName;    
    double mX,mY;
};

#endif // DATAPOINT_H


