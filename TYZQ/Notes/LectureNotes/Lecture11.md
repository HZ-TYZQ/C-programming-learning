# UESTC1005 · C 语言链表学习笔记

> **范围：** Lecture 11（Linked Lists 与 Big O）、Lecture 12（链表回顾、查找、分类），结合我们在对话中深入学习的二级指针操作。
>
> **说明：** `link` 定位“指向节点的指针成员”、统一插入和删除等，是我们的扩展讲解；课件原始代码可能使用 `IntNode`、`HEAD`、`node_ptr_ptr` 等不同命名，本文统一为 `Node`、`head`、`headPtr`、`link`。
>
> **本章核心：** 链表不靠节点在内存中相邻，而靠 `next` 保存的地址连接。链表的插入、删除，本质上是在**修改保存节点地址的指针变量**。

---

## 1. Node、head、next：链表是什么

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;
```

- `data`：节点的数据。实际题目可以包含多个成员，比如学号、姓名、成绩。
- `next`：指向下一个 `Node` 的**一级指针**；普通单向链表最后一个节点的 `next == NULL`。
- `Node *head`：保存首节点地址的**头指针**。空链表：`head == NULL`。
- `Node **headPtr`：保存某个 `Node *` 指针变量地址的**二级指针**，常用于从函数内部修改调用者的 `head`。

示例：

```text
head ──▶ [10 | next] ──▶ [20 | next] ──▶ [30 | NULL]
```

局部变量声明的节点和通过 `malloc` 创建的节点都可以用 `next` 连接；但 `free()` **只能用于合法、尚未释放的动态分配内存**，不能 `free()` 普通局部结构体变量。

## 2. `.`、`->`、`*`、`&`、二级指针

假设：

```c
Node *head = /* 指向第一个节点的合法地址 */;
Node **headPtr = &head;
Node **link = headPtr;
```

| 表达式 | 类型 / 作用 |
| --- | --- |
| `head` | `Node *`：首节点地址 |
| `&head` | `Node **`：变量 `head` 自身的地址 |
| `head->data` | 第一个节点的 `data` |
| `head->next` | 第一个节点的 `next`，类型 `Node *` |
| `headPtr` | `Node **`：指向调用者的头指针变量 |
| `*headPtr` | `Node *`：调用者头指针的当前值 |
| `(*headPtr)->data` | 通过二级指针访问首节点的数据 |
| `link` | `Node **`：当前“入口指针”的地址 |
| `*link` | `Node *`：当前入口指针保存的节点地址 |
| `&((*link)->next)` | 当前节点的 `next` **成员自身的地址**，类型 `Node **` |

**特别注意运算符优先级：** `(*headPtr)->data` 正确；不能把它错写为 `*headPtr->data`。为便于阅读，我们始终写完整括号。

### C 的值传递

```c
void wrongHeadChange(Node *head) {
    head = NULL;  // 只修改这个函数的局部形参
}

void correctHeadChange(Node **headPtr) {
    *headPtr = NULL;  // 修改调用者的头指针变量
}
```

调用第二个函数使用 `correctHeadChange(&head);`。注意：这个示例仅展示“修改指针变量”的差异；如果 `head` 指向的是还未释放的动态链表，**不能直接把它置为 NULL**，否则可能丢失内存引用造成泄漏。

## 3. 动态内存：`malloc` / `free`

```c
Node *newNode = malloc(sizeof *newNode);
if (newNode == NULL) {
    // 分配失败，必须妥善处理
}
else {
    newNode->data = 10;
    newNode->next = NULL;
}
```

- `malloc` 分配存储空间，**不会自动把 `data` 和 `next` 初始化为你想要的值**。
- `free(p)` 释放 `p` 指向的合法动态内存，并**不自动将所有指向该内存的变量置为 NULL**。
- `free(NULL)` 是合法的，不做任何事。
- `free(p)` 以后再访问 `p->data` 或 `p->next` 是**未定义行为（Undefined Behavior, UB）**。
- 如果失去动态分配节点的最后一条可用引用，且没有先 `free`，会发生**内存泄漏（Memory Leak）**。
- 多个指针指向同一块内存时，释放该内存后，这些指针都不能再用于访问原节点。

## 4. 一般遍历与查找

```c
for (const Node *current = head;
     current != NULL;
     current = current->next) {
    printf("%d ", current->data);
}
```

使用独立的 `current` 不会破坏 `head`。当 `current == NULL` 时不能再写 `current->data` 或 `current->next`。

按值查找：

```c
const Node *findValue(const Node *head, int value) {
    for (const Node *current = head;
         current != NULL;
         current = current->next) {
        if (current->data == value) return current;
    }
    return NULL;
}
```

最坏情况需要遍历全部节点，时间复杂度为 `O(n)`。

## 5. 插入：先接后面，再接前面

### 5.1 头插

```c
newNode->next = head;
head = newNode;
```

在需要修改调用者 `head` 的函数内：

```c
newNode->next = *headPtr;
*headPtr = newNode;
```

顺序不能反：如果先 `*headPtr = newNode`，再 `newNode->next = *headPtr`，会让新节点 `next` 指向自己，可能造成自环并丢失原链表入口。

### 5.2 已知前一个节点时，在其后插入

```c
newNode->next = prev->next;
prev->next = newNode;
```

这是 Lecture 11 中 `insertNode` 的主要思路。

### 5.3 二级指针定位“入口”（我们的扩展重点）

```c
Node **link = headPtr;  // 初始指向调用者的 head

