#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <ctype.h>

void deleteduplicate(char *key, char c)
{
    int i, k = 0;

    for (i = 0; key[i]; i++)
    {
        key[i] = key[i + k];

        if (key[i] == c)
        {
            k++;
            i--;
        }
    }
}

char findduplicate(char *key)
{
    char c = '*';
    int i, j;

    for (i = 0; key[i]; i++)
    {
        if (!(key[i] == c))
        {
            for (j = i + 1; key[j]; j++)
            {
                if (key[i] == key[j])
                    key[j] = c;
            }
        }
    }

    return c;
}

void printArray(char arr[5][5])
{
    int i, j;
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 5; j++)
        {

            printf("%c \t", arr[i][j]);
        }
        printf("\n");
    }
}

void markMapGen(char *key, char *mapgen, int sizeOfKey)
{
    int i, j;
    for (i = 0; i < sizeOfKey; i++)
    {
        for (j = 0; j < 26; j++)
        {
            if (key[i] == mapgen[j])
            {
                mapgen[j] = '.';
            }
        }
    }
}
void removeAll(char *str, const char toRemove)
{
    int i, j;
    int len = strlen(str);

    for (i = 0; i < len; i++)
    {
        /*
         * If the character to remove is found then shift all characters to one
         * place left and decrement the length of string by 1.
         */
        if (str[i] == toRemove)
        {
            for (j = i; j < len; j++)
            {
                str[j] = str[j + 1];
            }

            len--;

            // If a character is removed then make sure i doesn't increments
            i--;
        }
    }
}
void prepareInput(char *key)
{
    char c;
    int i;
    c = findduplicate(key);
    deleteduplicate(key, c);
    for (i = 0; i < 100; i++)
    {
        if (key[i] == 'j')
        {
            key[i] = 'i';
        }
    }
}

void pushKeyToMap(char map[5][5], char *mapgen, int sizeOfMapgen)
{
    int i, j, k = 0;
    for (i = 0; i < sizeOfMapgen; i++)
    {
        if (mapgen[i] == 'j')
        {
            mapgen[i] = '.';
        }
    }
    removeAll(mapgen, '.');
    printf("after removing j : \t %s \n", mapgen);
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 5; j++)
        {
            if (isalpha(map[i][j]) == 0)
            {
                map[i][j] = mapgen[k];
                k++;
            }
        }
    }
}

void encrypt(char ch1, char ch2, char map[5][5], char *result)
{
    int i, j, lch1i, lch1j, lch2i, lch2j;
    int *temp = (int *)malloc(sizeof(int) * 2);
    char ec1, ec2;
    int loc[4];
    //search for the char c1 and c2
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 5; j++)
        {
            if (map[i][j] == ch1)
            {
                lch1i = i;
                lch1j = j;
            }
            if (map[i][j] == ch2)
            {
                lch2i = i;
                lch2j = j;
            }
        }
    }

    //printf("%d %d \n", lch1i, lch1j);
    //printf("%d %d \n", lch2i, lch2j);
    if (lch1j == lch2j)
    {
        //same column
        ec1 = map[(lch1i + 1) % 5][lch1j];
        ec2 = map[(lch2i + 1) % 5][lch2j];
    }
    else if (lch1i == lch2i)
    {
        //same row
        ec1 = map[lch1i][(lch1j + 1) % 5];
        ec2 = map[lch2i][(lch2j + 1) % 5];
    }
    else
    {
        //rectangle
        ec1 = map[lch1i][lch2j];
        ec2 = map[lch2i][lch1j];
    }
    //printf("After encryption: %c %c \n", ec1, ec2);
    result[0] = ec1;
    result[1] = ec2;
}

void decrypt(char ch1, char ch2, char map[5][5], char *result)
{
    int i, j, lch1i, lch1j, lch2i, lch2j;
    int *temp = (int *)malloc(sizeof(int) * 2);
    char ec1, ec2;
    int loc[4];
    //search for the char c1 and c2
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 5; j++)
        {
            if (map[i][j] == ch1)
            {
                lch1i = i;
                lch1j = j;
            }
            if (map[i][j] == ch2)
            {
                lch2i = i;
                lch2j = j;
            }
        }
    }

    //printf("%d %d \n", lch1i, lch1j);
    //printf("%d %d \n", lch2i, lch2j);
    if (lch1j == lch2j)
    {
        //same column
        ec1 = map[(lch1i - 1) % 5][lch1j];
        ec2 = map[(lch2i - 1) % 5][lch2j];
    }
    else if (lch1i == lch2i)
    {
        //same row

        ec1 = map[lch1i][(lch1j == 0) ? 4 : (lch1j - 1) % 5];

        ec2 = map[lch2i][(lch2j == 0) ? 4 : (lch1j - 1) % 5];
    }
    else
    {
        //rectangle
        ec1 = map[lch1i][lch2j];
        ec2 = map[lch2i][lch1j];
    }
    printf("After decryption: %c %c \n", ec1, ec2);
    printf(" %d %d \n", lch1i, lch1j);
    printf(" %d %d \n", lch2i, lch2j);
    result[0] = ec1;
    result[1] = ec2;
}

