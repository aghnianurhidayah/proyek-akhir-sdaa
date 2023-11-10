#include <iostream>
#include <fstream>   // file
#include <windows.h> // system()
#include <string>    // to_string()
#include <sstream>   // convert string
#include <ctime>     // date
#include <iomanip>   // setionflags(), setw()
#include <unistd.h>  // sleep()
#include <conio.h>   // getch()
#include <bits/stdc++.h>
using namespace std;

// deklarasi struct user yang berisi variabel-variabel id user yang menyimpan id pengguna,
// username, password dan linked list user awal sama dengan kosong.
struct User
{
    int id_user;
    string username;
    string password;
    User *next = NULL;
};

// mendeklarasikan struct form dari inputan user
struct Form
{
    int id_user;
    int id_antrian;
    string nama_umkm;
    string jenis_umkm;
    string nama_pemilik;
    string kriteria;
    string tanggal;
    string status;
    Form *next = NULL;
};

// mendeklarasikan struct form2 yang sudah diperiksa oleh admin
struct Form2
{
    int id_user;
    int id_antrian;
    string nama_umkm;
    string jenis_umkm;
    string nama_pemilik;
    string kriteria;
    string tanggal;
    string status;
    Form2 *next = NULL;
};

string op, op2;
fstream file;
Form *Head = NULL;
Form2 *Head2 = NULL;
User *Headuser = NULL;
void writefile(), menuAdmin(), menuUser(int get_id_user, Form *head, Form2 *head2);

// table data dari struct form.
void table(Form *head)
{
    // memeriksa apakah liked list kosong
    // jika head nya kosong (user belum menginputkan data) maka akan ada keluaran tidak ada data.
    if (head == NULL)
    {
        cout << "Tidak ada data" << endl;
        // kemudian akan beralih ke kondisi else dimana terdapat 2 deklarasi variabel.
    }
    else
    {
        // digunakan untuk nomor urut(indeks) untuk setiap baris dalam tabel dimulai dari 1.
        int i = 0;
        // mendeklarasikan pointer temp sebagai head yang digunakan untuk mengakses linked list tanpa mengubah pointer head yang asli.
        Form *temp = head;
        cout << "==================================================================================================================\n";
        cout << "| No | ID Antrian |   Nama UMKM   |   Jenis UMKM   |  Nama Pemilik  |    Kriteria    |    Tanggal   |   Status   |\n";
        cout << "==================================================================================================================\n";
        // akan melakukan iterasi selama pointer temp tidak kosong.
        while (temp != NULL)
        {
            cout << "| " << setiosflags(ios::left) << setw(3) << i + 1 << "|";
            cout << " " << setiosflags(ios::left) << setw(11) << temp->id_antrian << "|";
            cout << " " << setiosflags(ios::left) << setw(14) << temp->nama_umkm << "|";
            cout << " " << setiosflags(ios::left) << setw(15) << temp->jenis_umkm << "|";
            cout << " " << setiosflags(ios::left) << setw(15) << temp->nama_pemilik << "|";
            cout << " " << setiosflags(ios::left) << setw(15) << temp->kriteria << "|";
            cout << " " << setiosflags(ios::left) << setw(13) << temp->tanggal << "|";
            cout << " " << setiosflags(ios::left) << setw(11) << temp->status << "|";
            cout << endl;
            // memindahkan pointer temp ke node berikutnya.
            temp = temp->next;
            // melakukan proses increment (menambah) data dari tabel sesuai  nomor urut (indeks).
            i++;
        }
        cout << "==================================================================================================================\n";
    }
}

// kurang lebih sama seperti di form hanya saja tabel ini digunakan untuk data dari user jika sudah diperiksa admin
void table2(Form2 *head)
{
    if (head == NULL)
    {
        cout << "Tidak ada data" << endl;
    }
    else
    {
        int i = 0;
        Form2 *temp = head;
        cout << "==================================================================================================================\n";
        cout << "| No | ID Antrian |   Nama UMKM   |   Jenis UMKM   |  Nama Pemilik  |    Kriteria    |    Tanggal   |   Status   |\n";
        cout << "==================================================================================================================\n";
        while (temp != NULL)
        {
            cout << "| " << setiosflags(ios::left) << setw(3) << i + 1 << "|";
            cout << " " << setiosflags(ios::left) << setw(11) << temp->id_antrian << "|";
            cout << " " << setiosflags(ios::left) << setw(14) << temp->nama_umkm << "|";
            cout << " " << setiosflags(ios::left) << setw(15) << temp->jenis_umkm << "|";
            cout << " " << setiosflags(ios::left) << setw(15) << temp->nama_pemilik << "|";
            cout << " " << setiosflags(ios::left) << setw(15) << temp->kriteria << "|";
            cout << " " << setiosflags(ios::left) << setw(13) << temp->tanggal << "|";
            cout << " " << setiosflags(ios::left) << setw(11) << temp->status << "|";
            cout << endl;
            temp = temp->next;
            i++;
        }
        cout << "==================================================================================================================\n";
    }
}

// menggunakan current date
// bertujuan untuk mengembalikan nilai string tanggal saat fungsinya dipanggil.
string tanggal_input()
{
    // variabel-variabel di bawah digunakan untuk menyimpan nilai string dari tanggal, bulan dan tahun.
    string tgl_str, bln_str, tahun_str;
    // variabel yang menyimpan waktu saat ini
    time_t now = time(0);
    struct tm *timeStruct = localtime(&now);
    // tm_mday untuk memperesentasikan hari dalam bulan dan menympan nilai integer antara 1 dan 31.
    int tgl = timeStruct->tm_mday;
    // tm_mon untuk memperesentasikan bulan, dari 0 himgga 11 dimana 0 adalah januari an 11 adalah desember. 1 pada nilai menyesuaikan rentangnya menjadi 1 hingga 12
    int bln = timeStruct->tm_mon + 1;
    // tm_year untuk mempersentasikan tahun.
    int tahun = timeStruct->tm_year + 1900;

    // mengkonversi variabel ('tgl', 'bln', 'tahun' ) kedalam bentuk string.
    tgl_str = to_string(tgl);
    bln_str = to_string(bln);
    tahun_str = to_string(tahun);
    // mengabungkan tiga variabel yang sudah dikonversikan ke string
    // untuuk membentuk format dd/mm/yyyy.
    string tanggal = tgl_str + "/" + bln_str + "/" + tahun_str;
    return tanggal;
}

