#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct {
    char opcode[20];
    char hex[20];
}optab[20];

struct {
    char symbol[20];
    char value[20];
}symtab[20];

void read_symtab(){
    FILE *sym;
    sym = fopen("symtab.txt","r");
    int i = 0;
    fscanf(sym,"%s\t%s",symtab[i].symbol,symtab[i].value);
    while(strcmp(symtab[i].symbol,"END") != 0){
        i++;
        fscanf(sym,"%s\t%s",symtab[i].symbol,symtab[i].value);
    }
    fclose(sym);
}

void read_optab(){
    FILE *op;
    op = fopen("optab.txt","r");
    int i = 0;
    fscanf(op,"%s\t%s",optab[i].opcode,optab[i].hex);
    while(strcmp(optab[i].opcode,"END") != 0){
        i++;
        fscanf(op,"%s\t%s",optab[i].opcode,optab[i].hex);
    }
    fclose(op);
}


void main(){
    read_optab();
    read_symtab();
    FILE *objcode,*assemlist,*len,*interm;
    int length,size,addr,start_addr,bytelen,j,k;
    char opcode[20],label[20],operand[20];
    interm = fopen("intermediate.txt","r");
    objcode = fopen("objectcode.txt","w");
    assemlist = fopen("assemlist.txt","w");
    len = fopen("length.txt","r");
    fscanf(len,"%x\t%x",&length,&size);
    fscanf(interm,"%s\t%s\t%s\t%s",&addr,label,opcode,operand);
    start_addr = atoi(operand);
    if(strcmp(opcode,"START") == 0 ){
        //Listing line
        fprintf(assemlist,"**\t**\t%s\t%s\n",opcode,operand);

        fprintf(objcode,"H^PGM   ^00%d^0000%x\n",start_addr,length);
        fprintf(objcode,"T^00%d^%x",start_addr,size);
        fscanf(interm,"%x\t%s\t%s\t%s",&addr,label,opcode,operand);
    }

    while(strcmp(opcode,"END") != 0){
        if(strcmp(opcode,"BYTE") == 0){
            fprintf(objcode,"^");
            bytelen = strlen(operand) - 1;
            fprintf(assemlist,"%x\t%s\t%s\t%s\t",addr,label,opcode,operand);
            if(operand[0] == 'C' || operand[0] == 'c'){
                for(int i = 2; i < bytelen; i++){
                    fprintf(objcode,"%x",operand[i]);
                    fprintf(assemlist,"%x",operand[i]);
                }
                fprintf(assemlist,"\n");
            }else{
                // If hex
                fprintf(assemlist,"%x\t%s\t%s\t%s\t",addr,label,opcode,operand);
                operand[bytelen] = '\0';
                fprintf(objcode,"%s",operand+2);
                fprintf(assemlist,"%s\n",operand+2);
            }
        }
        else if (strcmp(opcode,"WORD") == 0){
            fprintf(objcode,"^00000%x",atoi(operand));
            fprintf(assemlist,"%x\t%s\t%s\t%s\t%x\n",addr,label,opcode,operand,atoi(operand));
        }
        else if(strcmp(opcode,"RESB") == 0 || strcmp(opcode,"RESW") == 0){
            fprintf(assemlist,"%x\t%s\t%s\t%s\n",addr,label,opcode,operand);
        }else{
            j=k=0;
            while(strcmp(opcode,optab[j].opcode) != 0){
                j++;
            }
            while(strcmp(operand,symtab[k].symbol) != 0){
                k++;
            }
            fprintf(objcode,"^%s%s",optab[j].hex,symtab[k].value);
            fprintf(assemlist,"%x\t%s\t%s\t%s\t%s%s\n",addr,label,opcode,operand,optab[j].hex,symtab[k].value);
        }
        fscanf(interm,"%x\t%s\t%s\t%s",&addr,label,opcode,operand);
    }
    fprintf(objcode,"\nE^00%d",start_addr);
    fprintf(assemlist,"%x\t%s\t%s\t%s",addr,label,opcode,operand);

    fclose(interm);
    fclose(objcode);
    fclose(assemlist);
}