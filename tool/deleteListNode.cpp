#include <iostream>

using namespace std;

struct List {
    int Value;
    struct List * next;
};

List* deleteListNode(List * head, List * node) {
    if (head == NULL)
        return NULL;
    else if (node == NULL)
        return head;
    //不是尾结点
    if (node->next != NULL) {
        node->Value = node->next->Value;
        List* temp = node->next;
        node->next = node->next->next;
        delete temp;
        return head;
    }
    //只有一个结点
    else if (head == node) {
        delete head;
        return NULL;
    }
    //多个结点的尾结点
    else {
        List * trace = head;
        while (trace->next != node)
            trace = trace->next;
        List* temp = trace->next;
        trace->next = trace->next->next;
        delete temp;
        return head;
    }
}

void printList(List* head) {
    while (head != NULL) {
        cout << head->Value << " ";
        head = head->next;
    }
    cout << endl;
}

int main(void)
{
    List * head = new List;
    List * trace = head;
    int size = 1;
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
    head = deleteListNode(head, head);
    printList(head);
    return 0;
}
