import matplotlib.pyplot as plt
import re
import math
import numpy as np
from sympy import *

#opening file
file = open("datatrain.csv", "r")

#data class and class list
class dataClass:
    def __init__(self, X1, X2, Y):
        self.x1 = float(X1)
        self.x2 = float(X2)
        self.y = int(Y)

dataList = []

#reading file
for line in file:
    #print(line)
    elements = line.split(',')
    #print(elements)
    if elements[0] != 'x1': #-> First line
        dataList.append(dataClass(elements[0], elements[1], elements[2]))

#Calculating means -> means[3][2] -> Every classes' x1 and x2 means

means = [[0.0, 0.0], [0.0, 0.0], [0.0, 0.0]]
c0x1Sum = c0x2Sum = c1x1Sum = c1x2Sum = c2x1Sum = c2x2Sum = 0
numOfClass0 = numOfClass1 = numOfClass2 = 0

for item in dataList:
    if item.y == 0:
        c0x1Sum += item.x1
        c0x2Sum += item.x2
        numOfClass0 += 1
    elif item.y == 1:
        c1x1Sum += item.x1
        c1x2Sum += item.x2
        numOfClass1 += 1
    else:
        c2x1Sum += item.x1
        c2x2Sum += item.x2
        numOfClass2 += 1

means[0][0] = c0x1Sum / numOfClass0
means[0][1] = c0x2Sum / numOfClass0
means[1][0] = c1x1Sum / numOfClass1
means[1][1] = c1x2Sum / numOfClass1
means[2][0] = c2x1Sum / numOfClass2
means[2][1] = c2x2Sum / numOfClass2

#Calculating variances -> variance[3][2] -> Every classes' x1 and x2 variances

variance = [[0.0, 0.0], [0.0, 0.0], [0.0, 0.0]]
c0x1Gap = c0x2Gap = c1x1Gap = c1x2Gap = c2x1Gap = c2x2Gap = 0

for item in dataList:
    if item.y == 0:
        c0x1Gap += (item.x1 - means[0][0])
        c0x2Gap += (item.x2 - means[0][1])
    elif item.y == 1:
        c1x1Gap += (item.x1 - means[1][0])
        c1x2Gap += (item.x2 - means[1][1])
    else:
        c2x1Gap += (item.x1 - means[2][0])
        c2x2Gap += (item.x2 - means[2][1])

variance[0][0] = pow(c0x1Gap, 2) / (numOfClass0 - 1)
variance[0][1] = pow(c0x2Gap, 2) / (numOfClass0 - 1)
variance[1][0] = pow(c1x1Gap, 2) / (numOfClass0 - 1)
variance[1][1] = pow(c1x2Gap, 2) / (numOfClass0 - 1)
variance[2][0] = pow(c2x1Gap, 2) / (numOfClass0 - 1)
variance[2][1] = pow(c2x2Gap, 2) / (numOfClass0 - 1)

#Calculating covariances -> Every classes variances

covarianceClass0 = 0 #Covariance of x1 and x2 for class 0
covarianceClass1 = 0 #Covariance of x1 and x2 for class 1
covarianceClass2 = 0 #Covariance of x1 and x2 for class 2

c0GapsMultiplication = c1GapsMultiplication = c2GapsMultiplication = 0

for item in dataList:
    if item.y == 0:
        c0GapsMultiplication += (item.x1 - means[0][0]) * (item.x2 - means[0][1])
    elif item.y == 1:
        c1GapsMultiplication += (item.x1 - means[1][0]) * (item.x2 - means[1][1])
    else:
        c2GapsMultiplication += (item.x1 - means[2][0]) * (item.x2 - means[2][1])

covarianceClass0 = c0GapsMultiplication / (numOfClass0 - 1)
covarianceClass1 = c1GapsMultiplication / (numOfClass1 - 1)
covarianceClass2 = c2GapsMultiplication / (numOfClass2 - 1)

#Creating sigma's ->  Every classes sigmas

sigmaClass0 = [[variance[0][0], covarianceClass0], [covarianceClass0, variance[0][1]]]
sigmaClass1 = [[variance[1][0], covarianceClass1], [covarianceClass1, variance[1][1]]]
sigmaClass2 = [[variance[2][0], covarianceClass2], [covarianceClass2, variance[2][1]]]

#Discriminant Function
#gi(x) = lnP(x|Ci) + lnP(Ci)

#gi(x) = [-1/2 * (x - mu-i)-trans * sigma-inverse * (x - mu-i)] - [-1/2 * ln(abs(sigma-i))] + [ln(P(ci)]
def giFirst (i, x1, x2): #i is the class number -> y
    muTrans = np.array(means[i]) #means[i] -> [mx1, mx2] -> vector
    mu = muTrans.T
    if i == 0:
        sigma = np.matrix(sigmaClass0)
    elif i == 1:
        sigma = np.matrix(sigmaClass1)
    else:
        sigma = np.matrix(sigmaClass2)
    sigmaInverse = sigma.I
    x = [x1,x2]
    x = np.array(x)

    xMinusMu = np.subtract(x,mu)

    #[-1/2 * (x - mu-i)-trans * sigma-inverse * (x - mu-i)]
    resultP1 = (-0.5) * (xMinusMu.T @ sigmaInverse @ xMinusMu)

    #[-1/2 * ln(det(sigma))]
    determinantOfSigma = np.linalg.det(sigma)
    resultP2 = (-0.5) * np.log(abs(determinantOfSigma))

    totalNum = numOfClass0 + numOfClass1 + numOfClass2
    Pc = [numOfClass0/totalNum, numOfClass1/totalNum, numOfClass2/totalNum]

    #lnP(ci) - 1/2 * mu-i-trans * sigma-inverse * mu-i
    resultP3 = np.log(Pc[i])

    result = resultP1 + resultP2 + resultP3
    print("result: %d" % result)
    return result

