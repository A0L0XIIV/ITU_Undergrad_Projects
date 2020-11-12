def RabinKarpSearch(Text, Pattern, d, q): #d-> number of characters in input alphabet(256), q-> prime number
    m = len(Pattern)
    n = len(Text)
    p = 0   # hash value for pattern
    t = 0   # hash value for txt
    h = pow(d, m-1) % q
    results = []

    # Preprocessing - Calculate the hash value of pattern and first window of text
    for i in range(m):
        p = (d * p + ord(Pattern[i])) % q
        t = (d * t + ord(Text[i])) % q

    # Slide the pattern over text one by one
    for i in range(n-m+1):
        # Check the hash values of current window of text and
        # pattern if the hash values match then only check
        # for characters on by one
        if p == t:  #Check character by character
            found = True
            for j in range(m):
                if Text[i+j] != Pattern[j]:
                    found = False
                    break

            #Method #1 -> Prints all  one by one
            #j+=1
            ## if p == t and pat[0...M-1] = txt[i, i+1, ...i+M-1]
            #if j == M:
            #    print ("Pattern found at index " + str(i))

            #Method #2 -> Store results inside a list
            if found:
                results += [i]

        # Calculate hash value for next window of text: Remove
        # leading digit, add trailing digit
        if i < n-m:
            t = (d * (t-ord(Text[i])*h) + ord(Text[i+m])) % q
            # We might get negative values of t, converting it to
            # positive -> t = (t+q)%q
            if t < 0:
                t = t+q
    #Return results list
    return results

print (RabinKarpSearch ("3141592653589793", "26", 257, 11))
print (RabinKarpSearch ("xxxxx", "xx", 40999999, 999999937))
text = """Rekabet Kurumunun internet sitesinde yer alan Kurul kararlarına göre, Yavaşçalar Av Spor Malzemeleri Sanayi ve Ticaret AŞ hisselerinin Sarsılmaz Mühimmat Sanayi AŞ tarafından devralınması işlemine izin verildi.

İKİ ŞİRKET DE TMSF BÜNYESİNDE
Balıkesir'de bulunan  Yavaşçalar A.Ş.'nin temeli 1956 yılında atıldı. Şirketin sahibi İsmail Yavaşça, 15 Temmuz darbe girişimi sonrası gözaltına alındı. 6 ay kadar tutuklu kalan Yavaşça, adli kontrol şartı ile serbest bırakıldı. Yavaşça ailesinin  iki şirketi için de kayyum atanması kararı verildi. Hali hazırda Yavaşçalar Av Spor Malzemeleri San. ve Tic. A.Ş ile Yavaşçalar Av Fişek Tic. ve San. A.Ş TMSF bünyesinde bulunuyor.

Konuya yakın bir kaynak, ilgili Kanun Hükmünde Kararname'nin, TMSF bünyesindeki şirketlerin satışına olanak verdiğini aktardı.

TEMELİ 137 YIL ÖNCE ATILDI 

Temeli 1880'de atılan Sarsılmaz ise, sitesinde yer alan bilgiye göre TSK ve Emniyet Genel Müdürlüğü'nün tek özel tedarikçisi konumunda.

TAV İÇİN DE ONAY ÇIKTI
Rekabet Kurulu ayrıca, TAV Havalimanları Holding AŞ'nin Akfen Holding AŞ elinde bulunan belli orandaki hissesinin, Tank ÖWA Alph GmbH unvanlı iştiraki aracılığıyla Aeroports de Paris SA tarafından devralınması işlemine onay verildi Rekabet Kurulu, TAV Havalimanları  Holding AŞ'nin Akfen Holding AŞ elinde bulunan belli orandaki hissesinin, Tank ÖWA Alpha GmbH unvanlı iştiraki aracılığıyla Aeroports de Paris SA tarafından devralınması işlemine onay verdi.

Kurul, IDG Capital Partners'a ait olan LEDVANCE GmbH hisselerinin MLS Co. Ltd. tarafından devralınmasıyla Cummins Inc, Eaton

Corporation plc. ve bunların bağlı şirketleri tarafından Eaton Cummins Automated Transmission Technologies LLC ve Eaton Cummins Automated Transmission Technologies GmbH adında iki ortak girişim kurulması işlemlerine izin verdi.

 
TAV Havalimanları Holding AŞ'nin Akfen Holding AŞ elinde bulunan belli orandaki hissesinin, Tank ÖWA Alpha GmbH unvanlı iştiraki aracılığıyla Aeroports de Paris SA tarafından devralınması işlemi onaylandı."""
print (RabinKarpSearch (text, "Akfen Holding A.Ş.", 5000, 3))

