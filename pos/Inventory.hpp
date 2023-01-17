#ifndef __INVENTORY__HPP__
#define __INVENTORY__HPP__

#include "Records.hpp"
#include "Crud.hpp"

class ProductRecord : public Crud<int, Product>
{
public:
    ProductRecord() : file("data/productos.bin")
    {
        makeIndex();
    }
    const std::string &fileName() const override { return file; }

private:
    std::string file;
};

class Inventory
{
public:
    Inventory();

private:
    ProductRecord products;
};

#endif