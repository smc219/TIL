# you can write to stdout for debugging purposes, e.g.
# print("this is a debug message")

def solution(S, C):
    # write your code in Python 3.6
    d = dict()
    C = C.lower()
    S = S.split(',')
    print("S : {}".format(S))
    for name in S:
        name = name.strip(' ')
        name = name.split(' ')
        name = name[0] + '.' + name[-1]
        name = name.lower()
        print(name)
        if name not in d.keys(): d[name] = 1
        else: d[name] += 1
    for k in d.keys():
        print(k)
    pass
