/******************************************************************* -*- C++ -*-
*
* author: Jesus Emeterio Navarro Barrientos.
* web: https://sites.google.com/site/jenavarrob/
* date: 2017-01-03
*******************************************************************************/

#ifndef CENTROID_H
#define CENTROID_H

class Cluster;

class Centroid
{
public:
    Centroid(double cx, double cy);

    void calcCentroid();
    Cluster* getCluster();
    double getCx();
    double getCy();
    void setCluster(Cluster* c);

private:
    Cluster* mCluster;
    double mCx, mCy;
};

#endif // CENTROID_H
