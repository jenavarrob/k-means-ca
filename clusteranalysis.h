/******************************************************************* -*- C++ -*-
*
* author: Jesus Emeterio Navarro Barrientos.
* web: https://sites.google.com/site/jenavarrob/
* date: 2017-01-03
*******************************************************************************/

#ifndef CLUSTERANALYSIS_H
#define CLUSTERANALYSIS_H

#include <vector>

class Cluster;
class DataPoint;

class clusterAnalysis
{
public:
  clusterAnalysis(int k, int iter, std::vector<DataPoint> dataPoints);

    //methods
    void assignDPsToClusters();
    Cluster getCluster(int pos);
    std::vector<std::vector<DataPoint> > getClusterOutput();
    int getIterations();
    int getKValue();
    double getSWCSS() ;
    int getTotalDataPoints();
    void startAnalysis();

private:
    std::vector<Cluster> clusters;
    std::vector<DataPoint> mDataPoints;

    int miter;
    double mSWCSS;

    //methods
    void calcSWCSS();
    double getMaxXValue();
    double getMinXValue();
    double getMaxYValue();
    double getMinYValue();
    void setInitialCentroids(bool);
};

#endif // CLUSTERANALYSIS_H
