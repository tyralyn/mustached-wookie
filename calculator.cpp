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

struct node {
	token t = T_NONTOKEN;
	int num;
	node* next = NULL; 
};

class stack {
	node * head;
	//node * second;
	public:
	stack() {
		head = NULL;
	};
	
	void push(token T) {
		cout<<"pushing "<<tokenToString(T)<<endl;
		node* n = new node();
		//cout<<"quarter prelim "<<n<<"\n";
		n->next = NULL;
		//cout<<"halfway prelim\n";
		n->t = T;
		//cout<<"done prelim "<<tokenToString(T)<<endl;
		if (!head)
			head = n;
		else {
			//cout<<"more than one item in stack\n";
			node* temp = head;
			while (temp->next) {
				//cout<<"inLoop\n";
				temp = temp->next;
				//cout<<"leavingLoop\n";
			}
			temp->next = n;
		}
		//cout<<"done pushing "<<tokenToString(T)<<endl;
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
    
    // This flag indicates whether we should perform evaluation and throw
    // out-of-bounds and divide-by-zero errors. ONLY evaluate and throw these
    // errors if this flag is set to TRUE.
    bool evaluate;
    
    // You will need to add more methods for handling nonterminal symbols here.
    void Start();
    // WRITEME

public:
	void rule1();
	void rule2();
	void rule3();
	void rule4();
	void rule5();
	void rule6();
	void rule7();
	void rule8();
	void rule9();
	void rule10();
	void rule11();
	void rule12();
	void rule13();
	void rule14();
	void rule15();
	void rule16();
	void rule17();
	void rule18();
	void rule19();
	void rule20();
	
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
    
    // WRITEME
    switch (scanner.nextToken()) {
        case T_PLUS:
            scanner.eatToken(T_PLUS);
            Start();
            break;
        case T_EOF:
            break;
        default:
            parseError(scanner.lineNumber(), scanner.nextToken());
            break;
    }
}

// WRITEME (The rest of the nonterminal functions will need to be implemented here)

int main(int argc, char* argv[]) {
	stack* s = new stack();
	s->push(T_MINUS);
	s->printStack();
	s->push(T_PLUS);
	s->pop();
	s->printStack();
	s->push(T_MULTIPLY);
	s->printStack();
	s->pop();
	s->printStack();
	//cout<<"MAIN: "<<std::endl;
    /*if (argc == 2 && (strcmp(argv[1], "-s") == 0)) {
		//cout<<"IN IF\n";
        Scanner scanner;
        while (scanner.nextToken() != T_EOF) {
			//cout<<"inLoop\n";
            std::cout <<tokenToString(scanner.nextToken()) << " ";
            scanner.eatToken(scanner.nextToken());
        }
        std::cout<<std::endl;
    } else if (argc == 2 && (strcmp(argv[1], "-e") == 0)) {
		//cout<<"IN ELSE IF\n";
        Parser parser(true);
        parser.parse();
    } else {
		//cout<<"IN ELSE\n";
        Parser parser(false);
        parser.parse();
    }*/
    return 0;
}