// fungsi untuk menyimpan data user ke dalam file csv.
void writefileuser(User *head)
{
    // membuat pointer 'temp' untuk menujuk ke head liked list user
    // pointer ini untuk traversal linked list selama proses penulisan
    // atau penyimpanan ke file.
    User *temp = head;
    // 'file.open' untuk membuka file
    // 'ios::out untuk menulis file
    // 'ios::trunc untuk meriset file (file akan dihapus dan ditulis kembali)
    file.open("users.csv", ios::out | ios::trunc);
    while (temp != NULL)
    {
        file << temp->id_user << ",";
        file << temp->username << ",";
        file << temp->password << "\n";
        temp = temp->next;
    }
    file.close();
}

// fungsi untuk membaca data file csv dan memasukkan data ke dalam linked list 'User'.
void readfileuser(User **head)
{
    // mendeklarasikan variabel string (data, id_user, username, password;)
    // yang digunakan untuk baca file.
    string data, id_user, username, password;
    // mendeklarsikan variabel intger (id_user_int) yang akan digunakan
    // untuk menyimpan nilai 'id_user' setelah diubah tipe data nya.
    int id_user_int;
    file.open("users.csv", ios::in);
    if (file.is_open())
    {
        while (getline(file, data))
        {
            stringstream ss(data);
            getline(ss, id_user, ',');
            getline(ss, username, ',');
            getline(ss, password, '\n');
            stringstream id_user_str(id_user);
            // mengembalikan tipe data
            id_user_str >> id_user_int;
            // menyimpan nilai dari file ke struct User
            User *nodeBaru = new User;
            nodeBaru->id_user = id_user_int;
            nodeBaru->username = username;
            nodeBaru->password = password;
            nodeBaru->next = NULL;
            // jika linked list kosong
            if (*head == NULL)
            {
                *head = nodeBaru;
            }
            else
            {
                User *temp = *head;
                while (temp->next != NULL)
                {
                    temp = temp->next;
                }
                temp->next = nodeBaru;
            }
        }
    }
    file.close();
}

// menambahkan data yang diinput ke dalam file 'form.csv'
void writefile(Form *head)
{
    Form *temp = head;

    file.open("form.csv", ios::out | ios::trunc);
    while (temp != NULL)
    {
        file << temp->id_user << ",";
        file << temp->id_antrian << ",";
        file << temp->nama_umkm << ",";
        file << temp->jenis_umkm << ",";
        file << temp->nama_pemilik << ",";
        file << temp->kriteria << ",";
        file << temp->tanggal << ",";
        file << temp->status << "\n";
        temp = temp->next;
    }
    // menutup kembali file
    file.close();
}
// fungsi untuk menulis atau menyimpan data form2 ke file.
void writefile2(Form2 *head2)
{
    Form2 *temp2 = head2;
    // 'file.open' untuk membuka file
    // 'ios::out untuk menulis file
    // 'ios::trunc untuk meriset file (file akan dihapus dan ditulis kembali)
    file.open("form2.csv", ios::out | ios::trunc);
    while (temp2 != NULL)
    {
        file << temp2->id_user << ",";
        file << temp2->id_antrian << ",";
        file << temp2->nama_umkm << ",";
        file << temp2->jenis_umkm << ",";
        file << temp2->nama_pemilik << ",";
        file << temp2->kriteria << ",";
        file << temp2->tanggal << ",";
        file << temp2->status << "\n";
        temp2 = temp2->next;
    }
    // menutup kembali file
    file.close();
}

// membaca data yang ada pada file 'form.csv'
void readfile(Form **head)
{
    // mendeklasikan variabel string dan intger yang digunakan untuk membaca data.
    string data, id_user, id_antrian, nama_umkm, jenis_umkm, nama_pemilik, kriteria, tanggal, status;
    int id_user_int, id_antrian_int;

    // filr.open fungsi untuk membuka file
    // ios:: in menandakan file akan dibuka untuk kemudian dibaca.
    file.open("form.csv", ios::in);
    if (file.is_open())
    {
        while (getline(file, data))
        {
            stringstream ss(data);
            getline(ss, id_user, ',');
            getline(ss, id_antrian, ',');
            getline(ss, nama_umkm, ',');
            getline(ss, jenis_umkm, ',');
            getline(ss, nama_pemilik, ',');
            getline(ss, kriteria, ',');
            getline(ss, tanggal, ',');
            getline(ss, status, '\n');
            stringstream id_user_str(id_user);
            stringstream id_antrian_str(id_antrian);
            // mengembalikan tipe data
            id_user_str >> id_user_int;
            id_antrian_str >> id_antrian_int;
            // menyimpan nilai dari file ke struct Form
            Form *nodeBaru = new Form;
            nodeBaru->id_user = id_user_int;
            nodeBaru->id_antrian = id_antrian_int;
            nodeBaru->nama_umkm = nama_umkm;
            nodeBaru->jenis_umkm = jenis_umkm;
            nodeBaru->nama_pemilik = nama_pemilik;
            nodeBaru->kriteria = kriteria;
            nodeBaru->tanggal = tanggal;
            nodeBaru->status = status;
            nodeBaru->next = NULL;
            // jika linked list kosong
            if (*head == NULL)
            {
                *head = nodeBaru;
            }
            else
            {
                Form *temp = *head;
                while (temp->next != NULL)
                {
                    temp = temp->next;
                }
                temp->next = nodeBaru;
            }
        }
    }
    file.close();
}

