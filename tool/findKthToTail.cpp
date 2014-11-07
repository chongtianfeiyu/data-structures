#include <iostream>

using namespace std;

struct List {
    int Value;
    struct List * next;
};

void printList(List* head) {
    while (head != NULL) {
        cout << head->Value << " ";
        head = head->next;
    }
    cout << endl;
}

/*
   找链表中倒数第k个结点。
*/
List* findKthToTail(List* head, unsigned int k) {
    if (head == NULL || k <= 0)
        return NULL;
    unsigned int count = k - 1;
    List * t = head;
    List * kth;
    kth = head;
    while (count && t != NULL) {
        count--;
        t = t->next;
    }
    if (count)
        return NULL;
    while (t->next != NULL) {
        t = t->next;
        kth = kth->next;
    }
    return kth;
}

int main(void)
{
    List * head = new List;
    List * trace = head;
    int size = 10;
    for (int i = 0; ; ++i) {
        trace->Value = i;
        if (i + 1 < size) {
            trace->next = new List;
            trace = trace->next;
        }
        else {
            trace->next = NULL;
            break;
        }
    }
    printList(head);
    printList(findKthToTail(head, -1));
    return 0;
}
