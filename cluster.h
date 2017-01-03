#ifndef CLUSTER_H
#define CLUSTER_H

//forward declared dependencies
class DataPoint;
class Centroid;

#include <list>
#include <string>

class Cluster
{
public:
    Cluster();
    Cluster(QString);

    void addDataPoint(DataPoint dp);
    void calcSumOfSquares();
    Centroid* getCentroid();
    DataPoint getDataPoint(int pos);
    std::list<DataPoint> getDataPoints();
    string getName();
    int getNumDataPoints();
    double getSumSqr();
    void removeDataPoint(DataPoint dp);
    void setCentroid(Centroid* c);

private:
    Centroid* mCentroid;
    std::list<DataPoint> mDataPoints;
    string mName;
    double mSumSqr;
};

#endif // CLUSTER_H
