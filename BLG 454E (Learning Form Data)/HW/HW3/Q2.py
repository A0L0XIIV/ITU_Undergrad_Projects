import numpy as np
from numpy import linalg as LA
import matplotlib.pyplot as plt
import cv2
from numpy import zeros


#SVD -> A = U.S.V^t

#Read image as matrix
A = cv2.imread("data.jpg")

#Split RGB
b, g, r = cv2.split(A)
#img = cv2.merge((b,g,r))

#Transpose of RGB
b_transpose = np.transpose(b)
g_transpose = np.transpose(g)
r_transpose = np.transpose(r)

"""
#W = A.ATrans -> for RGB
Wred = np.dot(r, r_transpose)
Wgreen = np.dot(g, g_transpose)
Wblue = np.dot(b, b_transpose)

#Eigenvalues for A.ATrans and eigenvectors of W = U
UEigValRed, Ured = LA.eig(Wred)
UEigValGreen, Ugreen = LA.eig(Wgreen)
UEigValBlue, Ublue = LA.eig(Wblue)
"""
"""
#X = A^t.A -> for RGB
Xred = np.dot(r_transpose, r)
Xgreen = np.dot(g_transpose, g)
Xblue = np.dot(b_transpose, b)

#Eigenvalues for ATrans.A and eigenvectors of X = V
VEigValRed, Vred = LA.eig(Xred)
VEigValGreen, Vgreen = LA.eig(Xgreen)
VEigValBlue, Vblue = LA.eig(Xblue)

VTransRed = np.transpose(Vred)
VTransGreen = np.transpose(Vgreen)
VTransBlue = np.transpose(Vblue)

#S -> sorted sqrt eigenvalues matrix
Sred = zeros((1406, 2500))
Sgreen = zeros((1406, 2500))
Sblue = zeros((1406, 2500))

#Sort and sqrt
Sred_values = np.sort(np.sqrt(np.absolute(VEigValRed)))
Sgreen_values = np.sort(np.sqrt(np.absolute(VEigValGreen)))
Sblue_values = np.sort(np.sqrt(np.absolute(VEigValBlue)))

#S same size with A
for i in range (0, 1406):
    Sred[i][i] = Sred_values[i]
    Sgreen[i][i] = Sgreen_values[i]
    Sblue[i][i] = Sblue_values[i]

#U = A.V.S^-1
SredMatrix = np.matrix(Sred)
Ured = np.dot(r, np.dot(Vred, SredMatrix.I))
SgreenMatrix = np.matrix(Sgreen)
Ugreen = np.dot(g, np.dot(Vgreen, SgreenMatrix.I))
SblueMatrix = np.matrix(Sblue)
Ublue = np.dot(b, np.dot(Vblue, SblueMatrix.I))


plt.title("Original Image")
plt.imshow(A)

Vt = np.dstack((VTransBlue, VTransGreen, VTransRed))
U = np.dstack((Ublue, Ugreen, Ured))
S = np.dstack((Sblue, Sgreen, Sred))
"""
URed, SRedX, VtRed = np.linalg.svd(r)
UGreen, SGreenX, VtGreen = np.linalg.svd(g)
UBlue, SBlueX, VtBlue = np.linalg.svd(b)
"""
Vt = np.dstack((VtBlue, VtGreen, VtRed))
U = np.dstack((UBlue, UGreen, URed))
S = np.dstack((SBlue, SGreen, SRed)),
"""
k = 10

SRed = np.zeros((k, k))
SGreen = np.zeros((k, k))
SBlue = np.zeros((k, k))

for i in range(k):
    SRed[i][i] = SRedX[i]
    SGreen[i][i] = SGreenX[i]
    SBlue[i][i] = SBlueX[i]

#AcompR = np.matrix(URed[:, :k]) * np.diag(SRed[:k]) * np.matrix(VtRed[:k,:])
AcompR = np.dot(np.dot(URed[:, :k],SRed), VtRed[:k,:])
AcompG = np.dot(np.dot(UGreen[:, :k],SGreen), VtGreen[:k,:])
AcompB = np.dot(np.dot(UBlue[:, :k],SBlue), VtBlue[:k,:])
#AcompG = np.matrix(UGreen[:, :k]) * np.diag(SGreen[:k]) * np.matrix(VtGreen[:k,:])
#AcompB = np.matrix(UBlue[:, :k]) * np.diag(SBlue[:k]) * np.matrix(VtBlue[:k,:])
Acomp = cv2.merge((AcompB, AcompG, AcompR))
plt.imshow(Acomp)
title = "Image with rank %d" %k
plt.title(title)
plt.show()

"""
Acomp = np.matrix(U[:, :1]) * np.diag(S[:1]) * np.matrix(Vt[:1,:])
plt.imshow(Acomp)
plt.title("Image with rank 1")
plt.show()

Acomp = np.matrix(U[:, :5]) * np.diag(S[:5]) * np.matrix(Vt[:5,:])
plt.imshow(Acomp)
plt.title("Image with rank 5")
plt.show()

Acomp = np.matrix(U[:, :20]) * np.diag(S[:20]) * np.matrix(Vt[:20,:])
plt.imshow(Acomp)
plt.title("Image with rank 20")
plt.show()

Acomp = np.matrix(U[:, :50]) * np.diag(S[:50]) * np.matrix(Vt[:50,:])
plt.imshow(Acomp)
plt.title("Image with rank 50")
plt.show()
"""