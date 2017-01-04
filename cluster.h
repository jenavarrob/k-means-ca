#ifndef CLUSTER_H
#define CLUSTER_H

//forward declared dependencies
class DataPoint;
class Centroid;

#include <vector>
#include <string>

using namespace std;

class Cluster
{
public:
    Cluster();
    Cluster(string);

    void addDataPoint(DataPoint dp);
    void calcSumOfSquares();
    Centroid* getCentroid();
    DataPoint getDataPoint(int pos);
    vector<DataPoint> getDataPoints();
    string getName();
    int getNumDataPoints();
    double getSumSqr();
    void removeDataPoint(DataPoint dp);
    void setCentroid(Centroid* c);

private:
    Centroid* mCentroid;
    vector<DataPoint> mDataPoints;
    string mName;
    double mSumSqr;
};

#endif // CLUSTER_H
