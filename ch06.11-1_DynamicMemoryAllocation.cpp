// ch06.11_Dynamic Memory Allocation New and Delete
// 우리가 만든 프로그램에 메모리가 할당되는 것은 세 가지 종류로 나뉜다.
// 1. static memory allocation
//    전역 변수나 static 변수와 같이 한 번 만들면 프로그램이 끝날 때까지
//    계속 메모리를 갖고 있는 것들을 의미한다.
// 2. 자동 메모리 할당
//    변수를 선언하거나 정적 배열을 선언했을 때, 블럭 밖으로 나가면 전부 사라지고
//    다시 메모리가 OS로 반환된다.
// 3. 동적 메모리 할당
//    동적 메모리 할당을 사용하는 것이 포인터와 관련지어서 가장 까다로운 분야 중 하나다.
//    사용법을 잘 알아두면 여러 가지 중요한 깨달음을 얻을 수 있다.
//    장기적으로 표준 라이브러리나 스스로 만든 라이브러리를
//    편하게 사용할 수 있기 때문에 크게 걱정할 필요는 없다.
// 이 강의에서는 기본적인 사용법을 살펴 보고
// c나 c++ 프로그램이 까다롭다고 알려진 메모리 관리 부분에 대해서 살펴 본다.
//
// 데이터를 정적 할당할 수도 있다.
// 프로그램이 점점 커지다 보면 아주 커질 수가 있다.
// 사실 프로그래머 입장에서 보면 백만 개 정도는 그리 큰 게 아니다.
// 하지만 백만 개가 되는 array[1000000], 정적 배열을 생성하려고 하고
// 디버깅을 하면 뭔가 알 수 없는 오류가 뜬다.
// 이번 강의에는 위험한 것들이 좀 많다. 

#include <iostream>
using namespace std;

