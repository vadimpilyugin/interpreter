#include <string>
#include <iostream>
using namespace std;

#include "excp.h"
#include "executer.h"
#include "syntax.h"
#include "table.h"

#define DEBUG 1

class Interpreter
{
	Parser p;
	Executer e;
public:
	Interpreter (string path): p (path) {}
	void interpretation ();
};

void Interpreter::interpretation ()
{
	p.analyze ();
	e.execute (p.prog);
}

void p_argv (int argc, char **argv) {
	for(int i = 0; i < argc; i++) {
		cout << "Argument #" << i << ": " << argv[i] << endl;
	}
}
void p_env (char **envp) {
	for(int i = 0; envp[i] != NULL; i++) {
		cout << "Environment #" << i << ": " << envp[i] << endl;
	}
}

int main(int argc, char **argv, char **envp)
{
	#if DEBUG
	p_argv (argc, argv);
	p_env (envp);
	#endif
	try
	{
		fill (envp);
		Interpreter I (argv[1]);
		//Interpreter I("./test.prog");
		I.interpretation ();
		return 0;
	}
	catch(Excp &a)
	{
		cout << a.err_type () << " line " << a.get_line () << endl;
		cout << a.get_lex ();
		cout << "Error: " << a.what () << endl;
		return 0;
	}
}
