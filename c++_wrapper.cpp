// WRAPPER_CPP

extern "C" {

		#include "aplib.h"
}


#define ADD( A,B ) ADDP( A,B,DefaultPrecision )
#define SUB( A,B ) SUBP( A,B,DefaultPrecision )
#define MUL( A,B ) MULP( A,B,DefaultPrecision )
#define DIV( A,B ) DIVP( A,B,DefaultPrecision )


namespace aplib {
	

class apval { char* integer; char* fractional; char sign; unsigned long long int fp = 0; operator+( ap b ); };

/*
class aplib(void );
class aplib( PID ) { char* PID = PID; }
class aplib( L deprecisionay );
class aplib( L deprecisionay, char* PID );



class AP( _ ) { char* _ = (char*)_; }
AP operator+( AP A, AP B ){ return ADD( A,B ); }
AP operator-( AP A, AP B ){ return SUB( A,B ); }
AP operator*( AP A, AP B ){ return MUL( A,B ); }
AP operator/( AP A, AP B ){ return DIV( A,B ); }
AP operator|( AP A, AP B ){ return OR( A,B ); }
AP operator==( AP A, AP B ){ return !CmpAP( A,B ); }
AP operator!=( AP A, AP B ){ return CmpAP( A,B ); }
AP operator>=( AP A, AP B ){ return (CmpAP(A,B)>=0); }
AP operator<=( AP A, AP B ){ return (CmpAP(A,B)<=0); }
AP operator> ( AP A, AP B ){ return (CmpAP(A,B)>0);  }
AP operator< ( AP A, AP B ){ return (CmpAP(A,B)<0);  }
AP operator===(AP A ,AP B ){ return (&A == &B);      }
AP operator! ( AP A      ){ return NOT( AP A );		 }
AP operator& ( AP A, AP B ){ return AND( A,B );		 }
*/
}

