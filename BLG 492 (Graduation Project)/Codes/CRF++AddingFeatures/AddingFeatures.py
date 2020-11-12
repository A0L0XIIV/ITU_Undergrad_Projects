# coding=utf8
# the above tag defines encoding for this document and is for Python 2.x compatibility
# Note: for Python 2.7 compatibility, use ur"" to prefix the regex and u"" to prefix the test string and substitution.

import io
import re

inFileName = 'etiketlliKap.txt'
cityFileName = 'sehir_isimleri.txt'
nameFileName = 'kisi_isimleri.txt'
outFileName = 'featureKap.txt'

regex = r"(.\.)+|(\d+.\d+.\d+)|(‘‘)|[\"\-'‘.,;%&!?()]|(\w+)"

inFile = io.open(inFileName, 'r', encoding='utf-8')
lines = inFile.read().splitlines()

cityFile = io.open(cityFileName, 'r', encoding='utf-8')
cities = cityFile.read().splitlines()

nameFile = io.open(nameFileName, 'r', encoding='utf-8')
names = nameFile.read().splitlines()

outFile = io.open(outFileName, 'w', encoding='utf-8')

# translation for Turksih 'İ', usage:
# string.translate(tr_map).upper()
tr_map = {
    ord(u'ı'): u'I',
    ord(u'i'): u'İ',
    }

def hasNumbers(inputString):
    return any(char.isdigit() for char in inputString)

isCity = False
isName = False
#Feature ekleme
for line in lines:
    isCity = False
    isName = False
    for i in range(len(line)):
        if line[i] == '\t':

            if line[0].isupper():  # Is capital letter
                outFile.write(line[:i] + '\tCAP')               # Capital letter tag
                for city in cities:
                    if line[:i].translate(tr_map).upper() == city.translate(tr_map).upper():
                        outFile.write('\tCITY')                 # City name tag
                        isCity = True
                        break
                if not isCity:
                    for name in names:
                        if line[:i].translate(tr_map).upper() == name.translate(tr_map).upper():
                            outFile.write('\tNAME')             # Or person name tag
                            isName = True
                            break
                if not isCity and not isName:
                    outFile.write('\tGEN')                      # Or general name tag
                outFile.write('\tO' + '\tNDGT' + line[i:])      # Not punctiation and not digit tags

            else:   # Not capital letter
                outFile.write(line[:i] + '\tNCAP' + '\tGEN')    # Not capital and general name tags
                if line[:i] == '\'':
                    outFile.write('\tA')                        # Apostrophe tag
                elif line[:i] == '(' or line[:i] == ')':
                    outFile.write('\tP')                        # parentheses tag
                else:
                    outFile.write('\tO')                        # Not Apostrophe or parentheses tag

                if hasNumbers(line[:i]):
                    outFile.write('\tDGT')                      # Has any digit tag
                else:
                    outFile.write('\tNDGT')                     #Does not have any digit (Not digit) tag
                outFile.write(line[i:])
    outFile.write('\n')



