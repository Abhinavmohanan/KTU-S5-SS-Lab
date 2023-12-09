#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Block
{
    int data;
    struct Block *next;
};

struct File
{
    char name[20];
    struct Block *firstBlock;
};

void createFile(struct File **files, int *numFiles, char *name)
{
    if (*numFiles >= 50)
    {
        printf("Cannot create more files. Limit reached.\n");
        return;
    }

    struct File *newFile = (struct File *)malloc(sizeof(struct File));
    if (!newFile)
    {
        printf("Memory allocation failed.\n");
        return;
    }

    strcpy(newFile->name, name);
    newFile->firstBlock = NULL;

    files[*numFiles] = newFile;
    (*numFiles)++;

    printf("File '%s' created successfully.\n", name);
}

void allocateBlock(struct File *file, int blockNumber)
{
    struct Block *newBlock = (struct Block *)malloc(sizeof(struct Block));
    if (!newBlock)
    {
        printf("Memory allocation failed.\n");
        return;
    }

    newBlock->data = blockNumber;
    newBlock->next = NULL;

    if (!file->firstBlock)
    {
        file->firstBlock = newBlock;
    }
    else
    {
        struct Block *current = file->firstBlock;
        while (current->next)
        {
            current = current->next;
        }
        current->next = newBlock;
    }

    printf("Block %d allocated to file '%s'.\n", blockNumber, file->name);
}

void displayFiles(struct File **files, int numFiles)
{
    if (numFiles == 0)
    {
        printf("No files created yet.\n");
        return;
    }

    printf("List of files:\n");
    for (int i = 0; i < numFiles; i++)
    {
        struct File *file = files[i];
        printf("File '%s': Blocks -> ", file->name);

        struct Block *current = file->firstBlock;
        while (current)
        {
            printf("%d ", current->data);
            current = current->next;
        }

        printf("\n");
    }
}

int main()
{
    struct File *files[50];
    int numFiles = 0;
    int blockNumber = 1;

    int choice;
    char fileName[20];

    while (1)
    {
        printf("\nLinked File Allocation Simulation\n");
        printf("1. Create a new file\n");
        printf("2. Allocate a block to a file\n");
        printf("3. Display files and allocated blocks\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("Enter the name of the new file: ");
                scanf("%s", fileName);
                createFile(files, &numFiles, fileName);
                break;

            case 2:
                if (numFiles == 0)
                {
                    printf("No files created yet. Please create a file first.\n");
                }
                else
                {
                    int fileIndex;
                    printf("Enter the index of the file (0-%d): ", numFiles - 1);
                    scanf("%d", &fileIndex);
                    if (fileIndex >= 0 && fileIndex < numFiles)
                    {
                        allocateBlock(files[fileIndex], blockNumber);
                        blockNumber++;
                    }
                    else
                    {
                        printf("Invalid file index.\n");
                    }
                }
                break;

            case 3:
                displayFiles(files, numFiles);
                break;

            case 4:
                exit(0);

            default:
                printf("Invalid choice. Please enter a valid option.\n");
            }
    }

    return 0;
}