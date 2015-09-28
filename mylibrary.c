#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct string{
   char s[40];
}string;

char* read_file_content(char* filename){
    FILE* fptr = fopen(filename,"r");
    if(fptr==NULL){
      return "0";
    }
    int i=0;
    char c;
    char *buff;
    buff = (char*)malloc(1000*sizeof(char));
    do{
      c = fgetc(fptr);
      if(c == EOF) continue;
      buff[i++] = c;
    }while(c!=EOF);
    buff[i] = '\0';
    fclose(fptr);
    return buff;
}

string* cut_string(char* source_string,char cut_word){
    char* buff;
    buff = (char*)malloc(100*sizeof(char));
    string* result;
    result = (string*)malloc(100*sizeof(string));
    int i=0,j=0,count=0;
    while(source_string[count]!='\0'){
    	
      if(source_string[count+1]=='\0'){
        if(source_string[count]!=cut_word)
          buff[j++] = source_string[count];
        buff[j]='\0';
        strcpy(result[i].s,buff);
        //printf("%s\n",buff);
        break;
      }else if(source_string[count]==cut_word){
        count++;  
        buff[j] = '\0';
        strcpy(result[i].s,buff);
        //printf("%s\n",buff);
        i++;
        j=0;
      }else{
      	buff[j++]=source_string[count++];
      }    
    }   
    return result;
}


char* join_string(string* array_string,char join_word){
    char* buff = (char*)malloc(1000*sizeof(char));
    int i=0;
    while(array_string[i].s[0]!='\0'){
      //printf("%s\t",array_string[i].s);
      strcpy(buff+strlen(buff),array_string[i].s);
      //printf("%s\t",array_string[i].s);
            
      if(array_string[i+1].s[0]!='\0')
        buff[strlen(buff)]=join_word;
      //printf("%s\n",buff);
      i++;
    }
    buff[strlen(buff)] = '\0';
    return buff;
}


void write_file_content(char* source_string,char* filename){
    FILE* fptr = fopen(filename,"w");
    if(fptr==NULL){
      printf("file %s is not exist\n",filename);
      exit(0);
    }
    int i=0;
    while(source_string[i]!='\0'){
      fputc(source_string[i++],fptr);
    }
    fclose(fptr);
}  

