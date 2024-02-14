#include <stdio.h>
#include <stdbool.h>

// User structure to store subscription information
typedef struct {
    bool isSubscribed;
    int subscriptionLevel;  // 0: Free, 1: Basic, 2: Premium
} User;

// App structure to store app information
typedef struct {
    char name[50];
    int priceBasic;
    int pricePremium;
} App;

// Function to display user subscription status
void displaySubscription(User user) {
    printf("Subscription Status:\n");
    if (user.isSubscribed) {
        printf("You are subscribed to the %s subscription.\n", user.subscriptionLevel == 1 ? "Basic" : "Premium");
    } else {
        printf("You are using the Free subscription.\n");
    }
}

// Function to manage app subscription
void manageSubscription(User *user, App *app) {
    if (user->isSubscribed) {
        printf("You are already subscribed. Please cancel your current subscription first.\n");
        return;
    }

    int choice;
    printf("Select a subscription plan for %s:\n", app->name);
    printf("1. Basic Plan ($%d)\n", app->priceBasic);
    printf("2. Premium Plan ($%d)\n", app->pricePremium);
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        user->isSubscribed = true;
        user->subscriptionLevel = 1;
        printf("You have subscribed to the Basic Plan for %s. Enjoy streaming!\n", app->name);
    } else if (choice == 2) {
        user->isSubscribed = true;
        user->subscriptionLevel = 2;
        printf("You have subscribed to the Premium Plan for %s. Enjoy premium content!\n", app->name);
    } else {
        printf("Invalid choice. Subscription not processed.\n");
    }
}

int main() {
    User user;
    user.isSubscribed = false;  // Initialize as not subscribed
    user.subscriptionLevel = 0;  // Initialize as Free

    App netflix;
    strcpy(netflix.name, "Netflix");
    netflix.priceBasic = 10;   // Set Basic plan price
    netflix.pricePremium = 15; // Set Premium plan price

    App amazonPrime;
    strcpy(amazonPrime.name, "Amazon Prime Video");
    amazonPrime.priceBasic = 8;   // Set Basic plan price
    amazonPrime.pricePremium = 12; // Set Premium plan price

    int choice;

    do {
        printf("\nOTT App Subscription Management:\n");
        printf("1. Display Subscription Status\n");
        printf("2. Manage Netflix Subscription\n");
        printf("3. Manage Amazon Prime Video Subscription\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displaySubscription(user);
                break;
            case 2:
                manageSubscription(&user, &netflix);
                break;
            case 3:
                manageSubscription(&user, &amazonPrime);
                break;
            case 4:
                printf("Exiting the subscription management system. Thank you!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}

