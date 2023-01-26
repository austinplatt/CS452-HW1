#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "deq.h"
#include "error.h"

// indices and size of array of node pointers
typedef enum {Head,Tail,Ends} End;

typedef struct Node {
  struct Node *np[Ends];		// next/prev neighbors
  Data data;
} *Node;

typedef struct {
  Node ht[Ends];			// head/tail nodes
  int len;
} *Rep;

static Rep rep(Deq q) {
  if (!q) ERROR("zero pointer");
  return (Rep)q;
}

static void put(Rep r, End e, Data d) 
{
  struct Node* newNode;
  if (e == Head) 
  {
    newNode = (struct Node*)malloc(sizeof(struct Node));
    memset(newNode, 0, sizeof(*newNode));
    newNode->data = d;
    if (r->len == 0) 
    {
        r->ht[Head] = newNode;
        r->ht[Tail] = newNode;
    } else {
        struct Node* prevHead = r->ht[Head];
        r->ht[Head] = newNode;
        prevHead->np[Head] = newNode;
        newNode->np[Tail] = prevHead;
    }
    r->len++;
  }
  if(e == Tail)
  {
    newNode = (struct Node*)malloc(sizeof(struct Node));
    memset(newNode, 0, sizeof(*newNode));
    newNode->data = d;
    if (r->len == 0) 
    {
        r->ht[Tail] = newNode;
        r->ht[Head] = newNode;
    } else {
        struct Node* prevTail = r->ht[Tail];
        r->ht[Head] = newNode;
        prevTail->np[Tail] = newNode;
        newNode->np[Head] = prevTail;
    }
    r->len++;
  }
  free(newNode);
}
static Data ith(Rep r, End e, int i) 
{ 
  if (i < 0 || i >= r->len) 
  {
    printf("Index not found in list.\n");
    return NULL;
  }
  struct Node* currentNode = r->ht[Head];
  for (int j = 0; j != i; j++) 
  {
    if (e == Tail) 
    {
      currentNode = currentNode->np[Head];
    } else if (e == Head) 
    {
      currentNode = currentNode->np[Tail];
    }
  }
  return currentNode->data;
}
static Data get(Rep r, End e)         
{ 
  if (r->len > 2) 
  {
    Data dr = r->ht[e]->data;
    int i = 0;
    if (e == Head) 
    {
      i = 1;
    }
    struct Node* rmlNode = r->ht[e]->np[i];
    rmlNode->np[e] = NULL;
    free(r->ht[e]);
    r->ht[e] = rmlNode;
    r->len = r->len - 1;
    return dr;
  }
  if (r->len == 2) 
  {
    Data dr = r->ht[e]->data;
    int i = 0;
    if (e == Head) 
    {
      i = 1;
    }
    struct Node* rmlNode = r->ht[e]->np[i];
    rmlNode->np[Head] = NULL;
    rmlNode->np[Tail] = NULL;
    free(r->ht[e]);
    r->ht[Head] = rmlNode;
    r->ht[Tail] = rmlNode;
    r->len = r->len - 1;
    return dr;
  }
  if (r->len == 1) 
  {
    struct Node* rwards = r->ht[e];
    r->ht[Head] = NULL;
    r->ht[Tail] = NULL;
    free(r->ht[e]);
    r->len = r->len - 1;
    return rwards->data;
  }
  if (r->len == 0) 
  {
    printf("Error: Cannot remove from the Empty List.\n");
    return NULL;
  }
  return 0;
} 
static Data rem(Rep r, End e, Data d) 
{ 
  if(r->len==0)
  {
    printf("List is empty, data cannot be removed.\n");
    return NULL;
  }
  Node position;
  if(e==Tail)
  {
    position=r->ht[Tail];
  }else if(e==Head)
  {
    position=r->ht[Head];
  } else 
  {
    return NULL;
  }
  while(position != NULL)
  {
    //This section covers if the data is equal
    if(position->data == d)
    {
      if(position==r->ht[Head])
      {
        return get(r,Head);
      } else if(position==r->ht[Tail])
      {
        return get(r,Tail);
      } else
      {
        Data rem_data=position->data;
        Node prevNode = position->np[Head];
        Node nextNode = position->np[Tail];
        prevNode->np[Tail]=nextNode;
        nextNode->np[Head]=prevNode;
        free(position);
        r->len=r->len-1;
        return rem_data;
      }
    }
      //this section covers if data isn't equal
      else
    {
      if(position==r->ht[Head] || position==r->ht[Tail])
      {
        printf("List does not contain this data.\n");
        return NULL;
      } else
      {
        if(e==Tail)
        {
          position=position->np[Head];
        } else if(e==Head)
        {
          position=position->np[Tail];
        }
      }
    }
  }
return NULL;
}

extern Deq deq_new() {
  Rep r=(Rep)malloc(sizeof(*r));
  if (!r) ERROR("malloc() failed");
  r->ht[Head]=0;
  r->ht[Tail]=0;
  r->len=0;
  return r;
}

extern int deq_len(Deq q) { return rep(q)->len; }

extern void deq_head_put(Deq q, Data d) {        put(rep(q),Head,d); }
extern Data deq_head_get(Deq q)         { return get(rep(q),Head); }
extern Data deq_head_ith(Deq q, int i)  { return ith(rep(q),Head,i); }
extern Data deq_head_rem(Deq q, Data d) { return rem(rep(q),Head,d); }

extern void deq_tail_put(Deq q, Data d) {        put(rep(q),Tail,d); }
extern Data deq_tail_get(Deq q)         { return get(rep(q),Tail); }
extern Data deq_tail_ith(Deq q, int i)  { return ith(rep(q),Tail,i); }
extern Data deq_tail_rem(Deq q, Data d) { return rem(rep(q),Tail,d); }

extern void deq_map(Deq q, DeqMapF f) {
  for (Node n=rep(q)->ht[Head]; n; n=n->np[Tail])
    f(n->data);
}

extern void deq_del(Deq q, DeqMapF f) {
  if (f) deq_map(q,f);
  Node curr=rep(q)->ht[Head];
  while (curr) {
    Node next=curr->np[Tail];
    free(curr);
    curr=next;
  }
  free(q);
}

extern Str deq_str(Deq q, DeqStrF f) {
  char *s=strdup("");
  for (Node n=rep(q)->ht[Head]; n; n=n->np[Tail]) {
    char *d=f ? f(n->data) : n->data;
    char *t; asprintf(&t,"%s%s%s",s,(*s ? " " : ""),d);
    free(s); s=t;
    if (f) free(d);
  }
  return s;
}
