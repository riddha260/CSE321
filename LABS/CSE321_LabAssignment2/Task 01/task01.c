#include <stdio.h>
#include <stdlib.h>
struct FoodItem {
    int qty;
    int price_per_unit; 
};

int main() {
    struct FoodItem paratha, veg, water;
    int num_people;
    int total_cost = 0; 
    float cost_per_person;

    printf("Quantity Of Paratha: ");
    scanf("%d", &paratha.qty);
    printf("Unit Price: ");
    scanf("%d", &paratha.price_per_unit);

    printf("Quantity Of Vegetables: ");
    scanf("%d", &veg.qty);
    printf("Unit Price: ");
    scanf("%d", &veg.price_per_unit);

    printf("Quantity Of Mineral Water: ");
    scanf("%d", &water.qty);
    printf("Unit Price: ");
    scanf("%d", &water.price_per_unit);

    total_cost += paratha.qty * paratha.price_per_unit;
    total_cost += veg.qty * veg.price_per_unit;
    total_cost += water.qty * water.price_per_unit;

    printf("Number of People: ");
    scanf("%d", &num_people);

    cost_per_person = (float)total_cost / num_people; 

    printf("Individual people will pay: %.2f tk\n", cost_per_person);

    return 0;
}
