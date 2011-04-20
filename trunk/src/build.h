// build.h
// LMNO LALR(1) parser generator
//
// Copyright ©2010 Brigham Toskin
// (Based on LEMON v1 parser generator, public domain)
//////////////////////////////////////////////////////


void FindRulePrecedences();
void FindFirstSets();
void FindStates();
void FindLinks();
void FindFollowSets();
void FindActions();

