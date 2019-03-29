# -*- coding: utf-8 -*-

"""Auxiliary procedure for printing each item of row in columns in binary form
"""

"""
def _printTable(t, size):
    out = ""
    for i in range(len(t)):
        binaryForm = bin(t[i])
        binaryForm = binaryForm[2:]
        binaryForm = binaryForm.zfill(size)
        out += binaryForm + ", "
    out = out[: -2]
    print (out)
"""

"""Bitap (Shift-Or) fuzzy searching algorithm with Wu-Manber modifications.
http://habrahabr.ru/post/114997/
http://habrahabr.ru/post/132128/
http://ru.wikipedia.org/wiki/Двоичный_алгоритм_поиска_подстроки
Search needle(pattern) in haystack(real word from text) with maximum alterations = maxErrors.
If maxErrors equal 0 - execute precise searching only.
Return approximately place of needle in haystack and number of alterations.
If needle can't find with maxErrors alterations, return tuple of empty string and -1.
"""

def bitapSearch(haystack, needle, maxErrors):
    haystackLen = len(haystack)
    needleLen = len(needle)

    """Genarating mask for each letter in haystack.
    This mask shows presence letter in needle.
    """

    def _generateAlphabet(needle, haystack):
        alphabet = {}
        for letter in haystack:
            if letter not in alphabet:
                letterPositionInNeedle = 0
                for symbol in needle:
                    letterPositionInNeedle = letterPositionInNeedle << 1
                    letterPositionInNeedle |= int(letter != symbol)
                alphabet[letter] = letterPositionInNeedle
        return alphabet

    alphabet = _generateAlphabet(needle, haystack)

    table = []  # first index - over k (errors count, numeration starts from 1), second - over columns (letters of haystack)
    emptyColumn = (2 << (needleLen - 1)) - 1

    #   Generate underground level of table
    underground = []
    [underground.append(emptyColumn) for i in range(haystackLen + 1)]
    table.append(underground)
    #(BK)_printTable(table[0], needleLen)

    #(BK)
    result = []#("", -1)

    #   Execute precise matching
    k = 1
    table.append([emptyColumn])
    for columnNum in range(1, haystackLen + 1):
        prevColumn = (table[k][columnNum - 1]) >> 1
        letterPattern = alphabet[haystack[columnNum - 1]]
        curColumn = prevColumn | letterPattern
        table[k].append(curColumn)
        if (curColumn & 0x1) == 0:
            place = haystack[columnNum - needleLen: columnNum]
            #return (place, k - 1)
            result.append((place, k-1))
    #(BK)_printTable(table[k], needleLen)

    #   Execute fuzzy searching with calculation Levenshtein distance
    for k in range(2, maxErrors + 2):
        #(BK)print ("Errors =", k - 1)
        table.append([emptyColumn])

        for columnNum in range(1, haystackLen + 1):
            prevColumn = (table[k][columnNum - 1]) >> 1
            letterPattern = alphabet[haystack[columnNum - 1]]
            curColumn = prevColumn | letterPattern

            insertColumn = curColumn & (table[k - 1][columnNum - 1])
            deleteColumn = curColumn & (table[k - 1][columnNum] >> 1)
            replaceColumn = curColumn & (table[k - 1][columnNum - 1] >> 1)
            resColumn = insertColumn & deleteColumn & replaceColumn

            table[k].append(resColumn)
            if (resColumn & 0x1) == 0:
                startPos = max(0, columnNum - needleLen - 1)  # taking in account Replace operation
                endPos = min(columnNum + 1, haystackLen)  # taking in account Replace operation
                place = haystack[startPos: endPos]
                #return (place, k - 1)
                result.append((place, k - 1))

        #(BK)_printTable(table[k], needleLen)

    #(BK)
    if(len(result) == 0):
        result.append(("", -1))
    return result


"""Highlight letters in fullWord, which concur with letters in pattern with same order.
wordPart - it's a part of fullWord, where matching with pattern letters will execute.
"""

