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

    a->t = op;
    a->l = l;
    a->r = r;
    
    //vt is the type resulting from the operation
    a->vt = INTTYPE;

    //1.5 + 2, 2 + 1.4
    if(l->t == FLOATTYPE || r->t == FLOATTYPE){
        a->vt = FLOATTYPE;
    }
    //x + 5 and x == FLOATTYPE
    else if(l->t == REF && ((struct idref *)l)->id->t == FLOATTYPE){ 
        a->vt = FLOATTYPE;
    }
    //5 + y and y == FLOATTYPE
    else if(r->t == REF && ((struct idref *)l)->id->t == FLOATTYPE){
        a->vt = FLOATTYPE;
    }
    //result == FLOATTYPE + 4 or 3 + result == FLOATTYPE
    else if(((struct expr *)l)->vt == FLOATTYPE || ((struct expr *)l)->vt == FLOATTYPE){
        a->vt = FLOATTYPE;
    }

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
    struct expr_list *a = malloc(sizeof(struct expr_list));

    if(!a){
        yyerror("out of space");
        exit(0);
    }
    a->expr = expr;
    a->next = next;
    return a;
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
    struct output o;
    o->t = INTTYPE;
    o.v.n = 0;

    if(!a){
        return o;
    }

    if(a->t == LIST){
        eval(a->l);
        eval(a->r);
    }else if(a->t == DECL){
        calldecl((struct decl *)a);
    }else if(a->t == ASGN){
        struct asgn *b = (struct ast *)a;
        struct output r = eval(b->expr);
        if(b->id->t == INTTYPE && r.t == INTTYPE)
            b->id->v.n = r.v.n;
        else if(b->id->t == INTTYPE && r.t == FLOATTYPE)
            b->id->v.n = r.v.z;
        else if(b->id->t == INTTYPE && r.t == INTTYPE)
            b->id->v.z = r.v.n;
        else if(b->id->t == INTTYPE && r.t == FLOATTYPE)
            b->id->v.z = r.v.z;
        else if(b->id->t == DYNAMIC && r.t == INTTYPE){
            b->id->vt = INTTYPE;
            b->id->v.n = r.v.n;
        }
        else{
            b->id->vt = FLOATTYPE;
            b->id->v.z = r.v.z;
        }
    }else if(a->t == PRNT){
        struct print *b = (struct print *)a;
        callprint(b);
    }else if(a->t == ADD){
        struct expr *b = (struct expr *)a;
        o = addop(eval(b->l), eval(b->r));
    }else if(a->t == SUB){
        struct expr *b = (struct expr *)a;
        o = subop(eval(b->l), eval(b->r));
    }else if(a->t == MUL){
        struct expr *b = (struct expr *)a;
        o = mulop(eval(b->l), eval(b->r));
    }else if(a->t == DIV){
        struct expr *b = (struct expr *)a;
        o = divop(eval(b->l), eval(b->r));
    }else if(a->t == REF){
        struct idref *b = (struct idref *)a;
        o.t = b->id->vt;
        if(o.t == INTTYPE){
            o.v.n = b->id->v.n;
        }else{
            o.v.z = b->id->v.z;
        }
    }else if(a->t == INTTYPE){
        struct intval *b = (struct intval *)a;
        o.v.n = b->v;
    }else if(a->t == FLOATTYPE){
        struct floatval *b = (struct floatval *)a;
        o.t = FLOATTYPE;
        o.v.z = b->v;
    }

    return o;
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
    if(a->t == LIST){
        freetree(a->l);
        freetree(a->r);
    }else if(a->t == DECL){
        struct decl *n = (struct decl *)a;
        freeidlist(n->idlst);
    }else if(a->t == ASGN){
        struct asgn *n = (struct asgn *)a;
        free(n->id);
        freetree(n->expr);
    }else if(a->t == PRNT){
        struct print *n = (struct print *)a;
        freeexprlist(n->exprlst);
    }else if(a->t == ADD || a->t == SUB || a->t == MUL || a->t == DIV){
        freetree(a->l);
        freetree(a->r);
    }else if(a->t == REF){
        struct idref *n = (struct idref *)a;
        free(n->id);
    }else{ 
        free(a);
    }
}

void freeidlist(struct idlist *a){
    if(a->next){
        freeidlist(a->next);
    }
    free(a);
}

void freeexprlist(struct expr_list *a){
    if(a->next){
        freeexprlist(a->next);
    }
    free(a);
}