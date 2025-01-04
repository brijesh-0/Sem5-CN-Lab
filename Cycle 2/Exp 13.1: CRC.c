#include <stdio.h>
#include <string.h>
#define N strlen(gen_poly)

char data[28], gen_poly[10], check[28];
int data_len, i, j;

void XOR() {
    for (j = 0; j < N; j++) {
        check[j] = (check[j] == gen_poly[j]) ? '0' : '1';
    }
}

void crc() {
    for (i = 0; i < N; i++) {
        check[i] = data[i];
    }
    do {
        if (check[0] == '1') {
            XOR();
        }
        for (j = 0; j < N - 1; j++) {
            check[j] = check[j + 1];
        }
        check[j] = data[i++];
    } while (i <= data_len + N - 1);
}

void receiver() {
    printf("\nData received: ");
    scanf("%s", data);

    crc();
    for (i = 0; i < N - 1; i++) {
        if (check[i] == '1') {
            break;
        }
    }
    if (i < N - 1) {
        printf("\nERROR!");
    } else {
        printf("\nNO ERROR!");
    }
}

int main() {
    printf("\nEnter data: ");
    scanf("%s", data);
    printf("\nEnter generator: ");
    scanf("%s", gen_poly);

    data_len = strlen(data);

    // Append N-1 zeros to the data
    for (i = data_len; i < data_len + N - 1; i++) {
        data[i] = '0';
    }
    data[data_len + N - 1] = '\0'; // Null-terminate the string

    printf("\nData with padded 0's: %s", data);

    crc();

    printf("\nCheck sum: ");
    for (i = 0; i < N - 1; i++) {
        printf("%c", check[i]);
    }

    // Append checksum to data
    for (i = data_len; i < data_len + N - 1; i++) {
        data[i] = check[i - data_len];
    }
    data[data_len + N - 1] = '\0'; // Null-terminate the string

    printf("\nFinal data to be transmitted: %s", data);

    receiver();
    return 0;
}
