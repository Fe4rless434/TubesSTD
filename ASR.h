// ASR.h

#ifndef ASR_H
#define ASR_H

#include <iostream>
#include <string>

using namespace std;

// ==========================================================
// 1. ADT UNTUK TREE (Sistem Menu Restoran)
// ==========================================================

// PERUBAHAN DI SINI: Tidak pakai typedef, nama struct langsung di atas
struct MenuInfo {
    string name;      // Nama Menu/Sub-Menu/Item
    string type;      // "Menu Utama", "Sub-Menu", "Item"
    int price;        // Harga (0 jika bukan item)
    string key;       // Kunci unik (Nama Item)
};

// Pointer ke MenuNode kita sebut "address"
typedef struct MenuNode *address;

struct MenuNode {
    MenuInfo info;        // Tipe data ini tetap dikenali
    address first_child;
    address next_sibling;
};

// ==========================================================
// 2. ADT UNTUK QUEUE KUSTOM (Untuk Level-Order Traversal)
// ==========================================================

// Pointer ke QueueNode kita sebut "QueueAddress"
typedef struct QueueNode *QueueAddress;

struct QueueNode {
    address tree_node;
    QueueNode *next;
};

struct Queue {
    QueueAddress head;
    QueueAddress tail;
};

// ==========================================================
// 3. PROTOTIPE FUNGSI UMUM & BANTUAN
// ==========================================================

string CreateKey(string name);
void PrintMenuInfo(address p);
void print_end();
void clearInput();             // Fungsi Bantu Input
MenuInfo inputMenuInfo();      // Fungsi Bantu Input

// ==========================================================
// 4. PROTOTIPE FUNGSI QUEUE
// ==========================================================

void CreateQueue(Queue &Q);
bool isEmptyQueue(Queue Q);
void Enqueue(Queue &Q, address P);
address Dequeue(Queue &Q);

// ==========================================================
// 5. PROTOTIPE FUNGSI TREE
// ==========================================================

address CreateNode(MenuInfo info);
address Insert(address root, MenuInfo new_menu, string parent_key);
address Search(address root, string key);
address Delete(address root, string key_to_delete);

// Traversal Wajib & Inovasi
void PreOrder(address root);
void InOrder(address root);
void PostOrder(address root);
void LevelOrder(address root);

// ==========================================================
// 6. PROTOTIPE FUNGSI MANAJEMEN MENU
// ==========================================================

void tambahMenu(address &root);
void hapusMenu(address &root);
void cariMenu(address root);
void tampilkanMenu(address root);
void editMenuInfo(address root);

void cariMinMaxHarga(address root, address &minNode, address &maxNode);
void tampilkanHargaEkstrem(address root);

#endif // ASR_H
