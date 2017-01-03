/******************************************************************* -*- C++ -*-
*
* author: Jesus Emeterio Navarro Barrientos.
* web: https://sites.google.com/site/jenavarrob/
* date: 2017-01-03
*******************************************************************************/

#include "clusteranalysis.h"

#include "datapoint.h"
#include "centroid.h"
#include "cluster.h"

#define DEBUG  //for debugging

clusterAnalysis::clusterAnalysis(int k, int iter, std::list<DataPoint> dataPoints)
{
    for (int i = 0; i < k; i++)
    {
        Cluster clus1=Cluster("Cluster" + QString::number(i));
        clusters.append(clus1);

#ifdef DEBUG
        Cluster clus=clusters.at(i);
        std::cout << "appended cluster: " << clus.getName();
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
}

Cluster clusterAnalysis::getCluster(int pos)
{
    return clusters[pos];
}

std::list<std::list<DataPoint> > clusterAnalysis::getClusterOutput()
{
  std::list<std::list<DataPoint> > dpsOutput;

    for (int i = 0; i < clusters.size(); i++)
    {
        dpsOutput.append(clusters[i].getDataPoints());
    }

    return dpsOutput;
}

double clusterAnalysis::getMaxXValue()
{
    double temp;
    temp = ((DataPoint) mDataPoints.at(0)).getX();

    for (int i = 0; i < mDataPoints.size(); i++)
    {
        DataPoint dp = (DataPoint) mDataPoints.at(i);
        temp = (dp.getX() > temp) ? dp.getX() : temp;
    }
    return temp;
}

double clusterAnalysis::getMaxYValue()
{
    double temp = 0;
    temp = ((DataPoint) mDataPoints.at(0)).getY();

    for (int i = 0; i < mDataPoints.size(); i++)
    {
        DataPoint dp = (DataPoint) mDataPoints.at(i);
        temp = (dp.getY() > temp) ? dp.getY() : temp;
    }
    return temp;
}

double clusterAnalysis::getMinXValue()
{
    double temp = 0;
    temp = ((DataPoint) mDataPoints.at(0)).getX();

    for (int i = 0; i < mDataPoints.size(); i++)
    {
        DataPoint dp = (DataPoint) mDataPoints.at(i);
        temp = (dp.getX() < temp) ? dp.getX() : temp;
    }
    return temp;
}

double clusterAnalysis::getMinYValue()
{
    double temp = 0;
    temp = ((DataPoint) mDataPoints.at(0)).getY();

    for (int i = 0; i < mDataPoints.size(); i++)
    {
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

void clusterAnalysis::setInitialCentroids()
{
    //kn = (round((max-min)/k)*n)+min where n is from 0 to (k-1).
    double cx = 0, cy = 0;

    for (int n = 1; n <= clusters.size(); n++)
    {
        cx = (((getMaxXValue() - getMinXValue()) / (clusters.size() + 1)) * n) + getMinXValue();
        cy = (((getMaxYValue() - getMinYValue()) / (clusters.size() + 1)) * n) + getMinYValue();

        Centroid* c1 = new Centroid(cx, cy);
        clusters[n - 1].setCentroid(c1);
        c1->setCluster(&clusters[n - 1]);
    }
}

void clusterAnalysis::assignDPsToClusters()
{
    int n = 0;

    while (true)
    {
#ifdef DEBUG
        std::cout << "clusterAnalysis::startAnalysis(): clusters.size(): " << clusters.size() << endl;
        std::cout << "clusterAnalysis::startAnalysis(): mDataPoints.size(): " << mDataPoints.size();
#endif
        for (int l = 0; l < clusters.size(); l++)
        {
#ifdef DEBUG
            std::cout << "clusterAnalysis::startAnalysis(): l: " << l << endl;
            std::cout << "clusterAnalysis::startAnalysis(): n: " << n << endl;
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
    std::cout << "entering clusterAnalysis::startAnalysis(): " << endl;
#endif

    //set Starting centroid positions - Start of Step 1
    setInitialCentroids();


#ifdef DEBUG
    std::cout << "clusterAnalysis::startAnalysis(): assign DataPoint to clusters" << endl;
#endif

    //assign DataPoint to clusters
    assignDPsToClusters();

#ifdef DEBUG
    foreach(Cluster clus, clusters)
    {
        std::cout << "-----------Cluster" << ", size: "<< clus.getNumDataPoints() << "---------" << endl;

        foreach(DataPoint dp, clus.getDataPoints())
            std::cout << dp.getObjName() << "[" << dp.getX() << "," << dp.getY() << "]" << endl;
    }
    std::cout << "clusterAnalysis::startAnalysis(): calculate E for all the clusters" << endl;
#endif

    //calculate E for all the clusters
    calcSWCSS();

#ifdef DEBUG
    std::cout << "clusterAnalysis::startAnalysis(): recalculate Cluster centroids - Start of Step 2" << endl;
#endif

    //recalculate Cluster centroids - Start of Step 2
    for (int i = 0; i < clusters.size(); i++)
        clusters[i].getCentroid()->calcCentroid();

#ifdef DEBUG
    std::cout << "clusterAnalysis::startAnalysis(): recalculate E for all the clusters" << endl;
#endif

    //recalculate E for all the clusters
    calcSWCSS();

#ifdef DEBUG
    foreach(Cluster clus, clusters)
    {
        std::cout << "-----------Cluster" << ", size: "<< clus.getNumDataPoints() << "---------" << endl;

        foreach(DataPoint dp, clus.getDataPoints())
            std::cout << dp.getObjName() << "[" << dp.getX() << "," << dp.getY() << "]" << endl;
    }
    std::cout << "clusterAnalysis::startAnalysis(): entering loop for miterations" << endl;
#endif

    for (int i = 0; i < miter; i++)
    {
#ifdef DEBUG
        foreach(Cluster clus, clusters)
        {
            std::cout << "-----------Cluster" << ", size: "<< clus.getNumDataPoints() << "---------" << endl;

            for(DataPoint dp: clus.getDataPoints())
                std::cout << dp.getObjName() << "[" << dp.getX() << "," << dp.getY() << "]" << endl;
        }
        std::cout << "clusterAnalysis::startAnalysis(): iteration: " << i << endl;
#endif

        //enter the loop for cluster 1
        for (int j = 0; j < clusters.size(); j++)
        {
            for (int k = 0; k < clusters[j].getNumDataPoints(); k++)
            {
                //pick the first element of the first cluster
                //get the current Euclidean distance
                double tempEuDt = clusters[j].getDataPoint(k).getCurrentEuDt();
                Cluster* tempCluster=0;
                bool matchFoundFlag = false;

                //call testEuclidean distance for all clusters
                for (int l = 0; l < clusters.size(); l++)
                {
                    //if testEuclidean < currentEuclidean then
                    if (tempEuDt > clusters[j].getDataPoint(k).testEuclideanDistance(clusters[l].getCentroid()))
                    {
                        tempEuDt = clusters[j].getDataPoint(k).testEuclideanDistance(clusters[l].getCentroid());
                        tempCluster = &clusters[l];
                        matchFoundFlag = true;
                    }
                    //if statement - Check whether the Last EuDt is > Present EuDt

                }
                //for variable 'l' - Looping between different Clusters for matching a Data Point.
                //add DataPoint to the cluster and calcSWCSS

                if (matchFoundFlag)
                {
                    tempCluster->addDataPoint(clusters[j].getDataPoint(k));
                    clusters[j].removeDataPoint(clusters[j].getDataPoint(k));

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
    std::cout << "exiting clusterAnalysis::startAnalysis()" << endl << endl;
#endif
}
