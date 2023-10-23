#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int id;
  char name[50];
  float price;
} Product;


void choice() {
  printf("\n------------------------------\n");
  printf("|       1- REGISTER ITEM     |\n");
  printf("|       2- BUY ITEMS         |\n");
  printf("|       3- CART              |\n");  
  printf("|       4- PAY               |\n");
  printf("|       0- GO OUT            |\n");
  printf("------------------------------\n");
}


int registerItem() {
  FILE *data;
  data = fopen("items.txt", "a");

  Product *products = malloc(sizeof(Product));
  char yes_no;
  int qty_items;

  printf("\nInsert the product ID: ");
  scanf("%i", &products->id);

  printf("\nInsert the product name: ");
  scanf("%s", products->name);

  printf("\nInsert the product price: ");
  scanf("%f", &products->price);

  printf("\nProduct registered. Do you want register more items? (y/n)\n");
  scanf(" %c", &yes_no);
  fprintf(data, "ID: %i | Product Name: %s | Price: %.2f\n", products->id,
          products->name, products->price);

  while (1) {
    if (yes_no == 'y') {
      printf("\nHow many items do you want to register? ");
      scanf("%i", &qty_items);

      products = realloc(products, qty_items * sizeof(Product));

      for (int i = 0; i < qty_items; i++) {
        printf("\nInsert the product ID: ");
        scanf("%i", &products[i].id);

        printf("\nInsert the product name: ");
        scanf("%s", products[i].name);

        printf("\nInsert the product price: ");
        scanf("%f", &products[i].price);

        printf("\nProduct registered.");
        fprintf(data, "ID: %i | Product Name: %s | Price: %.2f\n", products[i].id,
                products[i].name, products[i].price);
      }
    } else
      break;
    fclose(data);
  }
  return 0;
  free(products);
}


void printItems() {
  FILE *data;
  data = fopen("items.txt", "r");

  FILE *cart;
  cart = fopen("cart.txt", "w");

  char c;
  int id_buy;
  int found = 0;
  Product product;
  char yes_no;

  while ((c = fgetc(data)) != EOF) {
    printf("%c", c);
  }

  printf("\n\nEnter the ID of the item you want: ");
  scanf("%i", &id_buy);

  rewind(data);

  while (fscanf(data, "ID: %i | Product Name: %s | Price: %f\n", &product.id,
                product.name, &product.price) != EOF) {

    if (id_buy == product.id) {
      printf("Item added to your cart. ");
      fprintf(cart, "ID: %i | Product Name: %s | Price: %.2f\n", product.id,
              product.name, product.price);
      found = 1;

      printf("Do you want to buy any more items? (y/n)\n");
      scanf(" %c", &yes_no);

      if (yes_no == 'y') {
        rewind(data);
        printf("Enter the ID of the item you want: ");
        scanf("%i", &id_buy);
      } else
        break;
    }
  }

  if (found == 0)
    printf("Item not found.\n");

  fclose(data);
  fclose(cart);
}


void printCart()
{
  FILE *cart;
  cart = fopen("cart.txt", "r");

  char c;
  float total_cart = 0;
  Product products_cart;

  printf("This is your cart:\n\n");
  
  while ((c = fgetc(cart)) != EOF) {
    printf("%c", c);
  }

  rewind(cart);
  
  while (fscanf(cart, "ID: %i | Product Name: %s | Price: %f\n", &products_cart.id, products_cart.name, &products_cart.price) != EOF) 
  {
      total_cart += products_cart.price;
  }
  printf("\nTotal: %.2f", total_cart);
  fclose(cart);
}



void pay() 
{
  FILE *cart;
  cart = fopen("cart.txt", "r");
  
  float user_pay;
  float change;
  float total_cart;
  Product products_cart;
  
  while (fscanf(cart, "ID: %i | Product Name: %s | Price: %f\n", &products_cart.id, products_cart.name, &products_cart.price) != EOF) 
  {
      total_cart += products_cart.price;
  }

  printf("\nTotal: %.2f", total_cart);

  while(1)
  {
    
    printf("\nInsert the amount you use to pay: $");
    scanf("%f", &user_pay);
  
    if (user_pay > total_cart)
    {
      change = user_pay - total_cart;
      printf("Thank you for your purchase. Your change is $%.2f", change);
      break; 
    } 
    else if (user_pay < total_cart)
    {
      printf("You don't have enough money. Try again");
    } else
    {
      printf("Thank you for your purchase.");
      break;
    }
  }
  fclose(cart);
}




int main() 
{  
  int user_choice;
  int password;
  char user[5];
  
  for (;;) {

    choice();
    scanf("%i", &user_choice);

    switch (user_choice) {
    case 1:
      printf("User: ");
      scanf("%s", user);
      
      if (strcmp(user, "admin") == 0) 
      {
        printf("Password: ");
        scanf("%i", &password);
        
        if (password == 123)
          registerItem();
        else 
          printf("Wrong password. Try again.");
          continue;
        
      } else
        printf("Wrong user. Try again.");
        continue;
    case 2:
      printItems();
      break;
    case 3:
      printCart();
      break;
    case 4:
      pay();  
    case 0:
      return 0;
      break;
    }
  }
}
