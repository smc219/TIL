# isogram

## 난이도
하

## 고민할 부분
어떻게 해야 C 스타일이 아니라 Pythonic하게 코드를 짤 수 있는가?
줄 수를 어떻게 줄일 수 있을까?

## My code

```{.python}
def is_isogram(string):
    d = dict()
    string = string.lower()
    for c in string:
        if c in d.keys():
            return False;
        else:
            d[c] = 1;
    return True
        
    #your code here
```

결국 줄이지는 못했다.

## Best Practice
```{.python}
def is_isogram(string):
    return len(string) == len(set(string.lower()))
```

굉장히 인상깊었는데, 결국 스트링을 다루는 여러가지 함수와 set같은 자료구조에 대해서 내가 아직 익숙하지 못하다는 사실을 배울 수 있었다.
len으로 길이를 재고, lower로 낮춘 것을 다시 set을 통해 중복을 제거한 len 값이 같다면 isogram임을 판별 가능.
문자열을 다루는 파이썬의 이런저런 함수에 대해서 추가적으로 배울 필요성을 느낌.