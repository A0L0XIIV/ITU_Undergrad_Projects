# coding=utf8
# the above tag defines encoding for this document and is for Python 2.x compatibility
# Note: for Python 2.7 compatibility, use ur"" to prefix the regex and u"" to prefix the test string and substitution.

import os
import subprocess
import io
import re
import string

#CRF++ TRAIN

#use to suppress output to stdout from the subprocess
# FNULL = open(os.devnull, 'w')

print("CRF++ Training")

folder = input("Folder name for files: ")
temp = input("Template file for training: ") #"testTemplate"
temp = folder + '\\' + temp  # Adding folder path
train = input("Train file (w/o .txt): ") #"testTrain.txt"
train = folder + '\\' + train  # Adding folder path
model = input("Model name: ") #"testModel"
model = folder + '\\' + model  # Adding folder path
algorithm = input("w/ MIRA algorithm (y/n) (Default CRF-L2):")

if algorithm == 'y' or algorithm == 'Y':
    argsLearn = "crf_learn.exe -a MIRA " + temp + " " + train + ".txt " + model
else:
    argsLearn = "crf_learn.exe " + temp + " " + train + ".txt " + model

subprocess.call(argsLearn, stdout=None, stderr=None, shell=False)

#CRF++ TEST

#use to suppress output to stdout from the subprocess
FNULL = open(os.devnull, 'w')

print("CRF++ Testing")

test = input("Test file name (w/o .txt): ") #"testTest.txt"
test = folder + '\\' + test + ".txt"   # It needs .txt extension because file is going to be open with that name
out = input("Output file name (w/o .txt): ") #"testOutput.txt"
out = folder + '\\' + out + ".txt"   # It needs .txt extension because file is going to be open with that name

#Adding features to the test file
regex = r"(.\.)+|(\d+.\d+.\d+)|(‘‘)|[\"\-'‘.,;%&!?()]|(\w+)"

cityFileName = folder + '\\' + 'sehir_isimleri.txt'
nameFileName = folder + '\\' + 'kisi_isimleri.txt'

cityFile = io.open(cityFileName, 'r', encoding='utf-8')
cities = cityFile.read().splitlines()

nameFile = io.open(nameFileName, 'r', encoding='utf-8')
names = nameFile.read().splitlines()

testFile = io.open(test, 'r', encoding='utf-8')
testLines = testFile.read().splitlines()

testFeatureFileName = folder + '\\' + 'testWithFeatures.txt'
testFeatureFile = io.open(testFeatureFileName, 'w', encoding='utf-8')

# translation for Turksih 'İ', usage:
# string.translate(tr_map).upper()
tr_map = {
    ord(u'ı'): u'I',
    ord(u'i'): u'İ',
    }

def hasNumbers(inputString):
    return any(char.isdigit() for char in inputString)

def hasPunctuation(inputString):
    return any(char in string.punctuation for char in inputString)

#Harflerin büyük küçüklüğü ve noktalama -> UU, UL, UPUP, UUP, L
#Şehir, isim veya diğer     -> CITY, NAME, O
#Sadece noktalama ise       ->  PUNC, P veya A
#Sayı veya sayı içeriyor    -> DGT, CDGT, NDGT

