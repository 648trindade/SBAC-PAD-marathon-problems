#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

// MAX char table (ASCII)
#define MAX 256

// Boyers-Moore-Hospool-Sunday algorithm for string matching
int bmhs(char* string, int n, char* substr, int m)
{

    int d[MAX];
    int i, j, k;

    // pre-processing
    for (j = 0; j < MAX; j++)
        d[j] = m + 1;
    for (j = 0; j < m; j++)
        d[(int)substr[j]] = m - j;

    // searching
    i = m - 1;
    while (i < n)
    {
        k = i;
        j = m - 1;
        while ((j >= 0) && (string[k] == substr[j]))
        {
            j--;
            k--;
        }
        if (j < 0)
            return k + 1;
        i = i + d[(int)string[i + 1]];
    }

    return -1;
}

FILE *fdatabase, *fquery, *fout;

void openfiles(char* input, char* query, char* output)
{

    fdatabase = fopen(input, "r+");
    if (fdatabase == NULL)
    {
        perror(input);
        exit(EXIT_FAILURE);
    }

    fquery = fopen(query, "r");
    if (fquery == NULL)
    {
        perror(query);
        exit(EXIT_FAILURE);
    }

    fout = fopen(output, "w");
    if (fout == NULL)
    {
        perror(output);
        exit(EXIT_FAILURE);
    }
}

void closefiles()
{
    fflush(fdatabase);
    fclose(fdatabase);

    fflush(fquery);
    fclose(fquery);

    fflush(fout);
    fclose(fout);
}

void remove_eol(char* line)
{
    int i = strlen(line) - 1;
    while (line[i] == '\n' || line[i] == '\r')
    {
        line[i] = 0;
        i--;
    }
}

char* bases;
char* str;

int main(int argc, char** argv)
{
    struct timeval timevalA;
    struct timeval timevalB;

    if (argc != 4)
    {
        perror("args: <input> <query> <output>");
        exit(EXIT_FAILURE);
    }

    bases = (char*)malloc(sizeof(char) * 1000001);
    if (bases == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    str = (char*)malloc(sizeof(char) * 1000001);
    if (str == NULL)
    {
        perror("malloc str");
        exit(EXIT_FAILURE);
    }

    openfiles(argv[1], argv[2], argv[3]);

    char desc_dna[100], desc_query[100];
    char line[100];
    int i, found, result;

    fgets(desc_query, 100, fquery);
    remove_eol(desc_query);
    gettimeofday(&timevalA, NULL);
    while (!feof(fquery))
    {
        fprintf(fout, "%s\n", desc_query);
        // read query string
        fgets(line, 100, fquery);
        remove_eol(line);
        str[0] = 0;
        i = 0;
        do
        {
            strcat(str + i, line);
            if (fgets(line, 100, fquery) == NULL)
                break;
            remove_eol(line);
            i += 80;
        } while (line[0] != '>');
        strcpy(desc_query, line);

        // read database and search
        found = 0;
        fseek(fdatabase, 0, SEEK_SET);
        fgets(line, 100, fdatabase);
        remove_eol(line);
        while (!feof(fdatabase))
        {
            strcpy(desc_dna, line);
            bases[0] = 0;
            i = 0;
            fgets(line, 100, fdatabase);
            remove_eol(line);
            do
            {
                strcat(bases + i, line);
                if (fgets(line, 100, fdatabase) == NULL)
                    break;
                remove_eol(line);
                i += 80;
            } while (line[0] != '>');

            result = bmhs(bases, strlen(bases), str, strlen(str));
            if (result > 0)
            {
                fprintf(fout, "%s\n%d\n", desc_dna, result);
                found++;
            }
        }

        if (!found)
            fprintf(fout, "NOT FOUND\n");
    }
    gettimeofday(&timevalB, NULL);

    closefiles();

    printf("time=%lf\n",
           timevalB.tv_sec - timevalA.tv_sec +
               (timevalB.tv_usec - timevalA.tv_usec) / (double)1000000);

    free(str);
    free(bases);

    return EXIT_SUCCESS;
}
