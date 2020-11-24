#ifndef MOD_CUSTOMER_H
#define MOD_CUSTOMER_H

struct CustomerOrder {
    char *name;
    int quantity;
    int price_per_quantity;
    CustomerOrder *next;
};

void buatPelangganBaru();
void lihatSeluruhDataPelanggan();
void cariDataPelanggan();

void freeCustomerNode();

#endif /* MOD_CUSTOMER_H */