#CoNLL format
for ln in testLines:
    matches = re.finditer(regex, ln, re.MULTILINE | re.IGNORECASE)
    for matchNum, match in enumerate(matches):
        matchNum = matchNum + 1
        match = match.group()

        #Adding features
        isCity = False
        isName = False

        if match[0].isupper():  # Is capital letter
            #Upper - Lower tags
            testFeatureFile.write(match + '\tU')

            numOfU = 1
            for j in range (1, len(match)):
                if match[j].islower():
                    testFeatureFile.write('L')
                    break
                elif match[j].isupper():
                    if numOfU >= 2:
                        break
                    testFeatureFile.write('U')
                    numOfU += 1
                elif hasPunctuation(match[j]):
                    testFeatureFile.write('P')
                else:
                    break
            # UL -> Upper lower, exp: Bursa
            # UU -> Upper upper, exp: BURSA
            # UPU -> Upper Punc Upper, exp: A.Ş
            # UUP -> Upper Upper Punc, exp: AŞ.
            # UPUP -> Upper Punc Upper Punc, exp: A.Ş.

            """
            if match[1].islower():
                testFeatureFile.write('L')                          # UL -> Upper lower, exp: Bursa
            elif match[1].isupper():
                testFeatureFile.write('U')                          # UU -> Upper upper, exp: BURSA
                if len(match) > 2 and hasPunctuation(match[2]):
                    testFeatureFile.write('P')                      # UUP -> Upper upper Punc, exp: AŞ.
            elif hasPunctuation(match[1]) and len(match) > 2 and match[2].isupper():
                testFeatureFile.write('PU')                         # UPU -> Upper Punc Upper, exp: A.Ş
                if len(match) > 3 and hasPunctuation(match[3]):
                    testFeatureFile.write('P')                      # UPUP -> Upper Punc Upper Punc, exp: A.Ş.
            """

                    #City - Name tags
            for city in cities:
                if match.translate(tr_map).upper() == city.translate(tr_map).upper():
                    testFeatureFile.write('\tCITY')                 # City name tag
                    isCity = True
                    break
            if not isCity:
                for name in names:
                    if match.translate(tr_map).upper() == name.translate(tr_map).upper():
                        testFeatureFile.write('\tNAME')             # Or person name tag
                        isName = True
                        break
            if not isCity and not isName:
                testFeatureFile.write('\tO')                        # Or other name tag

            #Punctuation and Digit tags
            testFeatureFile.write('\tNPNC' + '\tNDGT' + '\n')       # Not punctiation and not digit tags


        else:   # Not capital letter -> Lower (L)
            #Lower and Not City-Name tags
            testFeatureFile.write(match + '\tL' + '\tO')    # Lower and other name tags

            #Punctuation Tags
            if match == '\'':
                testFeatureFile.write('\tA')                        # Apostrophe tag
            elif match == '(' or match == ')':
                testFeatureFile.write('\tP')                        # Parentheses tag
            elif hasPunctuation(match):
                testFeatureFile.write('\tPUNC')                     # Punctuation tag
            else:
                testFeatureFile.write('\tNPNC')                     # Not punctuation tag

            #Digit tags
            if match.isdigit():
                testFeatureFile.write('\tDGT')                      # Digit tag
            elif hasNumbers(match):
                testFeatureFile.write('\tCDGT')                     # Contains any digit tag
            else:
                testFeatureFile.write('\tNDGT')                     #Does not have any digit (Not digit) tag
            testFeatureFile.write('\n')

    testFeatureFile.write('\n')

testFeatureFile.close();

#Run CRF++ Test
#argsTest = "crf_test.exe -m " + model + " " + test + ".txt>" + out
argsTest = "crf_test -m " + model + " " + testFeatureFileName + " > " + out

subprocess.call(argsTest, stdout=FNULL, stderr=None, shell=True)

"""
#TEST ACCURACY

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

#Confusion matrix
print("Confusion matrix:\n")
print("\tPredicted")
print("\tO\tI-ORG")
print("O\t" , O_O , "\t" , O_IORG)
print("I-ORG\t" , IORG_O , "\t" , IORG_IORG)

#Accuracy - Precision - Recall
accuracy = (IORG_IORG + O_O) / (IORG_IORG + O_O + O_IORG + IORG_O)
print("\nAccuracy: " , accuracy)
precision = IORG_IORG / (IORG_IORG + O_IORG)
print("Precision: " , precision)
recall = IORG_IORG / (IORG_IORG + IORG_O)
print ("Recall: " , recall)
print ("CoNLL Accuracy: (" , len(conllAcc), ") ", conllAcc)
"""



