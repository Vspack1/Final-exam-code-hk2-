#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

struct NhanVien {
    string MaSo;
    string HoTen;
    bool GioiTinh; // 1: Nam, 0: Nu
    double Luong;
};

void ChuanHoaTen(string &ten) {
    for (int i = 0; i < ten.length(); ++i)
        ten[i] = tolower(ten[i]);
    bool vietHoa = true;
    for (int i = 0; i < ten.length(); ++i) {
        if (vietHoa && ten[i] >= 'a' && ten[i] <= 'z')
            ten[i] -= 32;
        vietHoa = (ten[i] == ' ');
    }
}

void DocDuLieu(NhanVien nv[], int &n) {
    ifstream file("data.txt");
    n = 0;
    while (file >> nv[n].MaSo) {
        file.ignore(); // bỏ khoảng trắng
        getline(file, nv[n].HoTen);
        string gioi;
        file >> gioi >> nv[n].Luong;
        nv[n].GioiTinh = (gioi == "Nam");
        ++n;
    }
    file.close();
    for (int i = 0; i < n; ++i)
        ChuanHoaTen(nv[i].HoTen);
}

void SapXepTheoLuong(NhanVien nv[], int n) {
    for (int i = 0; i < n - 1; ++i)
        for (int j = i + 1; j < n; ++j)
            if (nv[i].Luong > nv[j].Luong)
                swap(nv[i], nv[j]);
}

void HienThiDanhSach(NhanVien nv[], int n) {
    cout << left << setw(10) << "Ma so"
         << setw(25) << "Ho ten"
         << setw(10) << "Gioi tinh"
         << setw(10) << "Luong" << endl;
    for (int i = 0; i < n; ++i) {
        cout << setw(10) << nv[i].MaSo
             << setw(25) << nv[i].HoTen
             << setw(10) << (nv[i].GioiTinh ? "Nam" : "Nu")
             << fixed << setprecision(0) << nv[i].Luong << endl;
    }
}

void HienThiTheoGioi(NhanVien nv[], int n, bool gioiTinh) {
    for (int i = 0; i < n; ++i)
        if (nv[i].GioiTinh == gioiTinh) {
            cout << setw(10) << nv[i].MaSo
                 << setw(25) << nv[i].HoTen
                 << setw(10) << (nv[i].GioiTinh ? "Nam" : "Nu")
                 << fixed << setprecision(0) << nv[i].Luong << endl;
        }
}

void XoaTheoLuong(NhanVien nv[], int &n, double mucLuong) {
    int k = 0;
    for (int i = 0; i < n; ++i)
        if (nv[i].Luong != mucLuong)
            nv[k++] = nv[i];
    n = k;
}

int main() {
    NhanVien nv[100];
    int n;
    DocDuLieu(nv, n);
    SapXepTheoLuong(nv, n);

    cout << "\n1. Danh sach tang dan theo luong:\n";
    HienThiDanhSach(nv, n);

    cout << "\n2. Danh sach NHAN VIEN NAM theo luong tang dan:\n";
    HienThiTheoGioi(nv, n, 1);

    cout << "\n2. Danh sach NHAN VIEN NU theo luong tang dan:\n";
    HienThiTheoGioi(nv, n, 0);

    double luongXoa;
    cout << "\n3. Nhap muc luong muon xoa: ";
    cin >> luongXoa;
    XoaTheoLuong(nv, n, luongXoa);
    SapXepTheoLuong(nv, n);

    cout << "\nDanh sach sau khi xoa:\n";
    HienThiDanhSach(nv, n);

    return 0;
}
