#include <iostream>

using namespace std;

class Node{
    public:
        int data;
        Node* next;

        Node(int _data){
            data = _data;
            next = nullptr;
        }
};

class LinkedList{
    public:
        Node* head;
        LinkedList(){
            head = nullptr;
        }
        ~LinkedList(){
            Node* tmp1 = head;
            Node* tmp2 = tmp1;
            while(tmp2 != nullptr){
                tmp2 = tmp2->next;
                delete tmp1;
                tmp1 = tmp2;
            }
        }

        void Enqueue(int data){
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
            return;
        }
        void Dequeue(){
            if(head == nullptr)
                return;

            Node* tmp = head;
            head = head->next;
            delete tmp;
            return;
        }
};

int main()
{
    LinkedList* linkedlist = new LinkedList();
    int n;
    cin >> n;
    string s;
    int x;
    for(int i = 0; i < n; i++){
        cin >> s;
        if(s == "enqueue"){
            cin >> x;
            linkedlist->Enqueue(x);
        }
        if(s == "dequeue"){
            linkedlist->Dequeue();
        }
    }

    for(auto e = linkedlist->head; e != nullptr; e = e->next){
        cout << e->data << ' ';
    }

    delete linkedlist;
    return 0;
}
