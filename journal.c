#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct page{
  int no;
  int size;
}page;

typedef struct book{
  page* start;
  int size;
  int len;
  int first;
  int oldd; // distance of oldest page from right side
}book;

// shift the pages of the book in center of allocated space as we are using array with buffer on both sides
void sffinc(book* b){  // shift book for increameneted book
  int sf=b->size/3;
  int i=b->len-1;
  while(i>=0){
    memcpy(b->start+sf+i,b->start+i,sizeof(page));
    i--;
  }
  b->first = sf-1;
}

// shift the pages of the book to start of book as we are reducing size of book
void sffdcr(book* b){
  int i=0;
  while(i<b->len){
    memcpy(b->start+i,b->start+b->first+i+1,sizeof(page));
    i++;
  }
}

// insert page at the start of the book in O(1)
void insertstart(book* b,page p){
  if(b->len==b->size || b->first==-1){
    b->start=realloc(b->start,(b->size*3)*sizeof(book));
    b->size=b->size*3;
    sffinc(b);
  }
  b->oldd++;
  *(b->start+b->first)=p;
   b->first--;
   b->len++;
}

// insert page at last of book in O(1)
void insertlast(book* b,page p){
  if(b->size==b->len || b->first+b->len==b->size){
    b->start=realloc(b->start,(b->size*3)*sizeof(book));
    b->size = b->size*3;
    sffinc(b);
  }
  *(b->start+b->first+b->len+1)=p;
  b->len++;
}

// display page
void ppage(page p){
  printf("%d and %d \n",p.no,p.size);
}

// display whole book
void pbook(book b){
  int i=b.first+1;
  printf("%d length of book and size is %d \n",b.len,b.size);
  while(i<b.first+1+b.len){
    ppage(*(b.start+i));
    i++;
  }
}

// delete the last page of book in O(1)
void deletelast(book *b){
  if(b->len > 0){
    b->len--;
    if(b->len < b->size/3){
      b->start=realloc(b->start,b->size/3*sizeof(page));
      b->first =-1;
      b->size/=3;
    }
    if(b->oldd >= b->len && b->oldd > 0)b->oldd--;
  }
}

// delete the first page of the book in O(1)
void deletefirst(book *b){
  if(b->len>0){
    b->len--;
    b->first++;
    if(b->oldd>0)b->oldd--;
    if(b->len <= b->size/3){
      sffdcr(b);
      b->start=realloc(b->start,b->size/3*sizeof(page));
      b->first =-1;
      b->size/=3;
    }
  }
}

// return the page present on given index
page* get(book *b, int k){
  return (b->start+b->first+k);
}

//return the oldest page in o(1) time
page* oldestpage(book *b){
  printf("%d oldest\n",b->oldd);
  return (b->start+b->first+b->oldd+1);
}

int main(){
  book b;
  b.size=10;
  b.first = 4;
  b.start = malloc(10*sizeof(page));
  page p;
  p.no =1;
  p.size = 111;
  page p1,p3;
  p3.no=19;
  p1.no=2;
  p1.size=222;
  page in;
  in.no=11;
  in.size=11;
  int i=0;
  insertlast(&b,p3);
  while(i<10){
    insertstart(&b,p);
    i++;
  }
  i=0;
  while(i<10){
    insertlast(&b,p1);
    i++;
  }
  i=0;
  while(i<29){
    deletelast(&b);
    i++;
  }
  //ppage(*(b.start+b.first+1));
  printf("%d \n",b.first);
  page *t;
  t=oldestpage(&b);
  ppage(*t);
  pbook(b);
  return 0;
}
