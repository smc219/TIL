## 
Javascript는 웹 사이트에서도 사용하지만, 인터랙티브한 것을 만들때도 사용됨
-> 예시로 나온 것은 게임, 앱 등

## ECMAScript 
일종의 규정 같은 것. specification. 브라우저가 어떻게 행동하고 에러를 하는지. 일종의 행동 메뉴얼인 것.
ES5, ES6는 이런 것들의 버전을 이야기하는 것.

브라우저는 이런 ECMA를 받아들이면 그대로 하려고 하는 것. 



## 바닐라 자바스크립트

임시방편이나 모던하지 않은 모습을 보임.

색감에 대한 센스와 포토샵을 바닐라 자바스크립트와 리액트 등의 프레임워크에 비유.

결국 바닐라 자바스크립트의 변형으로 다른 것들이 나온 것이기 때문에 바닐라 자바스크립트를 이해하는 것이 다른 것을 이해하는데도 유용하다는 논리

## 기본

자바스크립트를 어떻게 추가할 것인가?

```html
<DOCTYPE html>
<html>
	<head>
		<title>Title</title>
		<link rel ="stylesheet" href="index.css" />
		
	</head>
	<body>
    <h1>
      Test
    </h1>
    <script src="index.js"> </script>
	</body>
</html>
```

위에서 볼 수 있는 것처럼 일단 js는 기본적으로 body 맨 아랫줄에 넣어줄 것.

기본적으로 브라우저에는 바닐라 자바스크립트는 설치되어 있다. 다른 언어에 비하면 장점이라 할 수 있다고...

## 변수

create -> initialize -> use

기본적으로는 위의 삼단구조.

자바스크립트에서 변수를 사용하는 방법은 아래와 같다.

```javascript
let a = 100;
let b = a - 5;
const c = 10;
console.log(b);
```

const -> 상수를 뜻함.

const로 선언된 값이 바뀌면 TypeError가 발생한다.

var도 사용할 수 있지만 강의에서는 let을 권장

왜일까? 

통상적으로 let과 var 둘 다 재할당이 가능하다는 공통점을 가지고 있지만, 차이점 역시 존재한다.

1. var의 경우에는 변수 재선언이 가능하고 / let의 경우에는 불가능하다

   이는 블록 외부에서 선언된 var가 블록 내부에서 재선언되어도 -> 외부에서도 재선언된 값으로 나온다.

2. let의 경우에는 호이스팅(변수 선언이 뒤에 있더라도, 마치 맨 앞에 선언된 것처럼 처리해줌)이 불가능하지만, var의 경우에는 불가능하다

변수 선언은 가능하면 const로 할 것.

## Data Type

- string
  `const what = "Nicolas"`
- Boolean
  `const tf = true;` 와 같이 씀. 반대는 false. 똑같이 1, 0이다.
- Float
  `const what = 55.1;`
- 



