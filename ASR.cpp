#include "ASR.h"
#include <iostream>
#include <string>
#include <limits> // Diperlukan untuk membersihkan input buffer

using namespace std;

// ==========================================================
// IMPLEMENTASI FUNGSI BANTUAN & INPUT DARI USER (Dipindahkan)
// ==========================================================

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

// Fungsi untuk membersihkan buffer input setelah error
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Fungsi untuk mendapatkan MenuInfo dari user
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
    clearInput(); // Membersihkan buffer setelah input angka

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


// ... (IMPLEMENTASI PRIMITIF QUEUE KUSTOM dan PRIMITIF TREE tetap sama) ...
// ... (IMPLEMENTASI TRAVERSAL tetap sama) ...


// ==========================================================
// IMPLEMENTASI FUNGSI MANAJEMEN MENU (Dipindahkan)
// ==========================================================

void tambahMenu(address &root) {
    MenuInfo new_menu = inputMenuInfo();
    string parent_key;

    if (root == nullptr) {
        // Jika Tree kosong, item baru harus menjadi Root
        if (new_menu.name == "Daftar Menu Restoran") { // Contoh nama Root
            root = Insert(root, new_menu, "");
        } else {
            cout << "Error: Menu harus dimulai dengan Root Menu pertama kali." << endl;
        }
        return;
    }

    cout << "Nama Menu/Sub-Menu Parent: ";
    getline(cin, parent_key);

    root = Insert(root, new_menu, parent_key);
}

void hapusMenu(address &root) {
    if (root == nullptr) {
        cout << "GAGAL: Daftar Menu kosong." << endl;
        return;
    }

    string key_to_delete;
    cout << "\n--- Hapus Menu ---" << endl;
    cout << "Nama Menu/Item yang akan dihapus: ";
    getline(cin, key_to_delete);

    // --- PERBAIKAN DI SINI ---

    // 1. Cek dulu apakah barangnya ada menggunakan fungsi Search yang sudah Anda buat
    address found = Search(root, key_to_delete);

    if (found == nullptr) {
        // 2. Jika tidak ketemu, tampilkan pesan error
        cout << "GAGAL: Menu/Sub-Menu/Item '" << key_to_delete << "' tidak ditemukan." << endl;
    } else {
        // 3. Jika ketemu, baru lakukan penghapusan
        address temp_root = Delete(root, key_to_delete);

        // Update root jika yang dihapus adalah root itu sendiri
        if (root != nullptr && key_to_delete == root->info.key && root->first_child == nullptr) {
            root = temp_root;
        }
    }
}

void cariMenu(address root) {
    if (root == nullptr) {
        cout << "Daftar Menu kosong." << endl;
        return;
    }

    string key_to_find;
    cout << "\n--- Cari Menu ---" << endl;
    cout << "Masukkan Nama Menu/Sub-Menu/Item: ";
    getline(cin, key_to_find);

    address result = Search(root, key_to_find);

    if (result != nullptr) {
        cout << "SUKSES: Menu/Sub-Menu/Item Ditemukan!" << endl;
        cout << "Detail: ";
        PrintMenuInfo(result);
        print_end();
    } else {
        cout << "GAGAL: Menu/Sub-Menu/Item '" << key_to_find << "' tidak ditemukan dalam daftar." << endl;
    }
}

void tampilkanMenu(address root) {
    if (root == nullptr) {
        cout << "Daftar Menu kosong, silakan tambahkan Menu Root terlebih dahulu." << endl;
        return;
    }

    int choice;
    cout << "\n--- Tampilkan Daftar Menu ---" << endl;
    cout << "1. Pre-Order (Struktur Top-Down)" << endl;
    cout << "2. In-Order (Adaptasi General Tree)" << endl;
    cout << "3. Post-Order (Bottom-Up)" << endl;
    cout << "4. Level-Order (Per Tingkat/Level Menu)" << endl;
    cout << "Pilih mode traversal (1-4): ";

    if (!(cin >> choice) || choice < 1 || choice > 4) {
        cout << "Pilihan tidak valid." << endl;
        clearInput();
        return;
    }
    clearInput();

    cout << "\nHASIL TRAVERSAL: ";
    switch (choice) {
        case 1: PreOrder(root); break;
        case 2: InOrder(root); break;
        case 3: PostOrder(root); break;
        case 4: LevelOrder(root); break;
    }
    print_end();
}

void editMenuInfo(address root) {
    if (root == nullptr) {
        cout << "Daftar Menu kosong." << endl;
        return;
    }

    string key_to_edit;
    cout << "\n--- Edit Menu/Item Info ---" << endl;
    cout << "Masukkan Nama Menu/Sub-Menu/Ite yang akan diubah: ";
    getline(cin, key_to_edit);

    address p = Search(root, key_to_edit);

    if (p == nullptr) {
        cout << "GAGAL: Menu/Sub-Menu/Item '" << key_to_edit << "' tidak ditemukan." << endl;
        return;
    }

    cout << "\n--- Mengedit: [" << p->info.type << ": " << p->info.name << "] ---" << endl;

    // 1. Edit Nama (Termasuk Root)
    string new_name;
    cout << "Masukkan Nama Baru (Kosongkan jika tidak diubah): ";
    getline(cin, new_name);

    if (!new_name.empty()) {
        // Cek apakah nama baru sudah ada (kecuali jika namanya sendiri)
        if (Search(root, new_name) != nullptr && new_name != p->info.name) {
             cout << "GAGAL: Nama baru '" << new_name << "' sudah digunakan. Pembatalan edit." << endl;
             return;
        }

        p->info.name = new_name;
        p->info.key = new_name; // Update key
        cout << "SUKSES: Nama berhasil diubah menjadi: " << new_name << endl;
    }

    // 2. Edit Harga (Hanya jika Item)
    if (p->info.type == "Item") {
        int new_price = -1;
        cout << "Harga saat ini: Rp" << p->info.price << endl;
        cout << "Masukkan Harga Baru (Rp, 0 untuk membatalkan edit harga): ";

        if (!(cin >> new_price)) {
            cout << "Input tidak valid. Pembatalan edit harga." << endl;
            clearInput();
            return;
        }
        clearInput(); // Membersihkan buffer setelah input angka

        if (new_price > 0) {
            p->info.price = new_price;
            cout << "SUKSES: Harga berhasil diubah menjadi: Rp" << new_price << endl;
        } else if (new_price == 0) {
            cout << "Edit harga dibatalkan." << endl;
        } else {
             cout << "Harga tidak valid. Edit harga dibatalkan." << endl;
        }

    } else {
        cout << "Catatan: Node bertipe '" << p->info.type << "'. Harga tidak dapat diubah (hanya Item)." << endl;
    }
}