int main()
{
    //int array[1000000]; // int 백 만 개면 4메가 정도밖에 안 되는데도 디버깅을 해 보면 
                          // 문제가 생긴다. 
                          // 정적으로 할당한 메모리는 stack에 들어간다. stack은 용량이 작다.
    // 동적으로 할당된 메모리는 heap에 들어간다. heap은 훨씬 크다. 
    // 이러한 이유 때문에 동적 할당을 잘 사용하는 것은 필수적이다. 
    
    // int array[1000];      // 만 정도는 문제가 안 된고 했지만
                          // Warning	C6262	Function uses '40000' bytes of stack : 
                          // exceeds / analyze : stacksize 
                          // '16384'.Consider moving some data to heap.
                          // debugger에서 이런 Warning이 뜬다.

    // 앞으로 큰 프로그램을 만드려고 한다면 동적 메모리 할당과 친숙해지는 것이 좋겠다. 
    // 지금은 이렇게 문제가 발생할 수 있다는 것만, 개념만 알아두면 된다. 
    // 사용할 때는 library에서 잘 만들어진 것을 갖다 쓰면 된다. 

    // 우리가 OS에게 int 하나 size만큼 메모리를 달라고 하는 방법은?
    // int var;          // 이렇게 하는 방법이 하나 있었다. 
                         // 또 다른 방법은, 
    // new int;          // 이렇게 하는 것이다. 
                         // 4bytes, int 사이즈에 맞춰서 OS에게서 메모리를 받아온 다음에
                         // 그 메모리 주소를 우리에게 알려준다. 
                         // 그렇게 때문에 아래와 같이 포인터로 받아야 한다. 
    int* ptr = new int;  // 그러면 OS로부터 받아온 4bytes짜리의 메모리 주소가
                         // ptr에 저장이 된다. 
                         // 그러면 우리는 이 메모리를 그대로 사용할 수 있다.
    *ptr = 7;            // 역참조 ptr에 7을 넣어줬다. 
    // 위처럼 메모리를 받아오고 de-referncing ptr에 7을 넣어주는 것은 아래와 같다. 
    // int var;
    // var = 7;
    // 그러면 간단하게 쓰면 되지, 왜 new도 쓰고 포인터도 굳이 쓰느냐?
    // 이번 강의에서는 하나만 갖고 설명을 하지만 
    // 다음 강의에서 배열 동적 할당을 하기 시작하면 앞서 언급한 배열의 크기 문제도 있고, 
    // 여러 가지 차이점이 생긴다. 장점이 많이 생긴다. 
    // 이번 강의에서는 이렇게 변수 하나 정도의 사이즈만 갖고 하지만 
    // 실전에서 사용하게 되는 것은 훨씬 큰 사이즈이므로 사용법을 잘 익혀 두어라. 

    // 포인터로 메모리 할당을 하면서 동시에 초기화를 할 수도 있다. 

    int* ptr1 = new int(7);
    int* ptr2 = new int{ 7 };

    // 실제로 값이 들어갔는지 찍어 보자. 
    cout << ptr2 << endl;       // 00BF6EC0, 주소가 나온다. 
    cout << *ptr2 << endl;      // 7

    // 그 다음 더 중요하게 배워둬야 하는 것은, 할당받은 메모리를 OS에게 돌려주는 것이다. 
    // 왜 중요하냐면, 빅데이터나 딥러닝을 돌리게 되면, 컴퓨터 한 대로 감당할 수 없는
    // 데이터량을 사용해야 한다. 메모리에 한 번에 데이터가 안 들어갈 수도 있다. 
    // 그러면 지금 일부 데이터를 가지고 작업을 하고, 그 작업이 끝난 다음에 메모리를 OS에 
    // 돌려 줬다가 다시 메모리를 받아서 데이터를 갖고 와서 써야 할 수 있다. 
    // 또 다른 경우는, 여러 프로그램들이 메모리를 다 많이 쓰고 싶다면, 
    // 메모리를 많이 요구하는 프로그램을 동시에 여러 개 돌릴 수가 없다.  
    // 그러면 급한 애한테 먼저 많이 줬다가 게가 다 쓰고 나면, 급한 일이 끝나고 나면, 
    // 메모리를 회수해서 다른 프로그램에 메모리를 준다. 
    // 이렇게 왔다 갔다 하면서 쓰면, 더 효율적으로 컴퓨터를 사용할 수가 있다. 

    // os에게 메모리를 돌려 주는 방법을 살펴 보자.

    delete ptr2;    // 이렇게 하면 된다. 깔끔하게 끝난다. 
                    // os가 알아서 걷어가기 전에 먼저 반납하겠다는 것이다.

    // 오류가 생기는 경우를 살펴 보자. 
    cout << endl;
    int* ptr3 = new int{ 10 };

    cout << ptr3 << endl;               // 01157810
    cout << *ptr3 << endl;              // 10

    delete ptr3;

    cout << "After delete" << endl;
    //cout << ptr3 << endl;             // 00008123, 강좌에서는 delete 전의 주소와 동일.
    //cout << *ptr3 << endl;            // 출력이 안 된다. 강좌에서는 쓰레기 값이 출력됨.
                                        // 이것이 실행돼 있으면 이후 라인은 실행되지 않아서
                                        // 주석 처리해 놓았다. 
          // ptr3는 경고가 뜬다. Warning	C6001	Using uninitialized memory 'ptr3'.
    // 위 예제에 대한 결괏값은 강좌에서와 내 컴에서 다르다. 
    // 강좌에서는 delete ptr3 후의 ptr3 주소 값이 delete을 하기 전의 주소 값과 똑같았다. 
    // delete을 하고 난 후에도 주소 값은 그대로 있었던 것이다. 
    // 무슨 일이냐면 내가 군대를 갔는데 집이 이사를 간 후 나에게 새집 주소를 안 알려줬다. 
    // 원래 살던 집에 갔더니 우리 집이 아니라 다른 집이 돼 있더라. 이런 개념이다. 
    // 메모리를 반납을 했는데, 주소는 변수에 따로 저장되는 것이라서
    // delete 후에도 ptr3에 delete 전과 동일한 주소가 있다고 강좌에서는 설명했으나, 
    // visual studio 2019에서는 delete 후에는 주소도 달라졌고, *ptr3도 출력이 안 된다. 
    // Atom에서 실행해 봤더니, 다음과 같이 강좌의 설명과 동일한 결괏값이 출력됐다. 
    /*0x1051998         <- delete 전의 ptr3 주소
      10
      After delete
      0x1051998         <- delete 후의 ptr3 주소
      17136528          <- *ptr3에 뭔지 모를 알 수 없는 값이 들어가 있다. 
    */
    // 위에서 본 마와 같이 delete 후 나타나는 문제가 가장 큰 문제이다. 
    // visual studio 2019에서는 해결해 준 듯하다. 
    // 뒤에서 스마트 포인터를 사용하면 이런 것을 자동으로 해 준다. 
    // 또 대부분의 경우 클래스를 직접 만들어서 자동으로 처리하도록 한다. 
    // 그럼에도 불구하고 위의 현상을 설명한 이유는 고급 프로그래밍을 하게 되면,  
    // 이러한 개념을 알고 있어야 한다. 
    // 이것을 방지하는 방식이 몇 가지 있다. 
    cout << endl;
    int* ptr4 = new int{ 15 };

    cout << ptr4 << endl;        // 01157810
    cout << *ptr4 << endl;       // 10

    delete ptr4;
    ptr4 = nullptr;              // delete 후에 ptr4에 0, NULL 혹은 nullptr을 넣어 준다.
                       // nullptr는 이 포인터에는 쓸모 있는 주소가 없다는 것을 나타낸다. 

    cout << "After delete" << endl;
    if (ptr4 != nullptr)         // ptr4가 의미가 있을 때만 de-referencing을 하라.
    {                            // if (ptr4) 이렇게 짧게 써도 된다. 
        cout << ptr4 << endl;    // c++ 프로그래머들은 기계적으로 이렇게 짠다. 
        cout << *ptr4 << endl;   // 하지만 다음 세대 프로그래머들은 스마트 포인터를 쓰면 됨.
    }
    else
    {
        cout << "Could not allocate memory" << endl;    // 친절하게 이렇게 써 줘도 된다.
    }
    /*007B6E30                   // ptr4 
    15                           // *ptr4
    After delete                 // after delete 이후 아무 값도 출력되지 않는다. 
    Could not allocate memory    // else를 넣어 주면 이렇게 확인이 된다. 
    */
    
    // 가끔 메모리를 할당받으려는데 할당받지 못할 때가 있다. 
    // 다른 프로그램이 메모리를 다 쓰고 있어서 
    // 지금 사용할 프로그램이 메모리를 쓸 수 없는 경우가 있다. 
    // 그럴 때 프로그램이 그냥 죽어 버리게 짜는 방법이 하나 있고,
    // 어떤 경우에도 프로그램이 죽지 않고 살아 있다가 다른 프로그램이 메모리를 다 쓸 때까지
    // 기다렸다가 다시 메모리를 할당받는 시나리오도 생각할 수 있다. 
    // 그럴 때 new가 에러를 일으켜도 어떻게든 버텨야 한다. 
    // 다음과 같이 (std::nothrow)를 넘어 두면 된면 오류를 발생시키지 않고 그냥 쭉 진행한다.
    // 이건 예외 처리에서 다시 자세하게 다룰 것이다. 
    // 일단을 (std::nothrow)을 쓰면 오류를 발생시키지 않고 밀어부치더라 이렇게 알아 두라. 
    // 다음과 같이 if도 써 주면 더 안전하게 쓸 수 있다. 
    cout << endl;
    int* ptr5 = new (std::nothrow) int{ 20 };   // 오류를 발생시키지 말고 밀어부쳐라.

    if (ptr5)
    {
        cout << ptr5 << endl;       // 01157810, ptr4와 같은 메모리 주소 사용. 
                                    // ptr4 메모리는 반납됨.
        cout << *ptr5 << endl;      // 20
    }
    else
    {
        cout << "Could not allocate memory" << endl;    // 친절하게 이렇게 써 줘도 된다.
    }
    // 만약 new가 실패하면 nothrow에 의해 ptr5는 nullptr이 된다고 한다. 

    // 흔히 할 수 있는 실수는 무엇이 있을까?

    /*
    int* ptr5 = new (std::nothrow) int{ 25 };
    int* ptr6 = ptr5;

    delete ptr5;
    ptr5 = nullptr;
    */
    // 위처럼 하면 오류가 발생한다. 그럼 어떡하면 되는가?
    cout << endl; 
    int* ptr6 = new (std::nothrow) int(25);
    int* ptr7 = ptr6;

    delete ptr6;
    ptr6 = nullptr;
    ptr7 = nullptr;          // 이것도 잊지 않고 nullptr을 넣어 줘야 한다. 
                             // 그렇지 않으면 *ptr7에서 쓰레기 값이 출력된다. 
           // 예전에는 이런 것을 잊지 않고 꼼꼼하게 프로그래밍해 주도록 교육했다. 
           // 최근에는 스마트 포인터를 이용해서 프로그래머가 덜 걱정스럽게 코딩할 수 있도록
           // C++ 언어가 진화하고 있다. 다른 언어도 이런 안정 장치가 들어 있다. 
           // 단점은 위와 같이 짜는 것보다는 조금이라도 더 느려지게 된다. 

    //cout << *ptr7 << endl;   // 출력이 안 되고 이후 라인은 실행이 되지 않는다.  

    // 메모리 누수라는 무시무시한 것에 대해 알아 보자. 
    // memory leak
    // 메모리를 계속 만들기만 하는 것이다. 쓰지는 않고 OS로부터 계속 메모리를 받아 와서 
    // 어딘가에 갖다 놓는데 어디에 있는지 알 수도 없다. 
    cout << "memory leak" << endl;

    //while (true)
    //{
    //    int* ptr7 = new int;      // 포인터 변수가 사라진다. 
    //    cout << ptr7 << endl;     // 그러므로 알 수 없는 주소들이 계속 출력된다.
    //    delete ptr7;              // delete을 해 주면 메모리 누수가 생기지 않는다.
    //}
    // delete을 안 해 주면,
    // 지나가는 사람한테 전화 번호 쪽지를 받았는데 그냥 사라져 버리는 것과 같다. 
    // 이 지나가는 사람을 다시 만나기 전에는 전화 번호를 알 수가 없다. 
    // 컴퓨터 메모리를 다시 만날 일은 없다. 
    // 만나더라도 그 메모리가 이 메모리였는지 알 길이 없다. 
    // 그래서 int* ptr7 = new int; 와 같이 짜는 건 말도 안 되는 짓이다. 
    // 하지만 이런 실수를 프로그래머들이 많이 한다. 
    // 동적 메모리 할당 할 때 지우는 것을 깜박하면 문제가 생긴다. 

    // 이 문제를 파악하는 방법이 두 가지가 있다. 
    // new int 메모리에 할당받은 데이터가 클 경우에는, 
    // windows task manager를 띄우고 메모리 사용량을 본다. 
    // Memory 사용량이 쭉 올라가면 메모리가 세고 있는 것이다. 
    // 그 다음 방법은,
    // debugging 창을 띄우면, Diagnostics session이 쭉 올라가는 것을 볼 수 있다.
    // 1, 2, 3, 4, 5mb 계속 증가한다. <- 굉장히 위험하다. 
    // 이번에는 위 while문 안에 delete ptr7; 을 넣어 주고 디버거를 띄워 봐라.
    // debugging 창을 띄우면, 942kb에서 더 이상 증가하지 않는다. 메로리가 새고 있지 않다.
    // 메모리를 받았다가 돌려주고 받았다가 돌려주고를 반복한다. 

    // new와 delete을 사용하면 받았다가 돌려줬다 하므로 프로그램이 느려진다. 
    // 가능하면 new와 delete을 적게 사용하는 것이 좋다. 
    // 새로 나온 언어들 중 new와 delete을 사용 안 하는 언어들은 new와 delete이 
    // 언제 사용되는지 알 길이 없다. 그래서 느려질 수밖에 없다. 
    // C++를 쓰면 new와 delete을 직접 관리할 수 있으므로 최적화할 때 아주 좋다. 
    // 대신에 프로그래밍이 좀 어렵고 실수할 가능성이 많다. 
    // 최근에 그를 보완하는 방법이 많이 나오고 있다. 뒷 부분에서 다룬다. 

    // 동적 메모리 할당, new와 delete의 사용법에 대해서 변수 하나를 가지고 살펴 봤다. 
    // 기본적으로 stack을 사용하기 때문에, 
    // 동적 메모리 할당을 써야지만 heap을 사용해서 메모리를 크게 받을 수 있다. 
    // 메모리가 세는지 확인하는 방법도 살펴 봤다. delete을 잘 안 해주면 메모리가 센다. 
    // 이 부분은 반복해서 좋아하는 프로그램을 만들어 보면서 익히는 것이 가장 좋다. 
    // 다음 시간에 동적 메모리 할당으로 사이즈가 더 큰 배열을 어떻게 다루는지 살펴 보겠다. 
     
    return 0;
} 
