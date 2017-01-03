# K-Means Clustering Analysis

C++ modified version based on java code for k-means clustering analysis implemented by Shyam Sivaraman and which can be found here: http://www.sourcecodesworld.com/source/show.asp?scriptid=807 (last accesed 2017-01-03)

Clustering algorithms associate a cluster number with each instance, where each instance is characterized by the values of attributes that measure different aspects of the instance. Moreover, clustering algorithms are used in the field of Data Mining for data analysis and separation of data. Clustering algorithms are a type of unsupervised learning, i.e. no learning set is required.

K-Means partitions instances into disjoint clusters and the advantages of this method are that it is linear, meaning that each iteration needs *N × k* comparison and the number of iterations depend on data. Another advantage is that only one parameter needs to be specified, the number *k* of clusters. The disadvantages are that it can be tricky to determine the optimal number *k*. Moreover, the method can convergence to a local optimum due to its sensitive to initial centroid locations.

The method:
* Step 1: Initialize the cluster centroids randomly
* Step 2: Each data point is assigned to its closest centroid (data partitioning). For this, the algorithm computes the distance between centroids and instances and assigns each instance a cluster label.
* Step 3: Relocation of the *means*. Each cluster representative is relocated to the center (mean) of all data points assigned to it. For this, the function *UpdateCluster(ci)* calculates the centroid (mean) of instances in each cluster *ci*.
* Step 4: Repeat step 2 and step 3 until convergence. The algorithm converges when the assignments (the centers) no longer change.

K-means can be used to answer the following questions:
* Potential outliers: Which data items have errors or wrong class assignment? 
* Explanatory variables: How strong is the relation between two variables?
* Prediction: Which variable value A would be expected for new data with a 	given variable value B?
* Classification accuracy: Are there any other classes and subclasses for the data?
