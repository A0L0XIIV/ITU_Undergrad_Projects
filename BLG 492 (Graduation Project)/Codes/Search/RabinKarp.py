# Following program is the python implementation of
# Rabin Karp Algorithm given in CLRS book

# d is the number of characters in input alphabet
d = 256

# pat -> pattern
# txt -> text
# q -> A prime number

def search(pat, txt, q):
	M = len(pat)
	N = len(txt)
	i = 0
	j = 0
	p = 0 # hash value for pattern
	t = 0 # hash value for txt
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
				print ("Pattern found at index " + str(i) )

		# Calculate hash value for next window of text: Remove
		# leading digit, add trailing digit
		if i < N-M:
			t = (d*(t-ord(txt[i])*h) + ord(txt[i+M]))%q

			# We might get negative values of t, converting it to
			# positive
			if t < 0:
				t = t+q

# Driver program to test the above function
txt = "05.01.2018 tarihinde KAP'ta a��kland��� �zere �irketimiz 05.01.2018 tarih 2018/01 nolu Y�netim Kurulu karar� ile; �irketimiz ile ayn� ortakl�k yap�s�na sahip olan Akfen M�hendislik A.�.'nin 6102 Say�l� T�rk Ticaret Kanunu (\"TTK\")'nun 136 ve devam� maddeleri h�k�mleri ile 5520 say�l� Kurumlar Vergisi Kanunu  (\"KVK\")'nun 19 ve 20. maddeleri h�k�mleri dairesinde tasfiyesiz ve bir b�t�n (k�l) halinde �irketimize kat�lmas� suretiyle birle�mesine ve birle�me i�leminin TTK'nun 155 ve devam� h�k�mleri uyar�nca \"Sermaye �irketlerinin kolayla�t�r�lm�� �ekilde birle�mesi\" d�zenlemelerine uygun olarak yap�lmas�na karar vermi�tir. �irketimiz ile Akfen M�hendislik A.�.'nin birle�me i�lemi TTK ve KVK h�k�mlerine uygun olarak 28.02.2018 tarihinde i�lemin tescili ile tamamlanm��t�r."
pat = "Akfen M�hendislik A.�."
q = 101 # A prime number
search(pat,txt,q)

# This code is contributed by Bhavya Jain
