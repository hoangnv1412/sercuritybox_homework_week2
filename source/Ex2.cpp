#include "stdafx.h"
#include "string.h"
#include <ctype.h>
#include <malloc.h>
void clear_buffer() {
	int ch;
	while ((ch=getchar()) !='\n' && ch!=EOF);
}

FILE *fr;
FILE *fw;


char filenameR[30];
char filenameW[30];

int count=0;

void catStr(char* content, char* sub){
    int n = strlen(sub);
    int i = 0;
    while (i< n){
        content[count++] = sub[i++];
    }

}

int contextCount=0;
void ex2_search(){
    bool check = true;
	int lines = 1, pos=0;
    int times=0;
    char keyword[30] = "";
    int ln[1000],cl[1000];
	printf("Enter keyword: ");
	scanf("%s", keyword);

    char c;
    fseek( fr, 0, SEEK_SET );
    c = fgetc(fr);
    pos =0;
	while ( !feof(fr) ){
         if (c == EOF) break;
		 if (c == ' '){
            c = fgetc(fr);
            pos++;
            if( c== keyword[0]){
                char word[200];
                int index =0;
                int curPos = pos;
                while ( c != ' '){
                    word[index++] = c;
                    c = fgetc(fr);
                    pos ++;
                }
                word[index] = '\0';
                if ( strcmp(keyword,word) == 0 ) {
                        ln[times] = lines;
                        cl[times] = curPos;
                        times++;
                }
            }

		 }
		 else {
            if (c == '\n') {
                lines++;
                pos =0;
            }
            //check first word in txt file, run max once
            else if ( (c == keyword[0]) & (check) ){
                check = false;
                char word[200];
                int index =0;
                int curPos = pos;
                while ( c != ' '){
                    word[index++] = c;
                    c = fgetc(fr);
                    pos ++;
                }
                word[index] = '\0';
                if ( strcmp(keyword,word) == 0 ) {
                        ln[times] = lines;
                        cl[times] = curPos;
                        times++;
                }
            }
            c = fgetc(fr);
            pos++;
		 }
		 //check if first word = keyword, run max once

		 check = false;


	}

	//printf("lines: %d\n",lines);
	printf("Total appeared times: %d\n",times);

	fprintf(fw,"\n\tContext %d: search keyword\n",++contextCount);
	fprintf(fw,"\tKeyword: %s\n",keyword);
	fprintf(fw,"\tTotal position(s): %d\n",times);

    for (int i=0; i<times; i++){
        printf("\tLn %d, Col %d\n",ln[i],cl[i]);
        fprintf(fw,"\t\tLn %d, Col %d\n",ln[i],cl[i]);
    }

}



void ex2_replace(){
    bool check = true;
    char newword[30]="";
    char keyword[30]="";
    int times=0;
    int lines = 1, pos=0;
    int ln[1000],cl[1000];
    char c;
    char *content = (char *) calloc( 15*1024*1024, sizeof( char ));
    printf("keyword: ",keyword);
    scanf("%s", keyword);
    printf("Enter new keyword: ");
	scanf("%s", newword);

	fseek( fr, 0, SEEK_SET );

    pos=-1;
	while ( !feof(fr) ){
        if (c == ' ') check = true;
        c = fgetc(fr);
        if (c == EOF) break;
        pos++;

        if (c == ' '){
            content[count++] = c;
            c = fgetc(fr);
            pos++;
            if( c == keyword[0]){
                char word[200];
                int index =0;
                int curPos = pos;
                while ( c != ' '){
                    word[index++] = c;
                    c = fgetc(fr);
                    pos ++;
                }

                word[index] = '\0';
                if ( strcmp(keyword,word) == 0 ) {
                    ln[times] = lines;
                    cl[times] = curPos;
                    times++;
                    //fprintf(f_cpy,newword);
                    catStr(content,newword);
                }
                else {
                    //fprintf(f_cpy,word);
                    catStr(content,word);

                }
                //fputc(c,f_cpy); // c == ' '
                content[count++] = c;
            }else {//fputc(c,f_cpy);}
                content[count++] = c;}
        }
        else {
            if (c == '\n') {
                lines++;
                pos =0;
            }
            else if( ( c== keyword[0]) &&(check) ){
                check = false;
                char word[200];
                int index =0;
                int curPos = pos;
                do {
                    word[index++] = c;
                    c = fgetc(fr);
                    pos ++;
                }while ( c != ' ' && c != '.');
                word[index] = '\0';
                if ( strcmp(keyword,word) == 0 ) {
                    ln[times] = lines;
                    cl[times] = curPos;
                    times++;
                    //fprintf(f_cpy,newword);
                    catStr(content,newword);
                }
                else {
                        //fprintf(f_cpy,word);
                        catStr(content,word);
                }

            }
            //fputc(c,f_cpy);
            content[count++] = c;
        }

        check = false;
	}

    //fclose(f_cpy);
    fseek( fr, 0, SEEK_SET );
    fwrite(content,1,count-1,fr);
    fclose(fr);
    fr = fopen(filenameR,"rb+");
    //printf("Content: \n%s\n",content);

    fprintf(fw,"\n\tContext %d: replace by new keyword\n",++contextCount);
    fprintf(fw,"\tKeyword: %s\n",keyword);
    fprintf(fw,"\tNew Keyword: %s\n",newword);
	fprintf(fw,"\tTotal position(s): %d\n",times);


	printf("Total appeared times: %d\n",times);
    for (int i=0; i<times; i++){
        printf("\t\tLn %d, Col %d\n",ln[i],cl[i]);
        fprintf(fw,"\t\tLn %d, Col %d\n",ln[i],cl[i]);
    }

    printf("Replace \"%s\" by \"%s\" successfully\n",keyword,newword);
    printf("%s\n",content);
    free(content);

}

void ex2(){
    printf("Enter file: ");
	scanf("%s",filenameR);
    strcpy(filenameW,"D:\OUTPUT.TXT ");

    if ( (fr = fopen(filenameR,"rb+")) == NULL){
		 printf("cannot open %s\n",filenameR);
		 return;
    }
	else {
		printf("valid file, please choose the feature:\n");
	}

    fw = fopen(filenameW,"w");
    fprintf(fw,"\tInput file: %s\n",filenameR);
	int init=0;
    while (init != 3){
		printf("\t1.Search \n");
		printf("\t2.Replace \n");
		printf("\t3.Exit \n");
		scanf("%d",&init);
		clear_buffer();
		switch(init){
		  case 1: ex2_search(); break;
		  case 2: ex2_replace(); break;
		  case 3: printf("Goodbye."); break;
		  default:{
			  printf("Wrong syntax. Please try again");
			  break;
		  }
    }
    printf("\n\n\n");
    }

}

int _tmain()
{
    ex2();
    fclose(fr);
    fclose(fw);
    return 0;
}

