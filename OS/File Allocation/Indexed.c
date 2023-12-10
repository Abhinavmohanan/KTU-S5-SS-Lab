#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int dIndex = -1;

struct{
    char filename[100];
    int indexBlock;
    int noBlocks;
    bool isAllocated;
}directory[10];

struct diskStruct{
    int blockNo;
    int fileNo;
    bool isAllocated;
    bool isIndexBlock;
    int indexedBlocks[100];
}disk[100];



void createFile(){
    dIndex++;
    char name[100];
    printf("\nEnter name of file :");
    scanf("%s",&directory[dIndex].filename);
}

void allocateBlock(){
    if(dIndex == -1) {
        printf("No files to allocate blocks");
        return;
    }
    int fno,indexNo;
    printf("\nEnter the file no. to allocate blocks (0-%d): ",dIndex);

    if(directory[fno].isAllocated == true){
        printf("\nBlocks are already allocated to file !");
        return;
    }

    scanf("%d",&fno);

    if(fno > dIndex || fno < 0){
        printf("\nEnter valid file number ");
        return;
    }

    printf("\nEnter the index block no of file (%d): ",fno);

    scanf("%d",&indexNo);

    if(disk[indexNo].isAllocated == true){
        printf("\nError failed to allocated ,the block is already occupied");
        return;
    }else{
        disk[indexNo].isAllocated = true;
        disk[indexNo].isIndexBlock = true;
        disk[indexNo].fileNo = fno;
        int blockcount;
        printf("\nEnter no. of blocks to allocate to file : ");
        scanf("%d",&blockcount);
        directory[fno].noBlocks = blockcount;
        directory[fno].indexBlock = indexNo;


        int blocklist[blockcount];
        printf("\nEnter list of block numbers to allocate : ");
        for(int i = 0 ; i < blockcount;i++){
            scanf("%d",&blocklist[i]);
            if(disk[blocklist[i]].isAllocated == true){
                printf("Error allocating block , block %d is already occupied",blocklist[i]);
                return;
            }
        }

        for(int i = 0 ; i < blockcount;i++){
            disk[indexNo].indexedBlocks[i] = blocklist[i];
            disk[blocklist[i]].isAllocated = true;
            disk[blocklist[i]].fileNo = fno;
        }
        directory[fno].isAllocated = true;
        printf("Blocks allocated successfully");
    }
}

void listFiles(){
     if(dIndex == -1) {
        printf("No files to list blocks");
        return;
    }
    int fno,indexNo;
    printf("\nEnter the file no. to list blocks allocated (0-%d): ",dIndex);

    scanf("%d",&fno);

    if(directory[fno].isAllocated != true){
        printf("\nBlocks not allocated to file !");
        return;
    }

    if(fno > dIndex || fno < 0){
        printf("\nEnter valid file number ");
        return;
    }
    int indexBlock = directory[fno].indexBlock;
    printf("\n File %s index block : %d",directory[fno].filename,indexBlock);
    for(int i = 0 ; i < directory[fno].noBlocks ; i++){
        printf("\n%d indexed to %d",indexBlock,disk[indexBlock].indexedBlocks[i]);
    }
}


void main(){
    int option;
    while(1){
        printf("\n\nChoose option : \n1.Create a new file\n2.Allocate Blocks to file\n3.List files and block\n: ");
        scanf("%d",&option);

        switch(option){
            case 1: createFile();break;
            case 2: allocateBlock();break;
            case 3: listFiles();break;
            default: exit(0);
        }
    }
}