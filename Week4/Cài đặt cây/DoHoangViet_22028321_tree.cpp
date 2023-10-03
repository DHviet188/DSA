#include <iostream>
using namespace std;

// Một Node trong cây
class Node {
    // Chứa thông tin của Node đó
    int data;
    // Con trỏ đến Node cha
    Node* fatherNode;

    // Con trỏ đến các Node con
    // Đây là một danh sách liên kết (con trỏ đến con đầu tiên)
    // Thứ tự ưu tiên từ nhỏ đến lớn (con nhỏ được duyệt trước)
    Node* firstChild;
    Node* nextSibling;

public:
    Node() {
        this -> data = 0;
        this -> fatherNode = NULL;
        this -> firstChild = NULL;
        this -> nextSibling = NULL;
    }
    // Các hàm khởi tạo khác nếu cần thiết
    Node(int data, Node* parent){
        this->data = data;
        fatherNode = parent;
        firstChild = NULL;
        nextSibling = NULL;
    }

    // Hàm trả về số con của 1 node
    int NumOfChild(){
        int count = 0;
        Node* temp = firstChild;
        while(temp != NULL){
            count++;
            temp = temp->nextSibling;
        }
        return count;
    }

    // Hàm check một node có đúng là BST không
    bool isBSTNode(){
        if (NumOfChild() > 2) return false;
        if (NumOfChild() == 2) {
            if (data < firstChild->data || data > firstChild->nextSibling->data) return false;
        }
        return true;
    }

    // Hàm kiểm tra một node có thuộc cây maxHeap không
    bool isHeapNode(){
        if (!firstChild) return true; // leaf node
        Node* tmp = firstChild;
        while (tmp) {
            if (data < tmp->data) return false;
            tmp = tmp->nextSibling;
        }
        return true;
    }

    friend class Tree;
};

// Lớp Cây
class Tree {
    // Chứa một Node gốc
    Node* root;
public:
    Tree() {
        root = NULL;
    }
    Node* getRoot(){
        return root;
    }
    // Các hàm khởi tạo khác nếu cần thiết
    Tree(int data){
        root = new Node(data, NULL);
    }

    // Các hàm tìm kiếm và kiểm tra cây
    Node* find(Node* node, int data) {
        if (node) {
            if (node -> data == data) return node;
            Node* p = find(node -> firstChild, data);
            if (p) return p;
            p = find(node -> nextSibling, data);
            if (p) return p;
        }
        return NULL;
    }

    // Hàm thêm một Node vào cây
    // Hàm trả về false nếu Node cha không tồn tại trên cây
    // hoặc Node father đã có con là data
    bool insert(int father, int data) {
        if (root == NULL) root = new Node (father, NULL);
        Node* par = find(root, father);
        if (par == NULL) return false;
        Node* new_node = new Node(data, par);
        Node* check = par->firstChild;
        if (!check) par->firstChild = new_node;
        else {
            if (check -> data == data) return false; // already have a child with data
            while (check -> nextSibling) {
                if (check -> data == data) return false;
                check = check -> nextSibling;
            }
            if (check -> data == data) return false;
            check -> nextSibling = new_node;
        }
        return true;
    }

    // Hàm xoá một Node trên cây
    // Nếu không phải Node lá xoá Node đó và toàn bộ các Node con của nó
    // Hàm trả về số lượng Node đã xoá
    // Nếu Node data không tồn tại trả về 0 (zero)
    void remove_child (Node* del, Node* tmp, int& count) {
        if (!tmp) return;
        else count ++;
        remove_child(del, tmp->firstChild, count);
        // delete all child
        if (tmp!= del) remove_child(del, tmp->nextSibling, count);
        delete tmp;
    }
    int remove(int data) {
        Node* del = find(root, data);
        Node* par = del -> fatherNode;
        Node* tmp = par -> firstChild;

        // if delete the first child, shift the first child to the next sibling
        if (tmp == del) {
            par ->firstChild = del -> nextSibling;
        }
        else {
            while (tmp -> nextSibling != del) {
                tmp = tmp -> nextSibling;
            }
            tmp -> nextSibling = del -> nextSibling; // shift the next sibling to the previous position
        }

        if (!del) return 0;
        int count = 0;
        remove_child (del, del, count);
        return count;
    }

