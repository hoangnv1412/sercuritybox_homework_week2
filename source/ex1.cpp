
#include "stdafx.h"
#define MAX 200
#define difference 4
typedef struct{
  char c;
  int i;
}keyType;
typedef keyType StackType[MAX];

//Stack Function

StackType a;
StackType res;
int top;
void init(StackType stack){
  top = 0;
}

int isEcountpty(){
  return top == 0;
}

int isFull(){
  return top == MAX;
}

void push(keyType el, StackType stack){
  if (isFull())
    printf("stack overflow");
  else stack[top++] = el;
}

keyType pop(StackType stack){
  if(isEcountpty())
    printf("stack underflow");
  else return stack[--top];
}

int encode(char *c){
  switch(*c){
  case '(': return 3;
  case '[': return 2;
  case '{': return 1;
  case ')': return -1;
  case ']': return -2;
  case '}': return -3;
  default: return 0;
  }
}
char decode(int i){
  switch(i){
  case 3: return '(';
  case 2: return '[';
  case 1: return '{';
  case -1: return ')';
  case -2: return ']';
  case -3: return '}';
  default: return '\0';
  }
}

void ex1()
{
	init(a);
	int openBracket = 0;
	int len=0,i=0,count=0,position =-1;
	char c;
	keyType tmp ={0};
	int type=0, pair =0;
	printf("Enter brackets: ");
	while ( 1 ){
        c = getchar();
        type = encode(&c);
        if(type == 0){//end of string
        //fix left-over open brackets
            while(!isEcountpty()){
            tmp = pop(a);
              pair = encode(&(tmp.c));
              res[count].c = decode(pair - difference);
              res[count].i = ++position;
              count++;
            }
            break;
            }else{
        position++;
        if(type > 0){//case inputted char is an open bracket
          if(!isFull()){
            keyType temp;
            temp.c = c;
            temp.i = position;
            push(temp,a);
          }

          else{
            printf("Error: Stack overflow!\n");
            return;
          }
        }else{
          if(!isEcountpty()){
            while(!isEcountpty()){
              tmp = pop(a);
              pair = encode(&(tmp.c));
              if((type + difference) != pair){
                res[count].c = decode(pair - difference);
                res[count].i = tmp.i;
                count++;
              }
              else{
                type = 1;
                break;
                }
            }
            if(type != 1){
            res[count].c = decode(type + difference);
            res[count].i = tmp.i;
            count++;
            }
          }else{
            res[count].c = decode(type + difference);
            res[count].i = tmp.i;
            count++;
          }
        }
      }
	}

	printf("%d \n",count);

    for(i = 0; i < count; i++){
      printf("%c %i\n",res[i].c, res[i].i);
    }
}

int _tmain()
{
    ex1();
    return 0;
}
