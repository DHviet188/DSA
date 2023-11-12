#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

struct Item{
    int weight;
    int value;
    double _ratio;

    Item(int weight, int value) {
        this->weight = weight;
        this->value = value;
        _ratio = 1.0 * value/weight;
    }
};

bool compare(Item* first, Item* second) {
    return first->_ratio > second->_ratio;
}

int main() {
    int weightofbag, n_objects;
    cin >> weightofbag >> n_objects;
    vector <Item*> Items;
    Items.resize(n_objects);

    for (int i = 0; i < n_objects; i++) {
        int first,second;
        cin >> first >> second;
        Items[i] = new Item(first,second);
    }
    sort(Items.begin(), Items.end(), compare);

    int res = 0;
    int tmp = 0;
    while(weightofbag > 0 && tmp < n_objects) {
        if (weightofbag - Items[tmp]->weight >= 0) {
            res+=Items[tmp]->value;
            weightofbag -= Items[tmp]->weight;
        }
        tmp++;
    }

    cout << "Gia tri toi da co the trom la: " << res;
    return 0;
}

/*
12 5
12 8
3 6
2 4
9 7
4 5
*/
