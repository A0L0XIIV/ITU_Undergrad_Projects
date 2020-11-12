# coding=utf8
# the above tag defines encoding for this document and is for Python 2.x compatibility
# Note: for Python 2.7 compatibility, use ur"" to prefix the regex and u"" to prefix the test string and substitution.

import io
import re
import random

regex = r"(.\.)+|(\d+.\d+.\d+)|(‘‘)|[\"\-'‘.,;%&!?()]|(\w+)"

kapFile = io.open("featureKap.txt", 'r', encoding='utf-8')
Klines = kapFile.read().splitlines()

haberFile = io.open("featureHaber.txt", 'r', encoding='utf-8')
Hlines = haberFile.read().splitlines()

trainFile = io.open("trainKarışık.txt", 'w', encoding='utf-8')
testFile = io.open("testKarışık.txt", 'w', encoding='utf-8')

writeToTrain = True
for Kline in Klines:
    if len(Kline) == 0:
        if random.randint(1, 10) <= 7:#30% test, 70% train
            writeToTrain = True
        else:
            writeToTrain = False

    if writeToTrain == True:
        trainFile.write(Kline + '\n')
    else:
        testFile.write(Kline + '\n')

for Hline in Hlines:
    if len(Hline) == 0:
        if random.randint(1, 10) <= 7:#30% test, 70% train
            writeToTrain = True
        else:
            writeToTrain = False

    if writeToTrain == True:
        trainFile.write(Hline + '\n')
    else:
        testFile.write(Hline + '\n')

