#150130032
#Baran Kaya


import numpy as np              #Vector&matrix
from numpy import linalg as LA  #Distance
import matplotlib.pyplot as plt #Graph
from sklearn.preprocessing import StandardScaler    #PCA
from sklearn.decomposition import PCA               #PCA
import csv                      #File reading
from copy import deepcopy       #Copying lists
from math import pow            #SSE

#Data class
class dataClass:
    def __init__(self, line):
        self.features = line[0:len(line)]

dataList = []

#File reading
with open('dataTrain.csv') as file:
    readCSV = csv.reader(file, delimiter=',')
    first = True
    for line in readCSV:
        if first == True: #Get rid of the first line
            first = False
            continue
        #dataList.append(dataClass(line))
        dataList.append(line)

#Data matrix 64x3823
dataList = np.matrix(dataList)
dataList = dataList.astype(float)

instanceSize = len(dataList)
featureSize = 64#len(dataList[0].features)
K = input("K (1,5,10,20): ")
K = int(K)

#PCA -> 2 dimensional
stdData = StandardScaler().fit_transform(dataList)
pca = PCA(n_components = 2)
#print(pca.fit(stdData))
principalComponents = pca.fit_transform(stdData)

#Clustering
cluster = []
b = np.zeros((instanceSize, K)) #Apaydın's algorithm's b
b2 = np.zeros(instanceSize)     #New b for my algorithm
error = 1                       #Error starts with nonzero value.
selected = np.random.randint(instanceSize, size = K) #random index for principalComponents (0 to len)

for i in range(K):
    cluster.append(principalComponents[selected[i]]) #Select random K center points

clusters = np.array(cluster)
pc = np.array(principalComponents)

while error >= 0.001:#!= 0:#Repeat until converge

    for i in range (len(pc)):
        for j in range(K):
            if np.argmin(LA.norm(pc[i] - clusters[j])) == np.argmin(LA.norm(pc[i] - clusters, axis=1)):
                b[i][j] = 1 #If jth point is closer to the ith cluster center
            else:
                b[i][j] = 0 #Else
        b2[i] = np.argmin(LA.norm(pc[i] - clusters, axis=1))#b2 -> directly get the distance as a cluster value

    #Store last clusters for error calculation
    lastClusters = deepcopy(clusters)

    #Algorithm that in the HW file
    """
    for i in range (K):
        sum = np.zeros(2)
        numOfClusterPoints = 0
        for j in range (len(pc)):
            if b[j][i] == 1:
                sum = np.add(sum, pc[j])
            numOfClusterPoints += b[j][i]
        clusters[i] = np.true_divide(sum, numOfClusterPoints)
    #print ("clustes: ", clusters)
    error = LA.norm(lastClusters - clusters)
    print("Error: ", error)
    """

    for i in range (K):
        #clusterPoints = [] #Using np.mean
        sum = np.zeros(2)
        numOfClusterPoints = 0
        for j in range (len(pc)):
            if b2[j] == i:                                      #If jth point in the ith cluster
                sum = np.add(sum, pc[j])                        #Than add it to the sum
                numOfClusterPoints += 1                         #Increase the number
                #clusterPoints.append(pc[j]) #Using np.mean
        clusters[i] = np.true_divide(sum, numOfClusterPoints)   #And calculate the mean
        #clusters[i] = np.mean(clusterPoints, axis=0) #Using np.mean

    #Calculate the error with using distance between last clusters and the new ones
    error = LA.norm(lastClusters - clusters)
    print("Error: ", error)

#Print final centers and plot the graph
print("Final Clusters Centers:\n",clusters)
#Bigger graph
plt.figure(figsize=(15, 10))
#plt.scatter -> for different colors and shapes
for i in range(K):  #Draw every cluster
        clusterPoints = np.array([pc[j] for j in range(len(pc)) if b2[j] == i]) #Create new array with points in ith cluster
        plt.scatter(clusterPoints[:, 0], clusterPoints[:, 1], s = 10, c = np.random.rand(3,))#Draw every cluster with randomly selected color
plt.scatter(clusters[:, 0], clusters[:, 1], s = 100, c = 'black', marker='D') #Draw cluster centers (Black Diamond)
plt.grid()
plt.show()

#SSE
total = 0
for i in range(K):
    for j in range(len(pc)):
        if b2[j] == i:
            total += pow(LA.norm(pc[j] - clusters[i]), 2)
print("SSE: ", total)

