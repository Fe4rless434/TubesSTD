#include "ASR.h"
#include <iostream>
#include <string>
#include <limits>

using namespace std;

string CreateKey(string name) {
    return name;
}

void PrintMenuInfo(address p) {
    if (p != nullptr) {
        cout << "[" << p->info.type << ": " << p->info.name;
        if (p->info.type == "Item") {
            cout << " (Rp" << p->info.price << ")";
        }
        cout << "] -> ";
    }
}

void print_end() {
    cout << "END" << endl;
}

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

MenuInfo inputMenuInfo() {
    MenuInfo info;
    int type_choice;

    cout << "\n--- Input Menu Baru ---" << endl;

    cout << "Nama Menu/Sub-Menu/Item: ";
    getline(cin, info.name);

    cout << "Tipe Menu (1: Menu Utama, 2: Sub-Menu, 3: Item): ";
    while (!(cin >> type_choice) || type_choice < 1 || type_choice > 3) {
        cout << "Input tidak valid. Pilih 1, 2, atau 3: ";
        clearInput();
    }
    clearInput();

    switch (type_choice) {
        case 1: info.type = "Menu Utama"; info.price = 0; break;
        case 2: info.type = "Sub-Menu"; info.price = 0; break;
        case 3:
            info.type = "Item";
            cout << "Harga Item (Rp): ";
            while (!(cin >> info.price) || info.price < 0) {
                cout << "Harga tidak valid. Masukkan angka positif: ";
                clearInput();
            }
            clearInput();
            break;
    }

    return info;
}

void CreateQueue(Queue &Q) {
    Q.head = nullptr;
    Q.tail = nullptr;
}

bool isEmptyQueue(Queue Q) {
    return Q.head == nullptr;
}

void Enqueue(Queue &Q, address P) {
    QueueAddress newNode = new QueueNode;
    newNode->tree_node = P;
    newNode->next = nullptr;

    if (isEmptyQueue(Q)) {
        Q.head = newNode;
        Q.tail = newNode;
    } else {
        Q.tail->next = newNode;
        Q.tail = newNode;
    }
}

address Dequeue(Queue &Q) {
    if (isEmptyQueue(Q)) {
        return nullptr;
    }
    QueueAddress temp = Q.head;
    address tree_node_to_return = temp->tree_node;

    Q.head = Q.head->next;

    if (Q.head == nullptr) {
        Q.tail = nullptr;
    }

    delete temp;
    return tree_node_to_return;
}

address CreateNode(MenuInfo info) {
    address newNode = new MenuNode;
    newNode->info = info;
    newNode->info.key = CreateKey(info.name);
    newNode->first_child = nullptr;
    newNode->next_sibling = nullptr;
    return newNode;
}

address Search(address root, string key) {
    if (root == nullptr) return nullptr;

    if (root->info.key == key) {
        return root;
    }

    address found = Search(root->first_child, key);
    if (found != nullptr) return found;

    return Search(root->next_sibling, key);
}

address Insert(address root, MenuInfo new_menu, string parent_key) {
    address newNode = CreateNode(new_menu);

    if (root == nullptr) {
        if (parent_key == "") {
            cout << new_menu.name << " menjadi Root Menu." << endl;
            return newNode;
        } else {
            cout << "Error: Root kosong, tidak bisa menambah item
