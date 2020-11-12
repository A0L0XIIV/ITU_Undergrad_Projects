# coding=utf8

import io
import re

inFileName = 'etiketlenenKapAciklamalari_CoNLL_66000_v2.txt'
outFileName = 'uniquewords.txt'

regex = r"(.\.)+|(\d+.\d+.\d+)|(‘‘)|[\"\-'‘.,;%&!?()]|(\w+)"


#def number_check(string):
    #return re.search('\d', string)
# if you compile the regex string first, it's even faster
RE_D = re.compile('\d')
def number_check(string):
    return RE_D.search(string)

def punc_check(string):
    return re.match(r'^\w+$', string)


# translation for Turksih 'İ', usage:
# string.translate(tr_map).upper()
tr_map = {
    ord(u'ı'): u'I',
    ord(u'i'): u'İ',
    }


inFile = io.open(inFileName, 'r', encoding='utf-8')
outFile = io.open(outFileName, 'w', encoding='utf-8')
lines = inFile.read().splitlines()


word_list = []
for item in lines:

    if len(item) > 3 and len(item.split('\t')) == 2:   #3'ten küçükler noktalama işaretleri, sayı ya da tek harf (örn. kesilmiş ekler)
        words, tags = item.split('\t')
        if tags == 'O' and not number_check(words): #Sayıları ve tarihleri eleme
            #print(words)
            word_list.append(words.translate(tr_map).upper()) #Hepsini küçük harf olarak sakla
    #elif len(item.split('\t')) != 2: #Test amaçlıydı
        #print(item)
print("All words size: ", len(word_list))


#Set kullanarak unique word bulma -> büyük küçük harf ayrımı kendisi yapmıyor
unique_words = set(word_list)
print("Unique words size: ", len(unique_words)) #SIZE: 4135
for word in unique_words:
    #print(word)
    outFile.write(word + '\n')


#Hepsini küçük harfe çevirip kontrol etme
"""
unique_words = []
for word in word_list:
    word = word.translate(tr_map).lower()
    if word not in unique_words:
        unique_words.append(word)
        outFile.write(word + '\n')
print("Unique words size: ", len(unique_words))
"""


