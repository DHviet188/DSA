#include <iostream>

using namespace std;

class Node{
    public:
        int data;
        Node* next;
        Node* prev;
        Node(int _data){
            data = _data;
            next = nullptr;
            prev = nullptr;
        }
};

class DoubleLinkedList{
    public:
        Node* head;
        DoubleLinkedList(){
            head = nullptr;
        }
        ~DoubleLinkedList(){
            Node* tmp1 = head;
            Node* tmp2 = tmp1;
            while(tmp2 != nullptr){
                tmp2 = tmp2->next;
                delete tmp1;
                tmp1 = tmp2;
            }
        }

        void PushBack(int data){
            Node* NewNode = new Node(data);
            if(head == nullptr){
                head = NewNode;
                return;
            }
            Node* tmp = head;
            while(tmp->next != nullptr){
                tmp = tmp->next;
            }
            tmp->next = NewNode;
            NewNode->prev = tmp;
            return;
        }
};

int main()
{
    DoubleLinkedList* dll = new DoubleLinkedList();
    int n;
    cin >> n;
    int a;
    for(int i = 0; i < n; i++){
        cin >> a;
        dll->PushBack(a);
    }

    int count = 0;
    for(auto e = dll->head->next; e->next != nullptr; e = e->next)
        if(e->prev->data + e->data + e->next->data == 0)
            count++;
    cout << count;

    delete dll;
    return 0;
}
