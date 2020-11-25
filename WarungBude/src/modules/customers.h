#ifndef MOD_CUSTOMER_H
#define MOD_CUSTOMER_H

struct CustomerOrder {
    char *name;
    int quantity;
    int price_per_quantity;
    CustomerOrder *next;
};

struct CustomerNode {
    char *name;
    CustomerOrder *order;
    CustomerNode *next;
};

void buatPelangganBaru();
void lihatSeluruhDataPelanggan();
void cariDataPelanggan();

void buatOrderanBaru();
void lakukanPembayaran();

void freeCustomerNode();

#endif /* MOD_CUSTOMER_H */