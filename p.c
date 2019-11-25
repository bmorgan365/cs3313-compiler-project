#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "p.h"

// left and right child, create parent and assign left and right
struct ast *newlist(struct ast *l, struct ast *r){
    struct ast *a = malloc(sizeof(struct ast));

    if(!a){
        yyerror("out of space");
        exit(0);
    }

    a->t = LIST;
    a->l = l;
    a->r = r;
    return a;
}

struct ast *newint(long v){
    struct intval *a = malloc(sizeof(struct intval));

    if(!a){
        yyerror("out of space");
        exit(0);
    }

    a->t = INTTYPE;
    a->v = v;
        
    return (struct ast *)a;
}

struct ast *newfloat(double v){
    struct floatval *a = malloc(sizeof(struct floatval));

    if(!a){
        yyerror("out of space");
        exit(0);
    }

    a->t = FLOATTYPE;
    a->v = v;

    return (struct ast *)a;
}

struct ast *newprint(struct expr_list *l){
    struct print *a = malloc(sizeof(struct print));

    if(!a){
        yyerror("out of space");
        exit(0);
    }
    a->t = PRNT;
    a->exprlst = l;
    return (struct ast *)a;
}

struct ast *newref(struct id *s){
    struct idref *a = malloc(sizeof(struct idref));

    if(!a){
        yyerror("out of space");
        exit(0);
    }
    
    a->t = REF;
    a->id = s;
    return (struct ast *)a;
}

struct ast *newdecl(struct idlist *idlst, enum node_type type){
    struct decl *a = malloc(sizeof(struct decl));

    if(!a){
        yyerror("out of space");
        exit(0);
    }

    a->t = DECL;
    a->idlst = idlst;
    a->vt = type;

    return (struct ast *)a;
}

struct ast *newasgn(struct id *id, struct ast *expr){
    struct asgn *a = malloc(sizeof(struct asgn));

    if(!a){
        yyerror("out of space");
        exit(0);
    }

    a->expr = expr;
    a->t = ASGN;
    a->id = id;

    return (struct ast *)a;
}

struct ast *newexpr(enum node_type op, struct ast *l, struct ast *r){
    struct expr *a = malloc(sizeof(struct expr));

    if(!a){
        yyerror("out of space");
        exit(0);
    }

    a->l = l;
    a->r = r;
    a->t = op;
    a->vt = op;

    return (struct ast *)a;
}

struct idlist *newidlist(struct id *id, struct idlist *next){
    struct idlist *a = malloc(sizeof(struct idlist));

    if(!a){
        yyerror("out of space");
        exit(0);
    }

    a->id = id;
    a->next = next;

    return a;
}

//Implemented in class
struct expr_list *newexprlist(struct ast *expr, struct expr_list *next){

}

struct id *lookup(char *name){

}

static unsigned idhash(char *name){

}

static double callprint(struct print *p){

}

static double calldecl(struct decl *d){

}

struct output eval(struct ast *a){

}

struct output addop(struct output x, struct output y){

}

struct output subop(struct output x, struct output y){

}

struct output mulop(struct output x, struct output y){

}

struct output devop(struct output x, struct output y){

}

void freetree(struct ast *a){

}

void freeidlist(struct idlist *a){

}

void freeexprlist(struct expr_list *a){

}