// TESTS.H

#ifndef DAVE_TESTS_H
#define DAVE_TESTS_H


// TEST FUNCTION DECLS

int unitTests_ADD( void );
int unitTests_MUL( void );

void dec_2_Bin_2_dec(int argc, char **argv);
void basicTest(int argc, char **argv); // AD, SUB, MUL, EXP - requires 2 decimal strings in argv[1]/argv[2].
void fs_test1(int argc, char **argv);
void q_test(int argc, char **argv);
void readFloatTest(int argc, char **argv);
void writeFloatTest(int argc, char **argv);
void test2kMax(int argc, char **argv);

void notTest(int argc, char ** argv);
void andTest(int argc, char ** argv);
void orTest(int argc, char ** argv);
void exOrTest(int argc, char ** argv);


#endif