while (*link != NULL && (*link)->data != targetValue) {
    link = &((*link)->next);
}
```

`link = &((*link)->next)` 的逐层含义：

1. `*link`：得到当前 Node 的地址。
2. `(*link)->next`：得到当前 Node 的 `next` 成员保存的值（后继节点地址）。
3. `&((*link)->next)`：取得 **`next` 这个指针成员自身的地址**。
4. `link = ...`：让二级指针指向下一个入口。**只移动 `link`，不修改链表连接。**

当 `link` 定位到目标节点入口后：

```c
newNode->next = *link;  // 新节点先连到原目标节点
*link = newNode;        // 入口再改为新节点地址
```

**统一处理：** 头插（`link` 指向 `head`）、中间插入（`link` 指向某节点的 `next`）；当 `*link == NULL` 时，也能在末尾或空链表处插入。**但具体函数是否允许插入，仍取决于其查找/失败条件**，例如“在目标值前插入”若目标不存在，通常返回失败。

### 5.4 尾插（没有 tail 指针）

```c
Node **link = headPtr;
while (*link != NULL) {
    link = &((*link)->next);
}
*link = newNode;  // 要求 newNode->next == NULL
```

结束时 `*link == NULL`，但 **`link != NULL`**：它指向最后一个节点的 `next` 成员（空链表时指向 `head` 变量）。

**常见错误：** 把循环条件写成 `while (link != NULL)`。此时即使 `*link == NULL`，`link` 仍非 NULL，下一轮会尝试 `(*link)->next`，产生未定义行为。

### 5.5 升序有序插入

```c
Node **link = headPtr;
while (*link != NULL && (*link)->data < value) {
    link = &((*link)->next);
}
newNode->next = *link;
*link = newNode;
```

前提：**原链表已按非降序排列**。使用 `< value` 会把新节点放在已有相等值之前；使用 `<= value` 会放在相等值之后。这种写法可以自然处理空链表、头插、中间插、尾插。

## 6. 删除：先绕过，再释放

### 6.1 有 `prev` 和 `target` 时

```c
prev->next = target->next;
free(target);
```

仅用于 `prev` 确实存在且紧挨 `target` 前面时。删除头节点需要另外更新 `head`。

### 6.2 二级指针统一删除

假设 `link` 指向“保存待删除节点地址的指针成员”，且 `*link != NULL`：

```c
Node *temp = *link;
*link = temp->next;
free(temp);
```

- `temp`：保留待删节点地址。
- `*link = temp->next`：让入口指针绕过待删节点。
- `free(temp)`：释放正确的节点。
- `link` 自身**没有移动**，但 `*link` 已改为后继节点的地址。

**绕过节点不等于释放节点！** 如果只执行 `*link = (*link)->next` 而不先保留、释放旧节点，可能造成内存泄漏。

### 6.3 删除所有匹配值（连续重复节点也能删）

```c
int deleteAll(Node **headPtr, int value) {
    if (headPtr == NULL) return 0;
    Node **link = headPtr;
    int count = 0;

    while (*link != NULL) {
        if ((*link)->data == value) {
            Node *temp = *link;
            *link = temp->next;
            free(temp);
            ++count;
            // 删除后不移动 link：*link 已指向后继节点
        } else {
            link = &((*link)->next);
        }
    }
    return count;
}
```

例如 `10 → 20 → 20 → 30` 删除所有 20，结果 `10 → 30`。如果删除成功后立即移动 `link`，会漏掉紧接着的第二个 20。

## 7. 释放整条链表

### 7.1 Lecture 11 思路：用 `current` 逐个释放

```c
void freeList(Node **headPtr) {
    if (headPtr == NULL) return;
    Node *current = *headPtr;
    while (current != NULL) {
        Node *nextNode = current->next;
        free(current);
        current = nextNode;
    }
    *headPtr = NULL;
}
```

### 7.2 我们推导的简洁写法：直接移动调用者的 `head`

```c
void freeList(Node **headPtr) {
    if (headPtr == NULL) return;
    while (*headPtr != NULL) {
        Node *temp = *headPtr;
        *headPtr = temp->next;  // 先将 head 移向后继节点
        free(temp);            // 再释放旧头节点
    }
}
```

最后一次删除后，`*headPtr` 自然变成 `NULL`，无需额外赋值。

**错误示例：**

```c
free(current);
current = current->next;   // 错！访问已释放内存
```

```c
Node *temp = *headPtr;
*headPtr = temp->next;
free(*headPtr);            // 错！释放了“新头”，不是旧头；旧头可能泄漏
```

## 8. 时间复杂度 Big O

Big O 关注规模 `n` 增大时操作量的增长趋势。基本掌握：`O(1)`、`O(log n)`、`O(n)`、`O(n²)`。

| 操作 | 普通数组 / 动态数组 | 单向链表 |
| --- | --- | --- |
| 已知下标，访问第 k 个元素 | `O(1)` | `O(n)`（需要沿 `next` 走） |
| 无序按值查找 | `O(n)` | `O(n)` |
| 在开头插入 | `O(n)`（需要移动元素） | `O(1)` |
| 已经知道应修改的节点连接后插入 | 通常 `O(n)`（需要移动元素） | `O(1)` |
| 寻找某值并插入 / 删除 | `O(n)` | `O(n)`（找位置耗时） |
| 尾插 | 动态数组通常均摊 `O(1)` | 无 `tail` 为 `O(n)`；有 `tail` 为 `O(1)` |
| 全链表遍历 / 释放 | — | `O(n)` |

**关键：** 链表“修改连接”是 `O(1)`，不代表“寻找连接位置”是 `O(1)`。链表存储额外的 `next` 指针，因此有额外内存开销。

**课件强调的有序链表二分查找：** 链表不能按下标 `O(1)` 访问中间节点，所以通常无法获得有序数组二分查找那样的 `O(log n)` 效率；Lecture 12 将其记为 `O(n)`。

## 9. 三种链表类型（Lecture 12）

**Singly linked list（单向链表）：**

```text
head → 10 → 20 → 30 → NULL
```

只存 `next`，只能顺连接向后访问。

**Doubly linked list（双向链表）：**

```c
struct DNode {
    int data;
    struct DNode *prev;
    struct DNode *next;
};
```

```text
NULL ← 10 ⇄ 20 ⇄ 30 → NULL
```

可向前、向后遍历；每个节点额外存一个 `prev`。常见实现可以同时保存 `head` 和 `tail`，但是否保存这两个外部指针取决于设计。

**Circular linked list（循环链表）：**

```text
head → 10 → 20 → 30
        ↑          │
        └──────────┘
