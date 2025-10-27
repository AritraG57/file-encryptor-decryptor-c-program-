
#include <stdio.h>
#include <string.h>

void insertBeforeTxt(const char *original, const char *insert, char *result)
{
    const char *ext = strstr(original, ".txt");
    if (ext == NULL)
    {
        strcpy(result, original);
        return;
    }

    int prefixLen = ext - original;
    strncpy(result, original, prefixLen);
    result[prefixLen] = '\0';
    strcat(result, insert);
    strcat(result, ext);
}

int containsSubstring(const char *str, const char *sub)
{
    int len1 = strlen(str);
    int len2 = strlen(sub);
    if (len2 > len1)
        return 0;

    for (int i = 0; i <= len1 - len2; i++)
    {
        int j;
        for (j = 0; j < len2; j++)
        {
            if (str[i + j] != sub[j])
                break;
        }
        if (j == len2)
            return 1;
    }
    return 0;
}


void removeEncryptionTag(const char *filename, char *result)
{
    strcpy(result, filename);
    char *posA = strstr(result, "-encrypted-a");
    char *posB = strstr(result, "-encrypted-b");

    if (posA)
        memmove(posA, posA + strlen("-encrypted-a"), strlen(posA + strlen("-encrypted-a")) + 1);
    else if (posB)
        memmove(posB, posB + strlen("-encrypted-b"), strlen(posB + strlen("-encrypted-b")) + 1);
}

int main()
{
    FILE *fptr, *temp;
    char filename[100];
    printf("Enter the file name : ");
    scanf("%s", filename);

    fptr = fopen(filename, "r");
    if (fptr == NULL)
    {
        printf("The file does not exist!!!\n");
        return 0;
    }

    temp = fopen("temp.txt", "w");
    if (temp == NULL)
    {
        printf("Error creating temporary file!\n");
        fclose(fptr);
        return 0;
    }

    char ch;
    int offset;
    char method;

    // --- DECRYPTION SECTION ---
    if (containsSubstring(filename, "-encrypted-a") || containsSubstring(filename, "-encrypted-b"))
    {
        printf("Decryption Mode\n");

        if (containsSubstring(filename, "-encrypted-a"))
        {
            printf("Enter offset used for encryption: ");
            scanf("%d", &offset);

            while ((ch = fgetc(fptr)) != EOF)
            {
                ch = ch - offset; // decrypt using offset cipher
                fputc(ch, temp);
            }
        }
        else
        {
            // substitution cipher decryption (reverse mapping)
            char map[256];
            for (int i = 0; i < 256; i++)
                map[i] = i; // you can modify this if you used a custom substitution

            while ((ch = fgetc(fptr)) != EOF)
                fputc(map[(unsigned char)ch], temp);
        }

        char newname[100];
        removeEncryptionTag(filename, newname);
        fclose(fptr);
        fclose(temp);
        remove(filename);
        rename("temp.txt", newname);
        printf("File decrypted successfully: %s\n", newname);
    }
    // --- ENCRYPTION SECTION ---
    else
    {
        printf("Encryption Mode\n");
        printf("Enter method (a/b): ");
        scanf(" %c", &method);

        if (method == 'a')
        {
            printf("Enter the offset: ");
            scanf("%d", &offset);

            while ((ch = fgetc(fptr)) != EOF)
            {
                ch = ch + offset;
                fputc(ch, temp);
            }

            char newname[100];
            insertBeforeTxt(filename, "-encrypted-a", newname);
            fclose(fptr);
            fclose(temp);
            remove(filename);
            rename("temp.txt", newname);
            printf("File encrypted successfully: %s\n", newname);
        }
        else if (method == 'b')
        {
            char map[256];
            for (int i = 0; i < 256; i++)
                map[i] = i; // simple substitution (customize if needed)

            while ((ch = fgetc(fptr)) != EOF)
                fputc(map[(unsigned char)ch], temp);

            char newname[100];
            insertBeforeTxt(filename, "-encrypted-b", newname);
            fclose(fptr);
            fclose(temp);
            remove(filename);
            rename("temp.txt", newname);
            printf("File encrypted successfully: %s\n", newname);
        }
    }

    return 0;
}
