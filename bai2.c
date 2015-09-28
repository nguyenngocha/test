#include <stdio.h>
#include <string.h>
#include "mylibrary.h"

typedef struct student{
  string profile[5];
}student;

typedef struct subject_profile{
  string prof[7];
}subject;

char* get_filename(char* mmh,char*mhk,int rp){
  char *buff = (char*)malloc(15*sizeof(char));
  strcpy(buff,mmh);
  buff[strlen(buff)]='_';
  strcpy(buff+strlen(buff),mhk);
  if(rp==0) strcpy(buff+strlen(buff),".txt");
  else strcpy(buff+strlen(buff),"_rp.txt");
  return buff;
}

char* tinhdiem(int gk,int ck,int ts){
  char* buff = (char*)malloc(2*sizeof(char));
  if(gk*ts + ck*(100-ts)>=850)
    buff[0]='A';
  else if(gk*ts + ck*(100-ts)>=700)
    buff[0]='B';
  else if(gk*ts + ck*(100-ts)>=550)
    buff[0]='C';
  else if(gk*ts + ck*(100-ts)>=400)
    buff[0]='D';
  else
    buff[0]='F';
  buff[1]='\0';
  return buff;
}

int checkscore(char* buff){
  if(!isnumber(buff)) return 0;
  int CS = atoi(buff);
  if(CS>10||CS<0) return 0;
  return 1;
}

char* getStudentInfo(int F){
  student student;
  int i,c;
  strcpy(student.profile[0].s,"s");
  do{
    printf("MSSV: ");
    scanf("%s",student.profile[1].s);
    if(!isnumber(student.profile[1].s)) printf("MSSV khong hop le\nmssv phai la 1 chuoi so\nnhap lai\n\n");
  }while(!isnumber(student.profile[1].s));

  while((c=getchar())!='\n');
  printf("Hodem: ");
  gets(student.profile[2].s);
  printf("Ten: ");
  gets(student.profile[3].s);
  do{
    printf("Diem giua ky: ");
    scanf("%s",student.profile[4].s);
    if(!checkscore(student.profile[4].s)) printf("diem giua ky phai la so tu 0 den 10\n nhap lai \n\n");
  }while(!checkscore(student.profile[4].s));
  
  do{
    printf("Diem cuoi ky: ");
    scanf("%s",student.profile[5].s);
    if(!checkscore(student.profile[5].s)) printf("diem cuoi ky phai la so tu 0 den 10\n nhap lai \n\n");
  }while(!checkscore(student.profile[5].s));

  strcpy(student.profile[6].s,tinhdiem(atoi(student.profile[4].s),atoi(student.profile[5].s),F));
  student.profile[7].s[0]='\0';
  char* student_info = (char*)malloc(100*sizeof(char));
  strcpy(student_info,join_string(student.profile,'|'));
  return student_info;
}

int isnumber(char* buff){
  int i;
  for(i=0;i<strlen(buff);i++){
    if(buff[i]>'9'||buff[i]<'0')
      return 0;
  }
  return 1;
}

int checkF(char* buff){
  int f= atoi(buff);
  if(f>=100||f<=0){
    return 0;
  }
  return 1;
}

