/**
	Header que permite a la IDE de Arduino saltar determinadas líneas de
	código, si no se configurase en modo DEBUG.
    @file macro_debug.h
    @author Franco Abosso
    @author Julio Donadello
    @version 1.0 29/03/2021
*/

#ifdef DEBUG
	#define D if(1)
#else 
	#define D do{}while(0);
#endif