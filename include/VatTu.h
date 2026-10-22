#ifndef VAT_TU_H
#define VAT_TU_H

#include "Entity.h"
#include <sstream>
#include <iomanip>
#include <stdexcept>

class VatTu : public Entity {
private:
    std::string maVatTu;
    std::string tenVatTu;
    std::string donViTinh;
    int soLuongTon;

public:
    VatTu() : maVatTu(""), tenVatTu(""), donViTinh(""), soLuongTon(0) {}
    VatTu(std::string ma, std::string ten, std::string dvt, int sl)
        : maVatTu(ma), tenVatTu(ten), donViTinh(dvt), soLuongTon(sl) {}

    std::string getId() const override { return maVatTu; }
    std::string getTenVatTu() const { return tenVatTu; }
    int getSoLuongTon() const { return soLuongTon; }

    void setTenVatTu(const std::string& ten) {
        if (ten.empty()) throw std::invalid_argument("Tên vật tư không được để trống!");
        tenVatTu = ten;
    }

    void setSoLuongTon(int sl) {
        if (sl < 0) throw std::out_of_range("Số lượng tồn kho không được âm!");
        soLuongTon = sl;
    }

    void hienThi() const override {
        std::cout << std::left << std::setw(10) << maVatTu
            << std::setw(25) << tenVatTu
            << std::setw(15) << donViTinh
            << std::setw(10) << soLuongTon << "\n";
    }

    std::string serialize() const override {
        return maVatTu + "|" + tenVatTu + "|" + donViTinh + "|" + std::to_string(soLuongTon);
    }

    void deserialize(const std::string& line) override {
        std::stringstream ss(line);
        std::string slStr;
        std::getline(ss, maVatTu, '|');
        std::getline(ss, tenVatTu, '|');
        std::getline(ss, donViTinh, '|');
        std::getline(ss, slStr, '|');
        if (!slStr.empty()) {
            soLuongTon = std::stoi(slStr);
        }
    }
};

#endif