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
	T_NONTOKEN,
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
} token;

/*typedef enum {
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
} nonterminal;	*/

/*string nonterminalToString(nonterminal toConvert) {
	switch(toConvert) {
		case N_START:
			return "start";
		case N_STATEMENTS:
			return "statements";
		case N_STATEMENTSP:
			return "statements'";
		case N_STATEMENT:
			return "statement";
		case N_EXPRESSION:
			return "expression";
		case N_EXPRESSIONP:
			return "expression'";
		case N_TERM:
			return "term";
		case N_TERMP:
			return "term'";
		case N_EXPONENTIATION:
			return "exponentiation";
		case N_EXPONENTIATIONP:
			return "exponentiation'";
		case N_FACTOR:
			return "factor";
	}
}*/

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
		case N_START:
			return "start";
		case N_STATEMENTS:
			return "statements";
		case N_STATEMENTSP:
			return "statements'";
		case N_STATEMENT:
			return "statement";
		case N_EXPRESSION:
			return "expression";
		case N_EXPRESSIONP:
			return "expression'";
		case N_TERM:
			return "term";
		case N_TERMP:
			return "term'";
		case N_EXPONENTIATION:
			return "exponentiation";
		case N_EXPONENTIATIONP:
			return "exponentiation'";
		case N_FACTOR:
			return "factor";
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
		number[i]='0';
	}
	number[0]='1';
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
	//cout<<"1Nexttokenfunction: "<<tokenToString(next)<<endl;
	findToken();
	//cout<<"2Nexttokenfunction: "<<tokenToString(next)<<endl;
	return next;
}

void Scanner::findToken() {
	//cout<<"1next: "<<cin.peek()<<endl;
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
	
	c=cin.peek();
	if (c=='\n') {
		next = T_NEWLINE;
		line++;
		cin.get();
	}
	
	if( c != '0' && c != '1' && c != '2'
			&& c != '3' && c != '4' && c != '5'
			&& c != '6' && c != '7' && c != '8' 
			&& c != '9' && c != 'p' && c != 'r' 
			&& c != 'i' && c != 'n' && c != 't' 
			&& c != 'm' && c != '[' && c != ']' 
			&& c != '(' && c != ')' && c != '*' 
			&& c != '+' && c != '-' && c != '/'
			&& c != ' ' && c != '\n' && c != ';'
			&& c != '=') {
			scanError(lineNumber(),c);
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
			appendNumToArray(cin.get());
			}
		else {
			numbers = false;
		}
	} while (numbers);
	
	//if a number, put digits back in stream
	if (next == T_NUMBER) {
		repopulateIstream();
		//cout<<"was a number. next: "<<(char)cin.peek()<<endl;
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
				}
				else
					next = T_MULTIPLY;
				cin.putback('*');
				//cout<<"cin peek in *: "<<(char)cin.peek()<<endl;
				//cout<<"cin peek in *: "<<(char)cin.peek()<<endl;
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
			default:
				next = T_EOF;
				break;
	}
	//cout<<"peeking: "<<(char)cin.peek()<<endl;
	//cout<<"@END OF NEXT: "<<tokenToString(next)<<endl;
	//cout<<"@END OF NEXT: "<<tokenToString(next)<<endl;
	//cout<<"token2: \""<<c<<" "<<tokenToString(next)<<"\""<<endl<<endl;
	char h = cin.get();
	char i = cin.get();
	//cout<<"next: "<<i<<" "<<(char)cin.peek()<<endl;
	cin.putback(i);
	cin.putback(h);
	//cout<<"token: "<<tokenToString(next)<<" upcoming: "<<c1<<c2<<c3<<c4<<c5<<endl;
}