```

末节点 `next == head`，而不是 `NULL`。因此不能直接使用普通链表的 `while (current != NULL)` 作为非空循环链表的终止条件，否则可能无限遍历。

```c
if (head != NULL) {
    Node *current = head;
    do {
        printf("%d ", current->data);
        current = current->next;
    } while (current != head);
}
```

## 10. 必须会排查的错误

| 错误 | 为什么出问题 |
| --- | --- |
| `newNode->next = newNode` | 新节点自环，可能无限遍历 |
| 先改入口，再读取旧入口的后继 | 可能丢失原链表的连接 |
| `free(p)` 后再 `p->next` | use-after-free，未定义行为 |
| 忘记 `free()` 已摘下的动态节点 | 内存泄漏 |
| `while (link != NULL)`，然后访问 `(*link)->next` | `*link` 可能已经为 NULL |
| `while (p->next != NULL)` 但没先保证 `p != NULL` | 空链表会触发空指针访问 |
| 删除连续匹配节点后仍向后移动 | 跳过相邻的第二个匹配节点 |
| 普通遍历指针直接覆盖 `head` | 可能丢失头节点的唯一入口 |
| 把 `Node *` 形参赋值给 `NULL`，期望调用者 `head` 改变 | C 按值传参，只改了局部副本 |
| 把 `malloc` 创建的节点当成自动释放，或对栈节点执行 `free()` | 动态内存管理错误 |

## 11. 我们的六条“口令”

1. **移动一级遍历指针：** `current = current->next;`
2. **移动二级遍历指针：** `link = &((*link)->next);`
3. **插入新节点：** `newNode->next = *link; *link = newNode;`
4. **删除当前节点：** `temp = *link; *link = temp->next; free(temp);`
5. **删除成功以后先别移动 `link`；不删除时才移动。**
6. **释放整条链表：** 先保存后继或把 `head` 移到后继，之后才能 `free` 旧节点。

---

## 附录：可直接编译的单向链表参考程序

这份参考代码包含：创建、头插、尾插、按值前插、有序插入、按值删除、删除所有匹配项、打印、释放。不同题目并不需要全部使用；这里是复习模板。**有序插入要求链表本来就是有序的；与其他操作混用时，应由调用者保证这一前提。**

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *createNode(int value) {
    Node *newNode = malloc(sizeof *newNode);
    if (newNode == NULL) return NULL;
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

void printList(const Node *head) {
    for (const Node *current = head;
         current != NULL;
         current = current->next) {
        printf("%d -> ", current->data);
    }
    puts("NULL");
}

int pushFront(Node **headPtr, int value) {
    if (headPtr == NULL) return 0;
    Node *newNode = createNode(value);
    if (newNode == NULL) return 0;
    newNode->next = *headPtr;
    *headPtr = newNode;
    return 1;
}

int append(Node **headPtr, int value) {
    if (headPtr == NULL) return 0;
    Node *newNode = createNode(value);
    if (newNode == NULL) return 0;
    Node **link = headPtr;
    while (*link != NULL) link = &((*link)->next);
    *link = newNode;
    return 1;
}

int insertBefore(Node **headPtr, int targetValue, int newValue) {
    if (headPtr == NULL) return 0;
    Node **link = headPtr;
    while (*link != NULL && (*link)->data != targetValue) {
        link = &((*link)->next);
    }
    if (*link == NULL) return 0; // 没找到，不插入
    Node *newNode = createNode(newValue);
    if (newNode == NULL) return 0;
    newNode->next = *link;
    *link = newNode;
    return 1;
}

int insertSorted(Node **headPtr, int value) {
    if (headPtr == NULL) return 0;
    Node *newNode = createNode(value);
    if (newNode == NULL) return 0;
    Node **link = headPtr;
    while (*link != NULL && (*link)->data < value) {
        link = &((*link)->next);
    }
    newNode->next = *link;
    *link = newNode;
    return 1;
}

int deleteValue(Node **headPtr, int value) {
    if (headPtr == NULL) return 0;
    Node **link = headPtr;
    while (*link != NULL && (*link)->data != value) {
        link = &((*link)->next);
    }
    if (*link == NULL) return 0;
    Node *temp = *link;
    *link = temp->next;
    free(temp);
    return 1;
}

int deleteAll(Node **headPtr, int value) {
    if (headPtr == NULL) return 0;
    Node **link = headPtr;
    int count = 0;
    while (*link != NULL) {
        if ((*link)->data == value) {
            Node *temp = *link;
            *link = temp->next;
            free(temp);
            count++;
        } else {
            link = &((*link)->next);
        }
    }
    return count;
}

void freeList(Node **headPtr) {
    if (headPtr == NULL) return;
    while (*headPtr != NULL) {
        Node *temp = *headPtr;
        *headPtr = temp->next;
        free(temp);
    }
}

int main(void) {
    Node *head = NULL;

    append(&head, 10);
    append(&head, 20);
    append(&head, 30);
    printList(head);              // 10 -> 20 -> 30 -> NULL

    insertBefore(&head, 20, 15);
    printList(head);              // 10 -> 15 -> 20 -> 30 -> NULL

    deleteValue(&head, 10);
    printList(head);              // 15 -> 20 -> 30 -> NULL

    deleteAll(&head, 20);
    printList(head);              // 15 -> 30 -> NULL

    freeList(&head);
    printList(head);              // NULL
    return 0;
}
```

**编译建议：** `gcc -std=c11 -Wall -Wextra -pedantic linked_list.c -o linked_list`。附录的 `main` 为演示简洁未逐次处理分配失败，实际题目应检查插入函数返回值。

---

## 对照课件的范围说明

- **Lecture 11 — Linked Lists：** 节点与链、遍历、插入节点、使用二级指针实现 `freeLL`、链表与数组的 Big O 比较。
- **Lecture 12 — Linked List Review：** 插入／删除／查找、线性查找、有序链表二分查找的限制、链表与数组的比较、单向／循环／双向链表。
- **Lab 5 Manual（补充材料，非本笔记的实战目标）：** 头插与打印、dummy head + tail、合并两个有序链表、原地去重、交集、文件 I/O 等。
- **我们额外深入推导的技巧：** `link = &((*link)->next)`、二级指针统一头插/中插/尾插、二级指针删除所有匹配项、直接移动调用者 `head` 来清空链表。

**复习时最应该亲自写的三个函数：** `insertSorted`、`deleteAll`、`freeList`。它们能分别检验定位入口、改连接和内存释放三项核心能力。
