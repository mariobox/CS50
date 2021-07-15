from nltk.tokenize import sent_tokenize


def listAppend(a, b, c):
    """Iterate over two files (strings) and place similar parts in a new list """
    c = []
    for item in a:
        if item in b:
            if item not in c:
                c.append(item)
    return c


def buildSubstringList(x, n):
    """Build a list of substrings of n length in a file (string) called x"""
    c = []
    for i in range(len(x)):
        if len(x[i:(i + n)]) == n:
            c.append(x[i:(i + n)])
    return c


def lines(a, b):
    """ Return lines in both a and b"""
    list1 = a.split('\n')
    list2 = b.split('\n')
    list3 = []

    return listAppend(list1, list2, list3)


def sentences(a, b):
    """Return sentences in both a and b"""

    stlist1 = sent_tokenize(a)
    stlist2 = sent_tokenize(b)
    stlist3 = []

    return listAppend(stlist1, stlist2, stlist3)


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    nc = []

    na = buildSubstringList(a, n)

    nb = buildSubstringList(b, n)

    return listAppend(na, nb, nc)
