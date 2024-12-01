// APLIB_CPP

class IAPlib    {

    public:

        char* ADD( char* a, char* b ) = 0;
        char* SUB( char* a, char* b ) = 0;
        char* MUL( char* a, char* b ) = 0;
        char* DIV( char* a, char* b ) = 0;

    
}


class someUserDefinedProgam : public IAPlib {



}
/**
class IStringNotifier
{
public:
  virtual void sendMessage(std::string &strMessage) = 0;
  virtual ~IStringNotifier() { }
};

 */