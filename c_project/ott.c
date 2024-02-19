#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// User structure to store subscription information
typedef struct {
    bool isSubscribed;
    int subscriptionLevel;  // 0: Free, 1: Basic, 2: Premium
    char activationCode[50]; // Activation code (number or email)
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
        printf("Activation Code: %s\n", user.activationCode);
    } else {
        printf("No subscription.\n");
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
    printf("1. Basic Plan (Rs%d)\n", app->priceBasic);
    printf("2. Premium Plan (Rs%d)\n", app->pricePremium);
    printf("Enter your choice: ");
    scanf("%d", &choice);

      // Ask for activation (number or email)
    printf("Enter your activation (number or email): ");
    scanf("%s", user->activationCode);
    int p;
    printf("enter wallet password to pay:");
    scanf("%d",&p);
     printf("payment done via wallet\n");



    if (choice == 1) {
        user->isSubscribed = true;
        user->subscriptionLevel = 1;

	 printf("subscription activated successfully\n");
	 printf("You have subscribed to the Basic Plan for %s. Enjoy streaming!\n", app->name);
    } else if (choice == 2) {
        user->isSubscribed = true;
        user->subscriptionLevel = 2;
	 printf("subscription activated successfully\n");

         printf("You have subscribed to the Premium Plan for %s. Enjoy premium content!\n", app->name);
    } else {
        printf("Invalid choice. Subscription not processed.\n");
        return;
    }

   
}

int main() {
    User user;
    user.isSubscribed = false;  // Initialize as not subscribed
    user.subscriptionLevel = 0;  // Initialize as Free
    strcpy(user.activationCode, ""); // Initialize activation code as an empty string

    App apps[2];  // Define an array to store app information for multiple apps

    strcpy(apps[0].name, "Netflix");
    apps[0].priceBasic = 199;   // Set Basic plan price
    apps[0].pricePremium = 399; // Set Premium plan price

    strcpy(apps[1].name, "Amazon Prime Video");
    apps[1].priceBasic = 149;    // Set Basic plan price
    apps[1].pricePremium = 299;  // Set Premium plan price



    int appChoice=0;

    do {
        printf("\nOTT App Subscription Management:\n");
        printf("Select an OTT app:\n");
        printf("1. Netflix\n");
        printf("2. Amazon Prime Video\n");
        printf("3. Display Subscription Status\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &appChoice);

        switch (appChoice) {
            case 1:
                manageSubscription(&user, &apps[0]);
                break;
            case 2:
                manageSubscription(&user, &apps[1]);
                break;
            case 3:
                displaySubscription(user);
                break;
            case 4:
                printf("Exiting the subscription management system. Thank you!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
	appChoice+=1;
    } while (appChoice < 1);

    return 0;
}

