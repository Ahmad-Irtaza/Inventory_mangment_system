#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTS 100
#define MAX_NAME_LENGTH 50

void addProduct(char names[][MAX_NAME_LENGTH], int ids[], float prices[], int stocks[], int *numProducts);
void updateStock(int ids[], int stocks[], int numProducts);
void displayProducts(char names[][MAX_NAME_LENGTH], int ids[], float prices[], int stocks[], int numProducts);
void searchProduct(char names[][MAX_NAME_LENGTH], int ids[], float prices[], int stocks[], int numProducts, const char *name);
void removeProduct(char names[][MAX_NAME_LENGTH], int ids[], float prices[], int stocks[], int *numProducts);
void calculateTotalValue(float prices[], int stocks[], int numProducts);

int main() {
    char names[MAX_PRODUCTS][MAX_NAME_LENGTH];
    int ids[MAX_PRODUCTS];
    float prices[MAX_PRODUCTS];
    int stocks[MAX_PRODUCTS];
    int numProducts = 0;
    int choice;

    do {
        printf("\nInventory Control System\n");
        printf("1. Add Product\n");
        printf("2. Update Stock\n");
        printf("3. Display Products\n");
        printf("4. Search Product\n");
        printf("5. Remove Product\n");
        printf("6. Calculate Total Value\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addProduct(names, ids, prices, stocks, &numProducts);
                break;
            case 2:
                updateStock(ids, stocks, numProducts);
                break;
            case 3:
                displayProducts(names, ids, prices, stocks, numProducts);
                break;
            case 4: {
                char name[MAX_NAME_LENGTH];
                printf("Enter the product name to search: ");
                scanf("%s", name);
                searchProduct(names, ids, prices, stocks, numProducts, name);
                break;
            }
            case 5:
                removeProduct(names, ids, prices, stocks, &numProducts);
                break;
            case 6:
                calculateTotalValue(prices, stocks, numProducts);
                break;
            case 7:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);

    return 0;
}

void addProduct(char names[][MAX_NAME_LENGTH], int ids[], float prices[], int stocks[], int *numProducts) {
    if (*numProducts == MAX_PRODUCTS) {
        printf("Inventory is full. Cannot add more products.\n");
        return;
    }

    printf("Enter Product Name: ");
    scanf("%s", names[*numProducts]);
    printf("Enter Product ID: ");
    scanf("%d", &ids[*numProducts]);
    printf("Enter Product Price: ");
    scanf("%f", &prices[*numProducts]);
    printf("Enter Initial Stock Level: ");
    scanf("%d", &stocks[*numProducts]);

    (*numProducts)++;

    printf("Product added successfully.\n");
}

void updateStock(int ids[], int stocks[], int numProducts) {
    int id, quantity;
    printf("Enter Product ID to update stock: ");
    scanf("%d", &id);

    int found = 0;
    for (int i = 0; i < numProducts; i++) {
        if (ids[i] == id) {
            printf("Enter quantity to add/subtract: ");
            scanf("%d", &quantity);

            stocks[i] += quantity;
            printf("Stock updated successfully. New stock level: %d\n", stocks[i]);

            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Product not found.\n");
    }
}

void displayProducts(char names[][MAX_NAME_LENGTH], int ids[], float prices[], int stocks[], int numProducts) {
    printf("\nProduct List:\n");
    printf("-----------------------------------------------------------\n");
    printf("ID\tName\t\tPrice\tStock\n");
    printf("-----------------------------------------------------------\n");

    for (int i = 0; i < numProducts; i++) {
        printf("%d\t%s\t\t%.2f\t%d\n", ids[i], names[i], prices[i], stocks[i]);
    }
}

void searchProduct(char names[][MAX_NAME_LENGTH], int ids[], float prices[], int stocks[], int numProducts, const char *name) {
    int found = 0;

    printf("\nSearch Results:\n");
    printf("-----------------------------------------------------------\n");
    printf("ID\tName\t\tPrice\tStock\n");
    printf("-----------------------------------------------------------\n");

    for (int i = 0; i < numProducts; i++) {
        if (strcmp(names[i], name) == 0) {
            printf("%d\t%s\t\t%.2f\t%d\n", ids[i], names[i], prices[i], stocks[i]);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Product not found.\n");
    }
}

void removeProduct(char names[][MAX_NAME_LENGTH], int ids[], float prices[], int stocks[], int *numProducts) {
    int id;
    printf("Enter Product ID to remove: ");
    scanf("%d", &id);

    int found = 0;
    for (int i = 0; i < *numProducts; i++) {
        if (ids[i] == id) {
            for (int j = i; j < *numProducts - 1; j++) {
                strcpy(names[j], names[j + 1]);
                ids[j] = ids[j + 1];
                prices[j] = prices[j + 1];
                stocks[j] = stocks[j + 1];
            }

            (*numProducts)--;

            printf("Product removed successfully.\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Product not found.\n");
    }
}

void calculateTotalValue(float prices[], int stocks[], int numProducts) {
    float totalValue = 0;

    for (int i = 0; i < numProducts; i++) {
        totalValue += prices[i] * stocks[i];
    }

    printf("Total Inventory Value: %.2f\n", totalValue);
}
