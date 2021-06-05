# Tribonacci Sequence

## 난이도
하

## 고민할 부분
어떻게 해야 N<=3 이하의 개수와 초과하는 개수의 것을 깔끔한 형태로 짤 수 있을까?

## My Solution
```{.cpp}
std::vector<int> tribonacci(std::vector<int> signature, int n)
{
    std::vector<int> result;
    if (n <= 3) {
      for (int i = 0; i < n; ++i) result.push_back(signature[i]);
      return result;
    }
  
    result = signature;
    for (int i = 3; i < n; ++i) {
      result.push_back(result[i-3] + result[i-2] + result[i-1]);
    }
  
    return result;
}
```

## Best Practice

```{.cpp}
std::vector<int> tribonacci(std::vector<int> signature, int n)
{
    if(n<3){
       signature.resize(n);
    }
    for(unsigned int i = 3; i<n;i++){
      signature.push_back(signature[i-3]+signature[i-2]+signature[i-1]);
    }
    return signature;
}
```

차이점은 크게, 1) resize 함수를 사용해서 반복문을 쓴 부분을 한줄로 단순화시켰다는 것 2) result를 따로 선언하지 않고, signature를 그대로 사용했다는 점.
