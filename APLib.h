// APlib.h

// Make this any number of bytes you want. The new(int, int) function will +1 for the '\0' null-terminator. Default = 1023.
#define MAX_LENGTH_AP_PART 1023
// ((2^8)^8)^4 is probably the magnitude of MAX_VALUE (long long int) on 64-bit Intel-ISA-compatible architectures
// or, 2^(8*8*4), or, 2^256 (64*4)

#define NEW_LINE printf("\n")
#define NL NEW_LINE

#define ollie unsigned long long int
typedef struct	{

	char * major;
	char * minor;
	char sign;
	
	ollie length;
	ollie major_length;
	ollie minor_length;
	
} AP;

AP new(ollie maj, ollie min);
void clear(AP * a);

void flip_sign(AP * a);
void set_sign(AP * a, char sym);
char sign(AP * a);

signed short int cmp(AP a, AP b);
ollie overflow(AP * c, int result, ollie k);
char tt(AP a, AP b);

AP ADD(AP a, AP b);
AP SUB(AP a, AP b);

AP MUL(AP a, AP b);
AP DIV(AP a, AP b);

typedef struct LL_item {
  
  AP entry;
  struct LL_item * next;
  struct LL_item * prev;
  
} LL_item;

typedef struct LL {

  struct LL_item * top_entry;
} LL;



void init_LL(LL * linked_list)  {
  
  linked_list->top_entry = (LL_item *) NULL;
}

AP pull(LL * linked_list);
void push(LL * linked_list, AP item);

AP pull(LL * linked_list) {
  
  
  LL_item * result = linked_list->top_entry;
  
  LL_item * temp = linked_list->top_entry->prev;
  
  temp->next = NULL;
  linked_list->top_entry = temp;
  
  
  return result->entry;
}

void push(LL * linked_list, AP item) {
  
  LL_item * swap_item = linked_list->top_entry;
  
  LL_item * new_top_entry = (LL_item *)malloc( sizeof(LL_item) );
  
  new_top_entry->entry = item;
  new_top_entry->next = (LL_item *) NULL;
  new_top_entry->prev = swap_item;
  
  if( swap_item )
    swap_item->next = new_top_entry;
  else
    ;
  
  linked_list->top_entry = new_top_entry;
  
}



void print_ASCII(char start, char end)	{
	
	if( (start<32 || end<32) )	{
		
		printf("A scurrilous attempt was made to print the non-printable ascii characters below codepoint 32. Or even those new-fangled extended-ascii characters above codepoint 127. This is an outrage, and the function is immediately returning!");
		return;
	}
	
	if( start>end )	{
	
		char temp;
		temp = start;
		start = end;
		end = temp;
	}
	
	for( signed short int i=start; i<=end; i+=5 )	{
		
		char j=(char)i;
		signed int k = (end-i);
		
		if( k>4 )
			k=4;
		
		switch(k)
		{
			case 4:
				printf("[%d]:=(%c)\t", j, j);
				++j;
			case 3:
				printf("[%d]:=(%c)\t", j, j);
				++j;
			case 2:
				printf("[%d]:=(%c)\t", j, j);
				++j;
			case 1:
				printf("[%d]:=(%c)\t", j, j);
				++j;
			case 0:
				printf("[%d]:=(%c)", j, j);
			default:
				NEW_LINE;
			break;
		}
		
		if(i==end)
			return;
	}
}

