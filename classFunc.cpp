#include "infix.h"

int debugMode = 0;

/* Default constructor */
MyStack::MyStack()
{
  init();
}
/* initialize the stack */
void MyStack::init()
{
  size = 2;
  inUse = 0;
  topVal = 0;
  dynArr = new int[size];
  for ( int i = 0; i < size; i++ )
  {
    dynArr[i] = 0;
  }
}

/* check if the stack is empty */
bool MyStack::isEmpty()
{
  if ( inUse == 0 )
  {
    return true;
  }
  else
  {
    return false;
  }
}

/* return the top value in the stack */
int MyStack::top()
{
  if ( inUse == 0 )
  {
    return -1;
  }
  else
  {
    if ( debugMode == 1 )
    {
      printf("TopVal is: %d,  inUse: %d\n", topVal, inUse);
      printf("DynArr[inUse]: %d,   dynArr[topVal]: %d\n", dynArr[inUse], dynArr[topVal]);
      //return dynArr[inUse];
    }
    return dynArr[inUse-1];
  }
}
/* grow the dynamic array */
void MyStack::grow()
{
  int i;
  int *tmp = dynArr;
  size = size + 2;
  for ( i = 0; i < size; i++ )
  {
    tmp[i] = dynArr[i];
  }
  dynArr = tmp;
}
/* pushes value into the stack */
void MyStack::push(int value )
{
  /* check if the space is the same as the size of the dynamic array */
  if ( inUse == size )
  {
    grow();
    //push( value );
  }
  else
  {
    dynArr[inUse] = value;
    topVal = dynArr[inUse];
    inUse++;
  }
}

void MyStack::push( char op )
{
  /* check if the space is the same as the size of the dynamic array */
  if ( inUse == size )
  {
    grow();
    //push( op );
  }
  else
  {
    dynArr[inUse] = op;
    topVal = dynArr[inUse];
    inUse++;
  }
}
/* pops the top value from the stack */
void MyStack::pop()
{
  int tmp;

  /* check if stack is empty */
  if ( isEmpty() == true )
  {
    printf("*** ERROR: CANT POP EMPTY STACK ***\n");
  }
  else
  {
    //tmp = dynArr[inUse];
    inUse--;
  }
}
/* display the stack */
void MyStack::displayVals()
{
  int i;
  printf("This stack contains: ");
  for ( i = 0; i < inUse; i++ )
  {
    printf("%d ", dynArr[i]);
  }

  printf("\n\n");
}

void MyStack::displayOps()
{
  int i;
  printf("This stack contains: ");
  for ( i = 0; i < inUse; i++ )
  {
    printf("%c ", dynArr[i]);
  }

  printf("\n\n");
}


/* reset the stack */
void MyStack::reset()
{
  int i;
  size = 2;
  topVal = 0;
  inUse = 0;
  int *tmp = new int[size];
  delete[] dynArr;
  dynArr = tmp;
}

int popAndEval( MyStack intStack, MyStack opStack )
{
  /* values for arithmetic expression */
  char op;
  int v1, v2;
  ////////////////////////////////////////
  /* operator */
  op = opStack.top();
  /* check if its only value */
  if ( op == -1 )
  {
    if ( debugMode == 1 )
    {
      printf("*** ERROR: cannot access empty stack ***\n");
    }
    return -999;
  }
  printf("OP stack: ");
  opStack.displayOps();
  opStack.pop();
  //printf("Pop&Eval operatorSTack has: ");
  //opStack.displayOps();

  ////////////////////////////////////////
  /* operands */
  v2 = intStack.top();
  if ( v2 == -1 )
  {
    if ( debugMode == 1 )
    {
      printf("*** ERROR: cannot access empty stack ***\n");
    }
    return -999;
  }
  // const int tmp1 = v1;
  intStack.pop();
  //intStack.displayVals();

  v1 = intStack.top();
  if ( v1 == -1 )
  {
    if ( debugMode == 1 )
    {
      printf("*** ERROR: cannot access empty stack ***\n");
    }
    return -999;
  }
  // const int tmp2 = v2;
  intStack.pop();

  //opStack.displayOps();
  //intStack.displayVals();
  // printf("Pop&Eval valueStack has: ");
  // intStack.displayVals();

  printf("Value of op: %c\n", op);
  printf("Value of v1: %d,   value of v2: %d\n", v1, v2);
  //printf("Value of tmp1: %d,   value of tmp2: %d\n", tmp1, tmp2);
  int solution;
  /* check operator */
  if ( op == '*' )
  {
    //solution = tmp1 * tmp2;
    solution = v1 * v2; 
  }
  else if ( op == '/' )
  {
    //solution = tmp2 / tmp1;
    solution = v2 / v1;
  }
  else if ( op == '+' )
  {
    //solution = tmp1 + tmp2;
    solution = v1 + v2;
  }
  else if ( op == '-' )
  {
    solution = v1 - v2; 
  }
  else
  {
    printf("*** Error: cannot evalauate, operator is not arithmetic ***\n");
  }

  /* return the solution */
  //printf(" (1) %d\n", intStack.top());
  intStack.push( solution );
  //printf("Solution: %d\n", solution);
  //printf("(2) %d\n", intStack.top());
  //printf("(3) Pop&Eval valueStack has: ");
  printf("INT stack: ");
  intStack.displayVals();
  printf("OP stack: ");
  opStack.displayOps();
  //opStack.pop();
  return 1;
}
 
