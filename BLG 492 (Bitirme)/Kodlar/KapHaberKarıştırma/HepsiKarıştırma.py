# coding=utf8
# the above tag defines encoding for this document and is for Python 2.x compatibility
# Note: for Python 2.7 compatibility, use ur"" to prefix the regex and u"" to prefix the test string and substitution.

import io
import re
import random

regex = r"(.\.)+|(\d+.\d+.\d+)|(‘‘)|[\"\-'‘.,;%&!?()]|(\w+)"

kapFile = io.open("featureKap.txt", 'r', encoding='utf-8')
Klines = kapFile.read()

haberFile = io.open("featureHaber.txt", 'r', encoding='utf-8')
Hlines = haberFile.read()

allFile = io.open("hepsiKarışık.txt", 'w', encoding='utf-8')

#print("-" + Klines + "-")
Ksentences = Klines.split('\n\n')
Hsentences = Hlines.split('\n\n')

k = 0
h = 0
for i in range (len(Ksentences) + len(Hsentences)):
    if random.randint(0, 1) == 0:
        if k < len(Ksentences):
            allFile.write(Ksentences[k] + '\n\n')
            k += 1
        else:
            allFile.write(Hsentences[h] + '\n\n')
            h += 1
    else:
        if h < len(Hsentences):
            allFile.write(Hsentences[h] + '\n\n')
            h += 1
        else:
            allFile.write(Ksentences[k] + '\n\n')
            k += 1
