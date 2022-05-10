#include "std_lib_facilities.h"

class Token {
public:
    char kind;
    double value;
    string name;
    Token(char ch) :kind(ch), value(0) { }
    Token(char ch, double val) :kind(ch), value(val) { }
    Token(char ch, string n) :kind(ch), name(n) {}
};

class Token_stream {
private:
    bool full;
    Token buffer;
public:
    Token_stream() :full(0), buffer(0) { }

    Token get();
    void unget(Token t) { buffer = t; full = true; }

    void ignore(char c);
};

const char let = '#';
const char quit = 'Q';
const char print = ';';
const char number = '8';
const char name = 'a';
const char square_root = 's';
const char multiply = '^';
const string exitkey = "exit";

Token Token_stream::get()
{
    if (full) { full = false; return buffer; }
    char ch;
    cin >> ch;
    switch (ch) {
    case '(':
    case ')':
    case '+':
    case '-':
    case '*':
    case '/':
    case '%':
    case '=':
    case 's':
    case '^':
    case print:
    case quit:
        return Token(ch);
    case '.':
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    {    cin.unget();
    double val;
    cin >> val;
    return Token(number, val);
    }
    case '#':
        return Token(let);
    default:
        if (isalpha(ch)) {
            string s;
            s += ch;
            while (cin.get(ch) && (isalpha(ch) || isdigit(ch))) s += ch;
            cin.unget();
            if (s == exitkey) return Token(quit);
            return Token(name, s);
        }
        error("Bad token");
    }
    return 0;
}

void Token_stream::ignore(char c)
{
    if (full && c == buffer.kind) {
        full = false;
        return;
    }
    full = false;

    char ch=0;
    while (cin >> ch)
        if (ch == c) return;
}

class Variable {
public:
    string name;
    double value;
    Variable(string s, double d) :name(s), value(d) { }
};//

vector<Variable> names;



double get_value(string s)
{
    for (int i = 0; i < names.size(); ++i)
        if (names[i].name == s) return names[i].value;
    error("get: undefined name ", s);
    return 0;
}

void set_value(string s, double d)
{
    for (int i = 0; i <= names.size(); ++i)
        if (names[i].name == s) {
            names[i].value = d;
            return;
        }
    error("set: undefined name ", s);
}

bool is_declared(string s)
{
    for (int i = 0; i < names.size(); ++i)
        if (names[i].name == s) return true;
    return false;
}

double define_name(string s, double d)
{
    if(is_declared(s))error(s,"declared twice");
    names.push_back(Variable(s,d));
    return d;
}

Token_stream ts;

double expression();
double term();

double primary()
{
    Token t = ts.get();
    switch (t.kind) {
        case '(':
        {    double d = expression();
            t = ts.get();
            if (t.kind != ')') error("'）' expected");
            return d;
        }
        
        case '-':
            return -primary();
        case '+':
            return primary();
        case square_root:
            {
                double d = primary();
                if (d<0) error("you can't sqare root lass than 0");
                return sqrt(d);
                break;
            }
        case number:
            return t.value;
        case name:
            return get_value(t.name);
        default:
            error("primary expected");
        }
        return 0;
}

double term()
{
    double left = primary();
    Token t = ts.get();
    while (true) {
        switch (t.kind) {
        case '*':
            left *= primary();
            t = ts.get();
            break;
        case '/':
        {    double d = primary();
            if (d == 0) error("divide by zero");
            left /= d;
            t = ts.get();
            break;
        }
        case multiply:
        {   double d = primary();
            left = pow(left, d);
            t = ts.get();
            break;
        }
                
        default:
            ts.unget(t);
            return left;
        }
    }
}

double expression()
{
    double left = term();
    Token t = ts.get();
    while (true) {
        switch (t.kind) {
        case '+':
            left += term();
            t = ts.get();
            break;
        case '-':
            left -= term();
            t = ts.get();
            break;
        default:
            ts.unget(t);
            return left;
        }
    }
}

double declaration()
{
    Token t = ts.get();
    if (t.kind != 'a') error("name expected in declaration");
    string name = t.name;
    if (is_declared(name)) error(name, " declared twice");
    Token t2 = ts.get();
    if (t2.kind != '=') error("= missing in declaration of ", name);
    double d = expression();
    names.push_back(Variable(name, d));
    return d;
}

double statement()
{
    Token t = ts.get();
    switch (t.kind) {
    case let:
        return declaration();
        default:
        ts.unget(t);
        return expression();
    }
}

void clean_up_mess()
{
    ts.ignore(print);
}

const string prompt = "> ";
const string result = "= ";

void calculate()
{
    while (true) try {
        cout << prompt;
        Token t = ts.get();
        while (t.kind == print) t = ts.get();
        if (t.kind == quit) return;
        ts.unget(t);
        cout << result << statement() << endl;
    }
    catch (runtime_error& e) {
        cerr << e.what() << endl;
        clean_up_mess();
    }
}

int main()
{
try {
    calculate();
    define_name("k",1000);
    return 0;
}
catch (exception& e) {
    cerr << "exception: " << e.what() << endl;
    char c;
    while (cin >> c && c != ';');
    return 1;
}
catch (...) {
    cerr << "exception\n";
    char c;
    while (cin >> c && c != ';');
    return 2;
}
    return 0;
}
