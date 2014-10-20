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
	T_WHITESPACE
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
		//int lineNumber;
		string currentWord;
		int tokenLength;
    
	public:
		token nextToken(); 
		void eatToken(token);
		int lineNumber();
		int getNumberValue();
    
    // You may need to write a constructor for the scanner. This is not
    // required by the project description, but you may need it to complete
    // your implementation.
    // WRITEME
};

token Scanner::nextToken() {
    // This is a placeholder token, you will need to replace this code
    // with code to return the correct next token.
    
    // WRITEME
	token nextToken;
	tokenLength = 1;
	cout << "scanner.nextToken() called \n";
	char c, hold;
	bool spaces = true;
	//char eof = cin.eof();
	c=cin.peek();
	if (c == cin.eof()) {
		cout<<"eof\n";
		return T_EOF;
	}
	
	while (spaces) {
		c = cin.peek();
		cout<<c<<endl;
		if (c == ' ') {
			cout<<"spaced \n";
			cin.get();
			continue;
			}
		else 
			spaces = false;
		cout<<"spaces: "<<spaces<<endl;
		} 
		switch (c) {
			case '-':
				nextToken = T_MINUS;
				break;
			case '+':
				nextToken = T_PLUS;
				break;
			case '*':
				if (cin.peek()!= cin.eof()) {
					hold = cin.get();
					cout<<"test"<<cin.peek()<<endl;
					if (cin.peek() == '*') {
						//cout<<
						nextToken = T_POWER;
						tokenLength ++;
					}
					cin.putback(hold);
				}
				else 
					nextToken = T_MULTIPLY;
				break;
			case '/':
				nextToken = T_DIVIDE;
				break;
			case '=':
				nextToken = T_EQUALS;
				break;
			case '(':
				nextToken = T_OPENPAREN;
				break;
			case ')':
				nextToken = T_CLOSEPAREN;
				break;
			case '[':
				nextToken = T_OPENBRACKET;
				break;
			case ']':
				nextToken = T_CLOSEBRACKET;
				break;
			case 'm':
				nextToken = T_M;
				break;
			case ';':
				nextToken = T_SEMICOLON;
				break;
			case '\n':
				nextToken = T_NEWLINE;
				break;
			/*case eof:
				nextToken = T_EOF;*/
			default:
				nextToken=T_MINUS;
				break;				
		}
	cout<<"token: "<<tokenToString(nextToken)<<endl;
	
    return nextToken;
}

void Scanner::eatToken(token toConsume) {
    // This function consumes the next token.
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
            cin.get();
			break;
        case T_NUMBER:
            cin.get();
			break;
        case T_EOF:
            cin.get();
			break;
    }
	
}

int Scanner::lineNumber() {
    // This is also a placeholder, you will need to replace this code
    // with code to return the current line number (to be used for errors).
    
    // WRITEME
    return 0;
}

int Scanner::getNumberValue() {
    // This is also a placeholder, you will need to replace this code
    // with code to return the last number value that was scanned. This
    // will be used when evaluating expressions.
    
    // WRITEME
    return 0;
}

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

	//std::cout<<tokenToString(T_MINUS)<<std::endl;
    if (argc == 2 && (strcmp(argv[1], "-s") == 0)) {
        Scanner scanner;
        while (scanner.nextToken() != T_EOF) {
            std::cout << tokenToString(scanner.nextToken()) << " ";
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