    // Hàm in ra các Node theo thứ tự preorder
    void preorder(Node* node) {
        if (!node) return;
        cout << node -> data << " ";
        preorder(node -> firstChild);
        preorder(node -> nextSibling);
    }

    // Hàm in ra các Node theo thứ tự postorder
    void postorder(Node* node) {
        if (!node) return;
        postorder(node -> firstChild);
        if (node->firstChild) postorder(node ->firstChild -> nextSibling);
        cout << node -> data << " ";
    }

    // Hàm kiểm tra cây nhị phân
    bool isBinaryTree() {
        if (!root) return false;
        Node* tmp = root;
        while (tmp) {
            if (tmp -> NumOfChild() > 2) return false;
            while (tmp -> firstChild) {
                tmp = tmp -> firstChild;
                if (tmp -> NumOfChild() > 2) return false;
            }
            if (tmp -> nextSibling) {
                tmp = tmp -> nextSibling;
                if (tmp -> NumOfChild() > 2) return false;
            }
            // if no child -> leaf node -> traverse up -> go to next
            if (!(tmp->firstChild)){
                while (!(tmp->nextSibling) && tmp != root) {
                    tmp = tmp -> fatherNode;
                }
                tmp = tmp -> nextSibling;
            }

        }

        return true;
    }

    // Hàm kiểm tra cây tìm kiếm nhị phân
    bool isBinarySearchTree() {
        if (!root) return false;
        Node* tmp = root;
        while (tmp) {
            if (!(tmp -> isBSTNode())) return false;
            while (tmp -> firstChild) {
                tmp = tmp -> firstChild;
                if (!(tmp -> isBSTNode())) return false;
            }
            if (tmp -> nextSibling) {
                tmp = tmp -> nextSibling;
                if (!(tmp -> isBSTNode())) return false;
            }
            // if no child -> leaf node -> traverse up -> go to next
            if (!(tmp->firstChild)){
                while (!(tmp->nextSibling) && tmp != root) {
                    tmp = tmp -> fatherNode;
                }
                tmp = tmp -> nextSibling;
            }

        }

        return true;
    }

    // Hàm kiểm tra cây max-heap
    bool isMaxHeapTree() {
        if (!root) return false;
        Node* tmp = root;
        while (tmp) {
            while (tmp -> firstChild) {
                tmp = tmp -> firstChild;
                if (!(tmp -> isHeapNode())) return false;
            }
            if (tmp -> nextSibling) {
                tmp = tmp -> nextSibling;
                if (!(tmp -> isHeapNode())) return false;
            }
            // if no child -> leaf node -> traverse up -> go to next
            if (!(tmp->firstChild)){
                while (!(tmp->nextSibling) && tmp != root) {
                    tmp = tmp -> fatherNode;
                }
                tmp = tmp -> nextSibling;
            }

        }

        return true;
    }

    // Hàm in ra các Node theo thứ tự inorder nếu là cây nhị phân
    void inorder(Node * node) {
        if (isBinaryTree() == false) {
            cout << "Not a binary tree" << endl;
            return;
        }
        if (!node) return;
        inorder(node -> firstChild);
        cout << node -> data << " ";
        if (node->firstChild) inorder(node -> firstChild -> nextSibling);
    }

    // Hàm trả về độ cao của cây
    int height() {
        if (!root) return -1;
        int d,h = 0;
        Node* tmp = root;
        while (tmp) {
            while (tmp -> firstChild) {
                tmp = tmp -> firstChild;
            }
            d = depth(tmp->data);
            if (d >h) h = d;
            if (tmp -> nextSibling) {
                tmp = tmp -> nextSibling;
            }
            // if no child -> leaf node -> traverse up -> go to next (traverse right)
            if (!(tmp -> firstChild)){
                while (!(tmp -> nextSibling) && tmp != root) {
                    tmp = tmp -> fatherNode;
                }
                tmp = tmp -> nextSibling;
            }
        }

        return h;
    }

