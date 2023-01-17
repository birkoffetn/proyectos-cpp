#ifndef __RECORDS__HPP__
#define __RECORDS__HPP__

#define SIZE_CODE 12
#define SIZE_NAME 30
#define SIZE_TYPE 30

struct Product
{
    int id;
    char code[SIZE_CODE];
    char name[SIZE_NAME];
    int stock;
    double cost, price;
    char type[SIZE_TYPE];
};

#endif