void pairInputandEncrypt(char *message, char map[5][5], int size, char *et)
{
    int i;
    char encryptedText[2];

    printf("Without space: \t %s \n", message);
    if (size % 2 != 0)
    {
        message[size] = 'z';
    }

    for (i = 0; i < size; i += 2)
    {
        printf("Before encrpytion : %c %c  \n", message[i], message[i + 1]);
        encrypt(message[i], message[i + 1], map, encryptedText);
        printf("After encryption: %c %c \n", encryptedText[0], encryptedText[1]);
        et[i] = encryptedText[0];
        et[i + 1] = encryptedText[1];
    }
    //et to main fucntion for final answer
}

void pairInputandDecrypt(char *message, char map[5][5], int size, char *dt)
{
    int i;
    char decryptedText[2];

    for (i = 0; i < size; i += 2)
    {
        printf("Before encrpytion : %c %c  \n", message[i], message[i + 1]);
        decrypt(message[i], message[i + 1], map, decryptedText);
        dt[i] = decryptedText[0];
        dt[i + 1] = decryptedText[1];
    }
    //et to main fucntion for final answer
}

void main()
{
    int sizeOfKey, sizeOfMessage, i, j, k = 0;
    char key[26];
    char encryptedMessage[100];
    char decryptedMessage[100];
    char message[100];
    char map[5][5];
    char mapgen[] = "abcdefghiklmnopqrstuvwxyz";
    int choice;
    printf("1.Encryption \n2.Decryption\nPress 1 or 2\n");
    scanf(" %d", &choice);
    if (choice >= 3 || choice <= 0)
    {
        printf("Wrong choice, Please rerun the program and try again, %d", choice);
        exit(0);
    }

    printf("Enter message: \n");
    scanf(" %[^\n]%*c", message);

    printf("Enter Key String: \n");
    scanf(" %s", key);
    prepareInput(key);
    sizeOfKey = strlen(key);
    printf("Your entered key is : %s \n Its size is : %d \n", key, sizeOfKey);

    removeAll(message, ' ');
    sizeOfMessage = strlen(message);
    printf("Your entered message is : %s \n Its size is : %d \n", message, sizeOfMessage);

    // initializing values of map
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 5; j++)
        {
            map[i][j] = '.';
        }
    }

    //adding the key to the map
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 5; j++)
        {
            if (k < sizeOfKey)
                map[i][j] = key[k];
            k += 1;
        }
    }
    printf("\n");
    printf("Generated Map after adding the key to the map, now filling rest of the values .....");
    printf("\n");
    printArray(map);

    //preparing the mapgen, to fill in other values in the map

    //1. marking all duplicates
    markMapGen(key, mapgen, sizeOfKey);
    printf(" marking all duplicates: \t %s \n", mapgen);
    //2. removing all marked
    removeAll(mapgen, '.');
    printf("removing all marked : \t %s \n", mapgen);
    // mapgen prepared to push in map

    //pushing mapgen to map
    pushKeyToMap(map, mapgen, strlen(mapgen));
    printf("Generated Map after pushing mapgen to the map");
    printf("\n");
    printArray(map);

    if (choice == 1)
    {
        //Encryption

        //Pairing the input
        printf("Message to be encrypted: %s \n ", message);
        //replacing the j in the message with i
        for (i = 0; i <= strlen(message); i++)
        {
            if (message[i] == 'j')
            {
                message[i] = 'i';
            }
        }
        printf("Message to be encrypted after replacing j with i: %s \n ", message);
        pairInputandEncrypt(message, map, sizeOfMessage, encryptedMessage);
        //processing output - !!!PENDING
        for (i = 0; i < sizeOfMessage - 1; i++)
        {
            if (isalpha(encryptedMessage[i]) == 0)
            {
                encryptedMessage[i] = ' ';
            }
        }

        printf("\n The message in encrypted format is: \t %s \n", encryptedMessage);
    }
    else if (choice == 2)
    {
        //Decryption
        printf("decrypting...");
        pairInputandDecrypt(message, map, sizeOfMessage, decryptedMessage);
        printf("\n The message in decrypted format is: \t %s \n", decryptedMessage);
    }
    else
    {
        printf("Wrong choice, Please rerun the program and try again");
    }
}