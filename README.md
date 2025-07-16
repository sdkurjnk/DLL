# Doubly Linked List (DLL) 헤더파일 매뉴얼

이 헤더 파일은 C언어로 구현된 **이중 연결 리스트(Doubly Linked List)** 기본 구조와 함수들을 제공한다.

사용자는 이 기본 구조를 기반으로 자유롭게 확장할 수 있다.

---

## 구조체 정의

```c
struct list {
    struct list *after;   // 다음 노드를 가리키는 포인터
    struct list *before;  // 이전 노드를 가리키는 포인터
    int index;            // 인덱스
};
typedef struct list base_node;
```

이 형태를 상속하여 사용해야 한다.

---

## 함수 설명

### 1. `int init(&head);`

- 역할: 리스트의 시작 노드를 초기화한다.
- 정상적으로 작동되었다면 1을, 그렇지 않으면 0을 반환한다.
- 동작: `index`를 0으로, `before`와 `after`를 NULL로 설정한다.
- 사용 예:

```c
my_node *head = malloc(sizeof(my_node));
init((base_node **)head);
```

---

### 2. `void indexing(&head);`

- 역할: 리스트 내 모든 노드를 처음부터 순회하며 인덱스를 0부터 다시 부여한다.
- 정상적으로 작동되었다면 1을, 그렇지 않으면 0을 반환한다.
- 사용 시기: 노드가 추가되거나 삭제된 후 인덱스가 꼬였을 때 호출한다.
- 사용 예:
```c
indexing((base_node **)head);
```

---

### 3. `void append(&head, int i);`

- 역할: 현재 노드를 기준으로 새 노드를 앞(`-1`)이나 뒤(`1`)에 추가한다.
- 정상적으로 작동되었다면 1을, 그렇지 않으면 0을 반환한다.
- 동작:
  - 새 노드를 동적 할당하여 연결한다.
  - 인덱스를 자동으로 업데이트한다.
  - `head` 포인터를 새 노드로 변경한다.
- 사용 예:

```c
append(&head, 1);  // 현재 노드 뒤에 새 노드 추가
append(&head, -1); // 현재 노드 앞에 새 노드 추가
```

---

### 4. `int move(&head, int i);`

- 역할: 리스트 내에서 인덱스가 `i`인 노드로 `head` 포인터를 이동한다.
- 정상적으로 작동되었다면 1을, 그렇지 않으면 0을 반환한다.
- 반환값: 
  - `1` : 성공적으로 이동
  - `0` : 해당 인덱스 노드가 없음
- 사용 예:

```c
if (move(&head, 3)) {
    printf("인덱스 3 노드로 이동 성공\n");
} else {
    printf("해당 인덱스 노드가 없음.\n");
}
```

---

### 5. `void del(&head);`

- 역할: 현재 노드의 다음 노드(`head->after`)를 삭제한다.
- 정상적으로 작동되었다면 1을, 그렇지 않으면 0을 반환한다.
- 동작:
  - 삭제 대상 노드를 메모리 해제하고 연결을 재조정한다.
  - 이후 `indexing()` 함수를 호출해 인덱스를 재정렬한다.
- 사용 예:

```c
del(&head);  // 현재 노드 다음 노드 삭제
```

---

## 사용 예시

```c
#include <stdio.h>
#include <stdlib.h>
#include "DLL.h"

struct node
{
    struct node *after;
    struct node *before;
    int index;
    int data;
};
typedef struct node node;


int main()
{
    node *head = (node *)malloc(sizeof(node));
    init(&head);
    head->data = 0;
    
    for (int i = 1; i < 5; i++) {
        append(&head, 1);
        head->data = i;
    }

    move(&head, 0);
    for (int i = 0; i < 5; i++) {
        if (move(&head, i)) {
            printf("%d ", head->data);
        } else {
            printf("Index %d not found\n", i);
        }
    }

    return 0;
}
```

---

## 주의 사항

- 함수 호출 시 **반드시 이중 포인터 형태로 전달해야** 한다.

-사용 예:
```c
append(&head, 1);
```
- 구조체를 확장할 때는 반드시 `base_node`와 동일한 멤버 순서를 유지해야 안전한 형변환이 가능하다. 아래의 DLL.h파일의 일부 코드를 살펴보자.

```C
typedef struct my_node
{
    struct my_node *after;
    struct my_node *before;
    int index;
    int data;
} my_node;
```
구조체를 생성할 때, before, after, index 변수를 순서대로 선언한 후에 다른 변수를 새로 선언해야 한다.

---

## 함수 요약

| 함수명    | 설명                         |
| -------- | ---------------------------- |
| `init`   | 리스트 시작 노드 초기화       |
| `append` | 앞 또는 뒤에 새 노드 추가     |
| `indexing`| 리스트 인덱스 재정렬          |
| `move`   | 특정 인덱스 노드로 이동       |
| `del`    | 현재 노드 다음 노드 삭제      |
