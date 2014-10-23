#include <iostream>
#include <string>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <cstdio>

using namespace std;
// This is the token type, and contains all possible tokens in our language.
typedef enum {
    T_PLUS,
    T_MINUS,
    T_MULTIPLY,
    T_POWER,
    T_DIVIDE,
    T_OPENPAREN,
    T_CLOSEPAREN,
    T_OPENBRACKET,
    T_CLOSEBRACKET,
    T_EQUALS,
    T_SEMICOLON,
    T_M,
    T_PRINT,
    T_NUMBER,
    T_EOF,
	T_NEWLINE,
	T_WHITESPACE,
	T_NONTOKEN
} token;

typedef enum {
	N_START,
	N_STATEMENTS,
	N_STATEMENTSP,
	N_STATEMENT,
	N_EXPRESSION,
	N_EXPRESSIONP,
	N_TERM,
	N_TERMP,
	N_EXPONENTIATION,
	N_EXPONENTIATIONP,
	N_FACTOR
} nonterminal;	

// This function will convert a token to a string, for display.
std::string tokenToString(token toConvert) {
    switch (toConvert) {
        case T_PLUS:
            return std::string("+");
        case T_MINUS:
            return std::string("-");
        case T_MULTIPLY:
            return std::string("*");
        case T_POWER:
            return std::string("**");
        case T_DIVIDE:
            return std::string("/");
        case T_OPENPAREN:
            return std::string("(");
        case T_CLOSEPAREN:
            return std::string(")");
        case T_OPENBRACKET:
            return std::string("[");
        case T_CLOSEBRACKET:
            return std::string("]");
        case T_EQUALS:
            return std::string("=");
        case T_SEMICOLON:
            return std::string(";");
        case T_M:
            return std::string("M");
        case T_PRINT:
            return std::string("print");
        case T_NUMBER:
            return std::string("number");
        case T_EOF:
            return std::string("EOF");
		case T_NEWLINE:
            return std::string("NEWLINE");
		case T_NONTOKEN:
            return std::string("NONTOKEN");
    }
}

// Throw this error when the parser expects a given token from the scanner
// and the next token the scanner finds does not match.
void mismatchError(int line, token expected, token found) {
    std::cerr << "Parse error: expected " << tokenToString(expected) << " found " << tokenToString(found) << " at line " << line << std::endl;
    exit(1);
}

// Throw this error when the parser encounters a token that is not valid
// at the beginning of a specific grammar rule.
void parseError(int line, token found) {
    std::cerr << "Parse error: found invalid token " << tokenToString(found) << " at line " << line << std::endl;
    exit(1);
}

// Throw this error when an invalid character is found in the input, or
// if a bad character is found as part of a print token.
void scanError(int line, char badCharacter) {
    std::cerr << "Scan error: found invalid character " << badCharacter << " at line " << line << std::endl;
    exit(1);
}

// Throw this error when the index for memory is out of bounds (less
// than 0 or greater than 99). ONLY THROW IF evaluate flag is true.
void indexError(int line, int index) {
    std::cerr << "Semantic error: index " << index << " out of bounds at line " << line << std::endl;
    exit(1);
}

// Throw this error when a division by zero occurs. ONLY THROW IF evaluate flag is true.
void divideError(int line) {
    std::cerr << "Semantic error: division by zero at line " << line << std::endl;
    exit(1);
}

class Scanner {
    // You are allowed to private fields to the scanner, and this may be
    // necessary to complete your implementation. However, this is not
    // required as part of the project specification.
	private: 
		int line = 1;
		string currentWord;
		int tokenLength;
		token next;
		char number[16];
    
	public:
		token nextToken(); 
		void eatToken(token);
		int lineNumber();
		int getNumberValue();
		void findToken();
		void clearNumArray();
		void appendNumToArray(char c);
		void repopulateIstream();
		void repopulatePrint();
		void printNumber();
    // You may need to write a constructor for the scanner. This is not
    // required by the project description, but you may need it to complete
    // your implementation.
    // WRITEME
};

void Scanner::clearNumArray() {
	for (int i = 1; i < 16; i++) {
		number[i]=0;
	}
	number[0]=1;
}

void Scanner::appendNumToArray(char c) {
	number[tokenLength]=c;
}

void Scanner::repopulateIstream() {
	for (int i = tokenLength; i > 0; i--)  {
		cin.putback(number[i]);
	}
}

void Scanner:: repopulatePrint() {
	cin.putback('n');
	cin.putback('i');
	cin.putback('r');
	cin.putback('p');
}

void Scanner::printNumber() {
	cout<<"Number: ";
	for (int i = 1; i < 16; i ++) {
		cout<<number[i]<<" ";
	}
	cout<<endl;
}

