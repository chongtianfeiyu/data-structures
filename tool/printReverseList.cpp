#include <iostream>
#include <stack>

using namespace std;

struct List {
    int Value;
    struct List * next;
};

void printReverseList(List* head) {
    if (head == NULL)
        return;
    stack<List*> list_stack;

    List* p = head;
    while (p != NULL) {
        list_stack.push(p);
        p = p->next;
    }
    //cout << "size: " << list_stack.size() << endl;
    while (!list_stack.empty()) {
        p = list_stack.top();
        cout << p->Value << endl;
        list_stack.pop();
    }
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
    printReverseList(head);
    return 0;
}
