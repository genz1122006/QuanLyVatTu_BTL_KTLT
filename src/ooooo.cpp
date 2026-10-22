#include <iostream>
#include "Entity.h"
#include "VatTu.h"
#include "PhieuNhap.h"
#include "Repository.h"

int main() {
    Repository<VatTu> repoVatTu("data/vattu.txt");
    Repository<PhieuNhap> repoPhieuNhap("data/phieunhap.txt");

    int choice = 0;
    do {
        std::cout << "\n========================================\n";
        std::cout << "QUAN LY VAT TU & PHIEU NHAP KHO\n";
        std::cout << "========================================\n";
        std::cout << "1. Xem danh muc vat tu\n";
        std::cout << "2. Them vat tu moi\n";
        std::cout << "3. Xem danh sach phieu nhap kho\n";
        std::cout << "4. Tao phieu nhap kho moi\n";
        std::cout << "0. Thoat\n";
        std::cout << "Lua chon cua ban: ";

        if (!(std::cin >> choice)) {
            std::cout << "Loi nhap lieu! Vui long nhap so.\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        try {
            if (choice == 1) {
                std::cout << "\n--- DANH MUC VAT TU ---\n";
                for (const auto& vt : repoVatTu.getAll()) {
                    vt.hienThi();
                }
            }
            else if (choice == 2) {
                std::string ma, ten, dvt;
                int sl;
                std::cout << "Nhap ma vat tu: "; std::cin >> ma;
                std::cin.ignore();
                std::cout << "Nhap ten vat tu: "; std::getline(std::cin, ten);
                std::cout << "Nhap don vi tinh: "; std::cin >> dvt;
                std::cout << "Nhap so luong ton ban dau: "; std::cin >> sl;

                VatTu vt(ma, ten, dvt, sl);
                repoVatTu.add(vt);
                std::cout << "Them vat tu thanh cong!\n";
            }
            else if (choice == 3) {
                std::cout << "\n--- DANH SACH PHIEU NHAP KHO ---\n";
                for (const auto& pn : repoPhieuNhap.getAll()) {
                    pn.hienThi();
                }
            }
            else if (choice == 4) {
                std::string maP, ngay, maVT;
                int sl;
                double dg;
                std::cout << "Nhap ma phieu nhap: "; std::cin >> maP;
                std::cout << "Nhap ngay nhap (dd/mm/yyyy): "; std::cin >> ngay;
                std::cout << "Nhap ma vat tu can nhap: "; std::cin >> maVT;

                if (repoVatTu.findById(maVT) == nullptr) {
                    std::cout << "Loi: Ma vat tu khong ton tai trong danh muc!\n";
                    continue;
                }

                std::cout << "Nhap so luong nhap: "; std::cin >> sl;
                std::cout << "Nhap don gia: "; std::cin >> dg;

                PhieuNhap pn(maP, ngay, maVT, sl, dg);
                repoPhieuNhap.add(pn);

                VatTu* vt = repoVatTu.findById(maVT);
                if (vt != nullptr) {
                    vt->setSoLuongTon(vt->getSoLuongTon() + sl);
                    repoVatTu.saveToFile();
                }
                std::cout << "Tao phieu nhap va cap nhat kho thanh cong!\n";
            }
        }
        catch (const std::exception& e) {
            std::cout << "Loi ngoai le: " << e.what() << "\n";
        }

    } while (choice != 0);

    return 0;
}