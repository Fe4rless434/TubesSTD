#include "ASR.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    address MenuRoot = nullptr;
    int choice;

    MenuInfo root_info = {"Daftar Menu Restoran", "Root Menu", 0, ""};
    MenuRoot = Insert(MenuRoot, root_info, "");

    do {
        cout << "\n======= SISTEM MANAJEMEN MENU RESTORAN =======" << endl;
        cout << "1. Tambah Menu/Sub-Menu/Item" << endl;
        cout << "2. Hapus Menu/Sub-Menu/Item" << endl;
        cout << "3. Cari Menu/Sub-Menu/Item" << endl;
        cout << "4. Tampilkan Menu (Traversal)" << endl;
        cout << "5. Edit Menu/Sub-Menu/Item Info" << endl;
        cout << "6. Cek Harga Termurah & Termahal" << endl;
        cout << "0. Keluar" << endl;
        cout << "==============================================" << endl;
        cout << "Pilih opsi: ";

        if (!(cin >> choice)) {
            cout << "\nInput harus berupa angka." << endl;
            choice = -1;
            clearInput();
            continue;
        }
        clearInput();

        switch (choice) {
            case 1:
                tambahMenu(MenuRoot);
                break;
            case 2:
                hapusMenu(MenuRoot);
                break;
            case 3:
                cariMenu(MenuRoot);
                break;
            case 4:
                tampilkanMenu(MenuRoot);
                break;
            case 5:
                editMenuInfo(MenuRoot);
                break;
            case 6:
                tampilkanHargaEkstrem(MenuRoot);
                break;
            case 0:
                cout << "Terima kasih. Program selesai." << endl;
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
        }
    } while (choice != 0);

    return 0;
}
