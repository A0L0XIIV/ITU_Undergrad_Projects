def bitap_fuzzy_bitwise_search(text, pattern, k):
    result = None
    m = len(pattern)
    R = (k+1) * [0]
    pattern_mask = 128 * [0]

    if m == 0:
        return text
    if (m > 31):
        return "The pattern is too long!"

    #R = (unsigned long *)malloc((k + 1) * sizeof * R)
    for i in range (0,k):
        R[i] = ~1

    for i in range (0, 127):
        pattern_mask[i] = ~0

    for i in range (0,m):
        pattern_mask[i] &= ~(1 << i)#pattern_mask[pattern[i]] &= ~(1 << i)

    for i in range (0, len(text)):
        old_Rd1 = R[0]

        R[0] |= pattern_mask[i]#R[0] |= pattern_mask[text[i]]
        R[0] <<= 1

        for d in range (1,k+1):
            tmp = R[d]
            R[d] = (old_Rd1 & (R[d] | pattern_mask[i])) << 1#| pattern_mask[text[i]])) << 1
            old_Rd1 = tmp

        if (0 == (R[k] & (1 << m))):
            result = (text+i - m) + 1
        break

    return result


while (1):
    text = input("Text: ")
    if text == 'exit':
        break
    pattern = input("Pattern: ")
    if pattern == 'exit':
        break
    error = input("Error: ")
    if len(text) != 0 and len(pattern) != 0:
        result2 = bitap_fuzzy_bitwise_search(text, pattern, int(error));
        print(result2)#print("Result:" + result2)
    else:
        break
