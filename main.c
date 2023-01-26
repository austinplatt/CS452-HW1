#include <stdio.h>
#include <stdlib.h>

#include "deq.h"

int main() {
  testOne();
  testTwo();
  testThree();
  testFour();
  testFive();
  testSix();
  testSeven();
  testEight();
}

static void testOne()
{
  Deq q = deq_new();
  char letter1 = 'z';
  char *point = &letter1;
  deq_head_put(q, point);
  if (deq_len(q) == 1) 
  {
    printf("Pass: Test 1\n");
  } else 
  {
    printf("Fail: Test 1\n");
  }
  deq_del(q, 0);
}

static void testTwo()
{
  Deq q=deq_new();
  if(deq_head_get(q)==NULL)
  {
    printf("Pass: Test 2\n");
  }
  else
  {
    printf("Fail: Test 2\n");
  }
  deq_del(q,0);
}

static void testThree() 
{
  Deq q=deq_new();
  if(deq_head_rem(q,0)==NULL)
  {
    printf("Pass: Test 3\n");
  }
  else
  {
    printf("Fail: Test 3\n");
  }
  deq_del(q,0);
}

static void testFour()
{
  Deq q=deq_new();
  if(deq_tail_get(q)==NULL)
  {
    printf("Pass: Test 4\n");
  }
  else
  {
    printf("Fail: Test 4\n");
  }
  deq_del(q,0);
}

static void testFive()
{
  Deq q=deq_new();
  if(deq_head_rem(q,0)==NULL)
  {
    printf("Pass: Test 5\n");
  }
  else
  {
    printf("Fail: Test 5\n");
  }
  deq_del(q,0);
}

static void testSix() 
{
  Deq q = deq_new();
  char letter1 = 'z';
  char *point = &letter1;
  deq_tail_put(q, point);
  if (deq_len(q) == 1) 
  {
    printf("Pass: Test 6\n");
  } else 
  {
    printf("Fail: Test 6\n");
  }
  deq_del(q, 0);
}

static void testSeven()
{
  Deq q = deq_new();
  char letter1 = 'z';
  char *point = &letter1;
  deq_head_put(q, point); 
  char letter2 = 'y';
  char *point2 = &letter2;
  deq_head_put(q, point2);
  if (point == deq_tail_get(q)) 
  {
    printf("Pass: Test 7\n");
  } else 
  {
    printf("Fail: Test 7\n");
  }
  deq_del(q, 0);
}

static void testEight()
{
  Deq q = deq_new();
  char letter1 = 'z';
  char *point = &letter1;
  deq_head_put(q, point); 
  char letter2 = 'y';
  char *point2 = &letter2;
  deq_head_put(q, point2);
  if (point2 == deq_tail_get(q)) 
  {
    printf("Pass: Test 8\n");
  } else 
  {
    printf("Fail: Test 8\n");
  }
  deq_del(q, 0);
}

//remainder ?