// membaca data yang ada pada file 'form2.csv'
void readfile2(Form2 **head2)
{
    // mendeklasikan variabel string dan intger yang digunakan untuk membaca data.
    string data, id_user, id_antrian, nama_umkm, jenis_umkm, nama_pemilik, kriteria, tanggal, status;
    int id_user_int, id_antrian_int;
    // file.open fungsi untuk membuka file
    // ios:: in menandakan file akan dibuka untuk kemudian dibaca.
    file.open("form2.csv", ios::in);
    if (file.is_open())
    {
        while (getline(file, data))
        {
            stringstream ss(data);
            getline(ss, id_user, ',');
            getline(ss, id_antrian, ',');
            getline(ss, nama_umkm, ',');
            getline(ss, jenis_umkm, ',');
            getline(ss, nama_pemilik, ',');
            getline(ss, kriteria, ',');
            getline(ss, tanggal, ',');
            getline(ss, status, '\n');
            stringstream id_user_str(id_user);
            stringstream id_antrian_str(id_antrian);
            // mengembalikan tipe data
            id_user_str >> id_user_int;
            id_antrian_str >> id_antrian_int;
            // menyimpan nilai dari file ke struct Form2
            Form2 *nodeBaru = new Form2;
            nodeBaru->id_user = id_user_int;
            nodeBaru->id_antrian = id_antrian_int;
            nodeBaru->nama_umkm = nama_umkm;
            nodeBaru->jenis_umkm = jenis_umkm;
            nodeBaru->nama_pemilik = nama_pemilik;
            nodeBaru->kriteria = kriteria;
            nodeBaru->tanggal = tanggal;
            nodeBaru->status = status;
            nodeBaru->next = NULL;
            // jika linked list kosong
            if (*head2 == NULL)
            {
                *head2 = nodeBaru;
            }
            else
            {
                Form2 *temp2 = *head2;
                while (temp2->next != NULL)
                {
                    temp2 = temp2->next;
                }
                temp2->next = nodeBaru;
            }
        }
    }
    file.close();
}

// Fungsi untuk registrasi
void registrasi(User **head, User *head2)
{

    int id_user = 0;
    User *nodeBaru = new User;
    // User *temp = head;
    file.open("idtempUser.csv", ios::in);
    file >> id_user;
    file.close();
    while (true)
    {
        system("cls");
        cout << "+================================================================================================================+\n";
        cout << "|                                         SISTEM PENDATAAN DAN PERIZINAN UMKM                                    |" << endl;
        cout << "|----------------------------------------------------------------------------------------------------------------|" << endl;
        cout << "|                                                    Registrasi                                                  |" << endl;
        cout << "+================================================================================================================+\n";
        cout << " Masukan Username : ";
        // untuk membersikan buffer
        cin.sync();
        getline(cin, nodeBaru->username);
        // membuat pointer 'temp2' yang menunjuk ke head User.
        User *temp2 = head2;
        // mendeklarasikan variabel dan menginisialisasikannya dengan nilai 0.
        int isUsed = 0;
        while (temp2 != NULL)
        {
            // kondisi untuk mengecek username sudah ada di struck user User atau belum
            if (temp2->username == nodeBaru->username)
            {
                cout << "Username sudah digunakan. Silahkan coba lagi." << endl;
                isUsed = 1;
                sleep(1);
            }
            temp2 = temp2->next;
        }
        if (isUsed != 1)
        {
            break;
        }
    }
    cout << " Masukan Password : ";
    getline(cin, nodeBaru->password);
    cout << "+================================================================================================================+\n";
    nodeBaru->id_user = id_user + 1;

    // 'file.open' untuk membuka file
    // 'ios::out untuk menulis file
    // 'ios::trunc untuk meriset file (file akan dihapus dan ditulis kembali)
    file.open("idtempuser.csv", ios::out | ios::trunc);
    file << id_user + 1;
    file.close();
    cout << "Registrasi Berhasil!" << endl;
    if (*head == NULL)
    {
        *head = nodeBaru;
        writefileuser(Headuser); // memasukan kembali data list ke dalam file 'form.csv'
        return;
    }
    User *temp = *head;
    // jika temp tidak sama dengan NULL makan data sudah ada.
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = nodeBaru;
    writefileuser(Headuser);
    sleep(1);
}

void login(User *head)
{
    // me
    int isLogin;
    string username, password;
    system("cls");
    cout << "+================================================================================================================+\n";
    cout << "|                                         SISTEM PENDATAAN DAN PERIZINAN UMKM                                    |" << endl;
    cout << "|----------------------------------------------------------------------------------------------------------------|" << endl;
    cout << "|                                                       Login                                                    |" << endl;
    cout << "+================================================================================================================+\n";
    cout << " Masukkan Username : ";
    cin >> username;
    cout << " Masukkan Password : ";
    cin >> password;
    cout << "+================================================================================================================+\n";
    if (username == "admin" && password == "admin123")
    {
        cout << "Login Berhasil!" << endl;
        sleep(1);
        menuAdmin();
        isLogin = 1;
    }
    else
    {
        User *temp = head;
        while (temp != NULL)
        {
            if (temp->username == username && temp->password == password)
            {
                cout << "Login Berhasil!" << endl;
                sleep(1);
                int get_id_user = temp->id_user;
                menuUser(get_id_user, Head, Head2);
                isLogin = 1;
            }
            temp = temp->next;
        }
    }
    if (isLogin != 1)
    {
        cout << "Login Gagal!" << endl;
        sleep(1);
    }
}

// form untuk menambah data
Form *fillForm(Form2 *head2, int get_id_user)
{
    int id_antrian = 0;
    Form *nodeBaru = new Form;
    file.open("idtemp.csv", ios::in);
    file >> id_antrian;
    file.close();
    while (true)
    {
        system("cls");
        cout << "+================================================================================================================+\n";
        cout << "|                                         SISTEM PENDATAAN DAN PERIZINAN UMKM                                    |" << endl;
        cout << "|----------------------------------------------------------------------------------------------------------------|" << endl;
        cout << "|                                                 Isi Form Perizinan                                             |" << endl;
        cout << "+================================================================================================================+\n";
        cout << " Nama UMKM      : ";
        cin.sync();
        getline(cin, nodeBaru->nama_umkm);
        cin.sync();
        Form2 *temp2 = head2;
        int isUsed = 0;
        while (temp2 != NULL)
        {
            if (temp2->nama_umkm == nodeBaru->nama_umkm)
            {
                cout << "Nama UMKM sudah terdaftar. Silahkan coba lagi." << endl;
                isUsed = 1;
                sleep(1);
            }
            temp2 = temp2->next;
        }
        if (isUsed != 1)
        {
            break;
        }
    }
    cout << " Jenis UMKM     : ";
    getline(cin, nodeBaru->jenis_umkm);
    cout << " Nama Pemilik   : ";
    getline(cin, nodeBaru->nama_pemilik);
    cout << " Kriteria       : ";
    getline(cin, nodeBaru->kriteria);
    cout << "+================================================================================================================+\n";
    nodeBaru->id_user = get_id_user;
    nodeBaru->id_antrian = id_antrian + 1;
    nodeBaru->tanggal = tanggal_input();
    nodeBaru->status = "Antrian";
    file.open("idtemp.csv", ios::out | ios::trunc);
    file << id_antrian + 1;
    file.close();
    cout << "Form Berhasil Diisi!" << endl;
    return nodeBaru;
}