class bitapHighlighter():
    def __init__(self, fullWord, wordPart, pattern):
        self._fullWord = fullWord
        self._wordPart = wordPart
        self._pattern = pattern
        self._largestSequence = ""

    """Finding longest sequence of letters in word. Letters must have same order, as in pattern
    """

    def _nextSequence(self, fromPatternPos, fromWordPos, prevSequence):
        for patternPos in range(fromPatternPos, len(self._pattern)):
            char = self._pattern[patternPos]
            for wordPos in range(fromWordPos, len(self._wordPart)):
                if char == self._wordPart[wordPos]:
                    sequence = prevSequence + char
                    self._nextSequence(patternPos + 1, wordPos + 1, sequence)
        if len(self._largestSequence) < len(prevSequence):
            self._largestSequence = prevSequence

    """Divide fullWord on parts: head, place(wordPart) and tail.
    Select each letter of wordPart, which present in _largestSequence with <b></b> tags
    Return gathered parts in one highlighted full word
    """

    def _gatherFullWord(self):
        placePos = self._fullWord.find(self._wordPart)
        head = self._fullWord[0: placePos]
        tail = self._fullWord[placePos + len(self._wordPart):]
        highlightedPlace = ""
        for symbol in self._wordPart:
            if symbol == self._largestSequence[0: 1]:
                highlightedPlace += "<b>" + symbol + "</b>"
                self._largestSequence = self._largestSequence[1:]
            else:
                highlightedPlace += symbol
        return "\n1\n" + head + highlightedPlace + tail + "\n\n2\n\n" + self._gatherFullWord2()#head + highlightedPlace + tail

    def _gatherFullWord2(self):
        placePos = self._fullWord.find(self._wordPart)
        head = self._fullWord[0: placePos]
        tail = self._fullWord[placePos + len(self._wordPart):]
        highlightedPlace = self._wordPart
        return head + "<tag>" + highlightedPlace + "</tag>" + tail

    """Run highlighting and return highlited word.
    """

    def getHighlightedWord(self):
        self._nextSequence(0, 0, "")
        return self._gatherFullWord()

#haystack = input("Haystack:")
haystack = """05.01.2018 tarihinde KAP'ta açıklandığı üzere Şirketimiz 05.01.2018 tarih 2018/01 nolu Yönetim Kurulu kararı ile; Şirketimiz ile aynı ortaklık yapısına sahip olan Akfen Mühendislik A.Ş.'nin 6102 Sayılı Türk Ticaret Kanunu ("TTK")'nun 136 ve devamı maddeleri hükümleri ile 5520 sayılı Kurumlar Vergisi Kanunu  ("KVK")'nun 19 ve 20. maddeleri hükümleri dairesinde tasfiyesiz ve bir bütün (kül) halinde Şirketimize katılması suretiyle birleşmesine ve birleşme işleminin TTK'nun 155 ve devamı hükümleri uyarınca "Sermaye şirketlerinin kolaylaştırılmış şekilde birleşmesi" düzenlemelerine uygun olarak yapılmasına karar vermiştir. Şirketimiz ile Akfen Mühendislik A.Ş.'nin birleşme işlemi TTK ve KVK hükümlerine uygun olarak 28.02.2018 tarihinde işlemin tescili ile tamamlanmıştır."""
needle = input("Needle:")
errorsCount = input("Error:")
#print ("haystack = " + haystack + ". needle = " + needle + ". errorsCount = " + errorsCount)
"""
#   Display letters of haystack in columns
out = ""
out = out.ljust(len(needle) + 2)
for i in range(len(haystack)):
    out += haystack[i].ljust(len(needle)) + "  "
out = out[: -2]
print (out)
"""
#   Start bitap searching
#(needlePlace, errors) = bitapSearch(haystack, needle, int(errorsCount))
#(BK)
result = bitapSearch(haystack, needle, int(errorsCount))
preError = 0
for item in result:
    if(item[1] != preError):
        preError = item[1]
        print ("Result of Bitap searching:", item[0], item[1])
        print (bitapHighlighter(haystack, item[0], needle).getHighlightedWord())

#print ("Result of Bitap searching:", needlePlace, errors)
#print (bitapHighlighter(haystack, needlePlace, needle).getHighlightedWord())