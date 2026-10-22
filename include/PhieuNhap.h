#ifndef PHIEU_NHAP_H
#define PHIEU_NHAP_H

#include "Entity.h"
#include <sstream>
#include <iomanip>

class PhieuNhap : public Entity {
private:
    std::string maPhieu;
    std::string ngayNhap;
    std::string maVatTuNhap;
    int soLuongNhap;
    double donGia;

public:
    PhieuNhap() : maPhieu(""), ngayNhap(""), maVatTuNhap(""), soLuongNhap(0), donGia(0.0) {}

    PhieuNhap(std::string maP, std::string ngay, std::string maVT, int sl, double dg)
        : maPhieu(maP), ngayNhap(ngay), maVatTuNhap(maVT), soLuongNhap(sl), donGia(dg) {}

    std::string getId() const override { return maPhieu; }
    std::string getMaVatTuNhap() const { return maVatTuNhap; }
    int getSoLuongNhap() const { return soLuongNhap; }

    void hienThi() const override {
        std::cout << std::left << std::setw(12) << maPhieu
            << std::setw(15) << ngayNhap
            << std::setw(12) << maVatTuNhap
            << std::setw(10) << soLuongNhap
            << std::setw(15) << donGia << "\n";
    }

    std::string serialize() const override {
        return maPhieu + "|" + ngayNhap + "|" + maVatTuNhap + "|" + std::to_string(soLuongNhap) + "|" + std::to_string(donGia);
    }

    void deserialize(const std::string& line) override {
        std::stringstream ss(line);
        std::string slStr, dgStr;
        std::getline(ss, maPhieu, '|');
        std::getline(ss, ngayNhap, '|');
        std::getline(ss, maVatTuNhap, '|');
        std::getline(ss, slStr, '|');
        std::getline(ss, dgStr, '|');
        if (!slStr.empty()) soLuongNhap = std::stoi(slStr);
        if (!dgStr.empty()) donGia = std::stod(dgStr);
    }
};

#endif