void Scanner::eatToken(token toConsume) {
    // This function consumes the next token.
	cout<<"eating: "<<tokenToString(toConsume)<<endl;
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
			break;
        case T_PRINT:
			for (int i = 0; i < 5; i++) {
				cin.get();
			}
			break;
        case T_NUMBER:
			cout<<"number length: "<<tokenLength<<endl;
			//printNumber();
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
	token t;
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
	
	token top() {
		//token t = pop();
		//push(t);
		cout<<"top: "<<tokenToString(head->t)<<endl;
		return head->t;
	};
	
	void push(token T) {
		cout<<"pushing "<<tokenToString(T)<<endl;
		node* n = new node();
		n->next = NULL;
		n->t = T;
		n->next = head;
		head = n;
	};
	
	token pop() {
		if (!head) {
			node* n = new node();
			cout<<"popping empty!\n";
			return n->t;
		}
		else {
			token h = head->t;
			head = head->next;
			cout<<"popping "<<tokenToString(h)<<"\n";
			return h;
		}
	}
	
	void printStack() {
		//cout<<"printing start\n";
		//cout<<"hi\n";
		cout<<"printing: ";
		if (!head) {
			cout<<"empty stack!\n";
			return;
			}
		//cout<<"head: "<<head->t<<endl;
		node* temp = new node();
		temp = head;
		while (temp) {
			cout<<tokenToString(temp->t)<<" ";
			temp = temp->next;
		}
		cout<<endl;
	}
	
	void rule1() { // start ::= statements
		cout<<"rule 1\n";
		pop(); // should be start symbol
		push(N_STATEMENTS);
	};
	
	void rule2() { // statements ::= statement statements'
		cout<<"rule 2\n";
		pop();
		push(N_STATEMENTSP);
		push(N_STATEMENT);
	};	
	
	void rule3() { // statements' ::= ;statement statements'
		cout<<"rule 3\n";
		pop();
		push(N_STATEMENTSP);
		push(N_STATEMENT);
		push(T_SEMICOLON);
	};
	
	void rule4() { // statements' ::= epsilon
		cout<<"rule 4\n";
		pop();
	};
	
	void rule5() { // statement ::= m [ expression ] = expression
		cout<<"rule 5\n";
		pop();
		push(N_EXPRESSION);
		push(T_EQUALS);
		push(T_CLOSEBRACKET);
		push(N_EXPRESSION);
		push(T_OPENBRACKET);
		push(T_M);
	};
	
	void rule6() { // statement ::= print expression
		cout<<"rule 6\n";
		pop();
		push(N_EXPRESSION);
		push(T_PRINT);
	};
	
	void rule7() { // expression ::= term expression'
		cout<<"rule 7\n";
		pop();
		push(N_EXPRESSIONP);
		push(N_TERM);
	};
	
	void rule8() { // expression' ::= + term expression'
		cout<<"rule 8\n";
		pop();
		push(N_EXPRESSIONP);
		push(N_TERM);
		push(T_PLUS);
	};
	
	void rule9() { // expression' ::= - term expression'
		cout<<"rule 9\n";
		pop();
		push(N_EXPRESSIONP);
		push(N_TERM);
		push(T_MINUS);	
	};
	
	void rule10() { // expression' ::= epsilon
		cout<<"rule 10\n";
		pop();
	};
	
	void rule11() { // term ::= exponentiation term'
		cout<<"rule 11\n";
		pop();
		push(N_TERMP);
		push(N_EXPONENTIATION);
	};
	
	void rule12() { // term' ::= * exponentiation term'
		cout<<"rule 12\n";
		pop();
		push(N_TERMP);
		push(N_EXPONENTIATION);
		push(T_MULTIPLY);
	};
	
	void rule13() { // term' ::= / exponentiation term'
		cout<<"rule 13\n";
		pop();
		push(N_TERMP);
		push(N_EXPONENTIATION);
		push(T_DIVIDE);	
	};
	
	void rule14() { // term' ::= epsilon
		cout<<"rule 14\n";
		pop();
	};
	
	void rule15() { // exponentiation ::= factor exponentiation'
		cout<<"rule 15\n";
		pop();
		push(N_EXPONENTIATIONP);
		push(N_FACTOR);
	};
	
	void rule16() { // exponentiation' ::= ** exponentiation
		cout<<"rule 16\n";
		pop();
		push(N_EXPONENTIATION);
		push(T_POWER);
	};
	
	void rule17(){ // exponentiation' ::= epsilon
		cout<<"rule 17\n";
		pop();
	};
	
	void rule18() { // factor ::= ( expression )
		cout<<"rule 18\n";
		pop();
		push(T_CLOSEPAREN);
		push(N_EXPRESSION);
		push(T_OPENPAREN);
	};
	
	void rule19() { // factor ::= m [ expression ]
		cout<<"rule 19\n";
		pop();
		push(T_CLOSEBRACKET);
		push(N_EXPRESSION);
		push(T_OPENBRACKET);
		push(T_M);
	};
	
	void rule20(){ // factor ::= number
		cout<<"rule 20\n";
		pop();
		push(T_NUMBER);
	};
	
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
	void start(token t) {
		cout<<"start function\n";
		if(t == T_M || t == T_PRINT) {  stack.rule1(); }
		else parseError(scanner.lineNumber(), t);
	};
	
	void statements(token t) {
		cout<<"statements function\n";
		if(t == T_M || t == T_PRINT) stack.rule2();
		else parseError(scanner.lineNumber(), t);
	};
	
	void statementsp(token t) {	
		cout<<"statementsp function\n";
		if (t == T_SEMICOLON) stack.rule3();
		else if (t == T_EOF) stack.rule4();
		else parseError(scanner.lineNumber(), t);
	};
	
	void statement(token t) {
		cout<<"statement function\n";
		if (t == T_M) stack.rule5();
		else if (t == T_PRINT) stack.rule6();
		else parseError(scanner.lineNumber(), t);
	};
	
	void expression(token t) {
		cout<<"expression function\n";
		if (t == T_M || t == T_NUMBER || t == T_OPENPAREN) stack.rule7();
		else parseError(scanner.lineNumber(), t);
	};
	
	void expressionp(token t) {
		cout<<"expressionp function\n";
		if (t == T_CLOSEPAREN || t == T_CLOSEBRACKET || t == T_SEMICOLON || t == T_EOF)
			stack.rule10();
		else if (t == T_PLUS) stack.rule8();
		else if (t == T_MINUS) stack.rule9();
		else parseError(scanner.lineNumber(), t);
	};
	
	void term(token t) {
		cout<<"term function\n";
		if (t == T_M ||  t == T_NUMBER || t == T_OPENPAREN) stack.rule11();
		else parseError(scanner.lineNumber(), t);
	};
	
	void termp(token t) {
		cout<<"termp function\n";
		if (t == T_CLOSEPAREN || t == T_CLOSEBRACKET || t == T_SEMICOLON || t == T_EOF || t == T_PLUS || t == T_MINUS)
			stack.rule14();
		else if (t == T_MULTIPLY) stack.rule12();
		else if (t == T_DIVIDE) stack.rule13();
		else parseError(scanner.lineNumber(), t);
	};
	
	void exponentiation(token t) {
		cout<<"exponentiation function\n";
		if (t == T_M || t == T_NUMBER || t == T_OPENPAREN) stack.rule15();
		else parseError(scanner.lineNumber(), t);
	};
	
	void exponentiationp(token t) {
		cout<<"exponentiationp function\n";
		if (t == T_CLOSEPAREN || t == T_CLOSEBRACKET || t == T_SEMICOLON || t == T_EOF || t == T_PLUS || t == T_MINUS || t == T_MULTIPLY  || t == T_DIVIDE)
			stack.rule17();
		else if (t == T_POWER) stack.rule16();
		else parseError(scanner.lineNumber(), t);
	};
	
	void factor(token t) {
		cout<<"factor function\n";
		if (t == T_M) stack.rule19();
		else if (t == T_NUMBER) stack.rule20();
		else if (t == T_OPENPAREN) stack.rule18();
		else parseError(scanner.lineNumber(), t);
	};
	
	void match(token top, token input) {
		cout<<"called match function\n";
		if (top == input) {
			scanner.eatToken(input);
			stack.pop();
		}
		else
			mismatchError(scanner.lineNumber(), top, input);
		cout<<"nextToken: "<<tokenToString(scanner.nextToken())<<endl;
	}; // matches token t to current next word
	
    void parse();
	bool produce(token i, token t);
    Parser(bool evaluate) : evaluate(evaluate) {
        // You may need to complete a Parser constructor here
        // WRITEME
    }
};

