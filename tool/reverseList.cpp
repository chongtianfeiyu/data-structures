#include <iostream>

using namespace std;

struct List {
    int Value;
    struct List * next;
};

List* RerverseList(List* head) {
    List * left, * mid, * right;

    if (head == NULL)
        return NULL;
    left = head;
    mid = head->next;

    left->next = NULL;
    while (mid != NULL) {
        right = mid->next;
        mid->next = left;
        left = mid;
        mid = right;
    }
    return left;
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
    printList(RerverseList(head));
    return 0;
}
