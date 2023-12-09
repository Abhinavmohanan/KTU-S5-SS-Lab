#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>

void expand(char*label,char *opcode,char *operand,int start,int end);
void define(char *label,char *opcode,char *operand);

FILE *inputfile,*expanded;
int deftabIndex= 0,nametabIndex = 0, argtabIndex = 1;

bool expanding = false;

struct nametabs{
    char name[10];
    int start,end;
}namtab[20];

char deftab[20][100],argtab[20][100];

void get_line(int index,char* nextline){
    char label[100],opcode[100],operand[100];
    if(expanding == true){
        //Need to process argtab
        sscanf(deftab[index],"%s%s%s",label,opcode,operand);
        if(operand[0] == '?'){
            strcpy(operand,argtab[operand[1] - '0']);
        }
        sprintf(nextline,"%s %s %s",label,opcode,operand);
    }else{
        fscanf(inputfile,"%s%s%s",label,opcode,operand);
        sprintf(nextline,"%s %s %s",label,opcode,operand);
    }
}

struct nametabs* search_nam(char *opcode){
    for(int i =0 ; i <= nametabIndex; i++){
        if(strcmp(namtab[i].name,opcode)==0){
            return &namtab[i];
        }
    }
    return NULL;
}

void process_line(char *label,char *opcode,char *operand){
    struct nametabs* macro;
    macro = search_nam(opcode);
    if(macro != NULL){
        expand(label,opcode,operand,macro->start,macro->end);
    }else if(strcmp(opcode,"MACRO") == 0){
        define(label,opcode,operand);
    }else{
        fprintf(expanded,"%s %s %s\n",label,opcode,operand);
    }
}

void define(char *label,char *opcode,char *operand){
    strcpy(namtab[nametabIndex].name,label); // Write to namtab
    namtab[nametabIndex].start = deftabIndex;
    char nextline[100],defline[100];
    sprintf(nextline,"%s %s %s",label,opcode,operand);
    strcpy(deftab[deftabIndex],nextline); //Write prototype to deftab
    
    //ARG MAP
    char argmap[30][10];
    char *tok = strtok(operand,",");
    int argMapIndex = 1;
    while(tok != NULL){
        strcpy(argmap[argMapIndex],tok+1);
        tok = strtok(NULL,",");
        argMapIndex++;
    }

    deftabIndex++;
    int level = 1,i=0;
    while(level > 0){
        strcpy(defline,"");
        get_line(-1,nextline); //index -1 as it is not required here
        sscanf(nextline,"%s%s%s",label,opcode,operand);
        if(operand[0] == '&'){
            i=0;
            while(i < argMapIndex){
                if(strcmp(argmap[i],operand+1) == 0){
                    sprintf(operand,"%c%d",'?',i);
                    break;
                }
                i++;
            }
        }
        sprintf(deftab[deftabIndex],"%s %s %s",label,opcode,operand);
        deftabIndex++;

        if(strcmp(opcode,"MACRO") == 0){
            level++;
        }else if(strcmp(opcode,"MEND") == 0){
            level--;
        }
    }
    namtab[nametabIndex].end = deftabIndex-1;
    nametabIndex++;
}

void expand(char *label,char *opcode,char *operand,int start,int end){
    
    fprintf(expanded,"%s %s %s\n",".",opcode,operand);
    char *tok = strtok(operand,","),nextline[100];
    argtabIndex = 1;
    while(tok != NULL){
        strcpy(argtab[argtabIndex],tok);
        tok = strtok(NULL,",");
        argtabIndex++;
    }

    expanding = true;
    start++;
    while(start < end){
        get_line(start,nextline);
        sscanf(nextline,"%s%s%s",label,opcode,operand);
        process_line(label,opcode,operand);
        start++;
    }
    expanding = false;
}



void main(){
    char nextline[100],opcode[20],label[20],operand[20];
    inputfile = fopen("input.txt","r");
    expanded = fopen("expanded.txt","w");

    expanding = false;
    while(strcmp(opcode,"END") != 0){
        get_line(-1,nextline);
        sscanf(nextline,"%s%s%s",label,opcode,operand);
        process_line(label,opcode,operand);
    }

    FILE *nametabfile,*deftabfile,*argtabfile;

    nametabfile = fopen("namtab.txt","w");
    deftabfile = fopen("deftab.txt","w");
    argtabfile = fopen("argtab.txt","w");

    int i = 0;
    for(i = 0 ; i < nametabIndex;i++ ){
        fprintf(nametabfile,"%s %d %d\n",namtab[i].name,namtab[i].start,namtab[i].end);
    }

    for(i = 0 ; i < argtabIndex;i++ ){
        fprintf(argtabfile,"%s\n",argtab[i]);
    }

    for(i = 0 ; i < deftabIndex;i++ ){
        fprintf(deftabfile,"%s\n",deftab[i]);
    }


    fclose(inputfile);
    fclose(expanded);
    fclose(nametabfile);
    fclose(argtabfile);
    fclose(deftabfile);
}