// menghitung panjang node single linked list
int length(Form *head)
{
    int n = 0;
    while (head != NULL)
    {
        n++;
        head = head->next;
    }
    return n;
}

// menambahkan data form ke dalam list
void addForm(Form **head, int get_id_user)
{
    Form *nodeBaru = fillForm(Head2, get_id_user);

    if (*head == NULL)
    {

        *head = nodeBaru;
        writefile(Head); // memasukan kembali data list ke dalam file 'form.csv'
        return;
    }
    Form *temp = *head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = nodeBaru;
    writefile(Head);
}

// Merge Sort
Form *SortedMergeForm(Form *a, Form *b, string type, string var);
void FrontBackSplitForm(Form *source, Form **frontRef, Form **backRef);
Form2 *SortedMergeForm2(Form2 *a, Form2 *b, string type, string var);
void FrontBackSplitForm2(Form2 *source, Form2 **frontRef, Form2 **backRef);

// sorting data dari struct form
void MergeSortForm(Form **headRef, string type, string var)
{
    Form *head = *headRef;
    Form *a = NULL;
    Form *b;
    if ((head == NULL) || (head->next == NULL))
    {
        return;
    }
    FrontBackSplitForm(head, &a, &b);
    MergeSortForm(&a, type, var);
    MergeSortForm(&b, type, var);
    *headRef = SortedMergeForm(a, b, type, var);
}

void MergeSortForm2(Form2 **headRef, string type, string var)
{
    Form2 *head = *headRef;
    Form2 *a = NULL;
    Form2 *b;
    if ((head == NULL) || (head->next == NULL))
    {
        return;
    }
    FrontBackSplitForm2(head, &a, &b);
    MergeSortForm2(&a, type, var);
    MergeSortForm2(&b, type, var);
    *headRef = SortedMergeForm2(a, b, type, var);
}

Form *SortedMergeForm(Form *a, Form *b, string type, string var)
{
    Form *result = NULL;
    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);
    if (type == "default" && var == "idantrian")
    {
        if (a->id_antrian <= b->id_antrian)
        {
            result = a;
            result->next = SortedMergeForm(a->next, b, type, var);
        }
        else
        {
            result = b;
            result->next = SortedMergeForm(a, b->next, type, var);
        }
    }
    if (type == "ASC")
    {
        if (var == "tanggal")
        {
            if (a->tanggal <= b->tanggal)
            {
                result = a;
                result->next = SortedMergeForm(a->next, b, type, var);
            }
            else
            {
                result = b;
                result->next = SortedMergeForm(a, b->next, type, var);
            }
        }
        else if (var == "namaumkm")
        {
            if (a->nama_umkm <= b->nama_umkm)
            {
                result = a;
                result->next = SortedMergeForm(a->next, b, type, var);
            }
            else
            {
                result = b;
                result->next = SortedMergeForm(a, b->next, type, var);
            }
        }
    }
    if (type == "DESC")
    {
        if (var == "tanggal")
        {
            if (a->tanggal >= b->tanggal)
            {
                result = a;
                result->next = SortedMergeForm(a->next, b, type, var);
            }
            else
            {
                result = b;
                result->next = SortedMergeForm(a, b->next, type, var);
            }
        }
        else if (var == "namaumkm")
        {
            if (a->nama_umkm >= b->nama_umkm)
            {
                result = a;
                result->next = SortedMergeForm(a->next, b, type, var);
            }
            else
            {
                result = b;
                result->next = SortedMergeForm(a, b->next, type, var);
            }
        }
    }
    return (result);
}

Form2 *SortedMergeForm2(Form2 *a, Form2 *b, string type, string var)
{
    Form2 *result = NULL;
    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);
    if (type == "default" && var == "id_antrian")
    {
        if (a->id_antrian <= b->id_antrian)
        {
            result = a;
            result->next = SortedMergeForm2(a->next, b, type, var);
        }
        else
        {
            result = b;
            result->next = SortedMergeForm2(a, b->next, type, var);
        }
    }
    if (type == "ASC")
    {
        if (var == "tanggal")
        {
            if (a->tanggal <= b->tanggal)
            {
                result = a;
                result->next = SortedMergeForm2(a->next, b, type, var);
            }
            else
            {
                result = b;
                result->next = SortedMergeForm2(a, b->next, type, var);
            }
        }
        else if (var == "namaumkm")
        {
            if (a->nama_umkm <= b->nama_umkm)
            {
                result = a;
                result->next = SortedMergeForm2(a->next, b, type, var);
            }
            else
            {
                result = b;
                result->next = SortedMergeForm2(a, b->next, type, var);
            }
        }
    }
    if (type == "DESC")
    {
        if (var == "tanggal")
        {
            if (a->tanggal >= b->tanggal)
            {
                result = a;
                result->next = SortedMergeForm2(a->next, b, type, var);
            }
            else
            {
                result = b;
                result->next = SortedMergeForm2(a, b->next, type, var);
            }
        }
        else if (var == "namaumkm")
        {
            if (a->nama_umkm >= b->nama_umkm)
            {
                result = a;
                result->next = SortedMergeForm2(a->next, b, type, var);
            }
            else
            {
                result = b;
                result->next = SortedMergeForm2(a, b->next, type, var);
            }
        }
    }
    return (result);
}

void FrontBackSplitForm(Form *source, Form **frontRef, Form **backRef)
{
    Form *fast;
    Form *slow;
    slow = source;
    fast = source->next;
    while (fast != NULL)
    {
        fast = fast->next;
        if (fast != NULL)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }
    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
}

void FrontBackSplitForm2(Form2 *source, Form2 **frontRef, Form2 **backRef)
{
    Form2 *fast;
    Form2 *slow;
    slow = source;
    fast = source->next;
    while (fast != NULL)
    {
        fast = fast->next;
        if (fast != NULL)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }
    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
}

void mergeForm(string type, string var)
{
    Form *res = NULL;
    Form *a = NULL;
    MergeSortForm(&Head, type, var);
}

void mergeForm2(string type, string var)
{
    Form2 *res = NULL;
    Form2 *a = NULL;
    MergeSortForm2(&Head2, type, var);
}

