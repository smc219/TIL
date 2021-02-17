## ECF(Exceptional Control Flow)

코드가 Instruction 순차적으로 진행되면 좋겠지만, 도중에 갑작스런 변화를 처리해야할 때가 발생한다. 

예를 들자면

1. Hardware Timer가 꺼지는 경우
2. 패킷들이 네트워크 어댑터를 통해서 도착하고, 이것들이 반드시 메모리에 저장되어야 하는 경우
3. 프로그램이 디스크에 데이터를 요청하는 경우
4. 부모 프로세스가 자식 프로세스가 terminated 되는 것을 알아야하는 경우

이렇게 급작스런 변화(abrupt change)가 발생하는 경우 이를 다루는 방식이 바로 ECF

![스크린샷 2021-02-11 오후 12.54.14](/Users/seogminchang/Library/Application Support/typora-user-images/스크린샷 2021-02-11 오후 12.54.14.png)

Exception은 프로세스의 상태에 어떤 abrubt한 변화가 발생하는 것이라고 할 수 있다.

이렇게 abrupt change가 발생하면 state의 상태가 signal과 bits를 이용해서 인코딩되고, 이런 상태의 변화를 이벤트라고 한다. 

이렇게 이벤트가 발생하면 프로세스는 Procedure Call을 통해서 Exception Handler에 Exception Table을 Call한다.  이렇게 콜 한후에 Exception Processing이 끝나면 세가지 경우가 발생할 수 있다.

1. 원래 인스트럭션에 control을 돌려준다.
2. 원래 인스트럭션의 다음 인스트럭션에 control을 돌려준다.
3. 해당 program을 abort 시킨다.

## Exception Handling 과정

1. 부팅 시 Exception Table 할당, 초기화 
2. 이벤트 발생 시 해당하는 이벤트 entry K 결정
3. 해당 K에 해당하는 테이블을 통해서 trigerring한다
4. Exception Handler가 작동한다. 



### Exception의 종류

1. Interrupts
   I/O Device로부터 오는 Signal
2. Trap
   Intentional Exceptions. exit, fork, execve, read 따위를 User program이 Kernel에게 요청하는데, 이때 유저 프로그램은 syscall을 하고, trap이 발생한다. 
3. Fault
   error condition을 수정해야하는 경우 발생. 대표적인게 가상 메모리 상에서 원하는 physical memory를 찾지 못할때 발생하며, 이때 disk에 다시 접근한다.
   만약 error condition을 교정하면 현재 인스트럭션을 재수행, 아니면 abort
4. Abort
   recoverable하지 못한 에러. 어플리케이션 프로그램을 종료한다.



 