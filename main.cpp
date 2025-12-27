// main.cpp

#include "ASR.h"
#include <iostream>
#include <string>

using namespace std;

// HANYA ADA FUNGSI UTAMA main()

int main() {
    address MenuRoot = nullptr;
    int choice;

    // Inisialisasi Root Menu agar Tree dapat dioperasikan
    // Kita panggil fungsi Insert yang didefinisikan di ASR.cpp
    MenuInfo root_info = {"Daftar Menu", "Root Menu", 0};
    MenuRoot = Insert(MenuRoot, root_info, "");

    do {
        cout << "======= SISTEM MANAJEMEN MENU RESTORAN =======" << endl;
        cout << "1. Tambah Menu/Sub-Menu/Item" << endl;
        cout << "2. Hapus Menu/Sub-Menu/Item" << endl;
        cout << "3. Cari Menu/Sub-Menu/Ite" << endl;
        cout << "4. Tampilkan Menu (Traversal)" << endl;
        cout << "5. Edit Menu/Sub-Menu/Ite Info" << endl;
        cout << "6. Cek Harga Termurah & Termahal" << endl; // MENU BARU
        cout << "0. Keluar" << endl;
        cout << "==============================================" << endl;
        cout << "Pilih opsi: ";

        // Kita panggil fungsi clearInput yang didefinisikan di ASR.cpp
        if (!(cin >> choice)) {
            cout << "\nInput harus berupa angka." << endl;
            choice = 0;
            clearInput();
            continue;
        }
        clearInput();

        switch (choice) {
            case 1:
                tambahMenu(MenuRoot); // Panggil fungsi dari ASR.cpp
                break;
            case 2:
                hapusMenu(MenuRoot); // Panggil fungsi dari ASR.cpp
                break;
            case 3:
                cariMenu(MenuRoot); // Panggil fungsi dari ASR.cpp
                break;
            case 4:
                tampilkanMenu(MenuRoot); // Panggil fungsi dari ASR.cpp
                break;
            case 5:
                editMenuInfo(MenuRoot); // Panggil fungsi dari ASR.cpp
                break;
            case 6:
                tampilkanHargaEkstrem(MenuRoot); // Panggil fungsi baru
                break;
            case 0: // Sesuaikan dengan angka keluar
                cout << "Terima kasih. Program selesai." << endl;
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
        }
    } while (choice != 0);

    return 0;
}
