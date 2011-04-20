// plink.h
// LMNO LALR(1) parser generator
//
// Copyright ©2010 Brigham Toskin
// (Based on LEMON v1 parser generator, public domain)
//////////////////////////////////////////////////////


struct plink *Plink_new(/* void */);
void Plink_add(/* struct plink **, struct config * */);
void Plink_copy(/* struct plink **, struct plink * */);
void Plink_delete(/* struct plink * */);