#gi(x) = [xTrans * -1/2 * sigmaInverse * x] + [muTrans * sigmaInverse] + [-1/2 * muTrans * sigmaInverse * mu - 1/2 * ln|det(sigma)| + ln(P(ci))]
def gi (i, x1, x2): #i is the class number -> y
    muTrans = np.array(means[i]) #means[i] -> [mx1, mx2] -> vector
    mu = muTrans.T
    if i == 0:
        sigma = np.matrix(sigmaClass0)# -> Numpy
        #sigma = Matrix(sigmaClass0)    -> Sympy
    elif i == 1:
        sigma = np.matrix(sigmaClass1)# -> Numpy
        #sigma = Matrix(sigmaClass1)    -> Sympy
    else:
        sigma = np.matrix(sigmaClass2)# -> Numpy
        #sigma = Matrix(sigmaClass2)    -> Sympy

    sigmaInverse = sigma.I#   -> Numpy
    #sigmaInverse = sigma**-1 -> Sympy
    #x1 = symbols('x1')   -> Sympy
    #x2 = symbols('x2')   -> Sympy
    #x = Matrix([x1,x2])  -> Sympy
    x = [x1, x2]        # -> Numpy
    x = np.array(x)     # -> Numpy
    xTrans = x.T

    #[xTrans * -1/2 * sigmaInverse * x]
    W = (-0.5 * sigmaInverse)

    #[muTrans * sigmaInverse]
    wTrans = muTrans @ sigmaInverse# -> Numpy
    #wTrans = muTrans * sigmaInverse -> Sympy

    determinantOfSigma = np.linalg.det(sigma)# -> Numpy
    #determinantOfSigma = sigma.det() -> Sympy
    totalNum = numOfClass0 + numOfClass1 + numOfClass2
    Pc = [numOfClass0/totalNum, numOfClass1/totalNum, numOfClass2/totalNum]

    #[-1/2 * muTrans * sigmaInverse * mu - 1/2 * ln|det(sigma)| + ln(P(ci))]
    wi0 = (-0.5 * muTrans @ sigmaInverse @ mu) + (-0.5 * np.log(abs(determinantOfSigma))) + np.log(Pc[i])# -> Numpy
    result = (xTrans @ W @ x) + (wTrans @ x) + wi0# -> Numpy
    # wi0 = (-0.5 * (muTrans * sigmaInverse * mu)) + (-0.5 * ln(abs(determinantOfSigma))) + ln(Pc[i]) -> Sympy
    #result = (xTrans * W * x) + (wTrans * x) + wi0 -> Sympy
    print(result)
    return result

#Graph

h = 0.02
x1_min = min(dataList, key=lambda dataClass: dataClass.x1).x1
x1_max = max(dataList, key=lambda dataClass: dataClass.x1).x1
x2_min = min(dataList, key=lambda dataClass: dataClass.x2).x2
x2_max = max(dataList, key=lambda dataClass: dataClass.x2).x2

xx1, xx2 = np.meshgrid(np.arange(x1_min, x2_max, h), np.arange(x2_min, x2_max, h))
#Z = gi(0, np.c_[xx1.ravel(), xx2.ravel()])

#gi = gj -> Yapılacak fakat denklem şeklinde olmalı...
#g1 = g2, g2 = g3, g1 = g3 and g1 = g2 = g3
#x1,x2 = 0.0
#gi(0, x1, x2) = gi(1, x1, x2)
#eval('lambda x, y: x/y')
#son = eval('lambda x1, x2: gi(0, x1, x2)')
#son = eval('lambda x1, x2: gi(0, x1, x2)')
#son = eval(x1, gi(0, x1, x2) = gi(1, x1, x2))
#print(son)
#print(eval('lambda x1, x2: gi(0, x1, x2) - gi(1, x1, x2)'))
#sympy.symbols('x1 x2')
#x1 = symbols('x1')
#x2 = symbols('x2')
#expr = gi(0, x1, x2) - gi(1, x1, x2)
#print(expr)


plt.figure(1, figsize=(4,3))
#plt.pcolormesh(xx1, xx2)

plt.xlabel('X1')
plt.ylabel('X2')
plt.xlim(xx1.min(), xx1.max())
plt.ylim(xx2.min(), xx2.max())
plt.xticks(())
plt.yticks(())
#plt.plot(gi(0,1,1))

plt.show()

#opening test file
file = open("datatest.csv", "r")

#data class and class list
class dataTestClass:
    def __init__(self, X1, X2, Y):
        self.x1 = float(X1)
        self.x2 = float(X2)
        self.y = int(Y)
        self.y_calc = 0.0
    def calculate(self):
        self.y_calc = gi(self.y, self.x1, self.x2)

dataTestList = []

#reading test file
for line in file:
    #print(line)
    elements = line.split(',')
    #print(elements)
    if elements[0] != 'x1': #-> First line
        dataTestList.append(dataTestClass(elements[0], elements[1], elements[2]))

numOfTrue = 0
numOfTotal = 0

for item in dataTestList:
    if item.calculate() == item.y:
        numOfTrue += 1
    numOfTotal += 1

print("Accuracy: %d" % (numOfTrue/numOfTotal))