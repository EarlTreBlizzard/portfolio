// libraries
#include <cstdio>
#include <algorithm>

using namespace std;
//proto functions
void printSequence(int);
int longest (int,int);
int largest(int,int);
int length(int);
int next(int);

//main() gets input a value from the user and builds
//a hailstone sequence using that value

int main()
{
  int n;
  //gets the desired value
  printf ("What value would you like to start a hailstone sequence with.\n");
  scanf ("%d",&n);
  int t=longest(n,1);
  //prints all of the information about the hailstone sequence.
  printf ("The sequence is:\n");
  printSequence(n);
  printf ("\nThe length of the hailstone sequence is %d.\n",length(n));
  printf ("The largest value in the hailstone sequence is %d.\n",largest(n,0));
  printf ("The longest hailstone sequence starting with a number up to %d has length %d.\n",n,length(t));
  printf ("The longest hailstone sequence starting with a number up to %d begins with %d.\n",n,t);
}

//longest(t,m) returns the number that has the longest hailstone sequence
//less than or equal to t.

int longest(int t,int m)
{
  if (t==1)
  {
    return m;
  }
  if (t==0)
  {
    return 0;
  }
  if(length(t)>length(m))
  {
    return longest(t-1,t);
  }
  else
  {
    return longest(t-1,m);
  }
}

//printSequence(a) prints the numbers in the hailstone sequence of a.

void printSequence(int a)
{
  if (a!=1)
  {
    printf("%d ",a);
    printSequence(next(a));
  }
  else
  {
  printf("%d",a);
  }
}

//largest(z) returns the largest number in the hailstone sequencem of z.

int largest(int z,int m)
{
  if(z==0)
  {
    return 0;
  }
  if (z==1)
  {
    return m;
  }
  else
  {
    return largest(next(z),max(z,m));
  }
}

//length(y) returns the total length of the hailstone sequence of y.

int length(int y)
{ 
  if(y==1)
  {
    return 1;
  }
  else
  {
    return 1+length(next(y));
  }
}

//next(x) returns the next number in the hailstone sequence of x.

int next(int x)
{
  if(x%2==0)
  { 
    return x/2;
  }
  return 3*x+1;
}
