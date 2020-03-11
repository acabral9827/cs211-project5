#include <cstdio>
#include <cstring>
#include <cctype>


// Enumarated Type specifying all of the Tokens
enum TokenType{
  ERROR, OPERATOR, VALUE, EOLN, QUIT, HELP, EOFILE
};

// Class to hold the Token information
class Token
{
  private:
    TokenType type;
    char      op;       // using '$' as undefined/error
    int       val;      // using -999 as undefined/error
 
  public:
 
  // Default to initialize to the ERROR TokenType
  Token()
  {
    type = ERROR;
    op = '$';
    val = -999;
  }
 
  // Initialize to a specific TokenType
  Token (TokenType t)
  {
    type = t;
    op = '$';
    val = -999;
  }
 
  // Set to a specific TokenType
  void setToType(TokenType t)
  {
    type = t;
    op = '$';
    val = -999;
  }
 
  // Set to a OPERATOR TokenType with specific operator value
  void setToOperator(char c)
  {
    type = OPERATOR;
    op = c;
    val = -999;
  }
 
  // Set to a VALUE TokenType with a specific numeric value
  void setToValue(int v)
  {
    type = VALUE;
    op = '$';
    val = v;
  }
 
  // return true if the Current Token is of the given TokenType
  bool equalsType(TokenType t)
  {
    if (type == t)
      return true;
    else
      return false;
  }
 
  // return true if the Current Token is of the OPERATOR TokenType
  //     and contains the given operator character
  bool equalsOperator(char c)
  {
    if (type == OPERATOR && op == c)
      return true;
    else
      return false;
  }
 
  // Return the Operator for the current Token
  //   verify the current Token is of the OPERATOR TokenType
  char getOperator ()
  {
    if (type == OPERATOR)
      return op;
    else
      return '$';   // using $ to indicate an error value
  }
 
  // Return the Value for the current Token
  //   verify the current token is of the value TokenType
  int getValue()
  {
    if (type == VALUE)
      return val;
    else
      return -999;  // using -999 to indicate an error value
  }
};

class TokenReader
{
  private:
     char inputline[300];  // this assumes that all input lines are 300 characters or less in length
     bool needline;
     int pos;
 
 
  public:
 
  // initialize the TokenReader class to read from Standard Input
  TokenReader()
  {
    // set to read from Standard Input
    inputline[0] = '\0';
    pos = 0;
    needline = true;
  }
 
  // Force the next getNextToken to read in a line of input
  void clearToEoln()
  {
    needline = true;
  }
 
  // Return the next Token from the input line
  Token getNextToken()
  {
    char* endCheck;
 
    //printf ("getToken %d, %d, %s\n", pos, needline, inputline);
 
    // get a new line of input from user
    if (needline)
    {
      endCheck = fgets ( inputline, 300, stdin);
 
      if (endCheck == NULL )
      {
        printf ("Error in reading");
        Token t(EOFILE);
        return t;
      }
 
      for (int i = 0 ; i < strlen(inputline) ; i++)
          if ('\n' == inputline[i])
              inputline[i] = ' ';
      strcat (inputline , " ");    // add a space at end to help deal with digit calculation
      needline = false;
      pos = 0;
    }
 
    // skip over any white space characters in the beginning of the input
    while ( pos < strlen(inputline) && isspace(inputline[pos]) )
    {
      pos++;
    }
 
    // check for the end of the current line of input
    if (pos >= strlen(inputline))
    { // at end of line
      needline = true;
      Token t(EOLN);
      return t;
    }
 
    // Get the next character from the input line
    char ch = inputline[pos]; pos++;
 
    // check if 'q' or 'Q' was entered ==> QUIT Token
    if ( 'q' == ch || 'Q' == ch )
    {
      return Token (QUIT);
    }
 
    // check if "?" was entered ==> HELP Token
    if ( '?' == ch )
    {
      return Token (HELP);
    }
 
    // check for Operator values of: + - * / ( )  ==> OPERATOR Token
    if ( ('+' == ch) || ('-' == ch) || ('*' == ch) ||
      ('/' == ch) || ('(' == ch) || (')' == ch) )
    {
      Token t;
      t.setToOperator( ch );
      return t;
    }
 
    // check for a number  ==> VALUE Token
    if (isdigit(ch))
    {
      int number = int (ch) - int('0');  // subtract ascii value of ch from ascii value of '0'
      ch = inputline[pos]; pos++;
      while (isdigit(ch))
      {
        number = number * 10 + int (ch) - int('0');
        ch = inputline[pos]; pos++;
      }
      pos--; // since number calcuation check one character after the last digit
      Token t;
      t.setToValue( number );
      return t;
    }
 
    // Input in not valid if code get to this part ==> ERROR Token
    return Token (ERROR);
  }
 
};

class MyStack
{
  public:
      MyStack();  // default constructor ( calls init() )
      void init();           // initializes the stack
      bool isEmpty();       // checks if stack is empty
      int intTop();        // returns top value in int stack
      char charTop();      // returns top value in char stack
      void grow();     // grows the dynamic array
      void push( int value );   // pushes int value into int stack
      void push( char op );  // pushes char value into char stack
      int top();     // returns top value in stack 
      void pop();
      //void intPop();        // pops top int value from stack
      //void charPop();        // pops top char value from stack
      void displayVals();
      void displayOps();
      //int popAndEval( MyStack intStack, MyStack opStack );
      void reset();   // resets the stack values

  private:
      int *dynArr;
      int size;          // total amount of space allocated
      int inUse;        // space in use
      int topVal;      // value at the top of the stack
};

void processExpression (Token inputToken, TokenReader *tr);
int popAndEval( MyStack intStack, MyStack opStack );

void printCommands();