void getSubjectProfile(){
  subject* SubProfile =(subject*)malloc(sizeof(subject));
  char* buff = (char*)malloc(15*sizeof(char));
  char* buffxx = (char*)malloc(15*sizeof(char));
  char c;
  //get subject id
  printf("Subject ID: ");
  strcpy(SubProfile[0].prof[0].s,"Subject ID|");
 while((c=getchar())!='\n');
  gets(buffxx);
  strcpy(SubProfile[0].prof[0].s + strlen(SubProfile[0].prof[0].s),buffxx);
  // get subject name
  printf("Subject Name: ");
  strcpy(SubProfile[0].prof[1].s,"Subject Name|");
  gets(SubProfile[0].prof[1].s + strlen(SubProfile[0].prof[1].s));
  //get F
  do{
    printf("F: ");
    gets(buff);
    if(!isnumber(buff)||!checkF(buff)) printf("F: %s la  khong hop le\nsemester la 1 so tu 0 den 100\nNhap lai\n\n",buff);
  }while(!isnumber(buff)||!checkF(buff));    
  strcpy(SubProfile[0].prof[2].s,"F|");
  strcpy(SubProfile[0].prof[2].s+strlen(SubProfile[0].prof[2].s),buff);
  int f = atoi(buff);
  f = 100-f;
  sprintf(buff,"%d",f);
  SubProfile[0].prof[2].s[strlen(SubProfile[0].prof[2].s)]='|';
  strcpy(SubProfile[0].prof[2].s+strlen(SubProfile[0].prof[2].s),buff);
  //get semester
  printf("semester: ");
  strcpy(SubProfile[0].prof[3].s,"semester|");
  gets(buff);
  strcpy(SubProfile[0].prof[3].s + strlen(SubProfile[0].prof[3].s),buff);
  char* filename = get_filename(buffxx,buff,0);
  //get student number

  do{
  printf("studentNumber: ");
  scanf("%s",buff);
  if(!isnumber(buff)||!checkF(buff)) printf("so sinh vien: %s la khong hop le\nso sinh vien phai la 1 so tu 0 den 100\nnhap lai\n\n",buff);
  }while(!isnumber(buff)||!checkF(buff));
  strcpy(SubProfile[0].prof[4].s,"studentNumber|");
  strcpy(SubProfile[0].prof[4].s+strlen(SubProfile[0].prof[4].s),buff);
  char* subject = join_string(SubProfile[0].prof,'\n');
  //write file 
  write_file_content(subject,filename);
  printf("Maked subject profile successfully\n");
} 

void addscore(){
  char* subid = (char*)malloc(10*sizeof(char));
  char* semester = (char*)malloc(10*sizeof(char));
  char* filename;
  char* rstring;

  do{
    printf("Nhap ma mon hoc: ");
    scanf("%s",subid);
    printf("Nhap hoc ky: ");
    scanf("%s",semester);
    filename = get_filename(subid,semester,0);
    rstring = read_file_content(filename);
  if(rstring[0]=='0') printf("khong ton tai du lieu ve mon hoc %s trong hoc ky %s\nnhap lai\n\n",subid,semester);
  }while(rstring[0]=='0');

  string* arr = cut_string(rstring,'\n');
  string* brr = cut_string(arr[2].s,'|');
  char* student_info = getStudentInfo(atoi(brr[1].s));  
  
  rstring[strlen(rstring)] = '\n';
  strcpy(rstring+strlen(rstring),student_info);
  write_file_content(rstring,filename);
}

char* delete(char* rstring,int i){
  string* arr = cut_string(rstring,'\n');
  int count;
  for (count =i; arr[count].s[0]!='\0'; count++){
    strcpy(arr[count].s,arr[count+1].s);
  }
  rstring = join_string(arr,'\n');
  //printf("%s\n",rstring);
  return rstring;
}

void delete_student_info(){
  char* subid = (char*)malloc(10*sizeof(char));
  char* semester = (char*)malloc(10*sizeof(char));
  char* studentid = (char*)malloc(10*sizeof(char));
  char* filename;
  char* rstring;

  do{
    printf("Nhap ma mon hoc: ");
    scanf("%s",subid);
    printf("Nhap hoc ky: ");
    scanf("%s",semester);
    filename = get_filename(subid,semester,0);
    rstring = read_file_content(filename);
  if(rstring[0]=='0') printf("khong ton tai du lieu ve mon hoc %s trong hoc ky %s\nnhap lai\n\n",subid,semester);
  }while(rstring[0]=='0');
    printf("Nhap MSSV cua sv can xoa: ");
    scanf("%s",studentid);

  string* brr = cut_string(rstring,'\n');
  int i,err = 1;
  for (i = 5; brr[i].s[0]!='\0'; i++){
    string* crr = cut_string(brr[i].s,'|');
   if(strcmp(crr[1].s,studentid) ==0){
      rstring = delete(rstring,i);
      err = 0;
    }
  }
  if(err == 1) printf("Khong tim thay MSSV can xoa\n");
  else{
    //printf("%s\n",rstring);
    write_file_content(rstring,filename);
    printf("Xoa thanh cong sinh vien co mssv: %s\n",studentid);
  }
}

