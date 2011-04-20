// configlist.h
// LMNO LALR(1) parser generator
//
// Copyright ©2010 Brigham Toskin
// (Based on LEMON v1 parser generator, public domain)
//////////////////////////////////////////////////////


void Configlist_init(/* void */);
struct config *Configlist_add(/* struct rule *, int */);
struct config *Configlist_addbasis(/* struct rule *, int */);
void Configlist_closure(/* void */);
void Configlist_sort(/* void */);
void Configlist_sortbasis(/* void */);
struct config *Configlist_return(/* void */);
struct config *Configlist_basis(/* void */);
void Configlist_eat(/* struct config * */);
void Configlist_reset(/* void */);

