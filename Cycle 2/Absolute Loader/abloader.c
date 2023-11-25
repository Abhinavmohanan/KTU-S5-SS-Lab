#include<stdio.h>
#include<stdlib.h>

void main(){
    FILE *abs;
    abs = fopen("input.txt","r");
    char line[300];
    fscanf(abs,"%s",line);
    char addr[6];
    int i = 0,j=0,addressHex,prevaddressHex = 0xFFFF;
    while(line[0] != 'E'){
        if(line[0] == 'T'){
            for(i = 2,j=0; i <= 7;i++,j++){
                addr[j] = line[i];
            }
            addr[j] = '\0';
            addressHex = strtol(addr,NULL,16);
            while(prevaddressHex < addressHex){
                printf("\n%x : XX",prevaddressHex);
                prevaddressHex++;
            }
            i += 4;
            while(line[i] != '\0'){
                printf("\n%x : %c%c",addressHex,line[i],line[i+1]);
                i +=2;
                addressHex += 0x1;
                if(line[i] == '^') i++;
            }
            prevaddressHex = addressHex;
        }
        fscanf(abs,"%s",line);
    }
}