const int NO_OF_CHARS = 256;
void badCharHeuristic(string str, int size, int badChar[NO_OF_CHARS])
{
    for (int i = 0; i < NO_OF_CHARS; i++)
    {
        badChar[i] = -1;
    }
    for (int i = 0; i < size; i++)
    {
        badChar[(int)str[i]] = i;
    }
}

// mencari data dari form masuk berdasarkan nama umkm menggunakan metode boyer moore
void bmsearchForm(Form *head, string pat)
{
    int m = pat.size();
    Form *temp = head;
    while (temp != NULL)
    {
        int n = temp->nama_umkm.size();
        int badChar[NO_OF_CHARS];
        badCharHeuristic(pat, m, badChar);
        int s = 0;
        while (s <= (n - m))
        {
            int j = m - 1;
            while (j >= 0 && pat[j] == temp->nama_umkm[s + j])
            {
                j--;
            }
            if (j < 0)
            {
                cout << endl;
                cout << "+================================================================================================================+\n";
                cout << " ID Antrian     : " << temp->id_antrian << endl;
                cout << " Nama UMKM      : " << temp->nama_umkm << endl;
                cout << " Jenis UMKM     : " << temp->jenis_umkm << endl;
                cout << " Nama Pemilik   : " << temp->nama_pemilik << endl;
                cout << " Kriteria       : " << temp->kriteria << endl;
                cout << " Tanggal        : " << temp->tanggal << endl;
                cout << " Status         : " << temp->status << endl;
                cout << "+================================================================================================================+\n";
                break;
            }
            else
            {
                s += max(1, j - badChar[temp->nama_umkm[s + j]]);
            }
        }
        temp = temp->next;
    }
}

void bmsearchForm2(Form2 *head, string pat)
{
    int m = pat.size();
    Form2 *temp = head;
    while (temp != NULL)
    {
        int n = temp->nama_umkm.size();
        int badChar[NO_OF_CHARS];
        badCharHeuristic(pat, m, badChar);
        int s = 0;
        while (s <= (n - m))
        {
            int j = m - 1;
            while (j >= 0 && pat[j] == temp->nama_umkm[s + j])
            {
                j--;
            }
            if (j < 0)
            {
                cout << endl;
                cout << "+================================================================================================================+\n";
                cout << " ID Antrian     : " << temp->id_antrian << endl;
                cout << " Nama UMKM      : " << temp->nama_umkm << endl;
                cout << " Jenis UMKM     : " << temp->jenis_umkm << endl;
                cout << " Nama Pemilik   : " << temp->nama_pemilik << endl;
                cout << " Kriteria       : " << temp->kriteria << endl;
                cout << " Tanggal        : " << temp->tanggal << endl;
                cout << " Status         : " << temp->status << endl;
                cout << "+================================================================================================================+\n";
                break;
            }
            else
            {
                s += max(1, j - badChar[temp->nama_umkm[s + j]]);
            }
        }
        temp = temp->next;
    }
}

void cont()
{
    cout << endl;
    cout << "Tekan enter untuk kembali..." << endl;
    getche();
}

void readformmasuk(Form *head)
{
    while (true)
    {
        system("cls");
        cout << "+================================================================================================================+\n";
        cout << "|                                         SISTEM PENDATAAN DAN PERIZINAN UMKM                                    |" << endl;
        cout << "|----------------------------------------------------------------------------------------------------------------|" << endl;
        cout << "|                                                  Lihat Form Masuk                                              |" << endl;
        cout << "+================================================================================================================+\n";
        mergeForm("default", "idantrian");
        table(Head);
        cout << "+================================================================================================================+\n";
        cout << "|                                       [1] Urutkan Tanggal Masuk Form Ascending                                 |" << endl;
        cout << "|                                       [2] Urutkan Tanggal Masuk Form Descending                                |" << endl;
        cout << "|                                       [3] Urutkan Nama UMKM Ascending                                          |" << endl;
        cout << "|                                       [4] Urutkan Nama UMKM Descending                                         |" << endl;
        cout << "|                                       [5] Cari Form bedasarkan Nama UMKM                                       |" << endl;
        cout << "|                                       [0] Kembali                                                              |" << endl;
        cout << "+================================================================================================================+\n";
        cout << " Masukan Pilihan : ";
        cin >> op;
        cout << "+================================================================================================================+\n";
        if (op == "1")
        {
            system("cls");
            mergeForm("ASC", "tanggal");
            table(Head);
            cont();
        }
        else if (op == "2")
        {
            system("cls");
            mergeForm("DESC", "tanggal");
            table(Head);
            cont();
        }
        else if (op == "3")
        {
            system("cls");
            mergeForm("ASC", "namaumkm");
            table(Head);
            cont();
        }
        else if (op == "4")
        {
            system("cls");
            mergeForm("DESC", "namaumkm");
            table(Head);
            cont();
        }
        else if (op == "5")
        {
            string namaTemp;
            cout << "Masukan Nama UMKM : ";
            cin >> namaTemp;
            bmsearchForm(Head, namaTemp);
            cont();
        }
        else if (op == "0")
        {
            break;
        }
    }
}

void readformkeluar(Form2 *head2)
{
    while (true)
    {
        system("cls");
        cout << "+================================================================================================================+\n";
        cout << "|                                         SISTEM PENDATAAN DAN PERIZINAN UMKM                                    |" << endl;
        cout << "|----------------------------------------------------------------------------------------------------------------|" << endl;
        cout << "|                                                  Lihat Form Keluar                                             |" << endl;
        cout << "+================================================================================================================+\n";
        mergeForm2("default", "idantrian");
        table2(Head2);
        cout << "+================================================================================================================+\n";
        cout << "|                                       [1] Urutkan Tanggal Masuk Form Ascending                                 |" << endl;
        cout << "|                                       [2] Urutkan Tanggal Masuk Form Descending                                |" << endl;
        cout << "|                                       [3] Urutkan Nama UMKM Ascending                                          |" << endl;
        cout << "|                                       [4] Urutkan Nama UMKM Descending                                         |" << endl;
        cout << "|                                       [5] Cari Form bedasarkan Nama UMKM                                       |" << endl;
        cout << "|                                       [0] Kembali                                                              |" << endl;
        cout << "+================================================================================================================+\n";
        cout << " Masukan Pilihan : ";
        cin >> op;
        cout << "+================================================================================================================+\n";
        if (op == "1")
        {
            system("cls");
            mergeForm2("ASC", "tanggal");
            table2(Head2);
            cont();
        }
        else if (op == "2")
        {
            system("cls");
            mergeForm2("DESC", "tanggal");
            table2(Head2);
            cont();
        }
        else if (op == "3")
        {
            system("cls");
            mergeForm2("ASC", "namaumkm");
            table2(Head2);
            cont();
        }
        else if (op == "4")
        {
            system("cls");
            mergeForm2("DESC", "namaumkm");
            table2(Head2);
            cont();
        }
        else if (op == "5")
        {
            string namaTemp;
            cout << "Masukan Nama UMKM : ";
            cin >> namaTemp;
            bmsearchForm2(Head2, namaTemp);
            cont();
        }
        else if (op == "0")
        {
            break;
        }
    }
}

