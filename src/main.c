#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
  int id;
  char name[50];
  float price;
} Product;


void choice() {
  printf("------------------------------\n");
  printf("|       1- REGISTER ITEM     |\n");
  printf("|       2- BUY ITEMS         |\n");
  printf("|       3- CART              |\n");
  printf("|       0- GO OUT            |\n");
  printf("------------------------------\n");
}


int registerItem() {
  FILE *data;
  data = fopen("items.txt", "a");

  Product *products = malloc(sizeof(Product));
  char yes_no;
  int qty_items;

  printf("Insert the product ID: ");
  scanf("%i", &products->id);
  
  printf("Insert the product name: ");  
  scanf("%s", products->name);

  printf("Insert the product price: ");
  scanf("%f", &products->price);

  printf("Product registered. Do you want register more items? (y/n)");
  scanf(" %c", &yes_no);
  fprintf(data, "ID: %i | Product Name: %s | Price: %.2f\n", products->id, products->name, products->price);

  while (1)
  {
    if (yes_no == 'y') 
    {
      printf("How many items do you want to register?");
      scanf("%i", &qty_items);
  
      products = realloc(products, qty_items * sizeof(Product));
  
      for (int i = 0; i < qty_items; i++) 
      {
        printf("Insert the product ID: ");
        scanf("%i", &products[i].id);
        
        printf("Insert the product name: ");
        scanf("%s", products[i].name);
  
        printf("Insert the product price: ");
        scanf("%f", &products[i].price);
  
        printf("Product registered.");
        fprintf(data, "ID: %i | Product Name: %s | Price: %.2f\n", products->id, products->name, products->price);
      }
    }
    else
      break;
    fclose(data);
  }
  return 0;
}


void printItems() 
{
  FILE *data;
  data = fopen("items.txt", "r");

  FILE * cart;
  cart = fopen("cart.txt", "w");

  char c;
  int id_buy;
  int found = 0;
  Product product;
  
  while ((c = fgetc(data)) != EOF) {
    printf("%c", c);
  }

  printf("Enter the ID of the item you want: ");
  scanf("%i", &id_buy);

  while(fscanf(data, "%i %s %f", &product.id, product.name, &product.price) != EOF)
  {
    if(id_buy == product.id)
    {
        printf("Item added to your cart.");
        fprintf(cart, "ID: %i | Product Name: %s | Price: %f", product.id, product.name, product.price);
        found = 1;
    }
  }

  if (found == 0)
    printf("Item not found.\n");
  
  fclose(data);
  fclose(cart);
}


int main() 
{
  int user_choice;

  for (;;) {
    
    choice();
    scanf("%i", &user_choice);
    
    switch (user_choice) {
    case 1:
      registerItem();
      break;
    case 2:
      printItems();
      break;
    case 3:
      break;
    case 0:
      return 0;
      break;
    }
  }
}