token Scanner::nextToken() {
    // This is a placeholder token, you will need to replace this code
    // with code to return the correct next token
	findToken();
	//cout<<"token: "<<tokenToString(next)<<endl;
	return next;
}

void Scanner::findToken() {
	next = T_NONTOKEN;
	tokenLength = 0; //sets length of token to be 1 by default
	clearNumArray(); //clears array of numbers to be clear
	char c, hold; 
	bool spaces = true; //boolean to indicate whether a series of spaces is occurring
	bool numbers = true; //boolean to indicate whether in a series of digits
	//look at next item in stream
	c=cin.peek(); 
	
	//if multiple spaces present, pass through and discard them
	while (spaces) {
		c = cin.peek();
		if (c == ' ') {
			cin.get();
			continue;
			}
		else {
			spaces = false;
		}
	} 
	
	//if next char is eof, set next token to eof and end
	if (!cin) {
		next = T_EOF;
		return;
	}
	
	//check for next character being a number by cycling through until no longer a number
	do {
		c = cin.peek();
		if (c == '0' || c == '1' || c == '2'
			|| c == '3' || c == '4' || c == '5'
			|| c == '6' || c == '7' || c == '8' 
			|| c == '9' ) {
			next = T_NUMBER;
			tokenLength++;
			appendNumToArray(c);
			char k = cin.get();
			}
		else {
			numbers = false;
		}
	} while (numbers);
	
	//if a number, put digits back in stream
	if (next == T_NUMBER) {
		repopulateIstream();
		return;
	}
	
	//check for a print statement
	if (cin.peek() == 'p') {
		cin.get();
		hold = cin.peek();
		if ( hold == 'r') {
			cin.get();
			hold = cin.peek();
			if (hold == 'i') {
				cin.get();
				hold = cin.peek();
				if (hold == 'n') {
					cin.get();
					hold = cin.peek();
					if (hold == 't') {
						//cout<<"PRINTO!\n";
						next = T_PRINT;
						repopulatePrint();
						return;
					}
					else {
						//cout<<"afterError T: "<<(char)cin.peek()<<endl;
						scanError(lineNumber(), hold);
					}
					
				}
				else {
					//cout<<"afterError N: "<<(char)cin.peek()<<endl;
					scanError(lineNumber(), hold);
				}
			}
			else {
			//cout<<"afterError I: "<<(char)cin.peek()<<endl;
			scanError(lineNumber(),hold);
			}
		}
		else {
			//cout<<"afterError R: "<<(char)cin.peek()<<endl;
			scanError(lineNumber(), hold);
		}
	}	
		
		tokenLength = 1;
		//check for anything else
		switch (c) {
			case '-':
				next = T_MINUS;
				break;
			case '+':
				next = T_PLUS;
				break;
			case '*':
				hold = cin.get();
				if (cin.peek()=='*') {
					//cout<<"SO POWERFUL\n";
					next = T_POWER;
					cin.putback('*');
				}
				else
					next = T_MULTIPLY;
				break;
			case '/':
				next = T_DIVIDE;
				break;
			case '=':
				next = T_EQUALS;
				break;
			case '(':
				next = T_OPENPAREN;
				break;
			case ')':
				next = T_CLOSEPAREN;
				break;
			case '[':
				next = T_OPENBRACKET;
				break;
			case ']':
				next = T_CLOSEBRACKET;
				break;
			case 'm':
				next = T_M;
				break;
			case ';':
				next = T_SEMICOLON;
				break;
			case '\n':
				next = T_NEWLINE;
				line++;
				break;
			default:
				cout<<"default error\n";
				scanError(lineNumber(),c);
				break;
	}
	//cout<<"token2: \""<<c<<" "<<tokenToString(next)<<"\""<<endl<<endl;
	//char c1 = cin.get();
	//char c2 = cin.get();
	//char c3 = cin.get();
	//char c4 = cin.get();
	//char c5 = cin.get();
	//cout<<"token: "<<tokenToString(next)<<" upcoming: "<<c1<<c2<<c3<<c4<<c5<<endl;
}