bool Parser::produce(token i, token t) {
	switch (t) {
		case N_START:
			//cout<<"instart\n";
			start(i);
			break;
		case N_STATEMENTS:
			statements(i);
			break;
		case N_STATEMENTSP:
			statementsp(i);
			break;
		case N_STATEMENT:
			statement(i);
			break;
		case N_EXPRESSION:
			expression(i);
			break;
		case N_EXPRESSIONP:
			expressionp(i);
			break;
		case N_TERM:
			term(i);
			break;
		case N_TERMP:
			termp(i);
			break;
		case N_EXPONENTIATION:
			exponentiation(i);
			break;
		case N_EXPONENTIATIONP:
			exponentiationp(i);
			break;
		case N_FACTOR:
			factor(i);
			break;
		default:
			return false;
		}
	return true;
}

void Parser::parse() {
    // This is the entry point for the parser, which simply starts parsing
    // the grammar by calling the function for the start symbol.
	stack.push(T_EOF);
	stack.push(N_START);
	
	while (scanner.nextToken() != T_EOF) {
		cout<<"---------produce------------"<<endl;
		token t = stack.top();
		token i = scanner.nextToken();
		cout<<"stack: "<<tokenToString(t)<<" input: "<<tokenToString(scanner.nextToken())<<endl;
		//scanner.printNumber();
		bool b = produce(i,t);
		if (!b) match(t, scanner.nextToken());
		cout<<tokenToString(scanner.nextToken())<<endl;
		stack.printStack();
	}
	
    Start();
}

void Parser::Start() {
    // This is an example of a recursive-descent function for a
    // non-terminal symbol. In this case, it is just a placeholder
    // which accepts infinite numbers of T_PLUS. You will need to
    // replace this with correct code for the real grammar start symbol.
	
	//output for testing stack operations
	stack.pop();
	
	stack.printStack();
	stack.push(N_START);
	stack.printStack();
	stack.rule1();
	stack.printStack();
	
    
	
	
	/* (scanner.nextToken()) {
		case T_M://1
			break;
		case T_PRINT://2
			break;
		case T_NUMBER://3
			break;
		case T_OPENPAREN://4
			break;
		case T_CLOSEPAREN://5
			break;
		case T_OPENBRACKET://6
			break;
		case T_CLOSEBRACKET://7
			break;
		case T_SEMICOLON://8
			break;
		case T_EOF://9
			break;
		case T_PLUS://10
			break;
		case T_MINUS://11
			break;
		case T_MULTIPLY://12
			break;
		case T_DIVIDE://13
			break;
		case T_POWER://14
			break;*/
		
	//
	
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
