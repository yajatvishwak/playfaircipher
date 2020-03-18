#include <stdio.h>
#include <string.h>
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
char *trimwhitespace(char *str)
{
    char *end;

    // Trim leading space
    while (isspace((unsigned char)*str))
        str++;

    if (*str == 0) // All spaces?
        return str;

    // Trim trailing space
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end))
        end--;

    // Write new null terminator character
    end[1] = '\0';

    return str;
}

void main()
{
    int i, j, k = 0, sizekeyString, sizemessageString;
    char c;
    char key[26];      // Store Key value
    char message[100]; //Store message value
    char map[5][5];
    char mapgen[] = "abcdefghijklmnopqrstuvwxyz";

    printf("Enter Key String: \n");
    fgets(key, 26, stdin); // Input to avoid buffer overflow
    c = findduplicate(key);
    deleteduplicate(key, c);
    printf("%s", key);
    sizekeyString = strlen(key);

    // abcdefghijklmnopqrstuvwxyz

    //adding the key first
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 5; j++)
        {
            if (k < sizekeyString)
                map[i][j] = key[k];
            k += 1;
        }
    }
    //dotting the duplicates
    for (i = 0; i < strlen(key); i++)
    {
        for (j = 0; j < 26; j++)
        {
            if (key[i] == mapgen[j])
            {
                mapgen[j] = '.';
            }
        }
    }
    printf("%s \n", mapgen);
    k = 0;
    //removing those dots
    removeAll(mapgen, '.');
    printf("%s \n", mapgen);

    //filling the rest of the array with letters and avoiding 'j'
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (map[i][j] == '\0' || map[i][j] == ' ' || map[i][j] == '\n' || map[i][j] == 'G')
            {
                if (mapgen[k] != 'j')
                {
                    map[i][j] = mapgen[k];
                    k++;
                }
                else
                {
                    k++;
                    map[i][j] = mapgen[k];
                    k++;
                }
            }
        }
    }
    //printing the map
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 5; j++)
        {
            printf("%c \t", map[i][j]);
        }
        printf("\n");
    }
    //printf("Enter Message");
    // scanf("%s", message);
    // printf("%s", message);
    // sizemessageString = strlen(message);
    // for (i = 0; i < sizemessageString - 2; i += 2)
    // {
    //     printf("%c %c", message[i], message[i + 1]);
    // }
}