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

        void Insert(int pos, int data){
            Node* NewNode = new Node(data);

            if(pos == 0){
                NewNode->next = head;
                head = NewNode;
                return;
            }

            Node* tmp = head;
            for(int i = 0; i < pos - 1; i++){
                tmp = tmp->next;
            }
            NewNode->next = tmp->next;
            tmp->next = NewNode;

            return;
        }

        void Delete(int pos){
            Node* tmp1 = head;
            if(pos == 0){
                head = tmp1->next;
                delete tmp1;
                return;
            }

            for(int i = 0; i < pos - 1; i++){
                tmp1 = tmp1->next;
            }
            Node* tmp2 = tmp1->next;
            tmp1->next = tmp2->next;
            delete tmp2;

            return;
        }
};

int main()
{
    LinkedList* linkedlist = new LinkedList();
    int n;
    cin >> n;
    string s;
    int p, x;
    for(int i = 0; i < n; i++){
        cin >> s;
        if(s == "insert"){
            cin >> p >> x;
            linkedlist->Insert(p, x);
        }
        if(s == "delete"){
            cin >> p;
            linkedlist->Delete(p);
        }
    }

    for(auto e = linkedlist->head; e != nullptr; e = e->next)
        cout << e->data << ' ';

    delete linkedlist;
    return 0;
}