    // Hàm trả về độ sâu của một Node
    int depth(int data) {
        Node* node = find(root, data);
        if (!node) return -1;
        int d = 0;
        while (node -> fatherNode) {
            node = node -> fatherNode;
            d++;
        }
        return d;
    }

    // Hàm đếm số lượng lá
    int numOfLeaves() {
        if (!root) return 0;
        int leaves = 0;
        Node* tmp = root;
        while (tmp) {
            while (tmp -> firstChild) {
                tmp = tmp -> firstChild;
            }
            leaves ++;
            // move to next sibling and continue traverse down
            if (tmp -> nextSibling) {
                tmp = tmp -> nextSibling;
            }
            // if no child -> leaf node -> traverse up -> go to next (traverse right)
            if (!(tmp -> firstChild)){
                while (!(tmp -> nextSibling) && tmp != root) {
                    tmp = tmp -> fatherNode;
                }
                tmp = tmp -> nextSibling;
            }
        }

        return leaves;
    }

    // Hàm trả về Node có giá trị lớn nhất
    int findMax() {
        Node* tmp = root;
        int mx = tmp->data;
        while (tmp) {
            if (tmp->data > mx) mx = tmp->data;
            while (tmp->firstChild) {
                tmp = tmp->firstChild;
                if (tmp->data > mx) mx = tmp->data;
            }
            if (tmp->nextSibling) {
                tmp = tmp->nextSibling;
                if (tmp->data > mx) mx = tmp->data;
            }
            if (!(tmp->firstChild)) {
                while (!(tmp->nextSibling) && tmp != root) {
                    tmp = tmp->fatherNode;
                }
                tmp = tmp->nextSibling;
            }
        }
        return mx;
    }

    // Hàm trả về Node có nhiều con nhất
    int findMaxChild() {
        Node* tmp = root;
        int mx = 0;
        while (tmp) {
            if (tmp->NumOfChild() > mx) mx = tmp->NumOfChild();
            while (tmp -> firstChild) {
                tmp = tmp -> firstChild;
                if (tmp->NumOfChild() > mx) mx = tmp->NumOfChild();
            }
            if (tmp -> nextSibling) {
                tmp = tmp -> nextSibling;
                if (tmp->NumOfChild() > mx) mx = tmp->NumOfChild();
            }
            if (!(tmp -> firstChild)) {
                while (!(tmp ->nextSibling) && tmp != root) {
                    tmp = tmp -> fatherNode;
                }
                tmp = tmp -> nextSibling;
            }
        }

        return mx;
    }
};

int main(int argc, char const *argv[]) {
    // Tạo ra một cây ngẫu nhiên có tối thiểu 30 Node
    // Test thử các hàm của lớp cây
    Tree* tree = new Tree();
    for (int i = 1; i <= 30; i++) {
        tree -> insert(1, i+1);
    }
    //tree->preorder(tree->getRoot());
    //cout << tree->depth(6);
    //tree->remove(6);
    //tree->postorder(tree->getRoot());
    //cout << tree->getRoot()->NumOfChild();
    //cout << tree->isBinaryTree();
    //cout << tree->isBinarySearchTree();
    //cout << tree->isMaxHeapTree();
    //tree->inorder(tree->getRoot());
    //cout << tree->height();
    //cout << tree->numOfLeaves();

    // Tạo ra một cây thoả mãn tính chất là Binary Search Tree và test lại
    Tree *tr = new Tree();
    tr->insert(10, 1);
    tr->insert(10, 15);
    tr->insert(1, 2);
    tr->insert(2, 3);
    tr->insert(15, 11);
    tr->insert(15, 16);
    tr->insert(11, 13);
    tr->insert(16, 17);
    cout << tr->isBinarySearchTree();

    // Tạo ra một cây thoả mãn tính chất là Max Heap Tree và test lại
    Tree *tr1 = new Tree();
    tr1->insert(10, 8);
    tr1->insert(10, 9);
    tr1->insert(8, 7);
    tr1->insert(8, 6);
    tr1->insert(9, 5);
    tr1->insert(9, 4);
    cout << tr1->isMaxHeapTree();
    return 0;
}
