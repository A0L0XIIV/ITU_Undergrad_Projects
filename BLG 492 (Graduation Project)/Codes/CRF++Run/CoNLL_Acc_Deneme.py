# coding=utf8
# the above tag defines encoding for this document and is for Python 2.x compatibility
# Note: for Python 2.7 compatibility, use ur"" to prefix the regex and u"" to prefix the test string and substitution.

import os
import subprocess
import io

#CRF++ TRAIN

#use to suppress output to stdout from the subprocess
# FNULL = open(os.devnull, 'w')

out = input("Output file name (w/o .txt): ") #"testOutput.txt"
out += ".txt"   # It needs .txt extension because file is going to be open with that name

regex = r"(.\.)+|(\d+.\d+.\d+)|(‘‘)|[\"\-'‘.,;%&!?()]|(\w+)"

resultFile = io.open(out, 'r', encoding='utf-8')
lines = resultFile.read().splitlines()

O_O = 0
IORG_IORG = 0
IORG_O = 0
O_IORG = 0

for line in lines:
    if len(line) != 0:
        columns = line.split('\t')
        if columns[len(columns) - 1] == 'O': # Last column is O
            if columns[len(columns) - 2] == 'O': # Previous column is O
                O_O += 1
            elif columns[len(columns) - 2] == 'I-ORG': # Previous column is I-ORG
                IORG_O += 1
            else:
                print("-" + columns[len(columns) - 1] + "- - " + columns[len(columns) - 2] + "-" + "col: " + line)
                print("Error! Actual label is not O or I-ORG.") # Error previous column is not O or I-ORG
        elif columns[len(columns) - 1] == 'I-ORG': # Last column is I_ORG
            if columns[len(columns) - 2] == 'O': # Previous column is O
                O_IORG += 1
            elif columns[len(columns) - 2] == 'I-ORG': # Previous column is I-ORG
                IORG_IORG += 1
            else:
                print("-" + columns[len(columns) - 1] + "- - " + columns[len(columns) - 2] + "-" + "col: " + line)
                print("Error! Actual label is not O or I-ORG.") # Error previous column is not O or I-ORG
        else:
            print("Error! Predicted label is not O or I-ORG.") # Error last column is not O or I-ORG

conllAcc = []
i = 0
while i < (len(lines)):
    CAcolumns = lines[i].split('\t')
    correct = 0
    wrong = 0
    if CAcolumns[len(CAcolumns) - 2] == 'I-ORG':
        for j in range (i, len(lines)):
            #print(j, lines[j])
            CAcolumns2 = lines[j].split('\t')
            if CAcolumns2[len(CAcolumns) - 2] != 'I-ORG':
                i = j
                if correct != 0 and wrong != 0:
                    conllAcc.append( round((correct / (correct + wrong)), 3) )
                break
            else:
                if CAcolumns2[len(CAcolumns) - 1] == 'I-ORG':
                    correct += 1
                else:
                    wrong += 1
    i += 1


#Confusion matrix
print("Confusion matrix:\n")
print("\tPredicted")
print("\tO\tI-ORG")
print("O\t" , O_O , "\t" , O_IORG)
print("I-ORG\t" , IORG_O , "\t" , IORG_IORG)

#Precision - Recall
precision = IORG_IORG / (IORG_IORG + O_IORG)
print("\nPrecision: " , precision)
recall = IORG_IORG / (IORG_IORG + IORG_O)
print ("Recall: " , recall)
print ("CoNLL Accuracy: "  , conllAcc)




