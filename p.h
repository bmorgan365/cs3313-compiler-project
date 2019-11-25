//extern int yylineno;
void yyerror(char *s);


enum node_type {DECL, ASGN, PRNT, 
LIST, 
ADD, SUB, MUL, DIV, REF,
INTTYPE, FLOATTYPE, DYNAMIC};

struct id {
	char *name;
	enum node_type t;
	enum node_type vt;
	union {
		long n;
		double z;
	} v;
};


#define NHASH 9997
struct id idtab[NHASH];

struct id *lookup(char*);

struct idlist {
	struct id *id;
	struct idlist *next;
};

struct expr {
	enum node_type t;
	enum node_type vt;
	struct ast *l;
	struct ast *r;
};

struct expr_list {
	struct ast *expr;
	struct expr_list *next;
};

struct print {
	enum node_type t;
	struct expr_list *exprlst;
};
/*
struct intnum {
	enum node_type t;
	long v;
};
struct floatnum {
	enum node_type t;
	double v;
};

struct number {
	enum node_type t;
	union {
		long n;
		double z;
	} v;
};
*/
struct idref {
	enum node_type t;
	struct id *id;
};
struct asgn {
	enum node_type t;
	struct id *id;
	struct ast *expr;
};
struct decl {
	enum node_type t;
	struct idlist *idlst;
	enum node_type vt;
};
/*
struct decl_list {
	enum node_type t;
	struct decl *decl;
	struct decl_list *decllst;
};
struct stmt_list {
	enum node_type t;
	struct stmt *stmt;
	struct stmt_list *stmtlst;
};
struct stmt {
	enum node_type t;
	struct id *id;
	struct expr *expr;
	struct expr_list *exprlst;
};
*/

struct ast {
	enum node_type t;
	struct ast* l;
	struct ast* r;
};
struct intval {
	enum node_type t;
	long v;
};
struct floatval {
	enum node_type t;
	double v;
};

struct output {
	enum node_type t;
	union {
		long n;
		double z;
	} v;
};


//write these functions
struct ast *newlist(struct ast *l, struct ast *r);
struct ast *newint(long v);
struct ast *newfloat(double v);
struct ast *newprint(struct expr_list *l);
struct ast *newref(struct id *s);
struct ast *newdecl(struct idlist *idlst, enum node_type type);
struct ast *newasgn(struct id *id, struct ast *expr);
struct ast *newexpr(enum node_type op, struct ast* l, struct ast* r);
struct idlist *newidlist(struct id *id, struct idlist *next);
//


struct expr_list *newexprlist(struct ast *expr, struct expr_list *next);
struct id *lookup(char *name);
static unsigned idhash(char *name);
static double callprint(struct print *p);
static double calldecl(struct decl *d);
struct output eval(struct ast *a);
struct output addop(struct output x, struct output y);
struct output subop(struct output x, struct output y);
struct output mulop(struct output x, struct output y);
struct output divop(struct output x, struct output y);

void freetree(struct ast *a);
void freeidlist(struct idlist *a);
void freeexprlist(struct expr_list *a);
