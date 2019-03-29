# coding=utf8
# the above tag defines encoding for this document and is for Python 2.x compatibility
# Note: for Python 2.7 compatibility, use ur"" to prefix the regex and u"" to prefix the test string and substitution.

import io
import re
import string
import jsonlines

inFileName = input("Input file: ")
cityFileName = 'sehir_isimleri.txt'
nameFileName = 'kisi_isimleri.txt'
outFileName = input("Output file: ")

regex = r"(.\.)+|(\d+.\d+.\d+)|(‘‘)|[\"\-'‘.,;%&!?()]|(\w+)"

#inFile = io.open(inFileName, 'r', encoding='utf-8')
#lines = inFile.read().splitlines()

news = []

#JSON list dosyasını okuyup içerisindeki şirket isimlerini companyNamesList listesine kaydetme
with jsonlines.open(inFileName) as reader:
    for obj in reader:
        #print(obj['haber'])
        news.append(obj['haber'])

outFile = io.open(outFileName, 'w', encoding='utf-8')

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

#CoNLL format
for ln in news:
    matches = re.finditer(regex, ln, re.MULTILINE | re.IGNORECASE)
    for matchNum, match in enumerate(matches):
        matchNum = matchNum + 1
        match = match.group()

        #Adding features
        isCity = False
        isName = False

        if match[0].isupper():  # Is capital letter
            #Upper - Lower tags
            outFile.write(match + '\tU')

            numOfU = 1
            for j in range (1, len(match)):
                if match[j].islower():
                    outFile.write('L')
                    break
                elif match[j].isupper():
                    if numOfU >= 2:
                        break
                    outFile.write('U')
                    numOfU += 1
                elif hasPunctuation(match[j]):
                    outFile.write('P')
                else:
                    break
            # UL -> Upper lower, exp: Bursa
            # UU -> Upper upper, exp: BURSA
            # UPU -> Upper Punc Upper, exp: A.Ş
            # UUP -> Upper Upper Punc, exp: AŞ.
            # UPUP -> Upper Punc Upper Punc, exp: A.Ş.

            """
            if match[1].islower():
                outFile.write('L')                          # UL -> Upper lower, exp: Bursa
            elif match[1].isupper():
                outFile.write('U')                          # UU -> Upper upper, exp: BURSA
                if len(match) > 2 and hasPunctuation(match[2]):
                    outFile.write('P')                      # UUP -> Upper upper Punc, exp: AŞ.
            elif hasPunctuation(match[1]) and len(match) > 2 and match[2].isupper():
                outFile.write('PU')                         # UPU -> Upper Punc Upper, exp: A.Ş
                if len(match) > 3 and hasPunctuation(match[3]):
                    outFile.write('P')                      # UPUP -> Upper Punc Upper Punc, exp: A.Ş.
            """

                    #City - Name tags
            for city in cities:
                if match.translate(tr_map).upper() == city.translate(tr_map).upper():
                    outFile.write('\tCITY')                 # City name tag
                    isCity = True
                    break
            if not isCity:
                for name in names:
                    if match.translate(tr_map).upper() == name.translate(tr_map).upper():
                        outFile.write('\tNAME')             # Or person name tag
                        isName = True
                        break
            if not isCity and not isName:
                outFile.write('\tO')                        # Or other name tag

            #Punctuation and Digit tags
            outFile.write('\tNPNC' + '\tNDGT' + '\n')   # Not punctiation and not digit tags


        else:   # Not capital letter -> Lower (L)
            #Lower and Not City-Name tags
            outFile.write(match + '\tL' + '\tO')    # Lower and other name tags

            #Punctuation Tags
            if match == '\'':
                outFile.write('\tA')                        # Apostrophe tag
            elif match == '(' or match == ')':
                outFile.write('\tP')                        # Parentheses tag
            elif hasPunctuation(match):
                outFile.write('\tPUNC')                     # Punctuation tag
            else:
                outFile.write('\tNPNC')                     # Not punctuation tag

            #Digit tags
            if match.isdigit():
                outFile.write('\tDGT')                      # Digit tag
            elif hasNumbers(match):
                outFile.write('\tCDGT')                     # Contains any digit tag
            else:
                outFile.write('\tNDGT')                     #Does not have any digit (Not digit) tag
            outFile.write('\n')

    outFile.write('\n')


#Harflerin büyük küçüklüğü ve noktalama -> UU, UL, UPUP, UUP, L
#Şehir, isim veya diğer     -> CITY, NAME, O
#Sadece noktalama ise       ->  PUNC, P veya A
#Sayı veya sayı içeriyor    -> DGT, CDGT, NDGT