int main(int argc, char *argv[])
{
    /***************************************************************/
    /* Add code for checking command line arguments for debug mode */
    int i;
    /* debug mode check */
    for ( i = 0; i < argc; i++ )
    {
      if ( strcmp(argv[i], "-d") == 0 )
      {
        printf("\nDEBUG MODE IS ON\n");
        debugMode = 1;
      }
    }
 
    Token inputToken;
    TokenReader tr;
 
    printf ("Starting Expression Evaluation Program\n\n");
    printf ("Enter Expression: ");
 
 
    inputToken = tr.getNextToken ();
 
    while (inputToken.equalsType(QUIT) == false)
    {
      /* check first Token on Line of input */
      if(inputToken.equalsType(HELP))
      {
       printCommands();
       tr.clearToEoln();
      }
      else if(inputToken.equalsType(ERROR))
      {
       printf ("Invalid Input - For a list of valid commands, type ?\n");
       tr.clearToEoln();
      }
      else if(inputToken.equalsType(EOLN))
      {
       printf ("Blank Line - Do Nothing\n");
       /* blank line - do nothing */
      }
      else
      {
       processExpression(inputToken, &tr);
      }
 
      printf ("\nEnter Expression: ");
      inputToken = tr.getNextToken ();
    }
 
  printf ("Quitting Program\n");
  return 1;
}
 
void processExpression (Token inputToken, TokenReader *tr)
{
 /**********************************************/
 /* Declare both stack head pointers here      */
 MyStack valueStack;
 MyStack operatorStack;

 
 
 /* Loop until the expression reaches its End */
 while (inputToken.equalsType(EOLN) == false)
   {
    /* The expression contain a VALUE */
    if (inputToken.equalsType(VALUE))
      {
       /* make this a debugMode statement */
       if ( debugMode == 1 )
       {
          printf("Value: %d\n", inputToken.getValue() );
       }
 
       // add code to perform this operation here
       valueStack.push( inputToken.getValue() );
       //printf("Top value in int stack: %d\n", valueStack.top());
      }
 
    /* The expression contains an OPERATOR */
    if (inputToken.equalsType(OPERATOR))
      {
       /* make this a debugMode statement */
       if ( debugMode == 1 )
       {
          printf("Operator: %c\n", inputToken.getOperator() );
       }
       /* check for open parenthesis */
       if ( inputToken.getOperator() == '(' )
       {
         operatorStack.push(inputToken.getOperator());
       }
       if ( inputToken.getOperator() == '+' || inputToken.getOperator() == '-' )
       {
         while ( operatorStack.isEmpty() != true 
              && (operatorStack.top() == '+' || operatorStack.top() == '-' 
              || operatorStack.top() == '*' || operatorStack.top() == '/'))
         {
           popAndEval( valueStack, operatorStack );
           return;
         }

         // add code to perform this operation here
         operatorStack.push( inputToken.getOperator() );
         
         //printf("Top value in char stack: %c\n", operatorStack.top());
       }
       if ( inputToken.getOperator() == '*' || inputToken.getOperator() == '/' )
       {
         while ( operatorStack.isEmpty() != true 
             && (operatorStack.top() == '*' || operatorStack.top() == '/') )
            {
              popAndEval( valueStack, operatorStack );
              return;
            }
         operatorStack.push( inputToken.getOperator() );
       }
      //  if(inputToken.equalsType(EOLN))
      //  {
         
      //  }
       if ( inputToken.getOperator() == ')' )
       {
         while ( operatorStack.isEmpty() != true && operatorStack.top() != '(' )
         {
           popAndEval( valueStack, operatorStack );
           return;
         }
         if ( operatorStack.isEmpty() == true )
         {
           printf("*** ERROR: stack is empty ***\n");
         }
         else
         {
           operatorStack.pop();
         }
       }
      }
    /* get next token from input */
    inputToken = tr->getNextToken ();
   }
 
 /* The expression has reached its end */
 
 // add code to perform this operation here
 while ( operatorStack.isEmpty() != true )
 {
   if ( popAndEval( valueStack, operatorStack ) != -999 )
   {
     return;
   }
   //popAndEval( valueStack, operatorStack );
 }
/* get solution */
 int solution = valueStack.top();
 if ( solution == -1 )
 {
   if ( debugMode == 1 )
   {
     printf("*** ERROR: stack is empty ***\n");
     return;
   }
   return;
 }
/* print solution */
 printf("The answer is: %d\n", solution );
/* pop solution */
valueStack.pop();

if ( valueStack.isEmpty() != true )
{
  if ( debugMode == 1 )
  {
    printf("*** ERROR: stack is not empty after evaluation\n");
    return;
  }
  return;
}
 valueStack.reset();
 operatorStack.reset();
 printf ("\n");
}