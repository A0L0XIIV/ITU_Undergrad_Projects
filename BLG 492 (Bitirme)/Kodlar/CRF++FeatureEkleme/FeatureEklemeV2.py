# coding=utf8
# the above tag defines encoding for this document and is for Python 2.x compatibility
# Note: for Python 2.7 compatibility, use ur"" to prefix the regex and u"" to prefix the test string and substitution.

import io
import re
import string

inFileName = 'etiketliHaber.txt'
cityFileName = 'sehir_isimleri.txt'
nameFileName = 'kisi_isimleri.txt'
outFileName = 'featureHaber.txt'

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

def hasPunctuation(inputString):
    return any(char in string.punctuation for char in inputString)

isCity = False
isName = False
#Feature ekleme
for line in lines:
    isCity = False
    isName = False
    for i in range(len(line)):
        if line[i] == '\t':

            if line[0].isupper():  # Is capital letter
                #Upper - Lower tags
                outFile.write(line[:i] + '\tU')
                if line[1].islower():
                    outFile.write('L')                          #UL -> Upper lower, exp: Bursa
                elif line[1].isupper():
                    outFile.write('U')                          #UU -> Upper upper, exp: BURSA
                elif hasPunctuation(line[1]) and line[2].isupper() and hasPunctuation(line[3]):
                    outFile.write('PUP')                        #UPUP -> Upper Punc Upper Punc, exp: A.Ş.

                #City - Name tags
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
                    outFile.write('\tO')                        # Or other name tag

                #Punctuation and Digit tags
                outFile.write('\tNPNC' + '\tNDGT' + line[i:])   # Not punctiation and not digit tags


            else:   # Not capital letter -> Lower (L)
                #Lower and Not City-Name tags
                outFile.write(line[:i] + '\tL' + '\tO')    # Lower and other name tags

                #Punctuation Tags
                if line[:i] == '\'':
                    outFile.write('\tA')                        # Apostrophe tag
                elif line[:i] == '(' or line[:i] == ')':
                    outFile.write('\tP')                        # Parentheses tag
                elif hasPunctuation(line[:i]):
                    outFile.write('\tPUNC')                     # Punctuation tag
                else:
                    outFile.write('\tNPNC')                     # Not punctuation tag

                #Digit tags
                if line[:i].isdigit():
                    outFile.write('\tDGT')                      # Digit tag
                elif hasNumbers(line[:i]):
                    outFile.write('\tCDGT')                     # Contains any digit tag
                else:
                    outFile.write('\tNDGT')                     #Does not have any digit (Not digit) tag
                outFile.write(line[i:])
    outFile.write('\n')


#Harflerin büyük küçüklüğü ve noktalama -> UU, UL, UPUP, UUP, L
#Şehir, isim veya diğer     -> CITY, NAME, O
#Sadece noktalama ise       ->  PUNC, P veya A
#Sayı veya sayı içeriyor    -> DGT, CDGT, NDGT




