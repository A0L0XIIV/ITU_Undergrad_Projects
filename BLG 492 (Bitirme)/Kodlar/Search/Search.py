# Following program is the python implementation of
# Rabin Karp Algorithm given in CLRS book

import jsonlines
from fuzzywuzzy import fuzz
from fuzzywuzzy import process

companyNamesList = []
data = """05.01.2018 tarihinde KAP'ta açıklandığı üzere Şirketimiz 05.01.2018 tarih 2018/01 nolu Yönetim Kurulu kararı ile; Şirketimiz ile aynı ortaklık yapısına sahip olan Akfen Mühendislik A.Ş.'nin 6102 Sayılı Türk Ticaret Kanunu ("TTK")'nun 136 ve devamı maddeleri hükümleri ile 5520 sayılı Kurumlar Vergisi Kanunu  ("KVK")'nun 19 ve 20. maddeleri hükümleri dairesinde tasfiyesiz ve bir bütün (kül) halinde Şirketimize katılması suretiyle birleşmesine ve birleşme işleminin TTK'nun 155 ve devamı hükümleri uyarınca "Sermaye şirketlerinin kolaylaştırılmış şekilde birleşmesi" düzenlemelerine uygun olarak yapılmasına karar vermiştir. Şirketimiz ile Akfen Mühendislik A.Ş.'nin birleşme işlemi TTK ve KVK hükümlerine uygun olarak 28.02.2018 tarihinde işlemin tescili ile tamamlanmıştır."""
possibleCompanies = []
possibleCompaniesRatio = []

#JSON list dosyasını okuyup içerisindeki şirket isimlerini companyNamesList listesine kaydetme
with jsonlines.open('kapSirketAdlari.jl') as reader:
    for obj in reader:
        #print(obj['isim'])
        companyNamesList.append(obj['isim'])

#fuzzywuzzy ile bütün şirket listesi ile haber ya da özet bilgiyi karşılaştırma
for item in companyNamesList:
    ratio = fuzz.token_set_ratio(data, item)
    if (ratio > 50): #50 değişebilir
        print("item:", item)
        possibleCompanies.append(item)
        possibleCompaniesRatio.append(ratio)


# d is the number of characters in input alphabet
d = 256

# pat  -> pattern
# txt  -> text
# q    -> A prime number

def search(pat, txt, q):
    M = len(pat)
    N = len(txt)
    i = 0
    j = 0
    p = 0    # hash value for pattern
    t = 0    # hash value for txt
    h = 1

    # The value of h would be "pow(d, M-1)%q"
    for i in range(M-1):
        h = (h*d)%q

    # Calculate the hash value of pattern and first window
    # of text
    for i in range(M):
        p = (d*p + ord(pat[i]))%q
        t = (d*t + ord(txt[i]))%q

    # Slide the pattern over text one by one
    for i in range(N-M+1):
        # Check the hash values of current window of text and
        # pattern if the hash values match then only check
        # for characters on by one
        if p==t:
            # Check for characters one by one
            for j in range(M):
                if txt[i+j] != pat[j]:
                    break

            j+=1
            # if p == t and pat[0...M-1] = txt[i, i+1, ...i+M-1]
            if j==M:
                print ("Pattern found at index " + str(i))

        # Calculate hash value for next window of text: Remove
        # leading digit, add trailing digit
        if i < N-M:
            t = (d*(t-ord(txt[i])*h) + ord(txt[i+M]))%q

            # We might get negative values of t, converting it to
            # positive
            if t < 0:
                t = t+q

# Driver program to test the above function
txt = "GEEKS FOR GEEKS"
pat = "GEEK"
txt = data.lower()

#R.K kontrol ederken büyük-küçük harflere öenm veriyor, bu yüzden hepsi büyük,
# hepsi küçük ve sadece ilk harfi büyük olacak şekilde deneme yapmalı!

#Hepsini küçülttüm

for i in range (0, len(possibleCompanies)):
    if(possibleCompaniesRatio[i] > 80):
        pat = possibleCompanies[i]
    else:
        fullName = str(possibleCompanies[0])
        justName = fullName.split()
        pat = justName[0]
        pat = pat.lower()
        #pat = pat.capitalize()  #Sadece ilk harfi büyük olmalı çünkü R.K arama yaparken dikkat ediyor
        print("Splited one: %s" % pat)
    print("Company Name: ", pat)
    q = 101  # A prime number
    search(pat, txt, q)


 
# This code is contributed by Bhavya Jain