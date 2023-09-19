#include <bits/stdc++.h>
using namespace std;
class MyQueue{
    stack<int> s1;
    public:
    void push(int x){
        stack<int> s2;
        while (!s1.empty()){
            s2.push(s1.top());
            s1.pop();
        }
        s1.push(x);
        while (!s2.empty()){
            s1.push(s2.top());
            s2.pop();
        }
    }
    void pop(){
        s1.pop();
    }
    int front(){
        return s1.top();
    }
    bool empty(){
        return s1.empty();
    }
};
int main(){
    MyQueue q;
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    q.pop();
    q.pop();
    while (!q.empty()){
        cout << q.front() << " ";
        q.pop();
    }
}
