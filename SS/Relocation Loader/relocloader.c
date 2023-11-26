#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to convert a hexadecimal character to a 4-bit binary string
void convHex(char c, char *str) {
    switch (c) {
        case '0': strcpy(str, "0000"); break;
        case '1': strcpy(str, "0001"); break;
        case '2': strcpy(str, "0010"); break;
        case '3': strcpy(str, "0011"); break;
        case '4': strcpy(str, "0100"); break;
        case '5': strcpy(str, "0101"); break;
        case '6': strcpy(str, "0110"); break;
        case '7': strcpy(str, "0111"); break;
        case '8': strcpy(str, "1000"); break;
        case '9': strcpy(str, "1001"); break;
        case 'A': strcpy(str, "1010"); break;
        case 'B': strcpy(str, "1011"); break;
        case 'C': strcpy(str, "1100"); break;
        case 'D': strcpy(str, "1101"); break;
        case 'E': strcpy(str, "1110"); break;
        case 'F': strcpy(str, "1111"); break;
        default: strcpy(str, ""); break; // default case for invalid input
    }
}

// Main function
void main() {
    FILE *input;
    input = fopen("input.txt", "r");

    char *tok, *sections[100], recName, length, line[200], bits[100], temp[5], objcode[7];
    int hexAddr, i, start, current, bitNo = 0;

    // Read the first line from the file
    fscanf(input, "%s", line);

    // Get the starting address from the user
    printf("Enter the starting address of the program: ");
    scanf("%X", &start);

    // Continue processing lines until 'E' record is encountered
    while (line[0] != 'E') {
        if (line[0] == 'T') {
            bitNo = 0;

            // Extract starting address and load bit masks
            tok = strtok(line, "^");
            tok = strtok(NULL, "^");
            current = strtol(tok, NULL, 16);
            strtok(NULL, "^");
            tok = strtok(NULL, "^");

            // Convert bit masks to binary
            for (i = 0; i < strlen(tok); i++) {
                convHex(tok[i], temp);
                strcat(bits, temp);
            }

            tok = strtok(NULL, "^");

            // Process the remaining tokens
            while (tok != NULL) {
                hexAddr = strtol(tok, NULL, 16);

                // Update address based on bit masks
                if (bits[bitNo] == '1') {
                    hexAddr += start;
                }

                // Convert modified address to hexadecimal string
                sprintf(objcode, "%X", hexAddr);

                i = 0;

                // Print modified addresses and corresponding data
                while (objcode[i] != '\0') {
                    printf("%X : %c%c\n", current + start, objcode[i], objcode[i + 1]);
                    i += 2;
                    current++;
                }

                // Move to the next token and bit mask
                tok = strtok(NULL, "^");
                bitNo++;
            }

            // Reset bit masks for the next record
            strcpy(bits, "");
        }

        // Read the next line from the file
        fscanf(input, "%s", line);
        printf("\n");
    }

    // Close the file
    fclose(input);
}
