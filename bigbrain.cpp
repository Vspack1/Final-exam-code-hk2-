// Quản lý danh sách nhân viên (nâng cao) - KHÔNG dùng vector
// Dùng các thư viện: iostream, fstream, iomanip, string, cctype, cstdlib

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cctype>
#include <cstdlib>
using namespace std;

const int MAX = 100;

struct NhanVien {
    string maSo;
    string hoTen;
    bool gioiTinh; // 1: Nam, 0: Nu
    double luong;
    string ngaySinh; // dd/mm/yyyy
};

// Viết hoa chữ cái đầu của mỗi từ
string chuanHoaTen(string ten) {
    string kq = "";
    bool vietHoa = true;
    for (int i = 0; i < ten.length(); ++i) {
        if (ten[i] == ' ') {
            vietHoa = true;
            kq += ten[i];
        } else {
            if (vietHoa)
                kq += toupper(ten[i]);
            else
                kq += tolower(ten[i]);
            vietHoa = false;
        }
    }
    return kq;
}

// Đọc file data.txt
int docFile(NhanVien ds[], const char* filename) {
    ifstream fin(filename);
    if (!fin) {
        cout << "Khong mo duoc file!\n";
        return 0;
    }
    int n = 0;
    while (!fin.eof() && n < MAX) {
        fin >> ds[n].maSo;
        fin.ignore();
        getline(fin, ds[n].hoTen);
        fin >> ds[n].gioiTinh >> ds[n].luong >> ds[n].ngaySinh;
        ds[n].hoTen = chuanHoaTen(ds[n].hoTen);
        n++;
    }
    fin.close();
    return n;
}

// Hiển thị danh sách
void hienThi(NhanVien ds[], int n) {
    cout << setw(10) << "Ma so" 
         << setw(25) << "Ho ten" 
         << setw(10) << "Gioi tinh" 
         << setw(12) << "Luong" 
         << setw(15) << "Ngay sinh" << endl;
    for (int i = 0; i < n; ++i) {
        cout << setw(10) << ds[i].maSo
             << setw(25) << ds[i].hoTen
             << setw(10) << (ds[i].gioiTinh ? "Nam" : "Nu")
             << setw(12) << ds[i].luong
             << setw(15) << ds[i].ngaySinh << endl;
    }
}

// Sắp xếp theo lương tăng dần
void sapXepLuong(NhanVien ds[], int n) {
    for (int i = 0; i < n - 1; ++i)
        for (int j = i + 1; j < n; ++j)
            if (ds[i].luong > ds[j].luong)
                swap(ds[i], ds[j]);
}

// Hiển thị nhân viên nữ có lương cao hơn trung bình
void hienThiNuLuongCao(NhanVien ds[], int n) {
    double tong = 0;
    for (int i = 0; i < n; ++i)
        tong += ds[i].luong;
    double tb = tong / n;

    cout << "\nNhan vien nu co luong > trung binh:\n";
    for (int i = 0; i < n; ++i)
        if (!ds[i].gioiTinh && ds[i].luong > tb)
            cout << ds[i].hoTen << " - " << ds[i].luong << endl;
}

// Tìm nhân viên trùng ngày sinh (dd/mm)
void timNgaySinhTrung(NhanVien ds[], int n) {
    cout << "\nNhan vien co ngay sinh trung nhau (dd/mm):\n";
    for (int i = 0; i < n; ++i) {
        string ddmm1 = ds[i].ngaySinh.substr(0, 5);
        for (int j = i + 1; j < n; ++j) {
            string ddmm2 = ds[j].ngaySinh.substr(0, 5);
            if (ddmm1 == ddmm2) {
                cout << ds[i].hoTen << " - " << ds[i].ngaySinh << " | "
                     << ds[j].hoTen << " - " << ds[j].ngaySinh << endl;
            }
        }
    }
}

// Tìm kiếm nhân viên theo từ khóa tên
void timTheoTen(NhanVien ds[], int n, string tuKhoa) {
    cout << "\nTim nhan vien theo tu khoa \"" << tuKhoa << "\":\n";
    for (int i = 0; i < n; ++i)
        if (ds[i].hoTen.find(tuKhoa) != string::npos)
            cout << ds[i].hoTen << endl;
}

// Ghi danh sách ra file
void ghiFile(NhanVien ds[], int n, const char* filename) {
    ofstream fout(filename);
    for (int i = 0; i < n; ++i) {
        fout << ds[i].maSo << " "
             << ds[i].hoTen << " "
             << ds[i].gioiTinh << " "
             << ds[i].luong << " "
             << ds[i].ngaySinh << endl;
    }
    fout.close();
}

int main() {
    NhanVien ds[MAX];
    int n = docFile(ds, "data.txt");

    sapXepLuong(ds, n);
    hienThi(ds, n);
    hienThiNuLuongCao(ds, n);
    timNgaySinhTrung(ds, n);

    string tuKhoa;
    cout << "\nNhap tu khoa tim kiem: ";
    getline(cin, tuKhoa);
    timTheoTen(ds, n, tuKhoa);

    ghiFile(ds, n, "output.txt");

    return 0;
}
