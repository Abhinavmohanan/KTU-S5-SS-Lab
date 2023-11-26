#include<stdio.h>
#include<string.h>
#include<stdlib.h>


void display(){

}


void main(){
    FILE *in,*symtab,*optab,*fpl,*out;
    char label[30],opcode[30],operand[30],code[30],value[30];
    int locctr,start,length,bytelen,size=0;
    
    in = fopen("input.txt","r");
    symtab = fopen("symtab.txt","w");
    optab = fopen("optab.txt","r");
    fpl = fopen("length.txt","w");
    out = fopen("intermediate.txt","w");

    fscanf(in,"%s\t%s\t%s",label,opcode,operand);

    if(strcmp(opcode,"START") == 0){
        start = atoi(operand);
        locctr = start;
        fprintf(out,"**\t%s\t%s\t%s\n",label,opcode,operand);
        fscanf(in,"%s\t%s\t%s",label,opcode,operand);
    }else{
        locctr = 0;
    }

    while(strcmp(opcode,"END") != 0){
        fprintf(out,"%d\t%s\t%s\t%s\n",locctr,label,opcode,operand);
        if(strcmp(label,"**") != 0){
            fprintf(symtab,"%s\t%d\n",label,locctr);
        }

        fscanf(optab,"%s\t%s",code,value);
        while(strcmp(code,"END") != 0){
            if(strcmp(opcode,code) == 0){
                locctr += 3;
                size += 3;
                break;
            }
            fscanf(optab,"%s\t%s",code,value);
        }

        if(strcmp(opcode,"WORD") == 0){
            locctr += 3;
            size += 3;
        }else if(strcmp(opcode,"BYTE") == 0){
            bytelen = strlen(operand);
            if(operand[0] == 'C' || operand[0] == 'c'){
                locctr += (bytelen - 3);
                size += (bytelen - 3);
            }else{
                locctr += (bytelen - 3)/2;
                size += (bytelen - 3)/2;
            }
        }else if(strcmp(opcode,"RESW") == 0){
            locctr += 3 * atoi(operand);
        }else if(strcmp(opcode,"RESB") == 0){
            locctr += atoi(operand);
        }
        fscanf(in,"%s\t%s\t%s",label,opcode,operand);
    }

    fprintf(out,"%d\t%s\t%s\t%s\n",locctr,label,opcode,operand);
    length = locctr - start;
    printf("Length of assembly program is (in hex) : %x %x",length,size);
    fprintf(fpl,"%x\t%x",length,size);
    fprintf(symtab,"END\t*");

    fclose(in);
    fclose(out);
    fclose(symtab);
    fclose(optab);
    fclose(fpl);
}
