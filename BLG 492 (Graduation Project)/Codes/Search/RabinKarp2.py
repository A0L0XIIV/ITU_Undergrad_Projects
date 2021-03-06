#!/usr/bin/env python
# -*- coding: utf-8 -*-

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
            t = (d * (t-ord(Text[i])*h) + ord(Text[i+M])) % q
            # We might get negative values of t, converting it to
            # positive -> t = (t+q)%q
            if t < 0:
                t = t+q
    #Return results list
    return results

print (RabinKarpSearch ("3141592653589793", "26", 257, 11))
print (RabinKarpSearch ("xxxxx", "xx", 40999999, 999999937))