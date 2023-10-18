#include <stdio.h>
#include <stdlib.h>

int main();
void choice();
int registerItem();

typedef struct {
  char name[50];
  float price;
} Product;

void choice() {
  printf("------------------------------");
  printf("|       1- REGISTER ITEM     |");
  printf("|       2- ITEMS             |");
  printf("|       3- CART              |");
  printf("|       0- GO OUT            |");
  printf("------------------------------");
}

int registerItem() {
  FILE *data;
  data = fopen("items.txt", "a");

  Product *products = malloc(sizeof(Product));
  char yes_no;
  int qty_items;

  printf("Insert the product name: ");
  scanf("%s", products->name);

  printf("Insert the product price: ");
  scanf("%f", &products->price);

  printf("Product registered. Do you want register more items? (y/n)");
  scanf("%c", &yes_no);
  fprintf(data, "Product Name: %s | Price: %.2f\n", products->name,
          products->price);

  if (yes_no == 'y') {
    printf("How many items do you want to register?");
    scanf("%i", &qty_items);

    products = realloc(products, qty_items * sizeof(Product));

    for (int i = 0; i < qty_items; i++) {
      printf("Insert the product name: ");
      scanf("%s", products[i].name);

      printf("Insert the product price: ");
      scanf("%f", &products[i].price);

      printf("Product registered.");
      fprintf(data, "Product Name: %s | Price: %.2f\n", products[i].name, products[i].price);
    }
  }
  fclose(data);
  return 0;
}

void printItems() {
  FILE *data;
  data = fopen("items.txt", "r");

  char c;
  while ((c = fgetc(data)) != EOF) {
    printf("%c", c);
  }

  fclose(data);
}

int main() {
  int user_choice;

  for (;;) {
    choice();
    scanf("%i", &user_choice);
    switch (user_choice) {
    case 1:
      registerItem();
    case 2:

    case 3:

    case 0:
      break;
    }
  }
}