// update data form
void updateForm(Form *head, int get_id_user)
{
    system("cls");
    cout << "+================================================================================================================+\n";
    cout << "|                                         SISTEM PENDATAAN DAN PERIZINAN UMKM                                    |" << endl;
    cout << "|----------------------------------------------------------------------------------------------------------------|" << endl;
    cout << "|                                                 Ubah Form Peizinan                                             |" << endl;
    cout << "+================================================================================================================+\n";
    Form *temp = head;
    while (temp != NULL)
    {
        if (temp->id_user == get_id_user)
        {
            cout << "Data yang akan diubah :" << endl;
            cout << "==================================================================================================================\n";
            cout << " Nama UMKM      : " << temp->nama_umkm << endl;
            cout << " Jenis UMKM     : " << temp->jenis_umkm << endl;
            cout << " Nama Pemilik   : " << temp->nama_pemilik << endl;
            cout << " Kriteria       : " << temp->kriteria << endl;
            cout << " Tanggal        : " << temp->tanggal << endl;
            cout << " Status         : " << temp->status << endl;
            cout << "==================================================================================================================\n";
            cout << " Masukkan perubahan data :" << endl;
            cout << " Nama UMKM      : ";
            cin.sync();
            getline(cin, temp->nama_umkm);
            cout << " Jenis UMKM     : ";
            getline(cin, temp->jenis_umkm);
            cout << " Nama Pemilik   : ";
            getline(cin, temp->nama_pemilik);
            cout << " Kriteria       : ";
            getline(cin, temp->kriteria);

            cout << "Form Perizinan berhasil diperbarui!" << endl;
            writefile(Head);
        }
        temp = temp->next;
    }
}

// hapus data form
int deleteForm(Form **head, int get_id_user)
{
    int isFound;
    system("cls");
    cout << "+================================================================================================================+\n";
    cout << "|                                         SISTEM PENDATAAN DAN PERIZINAN UMKM                                    |" << endl;
    cout << "|----------------------------------------------------------------------------------------------------------------|" << endl;
    cout << "|                                                 Batalkan Perizinan                                             |" << endl;
    cout << "+================================================================================================================+\n";
    Form *temp = *head;
    while (temp != NULL)
    {
        if (temp->id_user == get_id_user)
        {
            cout << "Data yang akan dibatalkan :" << endl;
            cout << "==================================================================================================================\n";
            cout << " Nama UMKM      : " << temp->nama_umkm << endl;
            cout << " Jenis UMKM     : " << temp->jenis_umkm << endl;
            cout << " Nama Pemilik   : " << temp->nama_pemilik << endl;
            cout << " Kriteria       : " << temp->kriteria << endl;
            cout << " Tanggal        : " << temp->tanggal << endl;
            cout << " Status         : " << temp->status << endl;
            cout << "==================================================================================================================\n";
            cout << "Apakah Anda yakin ingin membatalkan perizinan ini? (y/n): ";
            cin >> op2;
            if (op2 == "y" || op2 == "Y")
            {
                Form *temp2 = *head;
                if (temp->id_antrian == temp2->id_antrian)
                {
                    *head = (*head)->next;
                }
                else
                {
                    for (int i = temp2->next->id_antrian; i < temp->id_antrian; i++)
                    {
                        if (temp2->next != NULL)
                        {
                            temp2 = temp2->next;
                        }
                    }
                    temp2->next = temp2->next->next;
                }
                writefile(Head);
                cout << "Form Perizinan berhasil dibatalkan." << endl;
                isFound = 0;
            }
            else if (op2 == "n" || op2 == "N")
            {
                cout << "Pembatalan perizinan gagal." << endl;
                isFound = 1;
            }
        }
        temp = temp->next;
    }
    return isFound;
}