void Scanner::eatToken(token toConsume) {
    // This function consumes the next token.
	//cout<<"--EATING TOKEN: "<<tokenToString(toConsume)<<endl;
	switch (toConsume) {
        case T_PLUS:
            cin.get();
			break;
        case T_MINUS:
            cin.get();
			break;
        case T_MULTIPLY:
            cin.get();
			break;
        case T_POWER:
            cin.get();
			cin.get();
			break;
        case T_DIVIDE:
            cin.get();
			break;
        case T_OPENPAREN:
            cin.get();
			break;
        case T_CLOSEPAREN:
            cin.get();
			break;
        case T_OPENBRACKET:
            cin.get();
			break;
        case T_CLOSEBRACKET:
            cin.get();
			break;
        case T_EQUALS:
            cin.get();
			break;
        case T_SEMICOLON:
            cin.get();
			break;
        case T_M:
            cin.get();
            cin.get();
			break;
        case T_PRINT:
            cin.get();
			cin.get();
			cin.get();
			cin.get();
			cin.get();
			break;
        case T_NUMBER:
			//cout<<"EATING NUMBER\n";
			for (int i = 1; i<= tokenLength; i++)
				cin.get();
			break;
        case T_EOF:
            cin.get();
			break;
		case T_NEWLINE:
			cin.get();
			break;
    }
	
}

int Scanner::lineNumber() {
    // This is also a placeholder, you will need to replace this code
    // with code to return the current line number (to be used for errors).
    
    // WRITEME
    return line;
}

int Scanner::getNumberValue() {
    // This is also a placeholder, you will need to replace this code
    // with code to return the last number value that was scanned. This
    // will be used when evaluating expressions.
    
    // WRITEME
    return 0;
}

class Table {
	private:
		/*
		 * TERMINAL ORDER
		 *      m print number ( ) [ ] ; eof + - * / **
		 * NONTERMINAL ORDER
		 *      start statements statements' 
		 *      statement expression expression' 
		 *      term term' exponentiation 
		 *      exponentiation' factor
		 */
		int ruleIndex[11][14] = { 
		 /* {  m   p     n   (   )     [   ]   ;     $   +   -     *   /   **   */
			{  1 , 1 ,   0 , 0 , 0 ,   0 , 0 , 0 ,   0 , 0 , 0 ,   0 , 0 , 0  } ,   // start
			{  2 , 2 ,   0 , 0 , 0 ,   0 , 0 , 0 ,   0 , 0 , 0 ,   0 , 0 , 0  } ,   // statements
			{  0 , 0 ,   0 , 0 , 0 ,   0 , 0 , 3 ,   4 , 0 , 0 ,   0 , 0 , 0  } ,   // statements'
			{  5 , 6 ,   0 , 0 , 0 ,   0 , 0 , 0 ,   0 , 0 , 0 ,   0 , 0 , 0  } ,   // statement
			{  7 , 0 ,   7 , 7 , 0 ,   0 , 0 , 0 ,   0 , 0 , 0 ,   0 , 0 , 0  } ,   // expression
			{  0 , 0 ,   0 , 0 , 10,   0 , 10, 10,   10, 8 , 9 ,   0 , 0 , 0  } ,   // expression'
			{  11, 0 ,   11, 11, 0 ,   0 , 0 , 0 ,   0 , 0 , 0 ,   0 , 0 , 0  } ,   // term
			{  0 , 0 ,   0 , 0 , 14,   0 , 14, 14,   14, 14, 14,   12, 13, 0  } ,   // term'
		   	{  15, 0 ,   15, 15, 0 ,   0 , 0 , 0 ,   0 , 0 , 0 ,   0 , 0 , 0  } ,   // exponentiation
			{  0 , 0 ,   0 , 0 , 17,   0 , 17, 17,   17, 17, 17,   17, 17, 16 } ,   // exponentiation'
			{  19, 0 ,   20, 18, 0 ,   0 , 0 , 0 ,   0 , 0 , 0 ,   0 , 0 , 0  } ,   // factor
		 };
	public:
		void getRule(int row, int column) {
			cout<<"ruleIndex: "<<ruleIndex[row-1][column-1]<<endl;
		}
		 
};

struct node {
	token t = T_NONTOKEN;
	int num;
	node* next = NULL; 
};

class Stack {
	node * head;
	//node * second;
	public:
	Stack() {
		head = NULL;
	};
	
	void push(token T) {
		cout<<"pushing "<<tokenToString(T)<<endl;
		node* n = new node();
		n->next = NULL;
		n->t = T;
		if (!head)
			head = n;
		else {
			node* temp = head;
			while (temp->next) {
				temp = temp->next;
			}
			temp->next = n;
		}
	};
	
	node* pop() {
		if (!head) {
			node* n = new node();
			return n;
		}
		else {
			node* temp = head;
			node* hold;
			while (temp->next) {
				hold = temp;
				temp = temp->next;
			}
			hold -> next = NULL;
			cout<<"popping "<<tokenToString(temp->t)<<endl;
			return temp;
		}
	}
	
