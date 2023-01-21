#include "Records.hpp"

#include <fstream>
#include <cassert>

bool ProductRecord::addData(const Product &product, std::streampos pos)
{
    auto it = dict.insert(std::make_pair(product.barcode, pos));
    return it.second;
}

bool ProductRecord::barcodeRead(int barcode, Product &product)
{
    auto it = dict.find(barcode);
    if (it == dict.end())
    {
        return false;
    }
    std::ifstream in(fileName(), std::ios::binary);
    assert(in.is_open());
    in.seekg(it->second);
    in.read((char *)&product, sizeof(Product));
    return true;
}