void verif(Form **head, Form2 **head2)
{
    while (true)
    {
        // membersihkan layar terminal
        // menampilkan header verifikasi
        // menampilkan table dan kemudian menu dari verif
        // membuat variabel pointer temp yang menunjuk ke alamat pertama dari linked list formulir head.
        //  diminta memasukkan imputan berdasarkan menu yang tersedia.
        system("cls");
        cout << "+================================================================================================================+\n";
        cout << "|                                         SISTEM PENDATAAN DAN PERIZINAN UMKM                                    |" << endl;
        cout << "|----------------------------------------------------------------------------------------------------------------|" << endl;
        cout << "|                                                    Verifikasi                                                  |" << endl;
        cout << "+================================================================================================================+\n";
        table(Head);
        Form *temp = *head;
        cout << "+================================================================================================================+\n";
        cout << "|                                            [1] Verifikasi Form Antrian                                         |" << endl;
        cout << "|                                            [0] Kembali                                                         |" << endl;
        cout << "+================================================================================================================+\n";
        cout << " Masukkan Pilihan : ";
        cin >> op;
        cout << "+================================================================================================================+\n";
        // mengecek jika pilihan sama dengan 1
        if (op == "1")
        {
            // melakukan perulangan ketika temp tidak sama dengan null untuk mengecek formulir yang belum diverif.
            // setiap formulir yang belum diverif diakses melalui variabel temp.
            while (temp != NULL)
            {
                // menampilkan informasi formulir yang terdiri dari id antrian, nama umkm, jenis umkm, nama pemilik, kriteria dan status.
                // admin diminta untuk memasukkan status verif
                cout << endl;
                cout << "Verifikasi ID Antrian " << temp->id_antrian << endl;
                cout << "==================================================================================================================\n";
                cout << " ID Antrian     : " << temp->id_antrian << endl;
                cout << " Nama UMKM      : " << temp->nama_umkm << endl;
                cout << " Jenis UMKM     : " << temp->jenis_umkm << endl;
                cout << " Nama Pemilik   : " << temp->nama_pemilik << endl;
                cout << " Kriteria       : " << temp->kriteria << endl;
                cout << " Status         : ";
                cin >> temp->status;
                cout << "==================================================================================================================\n";
                while (true)
                {
                    cout << "Yakin mengubah status verifikasi? (y/n): ";
                    cin >> op2;
                    if (op2 == "Y" || op2 == "y")
                    {
                        // delete first
                        *head = (*head)->next;
                        writefile(Head);
                        Form2 *nodeBaru = new Form2;
                        nodeBaru->id_user = temp->id_user;
                        nodeBaru->id_antrian = temp->id_antrian;
                        nodeBaru->nama_umkm = temp->nama_umkm;
                        nodeBaru->jenis_umkm = temp->jenis_umkm;
                        nodeBaru->nama_pemilik = temp->nama_pemilik;
                        nodeBaru->kriteria = temp->kriteria;
                        nodeBaru->tanggal = temp->tanggal;
                        nodeBaru->status = temp->status;
                        if (*head2 == NULL)
                        {
                            *head2 = nodeBaru;
                            writefile2(Head2); // memasukan kembali data list ke dalam file 'form.csv'
                            return;
                        }
                        // mau diubah jadi add first
                        Form2 *temp2 = *head2;
                        while (temp2->next != NULL)
                        {
                            temp2 = temp2->next;
                        }
                        temp2->next = nodeBaru;
                        writefile2(Head2);
                        cout << "Status berhasil diubah." << endl;
                        break;
                    }
                    else if (op2 == "N" || op2 == "n")
                    {
                        temp->status = "Antrian";
                        cout << "Status batal diubah." << endl;
                        break;
                    }
                    else
                    {
                        cout << "Pilihan tidak ada" << endl;
                    }
                }
                break;
                temp = temp->next;
            }
            break;
            cout << "Tidak ada antrian" << endl;
        }
        else if (op == "0")
        {
            break;
        }
        else
        {
            cout << "Pilihan tidak ada" << endl;
        }
    }
}

void menuAdmin()
{
    while (true)
    {
        system("cls");
        cout << "+================================================================================================================+\n";
        cout << "|                                         SISTEM PENDATAAN DAN PERIZINAN UMKM                                    |" << endl;
        cout << "|----------------------------------------------------------------------------------------------------------------|" << endl;
        cout << "|                                                    Menu Admin                                                  |" << endl;
        cout << "+================================================================================================================+\n";
        cout << "|                                            [1] Lihat Form Masuk                                                |" << endl;
        cout << "|                                            [2] Lihat Form Keluar                                               |" << endl;
        cout << "|                                            [3] Verifikasi Data Perizinan                                       |" << endl;
        cout << "|                                            [0] Keluar                                                          |" << endl;
        cout << "+================================================================================================================+\n";
        cout << " Masukan Pilihan : ";
        cin >> op;
        cout << "+================================================================================================================+\n";
        if (op == "1")
        {
            readformmasuk(Head);
        }
        else if (op == "2")
        {
            readformkeluar(Head2);
        }
        else if (op == "3")
        {
            verif(&Head, &Head2);
            cont();
        }
        else if (op == "0")
        {
            break;
        }
        else
        {
            cout << "Pilihan tidak ada" << endl;
            sleep(1);
        }
    }
}

