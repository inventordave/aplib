

void pause()	{

	getchar();
	return;
}

void arg_assert( int argc, int min )	{
	
	if( (argc-1)<min )	{
		
		printf( "Not enough cmd-line arguments. %d are required, only %d args passed. Exiting.", min, argc-1 );
		exit(1);
	}

	return;
}

