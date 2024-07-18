#include <stdio.h>
#include <string.h>

// Function to calculate the number of parity bits required
int calcNumParityBits(int dataLength) {
    int m = 1;
    while ((1 << m) < (dataLength + m + 1)) {
        m++;
    }
    return m;
}

// Function to insert parity bits at correct positions
void insertParityBits(char data[], int dataLength, char hamming[]) {
    int m = calcNumParityBits(dataLength);
    int hammingIndex = 0, dataIndex = 0;

    for (int i = 1; i <= dataLength + m; i++) {
        // If current index is a power of 2, insert parity bit
        if ((i & (i - 1)) == 0) {
            hamming[hammingIndex++] = '0'; // Placeholder for parity bit
        } else {
            hamming[hammingIndex++] = data[dataIndex++];
        }
    }
}

// Function to calculate parity bits and fill them in the Hamming code
void calculateParityBits(char hamming[], int hammingLength) {
    int m = calcNumParityBits(hammingLength - 1); // Excluding parity bits
    for (int i = 0; i < m; i++) {
        int parityIndex = (1 << i) - 1; // Calculate the position of parity bit
        int parity = 0;
        for (int j = parityIndex; j < hammingLength; j += (1 << (i + 1))) {
            for (int k = 0; k < (1 << i) && (j + k) < hammingLength; k++) {
                parity ^= (hamming[j + k] - '0'); // Calculate parity
            }
        }
        hamming[parityIndex] = parity + '0'; // Update parity bit
    }
}

int main() {
    char binary[100], hamming[100];
    printf("Enter the binary code: ");
    scanf("%s", binary);

    int dataLength = strlen(binary);
    insertParityBits(binary, dataLength, hamming);
    calculateParityBits(hamming, strlen(hamming));

    printf("The Hamming code is: %s\n", hamming);

    return 0;
}
