#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <limits>
using namespace std;

struct Lagu
{
    char judul[50];
    char penyanyi[50];
    char genre[30];
    int tahun;
};

const int MAX_LAGU = 100;
Lagu daftarLagu[MAX_LAGU];
int jumlahLagu = 0;
const char FILE_NAME[] = "playlist.dat";

void simpanKeFile()
{
    FILE *file = fopen(FILE_NAME, "wb");
    if (!file)
    {
        cout << "Gagal menyimpan ke file!" << endl;
        return;
    }
    fwrite(&jumlahLagu, sizeof(int), 1, file);
    fwrite(daftarLagu, sizeof(Lagu), jumlahLagu, file);
    fclose(file);
}

void bacaDariFile()
{
    FILE *file = fopen(FILE_NAME, "rb");
    if (!file)
    {
        jumlahLagu = 0;
        return;
    }
    fread(&jumlahLagu, sizeof(int), 1, file);
    if (jumlahLagu < 0 || jumlahLagu > MAX_LAGU)
    {
        jumlahLagu = 0;
    }
    else
    {
        fread(daftarLagu, sizeof(Lagu), jumlahLagu, file);
    }
    fclose(file);
}

void bubbleSort()
{
    for (int i = 0; i < jumlahLagu - 1; i++)
    {
        for (int j = 0; j < jumlahLagu - i - 1; j++)
        {
            if (strcmp(daftarLagu[j].judul, daftarLagu[j + 1].judul) > 0)
            {
                Lagu temp = daftarLagu[j];
                daftarLagu[j] = daftarLagu[j + 1];
                daftarLagu[j + 1] = temp;
            }
        }
    }
}

void tambahLagu()
{
    int jumlahInput;
    cout << "Masukkan jumlah lagu yang ingin diinput: ";
    cin >> jumlahInput;
    cin.ignore();

    if (jumlahLagu + jumlahInput > MAX_LAGU)
    {
        cout << "Kapasitas daftar lagu tidak mencukupi!\n";
        return;
    }

    for (int i = 0; i < jumlahInput; i++)
    {
        cout << "Masukkan judul lagu\t: ";
        cin.getline(daftarLagu[jumlahLagu].judul, 50);
        cout << "Masukkan penyanyi\t: ";
        cin.getline(daftarLagu[jumlahLagu].penyanyi, 50);
        cout << "Masukkan genre lagu\t: ";
        cin.getline(daftarLagu[jumlahLagu].genre, 30);
        cout << "Masukkan tahun lagu\t: ";
        cin >> daftarLagu[jumlahLagu].tahun;
        cin.ignore();
        jumlahLagu++;
        cout << endl;
    }
    simpanKeFile();
    cout << "Lagu berhasil ditambahkan!\n";
}

void tampilkanDaftarLagu()
{
    if (jumlahLagu == 0)
    {
        cout << "Daftar lagu masih kosong.\n";
        return;
    }
    
    bubbleSort();
    
    cout << "\nDaftar Lagu:\n";
    cout << setw(45) << setfill('=') << "=" << endl;
    for (int i = 0; i < jumlahLagu; i++)
    {
        cout << daftarLagu[i].judul << " - " << daftarLagu[i].penyanyi << " - " << daftarLagu[i].genre << " - " << daftarLagu[i].tahun << endl;
    }
}

void editLagu()
{
    char judulCari[50];
    cin.ignore();
    cout << "Masukkan judul lagu yang ingin diedit: ";
    cin.getline(judulCari, 50);
    for (int i = 0; i < jumlahLagu; i++)
    {
        if (strcmp(daftarLagu[i].judul, judulCari) == 0)
        {
            cout << "Masukkan judul baru\t: ";
            cin.getline(daftarLagu[i].judul, 50);
            cout << "Masukkan penyanyi baru\t: ";
            cin.getline(daftarLagu[i].penyanyi, 50);
            cout << "Masukkan genre baru\t: ";
            cin.getline(daftarLagu[i].genre, 30);
            cout << "Masukkan tahun baru\t: ";
            cin >> daftarLagu[i].tahun;
            simpanKeFile();
            cout << "Lagu berhasil diedit!\n";
            return;
        }
    }
    cout << "Lagu tidak ditemukan!\n";
}

void cariLagu()
{
    char judulCari[50];
    cin.ignore();
    cout << "Masukkan judul lagu yang dicari: ";
    cin.getline(judulCari, 50);
    for (int i = 0; i < jumlahLagu; i++)
    {
        if (strcmp(daftarLagu[i].judul, judulCari) == 0)
        {   
            cout << "=====================" << endl;
            cout << "\nFile berhasil dibuka\n";
            cout << "=====================" << endl;
            cout << "\nLagu ditemukan!\n";
            cout << "Judul\t\t: " << daftarLagu[i].judul;
            cout << "\nPenyanyi\t: " << daftarLagu[i].penyanyi;
            cout << "\nGenre\t\t: " << daftarLagu[i].genre;
            cout << "\nTahun\t\t: " << daftarLagu[i].tahun << endl;
            return;
        }
    }
    cout << "Lagu tidak ditemukan!\n";
}

void hapusSemuaLagu()
{
    jumlahLagu = 0;
    simpanKeFile();
    cout << "Semua lagu berhasil dihapus!\n";
}

int main()
{
    bacaDariFile();
    int pilihan;
    bool kembaliMenu = true;
    while (kembaliMenu)
    {
        cout << "\nPlaylist Lagu" << endl;
        cout << "=====================" << endl;
        cout << "1. Tambah Lagu" << endl;
        cout << "2. Edit Lagu" << endl;
        cout << "3. Tampilkan Daftar Lagu" << endl;
        cout << "4. Cari Lagu" << endl;
        cout << "5. Hapus Semua Lagu" << endl;
        cout << "6. Keluar" << endl;
        cout << "Pilih menu: ";
        cin >> pilihan;
        cin.clear();
        cout << endl;

        switch (pilihan)
        {
        case 1:
            tambahLagu();
            break;
        case 2:
            editLagu();
            break;
        case 3:
            tampilkanDaftarLagu();
            break;
        case 4:
            cariLagu();
            break;
        case 5:
            hapusSemuaLagu();
            break;
        case 6:
            cout << "Keluar program.\n";
            kembaliMenu = false;
            break;
        default:
            cout << "Pilihan tidak valid!\n";
        }
    }
    return 0;
}
