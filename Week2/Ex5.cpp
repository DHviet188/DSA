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

        void Push(int data){
            Node* NewNode = new Node(data);
            if(head == nullptr){
                head = NewNode;
                return;
            }

            NewNode->next = head;
            head = NewNode;
            return;
        }
        void Pop(){
            Node* tmp = head;
            head = head->next;
            delete tmp;
            return;
        }
        void print(Node* tmp){
            if(tmp == nullptr)
                return;
            print(tmp->next);
            cout << tmp->data << ' ';
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
        if(s == "push"){
            cin >> x;
            linkedlist->Push(x);
        }
        if(s == "pop"){
            linkedlist->Pop();
        }
    }

    linkedlist->print(linkedlist->head);

    delete linkedlist;
    return 0;
}
