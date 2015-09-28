#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mylibrary.h"


  void thongtin(char* ss){
  //printf("%s\t",ss);
  if(!strcmp(ss,"BA0")) printf("Evacuation: Cần mặt nạ phòng độc và găng tay bảo vệ\n");
  if(!strcmp(ss,"BA1")) printf("Evacuation: Cần mặt nạ phòng độc và găng tay bảo vệ khi co lua\n");
  if(!strcmp(ss,"FULL")) printf("Protection: Bảo vệ toàn thân với quần áo và mặt nạ\n");	
  if(!strcmp(ss,"DILUTE")) printf("Containment: hóa chất có thể được pha loãng với nước và rửa sạch\n");
  if(!strcmp(ss,"CONTAIN")) printf("Containment: hóa chất phải được chứa trong các vật chứa. Không cho tiếp xúc với hóa chất khác và nước.\n");
  if(!strcmp(ss,"V")) printf("Reactivity: có thể phản ứng mạnh\n"); 
  if(!strcmp(ss,"1")) printf("Material: Jets\n");
  if(!strcmp(ss,"2")) printf("Material: Fog\n");
  if(!strcmp(ss,"3")) printf("Material: Foam\n");
  if(!strcmp(ss,"4")) printf("Material: Dry agent\n");
  if(!strcmp(ss,"E")) printf("evacuation: tiến hành sơ tán\n");
}

  string getcontent(char* name){
  char* content;
  content = read_file_content("test.txt");
  string* array = cut_string(content,'\n');
  int i,j;
  for(i=0;array[i].s[0]!='\0';i++){
    string* brray = cut_string(array[i].s,'|');
    if(!strcmp(brray[0].s,name)) return array[i];
  }
}

int check1(char c){
  if('0'<c && c<'5')
    return 1;
  else return 0;
}

int check2(char c){
  switch(c){
  case 'P':
  case 'R':
  case 'W':
  case 'X':
    return 1;
  case 'S':
  case 'T':
  case 'Y':
  case 'Z':
    return 2;
  default: 
    return 0;
  }
}

int check3(char c){	
  if(c == 'E'||c == 'e') return 2;
  else if(c == '\0') return 1;
  else return 0;
}

int check4(char* str){
   if(!strcmp(str,"yes")||!strcmp(str,"YES")) return 2;
   if(!strcmp(str,"no")||!strcmp(str,"NO")) return 1;
   return 0;
}

main(){
  char buff1[3],buff2[3],buff3[5],HAZCHEM[4];
  char c;
do{

  printf("nhap ma hoa chat: ");
  scanf("%s",HAZCHEM);
  int flag = 1,flag2=1;

  if(strlen(HAZCHEM)>3||strlen(HAZCHEM)<2){
    printf("\ndo dai xau khong hop le\nvui long nhap lai ma hoa chat\n\n");
    continue;
  }


// check ky tu thu 1
  if(check1(HAZCHEM[0])==0){
    printf("ma ki tu 1 sai\n");
    flag =0;
  }else {
    buff1[0] = HAZCHEM[0];
    buff1[1] = '\0';
  }


// check ky tu thu 2
  if(check2(toupper(HAZCHEM[1]))==0){
    printf("ma ki tu thu 2 sai\n");
    flag =0;
  }else if(check2(toupper(HAZCHEM[1]))==2){
    buff2[0]=toupper(HAZCHEM[1]);
    do{
      printf("Is the S reverse coloured? ");
      scanf("%s",buff3);
      if(check4(buff3) == 0){
        printf("must be yes/no\n");
      }else if(check4(buff3) == 1){
	buff2[1] = '0';
	buff2[2] = '\0';
      }else {
	buff2[1] = '1';
	buff2[2] = '\0';
      }
    }while(check4(buff3) == 0);
  }else {
    buff2[0]=toupper(HAZCHEM[1]);
    buff2[1] = '\0'; 
}


// check ky tu thu 3
if(strlen(HAZCHEM)==3){
  if(check3(HAZCHEM[2])==0){
    printf("ma ki tu thu 3 sai\n");
    flag = 0;
  }else if(check3(HAZCHEM[2])==2){
    buff3[0] =toupper(HAZCHEM[2]);
    buff3[1] = '\0';
  }else{
    flag2=0;
  }
}
// in thong tin ma hoa chat
  if(flag !=0){
    printf("\n*****\nthong tin hoa chat\n******************\n\n");
    string s = getcontent(buff2);
    string* strarray = cut_string(s.s,'|');
    int i;
    thongtin(buff1);
    for(i=1;strarray[i].s[0]!='\0';i++){
    thongtin(strarray[i].s);
  }if(flag2!=0){
    thongtin(buff3);
    }
  }
  printf("\nban muon tiep tuc(y/n): ");
  while((c= getchar()) != '\n');
  scanf("%c",&c);
  // printf("%c\n",c);
}while(c !='n');
  return 0;
}
