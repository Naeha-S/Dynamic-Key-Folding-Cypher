#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 1000
#define MIN_ASCII 32
#define MAX_ASCII 126
#define ASCII_RANGE (MAX_ASCII - MIN_ASCII + 1)

// Function prototypes
void generateKey(int* key, int length);
void substitute(char* text, const int* key, int length, int encrypt);
void foldAndShuffle(char* text, int length, int encrypt);
void encrypt(char* text);
void decrypt(char* text);
void clearInputBuffer();

int main() {
    char text[MAX_LENGTH];
    int choice;

    while (1) {
        // Clear the screen (works in Windows)
        system("cls");

        printf("Dynamic Key Folding Cipher\n");
        printf("==========================\n");
        printf("1. Encrypt a message\n");
        printf("2. Decrypt a message\n");
        printf("3. Exit\n");
        printf("\nEnter your choice (1-3): ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please try again.\n");
            clearInputBuffer();
            system("pause");
            continue;
        }
        clearInputBuffer();

        if (choice == 3) {
            printf("\nGoodbye!\n");
            break;
        }

        if (choice != 1 && choice != 2) {
            printf("Invalid choice. Please try again.\n");
            system("pause");
            continue;
        }

        printf("\nEnter the %s (max %d characters): ",
               (choice == 1) ? "message to encrypt" : "message to decrypt",
               MAX_LENGTH - 1);

        if (fgets(text, MAX_LENGTH, stdin) == NULL) {
            printf("Error reading input.\n");
            system("pause");
            continue;
        }

        // Remove trailing newline if present
        size_t len = strlen(text);
        if (len > 0 && text[len-1] == '\n') {
            text[len-1] = '\0';
            len--;
        }

        if (len == 0) {
            printf("Message cannot be empty.\n");
            system("pause");
            continue;
        }

        if (choice == 1) {
            encrypt(text);
            printf("\nEncrypted message: %s\n", text);
        } else {
            decrypt(text);
            printf("\nDecrypted message: %s\n", text);
        }

        printf("\nPress any key to continue...");
        system("pause >nul");
    }

    return 0;
}

void generateKey(int* key, int length) {
    // Fixed key sequence for consistency
    const int baseKey[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    int baseKeyLength = 10;

    for (int i = 0; i < length; i++) {
        key[i] = baseKey[i % baseKeyLength];
    }
}

void substitute(char* text, const int* key, int length, int encrypt) {
    for (int i = 0; i < length; i++) {
        char c = text[i];
        int shift = key[i];

        if (!encrypt) {
            shift = -shift;
        }

        int val = c - MIN_ASCII;
        val = (val + shift + ASCII_RANGE) % ASCII_RANGE;
        text[i] = (char)(val + MIN_ASCII);
    }
}

void foldAndShuffle(char* text, int length, int encrypt) {
    char temp[MAX_LENGTH];
    strcpy(temp, text);

    // Simple reversal
    for (int i = 0; i < length; i++) {
        text[i] = temp[length - 1 - i];
    }
}

void encrypt(char* text) {
    int length = strlen(text);
    int key[MAX_LENGTH];
    generateKey(key, length);
    substitute(text, key, length, 1);
    foldAndShuffle(text, length, 1);
}

void decrypt(char* text) {
    int length = strlen(text);
    int key[MAX_LENGTH];
    generateKey(key, length);
    foldAndShuffle(text, length, 0);
    substitute(text, key, length, 0);
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
