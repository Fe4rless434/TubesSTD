#ifndef ASR_H
#define ASR_H

#include <iostream>
#include <string>

using namespace std;

struct MenuInfo {
    string name;
    string type;
    int price;
    string key;
};

typedef struct MenuNode *address;

struct MenuNode {
    MenuInfo info;
    address first_child;
    address next_sibling;
};

typedef struct QueueNode *QueueAddress;

struct QueueNode {
    address tree_node;
    QueueNode *next;
};

struct Queue {
    QueueAddress head;
    QueueAddress tail;
};

string CreateKey(string name);
void PrintMenuInfo(address p);
void print_end();
void clearInput();
MenuInfo inputMenuInfo();

void CreateQueue(Queue &Q);
bool isEmptyQueue(Queue Q);
void Enqueue(Queue &Q, address P);
address Dequeue(Queue &Q);

address CreateNode(MenuInfo info);
address Insert(address root, MenuInfo new_menu, string parent_key);
address Search(address root, string key);
address Delete(address root, string key_to_delete);

void PreOrder(address root);
void InOrder(address root);
void PostOrder(address root);
void LevelOrder(address root);

void tambahMenu(address &root);
void hapusMenu(address &root);
void cariMenu(address root);
void tampilkanMenu(address root);
void editMenuInfo(address root);

void cariMinMaxHarga(address root, address &minNode, address &maxNode);
void tampilkanHargaEkstrem(address root);

#endif