	void printStack() {
		node* temp = head;
		cout<<"printing: ";
		while (temp) {
			cout<<tokenToString(temp->t)<<" ";
			temp = temp->next;
		}
		cout<<endl;
	}
	
	
	void testStack() {
		push(T_MINUS);
		printStack();
	}
};

class Parser {
    // You are allowed to private fields to the parser, and this may be
    // necessary to complete your implementation. However, this is not
    // required as part of the project specification.
    
private:
    Scanner scanner;
    Stack stack;
	Table table;
    // This flag indicates whether we should perform evaluation and throw
    // out-of-bounds and divide-by-zero errors. ONLY evaluate and throw these
    // errors if this flag is set to TRUE.
    bool evaluate;
    
    // You will need to add more methods for handling nonterminal symbols here.
    void Start();
    // WRITEME

public:
	void rule1() { // start ::= statements
		
	};
	void rule2() { // statements ::= statement statements'
	
	};
	void rule3() { // statements' ::= ;statement statements'
	
	};
	void rule4() { // statements' ::= epsilon
	
	};
	void rule5() { // statement ::= m [ expression ]
	
	};
	void rule6() { // statement ::= print expression
	
	};
	void rule7() { // expression ::= term expression'
	
	};
	void rule8() { // expression' ::= + term expression'
	
	};
	void rule9() { // expression' ::= - term expression'
	
	};
	void rule10() { // expression' ::= epsilon
	
	};
	void rule11() { // term ::= exponentiation term'
	
	};
	void rule12() { // term' ::= * exponentiation term'
	
	};
	void rule13() { // term' ::= / exponentiation term'
	
	};
	void rule14() { // term' ::= epsilon
	
	};
	void rule15() { // exponentiation ::= factor exponentiation'
	
	};
	void rule16() { // exponentiation' ::= ** exponentiation'
	
	};
	void rule17(){ // exponentiation' ::= epsilon
	
	};
	void rule18() { // factor ::= ( expression )
	
	};
	void rule19() { // factor ::= m [ expression ]
	
	};
	void rule20(){ // factor ::= number
	
	};
	
    void parse();
    Parser(bool evaluate) : evaluate(evaluate) {
        // You may need to complete a Parser constructor here
        // WRITEME
    }
};

void Parser::parse() {
    // This is the entry point for the parser, which simply starts parsing
    // the grammar by calling the function for the start symbol.
    Start();
}

void Parser::Start() {
    // This is an example of a recursive-descent function for a
    // non-terminal symbol. In this case, it is just a placeholder
    // which accepts infinite numbers of T_PLUS. You will need to
    // replace this with correct code for the real grammar start symbol.
    
	switch (scanner.nextToken()) {
		case T_M:
			break;
		case T_PRINT:
			break;
		case T_NUMBER:
			break;
		case T_OPENPAREN:
			break;
		case T_CLOSEPAREN:
			break;
		case T_OPENBRACKET:
			break;
		case T_CLOSEBRACKET:
			break;
		case T_SEMICOLON:
			break;
		case T_EOF:
			break;
		case T_PLUS:
			break;
		case T_MINUS:
			break;
		case T_MULTIPLY:
			break;
		case T_DIVIDE:
			break;
		case T_POWER:
			break;
		
	}
	
    // WRITEME
    /*switch (scanner.nextToken()) {
        case T_PLUS:
            scanner.eatToken(T_PLUS);
            Start();
            break;
        case T_EOF:
            break;
        default:
            parseError(scanner.lineNumber(), scanner.nextToken());
            break;
    }*/
}

// WRITEME (The rest of the nonterminal functions will need to be implemented here)

int main(int argc, char* argv[]) {
	
	//testing output for Table
	/*Table* table = new Table();
	table->getRule(1,1);
	table->getRule(1,2);
	table->getRule(2,1);
	table->getRule(2,2);
	table->getRule(11,1);
	table->getRule(10,14);*/
	
	//testing output for Stack
	/*Stack* s = new Stack();
	s->push(T_MINUS);
	s->printStack();
	s->push(T_PLUS);
	s->pop();
	s->printStack();
	s->push(T_MULTIPLY);
	s->printStack();
	s->pop();
	s->printStack();*/
	
	
    if (argc == 2 && (strcmp(argv[1], "-s") == 0)) {
        Scanner scanner;
        while (scanner.nextToken() != T_EOF) {
            std::cout <<tokenToString(scanner.nextToken()) << " ";
            scanner.eatToken(scanner.nextToken());
        }
        std::cout<<std::endl;
    } else if (argc == 2 && (strcmp(argv[1], "-e") == 0)) {
        Parser parser(true);
        parser.parse();
    } else {
        Parser parser(false);
        parser.parse();
    }
    return 0;
}
