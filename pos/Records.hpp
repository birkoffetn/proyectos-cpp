#ifndef __RECORDS__HPP__
#define __RECORDS__HPP__

#define SIZE_CODE 12
#define SIZE_NAME 30
#define SIZE_TYPE 30

#include "Crud.hpp"

struct Product
{
    int id;
    int barcode;
    char name[SIZE_NAME];
    int stock;
    double cost, price;
    char type[SIZE_TYPE];
};

class ProductRecord : public Crud<int, Product>
{
public:
    ProductRecord() : Crud("productos.dat") {}

protected:
    bool addData(const Product &product, std::streampos pos) override;
    bool barcodeRead(int barcode, Product &product);

private:
    std::map<int, std::streampos> dict;
};

#endif