// fumngsi menu user
void menuUser(int id_user, Form *head, Form2 *head2)
{
    int isFound = 0;
    int isLogout = 0;
    int isDone = 0;
    while (true)
    {
        //
        Form *temp = head;
        while (temp != NULL)
        {
            if (temp->id_user == id_user)
            {
                while (true)
                {
                    system("cls");
                    cout << "+================================================================================================================+\n";
                    cout << "|                                         SISTEM PENDATAAN DAN PERIZINAN UMKM                                    |" << endl;
                    cout << "|----------------------------------------------------------------------------------------------------------------|" << endl;
                    cout << "|                                                       User                                                     |" << endl;
                    cout << "+================================================================================================================+\n";
                    cout << " Nama UMKM      : " << temp->nama_umkm << endl;
                    cout << " Jenis UMKM     : " << temp->jenis_umkm << endl;
                    cout << " Nama Pemilik   : " << temp->nama_pemilik << endl;
                    cout << " Kriteria       : " << temp->kriteria << endl;
                    cout << " Tanggal        : " << temp->tanggal << endl;
                    cout << " Status         : " << temp->status << endl;
                    cout << "+================================================================================================================+\n";
                    cout << "|                                            [1] Perbarui Form Perizinan                                         |" << endl;
                    cout << "|                                            [2] Batalkan Form Perizinan                                         |" << endl;
                    cout << "|                                            [0] Keluar                                                          |" << endl;
                    cout << "+================================================================================================================+\n";
                    cout << " Masukan Pilihan : ";
                    cin >> op;
                    cout << "+================================================================================================================+\n";
                    // jika pilihan sama dengan satu, maka akan memanggil fungsi updateform dari user itu sendiri.
                    if (op == "1")
                    {
                        updateForm(Head, id_user);
                        isFound = 1;
                        cont();
                        break;
                    }
                    // jika pilihan sama dengan dua, maka akan memanggil fungsi deleteform dari user itu sendiri.
                    else if (op == "2")
                    {
                        isFound = deleteForm(&Head, id_user);
                        cont();
                        break;
                    }
                    // jika pilihan sama dengan nol, maka akan keluar.
                    else if (op == "0")
                    {
                        isLogout = 1;
                        isFound = 1;
                        break;
                    }
                    // jika memilih selain dari itu maka pilihan tidak ada. Dan akan menunggu selama satu detik sebelum masuk kemenu berikutnya.
                    else
                    {
                        cout << "Pilihan tidak ada" << endl;
                        sleep(1);
                    }
                }
                break;
            }
            // temp akan menunjuk ke temp berikutnya.
            temp = temp->next;
        }
        // pointer temp2 sama dengan head2.
        Form2 *temp2 = head2;
        // perulangan ketika temp 2 tidak sama dengan null maka akan masuk ke dalam if.
        while (temp2 != NULL)
        {
            // mengecek apakah id user yang di temp2 sama dengan id user pas user melakukan login.
            if (temp2->id_user == id_user)
            {
                // perulangan
                while (true)
                {
                    // membersihkan layar terminal
                    // menampilkan menu user
                    // menampilkan informasi formulir yang telah disetujui
                    system("cls");
                    cout << "+================================================================================================================+\n";
                    cout << "|                                         SISTEM PENDATAAN DAN PERIZINAN UMKM                                    |" << endl;
                    cout << "|----------------------------------------------------------------------------------------------------------------|" << endl;
                    cout << "|                                                       User                                                     |" << endl;
                    cout << "+================================================================================================================+\n";
                    cout << "Form Perizinan Anda telah diperiksa" << endl;
                    cout << " Nama UMKM      : " << temp2->nama_umkm << endl;
                    cout << " Jenis UMKM     : " << temp2->jenis_umkm << endl;
                    cout << " Nama Pemilik   : " << temp2->nama_pemilik << endl;
                    cout << " Kriteria       : " << temp2->kriteria << endl;
                    cout << " Tanggal        : " << temp2->tanggal << endl;
                    cout << " Status         : " << temp2->status << endl;
                    // jika status sama dengan disetujui maka hanya terdapat menu keluar
                    if (temp2->status == "Disetujui")
                    {
                        cout << "+================================================================================================================+\n";
                        cout << "|                                            [0] Keluar                                                          |" << endl;
                        cout << "+================================================================================================================+\n";
                        cout << " Masukan Pilihan : ";
                        cin >> op;
                        cout << "+================================================================================================================+\n";
                        if (op == "0")
                        {
                            isLogout = 1;
                            isFound = 1;
                            break;
                        }
                        else
                        {
                            cout << "Pilihan tidak ada" << endl;
                            sleep(1);
                        }
                    }
                    if (temp2->status == "Ditolak")
                    {
                        cout << "+================================================================================================================+\n";
                        cout << "|                                            [1] Isi Form Perizinan                                              |" << endl;
                        cout << "|                                            [0] Keluar                                                          |" << endl;
                        cout << "+================================================================================================================+\n";
                        cout << " Masukan Pilihan : ";
                        cin >> op;
                        cout << "+================================================================================================================+\n";
                        if (op == "1")
                        {
                            addForm(&Head, id_user);
                            Form2 *temp3 = head2;
                            if (temp2->id_antrian == temp3->id_antrian)
                            {
                                head2 = head2->next;
                            }
                            else
                            {
                                for (int i = temp3->next->id_antrian; i < temp3->id_antrian; i++)
                                {
                                    if (temp3->next != NULL)
                                    {
                                        temp3 = temp3->next;
                                    }
                                }
                                temp3->next = temp3->next->next;
                            }
                            writefile2(Head2);
                            isFound = 1;
                            isDone = 1;
                            cont();
                            break;
                        }
                        else if (op == "0")
                        {
                            isFound = 1;
                            isLogout = 1;
                            break;
                        }
                        else
                        {
                            cout << "Pilihan tidak ada" << endl;
                            sleep(1);
                        }
                    }
                }
                break;
            }
            temp2 = temp2->next;
            if (isDone == 1)
            {
                break;
            }
        }
        if (isFound != 1)
        {
            while (true)
            {
                // membersihkan layar terminal.
                // menampilkan menu user ketika belum mengisi form.
                // user diminta memasukkan inputan berdasarkan menu yang tersedia.
                system("cls");
                cout << "+================================================================================================================+\n";
                cout << "|                                         SISTEM PENDATAAN DAN PERIZINAN UMKM                                    |" << endl;
                cout << "|----------------------------------------------------------------------------------------------------------------|" << endl;
                cout << "|                                                       User                                                     |" << endl;
                cout << "+================================================================================================================+\n";
                cout << "|                                            [1] Isi Form Perizinan                                              |" << endl;
                cout << "|                                            [0] Keluar                                                          |" << endl;
                cout << "+================================================================================================================+\n";
                cout << " Masukan Pilihan : ";
                cin >> op;
                cout << "+================================================================================================================+\n";
                // jika pilihan sama dengan 1 maka akan dilanjutkan ke fungsi addForm. User akan mengisi form
                if (op == "1")
                {
                    addForm(&Head, id_user);
                    isFound = 1;
                    cout << temp << endl;
                    cont();
                    break;
                }
                else if (op == "0")
                {
                    isLogout = 1;
                    break;
                }
                else
                {
                    cout << "Pilihan tidak ada" << endl;
                    sleep(1);
                }
                // if (temp->next == 0)
                // {
                //     break;
                // }
            }
        }
        if (isLogout == 1)
        {
            break;
        }
    }
}

int main()
{
    // memasukkan data dari csv ke dalam struct
    readfile(&Head);
    readfile2(&Head2);
    readfileuser(&Headuser);
    while (true)
    {
        // membersihkan layar terminal.
        // menampilkan menu regis, login dan keluar.
        // user diminta memasukkan pilihan berdasarkan menu.
        system("cls");
        cout << "+================================================================================================================+\n";
        cout << "|                                         SISTEM PENDATAAN DAN PERIZINAN UMKM                                    |" << endl;
        cout << "+================================================================================================================+\n";
        cout << "|                                                [1] Registrasi                                                  |" << endl;
        cout << "|                                                [2] Login                                                       |" << endl;
        cout << "|                                                [0] Keluar                                                      |" << endl;
        cout << "+================================================================================================================+\n";
        cout << " Masukan Pilihan : ";
        cin >> op;
        cout << "+================================================================================================================+\n";
        // jika pilihan sama dengan 1, maka akan lanjut ke registrasi
        if (op == "1")
        {
            registrasi(&Headuser, Headuser);
        }
        // jika pilihan sama dengan 2, maka akan lanjut ke login
        else if (op == "2")
        {
            login(Headuser);
        }
        // jika pilihan sama dengan 0, maka akan keluar dari program.
        else if (op == "0")
        {
            cout << "Keluar dari program." << endl;
            break;
        }
        // jika selain dari pilihan di atas maka akan menampilkan pesan pilihan tidak ada
        // kemudian diberi jeda 1 detik untuk lanjut ke berikutnya.
        else
        {
            cout << "Pilihan tidak ada. Silakan coba lagi." << endl;
            sleep(1);
        }
    }
    return 0;
}