// ... (LANJUTAN IMPLEMENTASI PRIMITIF TREE) ...

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
            cout << "Error: Root kosong, tidak bisa menambah item." << endl;
            delete newNode;
            return root;
        }
    }

    address parent_node = Search(root, parent_key);

    if (parent_node == nullptr) {
        cout << "Error: Menu Parent '" << parent_key << "' tidak ditemukan." << endl;
        delete newNode;
        return root;
    }

    // Validasi sederhana: Item tidak boleh punya anak
    if (parent_node->info.type == "Item") {
        cout << "Error: Item Menu ('" << parent_key << "') tidak boleh memiliki sub-menu/item di bawahnya." << endl;
        delete newNode;
        return root;
    }

    // Tambahkan sebagai Sibling pertama dari First Child
    newNode->next_sibling = parent_node->first_child;
    parent_node->first_child = newNode;
    cout << "SUKSES: " << new_menu.name << " (" << new_menu.type << ") ditambahkan di bawah "
              << parent_node->info.name << "." << endl;

    return root;
}

address Delete(address root, string key_to_delete) {
    if (root == nullptr) return nullptr;

    if (root->info.key == key_to_delete) {
        if (root->first_child != nullptr) {
            cout << "GAGAL: Tidak dapat menghapus " << root->info.name << " karena memiliki sub-menu/item di bawahnya." << endl;
            return root;
        }

        address next = root->next_sibling;
        delete root;
        cout << "SUKSES: Node '" << key_to_delete << "' berhasil dihapus." << endl;
        return next;
    }

    root->first_child = Delete(root->first_child, key_to_delete);
    root->next_sibling = Delete(root->next_sibling, key_to_delete);

    return root;
}


// ... (IMPLEMENTASI PRIMITIF QUEUE KUSTOM, TRAVERSAL tetap sama) ...

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

void PreOrder(address root) {
    if (root != nullptr) {
        PrintMenuInfo(root);
        PreOrder(root->first_child);
        PreOrder(root->next_sibling);
    }
}

void InOrder(address root) {
    if (root != nullptr) {
        InOrder(root->first_child);
        PrintMenuInfo(root);
        InOrder(root->next_sibling);
    }
}

void PostOrder(address root) {
    if (root != nullptr) {
        PostOrder(root->first_child);
        PostOrder(root->next_sibling);
        PrintMenuInfo(root);
    }
}

void LevelOrder(address root) {
    if (root == nullptr) return;

    Queue Q;
    CreateQueue(Q);

    Enqueue(Q, root);

    while (!isEmptyQueue(Q)) {
        address current = Dequeue(Q);
        PrintMenuInfo(current);

        address child = current->first_child;
        while (child != nullptr) {
            Enqueue(Q, child);
            child = child->next_sibling;
        }
    }
}

void cariMinMaxHarga(address root, address &minNode, address &maxNode) {
    if (root == nullptr) return;

    // 1. PROSES NODE SAAT INI (Kunjungi Root)
    // Kita hanya membandingkan jika tipenya "Item" agar Menu Utama (Rp 0) tidak dianggap termurah
    if (root->info.type == "Item") {
        // Cek Minimum
        if (minNode == nullptr || root->info.price < minNode->info.price) {
            minNode = root;
        }
        // Cek Maximum
        if (maxNode == nullptr || root->info.price > maxNode->info.price) {
            maxNode = root;
        }
    }

    // 2. REKURSIF KE ANAK (First Child)
    cariMinMaxHarga(root->first_child, minNode, maxNode);

    // 3. REKURSIF KE SAUDARA (Next Sibling)
    cariMinMaxHarga(root->next_sibling, minNode, maxNode);
}

// Fungsi Utama untuk dipanggil di Main
void tampilkanHargaEkstrem(address root) {
    if (root == nullptr) {
        cout << "Daftar Menu kosong." << endl;
        return;
    }

    address minNode = nullptr;
    address maxNode = nullptr;

    cout << "\n--- Statistik Harga Menu (Termurah & Termahal) ---" << endl;

    // Panggil fungsi rekursif
    cariMinMaxHarga(root, minNode, maxNode);

    if (minNode != nullptr && maxNode != nullptr) {
        cout << "1. Item Termurah: " << endl;
        cout << "   Nama  : " << minNode->info.name << endl;
        cout << "   Harga : Rp" << minNode->info.price << endl;

        cout << "\n2. Item Termahal: " << endl;
        cout << "   Nama  : " << maxNode->info.name << endl;
        cout << "   Harga : Rp" << maxNode->info.price << endl;
    } else {
        cout << "Belum ada 'Item' dengan harga yang terdaftar di menu." << endl;
    }

    print_end();
}