void find_score_student(){
  char* subid = (char*)malloc(10*sizeof(char));
  char* semester = (char*)malloc(10*sizeof(char));
  char* studentid = (char*)malloc(10*sizeof(char));

  char* filename;
  char* rstring;

  do{
    printf("Nhap ma mon hoc: ");
    scanf("%s",subid);
    printf("Nhap hoc ky: ");
    scanf("%s",semester);
    filename = get_filename(subid,semester,0);
    rstring = read_file_content(filename);
  if(rstring[0]=='0') printf("khong ton tai du lieu ve mon hoc %s trong hoc ky %s\nnhap lai\n\n",subid,semester);
  }while(rstring[0]=='0');
  printf("Nhap MSSV cua sv can xoa: ");
  scanf("%s",studentid);
  
  string* arr = cut_string(rstring,'\n');
  int i,err = 1;
  for (i = 5; arr[i].s[0]!='\0'; i++){
    string* brr = cut_string(arr[i].s,'|');
   if(strcmp(brr[1].s,studentid) == 0){
      err = 0;
      break;
    }
  }
  if(err == 1) printf("Khong tim thay MSSV can xoa\n");
  else{
    string* brr = cut_string(arr[i].s,'|');
    printf("Thong tin diem\n");
    printf("Ho ten SV: %s %s\n",brr[2].s,brr[3].s);
    printf("Diem giua ky: %s\n",brr[4].s);
    printf("Diem cuoi ky: %s\n",brr[5].s);
    printf("Xep loai: %s\n",brr[6].s);
  }
}



void display_score(){
  char* subid = (char*)malloc(10*sizeof(char));
  char* semester = (char*)malloc(10*sizeof(char));
  char* studentid = (char*)malloc(10*sizeof(char));
  char* filename;
  char* rstring;

  do{
    printf("Nhap ma mon hoc: ");
    scanf("%s",subid);
    printf("Nhap hoc ky: ");
    scanf("%s",semester);
    filename = get_filename(subid,semester,0);
    rstring = read_file_content(filename);
  if(rstring[0]=='0') printf("khong ton tai du lieu ve mon hoc %s trong hoc ky %s\nnhap lai\n\n",subid,semester);
  }while(rstring[0]=='0');

  string* arr = cut_string(rstring,'\n');
  int i,err = 1;

  string* score_board = (string*)malloc(6*sizeof(string));
  score_board[6].s[0]='\0';
  sprintf(score_board[0].s,"A historygram of the subject %s is:",subid);
  strcpy(score_board[1].s,"A:");
  strcpy(score_board[2].s,"B:");
  strcpy(score_board[3].s,"C:");
  strcpy(score_board[4].s,"D:");
  strcpy(score_board[5].s,"F:");

  for (i = 5; arr[i].s[0]!='\0'; i++){
    string* brr = cut_string(arr[i].s,'|');
    switch(brr[6].s[0]){
      case 'A':
        strcpy(score_board[1].s+strlen(score_board[1].s),"*\0");
        break;
      case 'B':
        strcpy(score_board[2].s+strlen(score_board[2].s),"*\0");
        break;
      case 'C':
        strcpy(score_board[3].s+strlen(score_board[3].s),"*\0");
        break;
      case 'D':
        strcpy(score_board[4].s+strlen(score_board[4].s),"*\0");
        break;
      case 'F':
        strcpy(score_board[5].s+strlen(score_board[5].s),"*\0");
        break;
      default:
        break;
    }
  }
  char* content = join_string(score_board,'\n');
  printf("%s\n",content);
  filename = get_filename(subid,semester,1);
  // printf("%s\n\n",filename);
  write_file_content(content,filename);
}



main(){

  int sw;
  do{
    printf("\n\nLearning Management System\n-------------------------------------\n");
    printf("1. Add a new score board\n");
    printf("2. Add score\n");
    printf("3. Remove score\n");
    printf("4. Search score\n");
    printf("5. Display score board and score report\n");
    printf("6. Exit\n");
    printf("choice: ");
    scanf("%d",&sw);
    switch(sw){
      case 1:
        getSubjectProfile();
        break;
      case 2:
        addscore();
        break;
      case 3:
        delete_student_info();
        break;
      case 4:
        find_score_student();
        break;
      case 5:
        display_score();
        break;
      case 6:
        break;
      default:
        printf("Nhap sai! vui long nhap lai\n");
        break;
    }
  }while(sw!=6);
  return 0;
}

