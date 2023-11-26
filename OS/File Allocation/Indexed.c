#include <stdio.h>

#include <stdlib.h>

int files[50], indexBlock[50], indBlock, n;
void recurse1();
void recurse2();

void recurse1(){
    printf("Enter the index block: ");
    scanf("%d", &indBlock);
    if (files[indBlock] != 1){
        printf("Enter the number of blocks required for the file : ", indBlock);
        scanf("%d", &n);
    }
    else{
        printf("%d is already allocated\n", indBlock);
        recurse1();
    }
    recurse2();
}

void recurse2(){
    int ch;
    int flag = 0;
    printf("\nEnter %d block numbers to allocate the file to : \n",n);
    for (int i=0; i<n; i++){
        scanf("%d", &indexBlock[i]);
        if (files[indexBlock[i]] == 0)
            flag++;
    }
    if (flag == n){
        for (int j=0; j<n; j++){
            files[indexBlock[j]] = 1;
        }
        printf("Allocated\n");
        printf("File Indexed\n");
        for (int k=0; k<n; k++){
            printf("%d index to %d : %d\n", indBlock, indexBlock[k], files[indexBlock[k]]);
        }
    }
    else{
        printf("File in the index is already allocated\n");
        printf("Enter another indexed file\n");
        recurse2();
    }
    printf("Do you want to enter more files?\n");
    printf("1 = Yes, 0 = No");
    scanf("%d", &ch);
    if (ch == 1)
        recurse1();
    else
        exit(0);
    return;
}

int main()
{
    for(int i=0;i<50;i++)
        files[i]=0;

    recurse1();
    return 0;
}

