/*
 * A mini G_Code language scanner.
 */


#include "gParcer.h"

//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//#include <string.h>
//#include <stddef.h>


//#define BUFLEN 512

typedef void (*gfunction)(size_t, char *, size_t );  // Declare typedef

#define INPUT_BUFSIZE 1024





enum prsCmd{
	eCommand, eComment, eGcommand, eXparam, eYparam, eZparam, eAparam
	, eBparam, eCparam, eDparam, eEparam, eFparam, eIparam, eJparam
	, eKparam, eLparam, eMparam, eNparam, ePparam, eRparam, eSparam
	, eTpaam, eUparam, eVparam, eWparam, eStarparam
	
};


typedef void (*WriteFunc)( char *data, int len );

struct format
{
	char* buf;	//char buf[BUFLEN+1];
	int buflen;
	WriteFunc write;

	int flags;
	int width;
	int prec;
	int cs;
	//--------
	int act;
	char* te;
	char* ts;
	char* p;
	char* pe;
	char* eof;
	int done;	// Исполнение текущего тега.
	int have;
	int curline;
	int space;
	int eofile;
	int lenfile;
	uint state;
};

//#define curline	fsm->curline

//------------------- vars

static const int format_start = 11;
static const int format_first_final = 11;
static const int format_error = 0;

char buf[INPUT_BUFSIZE];


//	int have = 0, curline = 1;
//	char *ts, *te = 0;
//	int done = 0;

	struct sGcode sgcode;

	FILE *fp;
	FILE *flog;
//static void (* parser_out)(size_t number, char * param, size_t len);

static gfunction parser_out;

 void command (size_t curline, char * param, size_t len);
 void gcomment (size_t curline, char * param, size_t len);
 void g_command (size_t curline, char * param, size_t len);
 void x_coordinate(size_t curline, char * param, size_t len);
 void y_coordinate(size_t curline, char * param, size_t len);
 void z_coordinate(size_t curline, char * param, size_t len);
 void a_parameter(size_t curline, char * param, size_t len);
 void b_parameter(size_t curline, char * param, size_t len);
 void c_parameter(size_t curline, char * param, size_t len);
 void d_parameter(size_t curline, char * param, size_t len);
 void e_parameter(size_t curline, char * param, size_t len);
 void f_parameter(size_t curline, char * param, size_t len);
 void i_parameter(size_t curline, char * param, size_t len);
 void j_parameter(size_t curline, char * param, size_t len);
 void k_parameter(size_t curline, char * param, size_t len);
 void l_parameter(size_t curline, char * param, size_t len);
 void m_parameter(size_t curline, char * param, size_t len);
 void n_parameter(size_t curline, char * param, size_t len);
 void p_parameter(size_t curline, char * param, size_t len);
 void r_parameter(size_t curline, char * param, size_t len);
 void s_parameter(size_t curline, char * param, size_t len);
 void t_parameter(size_t curline, char * param, size_t len);
 void u_parameter(size_t curline, char * param, size_t len);
 void v_parameter(size_t curline, char * param, size_t len);
 void w_parameter(size_t curline, char * param, size_t len);
 void star_parameter(size_t curline, char * param, size_t len);

gfunction prs[] = {&command,&gcomment,&g_command,&x_coordinate
	, &y_coordinate	,&z_coordinate,&a_parameter, &b_parameter
	, &c_parameter, &d_parameter, &e_parameter, &f_parameter
	, &i_parameter, &j_parameter, &k_parameter, &l_parameter
	, &m_parameter, &n_parameter, &p_parameter, &r_parameter
	, &s_parameter, &t_parameter, &u_parameter, &v_parameter
	, &w_parameter, &star_parameter };


// g Command
 void command (size_t curline, char * param, size_t len){
		fprintf(flog, "Command(%lu): ", curline );
		fwrite( param, 1, len, flog );  
		fprintf(flog,"\n");
#ifdef SCANNER
		b_command(curline,param,len);
#endif
}




// g comment
 void gcomment (size_t curline, char * param, size_t len){
		fprintf(flog, "gcomment(%lu): ", curline );
		fwrite( param, 1, len, flog );  
		fprintf(flog,"\n");
#ifdef SCANNER		
		b_gcomment(curline,param,len);
#endif
}

// g GXX.X digit 		=command=	command GXX.X
 void g_command (size_t curline, char * param, size_t len){
		fprintf(flog, "G command(%lu): ", curline );
		fwrite( param, 1, len, flog );
		fprintf(flog,"\n");
#ifdef SCANNER		
		b_g_command (curline, param, len);
#endif
}

// g X coordinate
 void x_coordinate(size_t curline, char * param, size_t len)
{
		fprintf(flog, "\tX parameter(%lu): ", curline );
		fwrite( param, 1, len, flog );
		fprintf(flog,"\n");
#ifdef SCANNER		
		b_x_coordinate (curline, param, len);
#endif
}

// g Y 	coordinat
 void y_coordinate(size_t curline, char * param, size_t len)
{
		fprintf(flog, "\tY parameter(%lu): ", curline );
		fwrite( param, 1, len, flog );
		fprintf(flog,"\n");
#ifdef SCANNER
		b_y_coordinate (curline, param, len);
#endif
}

// g Z 	coordiane Line78
 void z_coordinate(size_t curline, char * param, size_t len)
{
		fprintf(flog, "\tZ parameter(%lu): ", curline );
		fwrite( param, 1, len, flog );
		fprintf(flog,"\n");
#ifdef SCANNER
		b_z_coordinate (curline, param, len);
#endif
}

// g A	 decimal   Stepper A position or angle {Annn] 

 void a_parameter(size_t curline, char * param, size_t len)
{
		fprintf(flog, "\tA parameter(%lu): ", curline );
		fwrite( param, 1, len, flog );
		fprintf(flog,"\n");
#ifdef SCANNER
		b_a_parameter (curline, param, len);
#endif
}

// g B	 decimal Stepper B position or angle {Bnnn}
 void b_parameter(size_t curline, char * param, size_t len)
{
		fprintf(flog, "\tB parameter(%lu): ", curline );
		fwrite( param, 1, len, flog );
		fprintf(flog,"\n");
#ifdef SCANNER
		b_b_parameter (curline, param, len);
#endif
}

// g C	 decimal Stepper C position or angle {Cnnn}
 void c_parameter(size_t curline, char * param, size_t len)
{
		fprintf(flog, "\tC parameter(%lu): ", curline );
		fwrite( param, 1, len, flog );
		fprintf(flog,"\n");
#ifdef SCANNER
		b_c_parameter (curline, param, len);
#endif		
}

// g D	 none Adjust Diagonal Rod {D}
 void d_parameter(size_t curline, char * param, size_t len)
{
		fprintf(flog, "\tD parameter(%lu): ", curline );
		fwrite( param, 1, len, flog );
		fprintf(flog,"\n"); 
#ifdef SCANNER
		b_d_parameter (curline, param, len);
#endif		
}

// g E	 optional coordinate
 void e_parameter(size_t curline, char * param, size_t len)
{
		fprintf(flog, "\tE parameter(%lu): ", curline );
		fwrite( param, 1, len, flog );
		fprintf(flog,"\n"); 
#ifdef SCANNER
		b_e_parameter (curline, param, len);
#endif		
}

// g F 	decimal Feed rate parameter in G-command
 void f_parameter(size_t curline, char * param, size_t len)
{
		fprintf(flog, "\tF parameter(%lu): ", curline );
		fwrite( param, 1, len, flog );
		fprintf(flog,"\n"); 
#ifdef SCANNER
		b_f_parameter (curline, param, len);
#endif		
}

// g I 	optional X offset for arcs and G87 canned cycles
 void i_parameter(size_t curline, char * param, size_t len)
{
		fprintf(flog, "\tI parameter(%lu): ", curline );
		fwrite( param, 1, len, flog );
		fprintf(flog,"\n"); 
#ifdef SCANNER
		b_i_parameter (curline, param, len);
#endif		
}

// g J	 decimal Y offset for arcs and G87 canned cycles
 void j_parameter(size_t curline, char * param, size_t len)
{
		fprintf(flog, "\tJ parameter(%lu): ", curline );
		fwrite( param, 1, len, flog );
		fprintf(flog,"\n"); 
#ifdef SCANNER
		b_j_parameter (curline, param, len);
#endif
}

// g K 	decimal Z offset for arcs and G87 canned cycles.
 void k_parameter(size_t curline, char * param, size_t len)
{
		fprintf(flog, "\tK parameter(%lu): ", curline );
		fwrite( param, 1, len, flog );
		fprintf(flog,"\n"); 
#ifdef SCANNER
		b_k_parameter (curline, param, len);
#endif
}

// g L 			decimal	 generic parameter word for G10, M66 and others
 void l_parameter(size_t curline, char * param, size_t len)
{
		fprintf(flog, "\tL parameter(%lu): ", curline );
		fwrite( param, 1, len, flog );
		fprintf(flog,"\n"); 
#ifdef SCANNER
		b_l_parameter (curline, param, len);
#endif		
}

// g M 	digit 	= command= Code Modal Groups
 void m_parameter(size_t curline, char * param, size_t len)
{
		fprintf(flog, "M command(%lu): ", curline );
		fwrite( param, 1, len, flog );
		fprintf(flog,"\n");
#ifdef SCANNER
		b_m_parameter (curline, param, len);
#endif	
}

// g N digit				Line number
 void n_parameter(size_t curline, char * param, size_t len)
{
		fprintf(flog, "\tN parameter(%lu): ", curline );
		fwrite( param, 1, len, flog );
		fprintf(flog,"\n"); 
#ifdef SCANNER
		b_n_parameter (curline, param, len);
#endif		
}

// g P	alnum_u		Command parameter, such as time in milliseconds; proportional (Kp) in PID Tuning 
 void p_parameter(size_t curline, char * param, size_t len)
{
		fprintf(flog, "\tP parameter(%lu): ", curline );
		fwrite( param, 1, len, flog );
		fprintf(flog,"\n"); 
#ifdef SCANNER
		b_p_parameter (curline, param, len);
#endif		
}

// g R 	optional	Arc radius or canned cycle plane
 void r_parameter(size_t curline, char * param, size_t len)
{
		fprintf(flog, "\tR parameter(%lu): ", curline );
		fwrite( param, 1, len, flog );
		fprintf(flog,"\n"); 
#ifdef SCANNER
		b_r_parameter (curline, param, len);
#endif		
}

// g S	optional	Spindle speed; Command parameter, such as time in seconds; temperatures; voltage to send to a motor 
 void s_parameter(size_t curline, char * param, size_t len)
{
		fprintf(flog, "\tS parameter(%lu): ", curline );
		fwrite( param, 1, len, flog );
		fprintf(flog,"\n"); 
#ifdef SCANNER
		b_s_parameter (curline, param, len);
#endif		
}

// g T	digit	=command= 	Tool selection
 void t_parameter(size_t curline, char * param, size_t len)
{
		fprintf(flog, "\tT parameter(%lu): ", curline );
		fwrite( param, 1, len, flog );
		fprintf(flog,"\n"); 
#ifdef SCANNER
		b_t_parameter (curline, param, len);
#endif		
}

// g U	optional  	U axis of machine;
 void u_parameter(size_t curline, char * param, size_t len)
{
		fprintf(flog, "\tU parameter(%lu): ", curline );
		fwrite( param, 1, len, flog );
		fprintf(flog,"\n"); 
#ifdef SCANNER
		b_u_parameter (curline, param, len);
#endif		
}

// g V	optional  	V axis of machine;
 void v_parameter(size_t curline, char * param, size_t len)
{
		fprintf(flog, "\tV parameter(%lu): ", curline );
		fwrite( param, 1, len, flog );
		fprintf(flog,"\n"); 
#ifdef SCANNER
		b_v_parameter (curline, param, len);
#endif		
}

// g W	optional  	W axis of machine;
 void w_parameter(size_t curline, char * param, size_t len)
{
		fprintf(flog, "\tW parameter(%lu): ", curline );
		fwrite( param, 1, len, flog );
		fprintf(flog,"\n"); 
#ifdef SCANNER
		b_w_parameter (curline, param, len);
#endif		
}

// g *	digit		Checksum 
 void star_parameter(size_t curline, char * param, size_t len)
{
		fprintf(flog, "\tchecksum_lit(%lu): ", curline );
		fwrite( param, 1, len, flog );
		fprintf(flog,"\n");
#ifdef SCANNER
		b_star_parameter (curline, param, len);
#endif		
}




// 		punct			Symbols.

%%{
	machine gparcer;
	
	
	access fsm->;
	variable p fsm->p;
	variable pe fsm->pe;
	variable eof fsm->eof;
	variable cs fsm->cs;
	
	action finish_ok {
//		if ( fsm->buflen > 0 )
//			fsm->write( fsm->buf, fsm->buflen );
//		fwrite("End\n",1,4,stdout);
		printf("Parcer ended.");
	}
	
	newline = '\n' @{
		//parser_out = command;
		(*prs[eCommand])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
		fsm->curline += 1;
		fsm->pe = fsm->te;
		fsm->done = 1;
//		fsm->eof = fsm->te;
		};
		
	any_count_line = any | newline;

	# Consume a C comment.
#	c_comment := any_count_line* :>> '*/' @{fgoto main;};
#	g_comment :=  any* :>> '\n' @{ fprintf(flog, "gcomment(%lu): ", fsm->curline );
#		//fprintf(flog,"te=%5s  te=%5s",te,ts);
#		//printf("te=%lu ts=%lu ;",te,ts);
#		//curline ++;
#		fgoto main;};

	# Alpha numberic characters or underscore.
	alnum_u = alnum | '_';

	# Alpha charactres or underscore.
	alpha_u = alpha | '_';

	optional = (('+'|'-')? digit+ ('.' digit+)?){,1};
	
	decimal = ('+'|'-')? digit+ ('.' digit+)?;
		
	word = alnum*;

	main := |*
#	gparcer := |*

	# g comment
#	';' { fgoto g_comment; };
#	';' any* :>> '\n' { printf("[42]te=%lu ts=%lu ;",fsm->te,fsm->ts); fsm->curline++;};
	';' (any-'\n')* { 
		//parser_out = gcomment;
		(*prs[eComment])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
		};
	'(' any* :>> ')'  {
		//parser_out = gcomment;
		(*prs[eComment])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
		};

	# g command GXX.X
	'G' digit{1,2} ('.' digit+)? {
		//parser_out = g_command;
		(*prs[eGcommand])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
		};

	# g X coordinate
	'X' optional {
		//parser_out = x_coordinate;
		(*prs[eXparam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
		};

	# g Y coordinate
	'Y' optional {
		//parser_out = y_coordinate;
		(*prs[eYparam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
		};

	# g Z coordiane
	'Z' optional {
		//parser_out = z_coordinate;
		(*prs[eZparam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
		};

	# g A    Stepper A position or angle {Annn]
	'A' decimal {
		//parser_out = a_parameter;
		(*prs[eAparam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
		};
	
	# g B  Stepper B position or angle {Bnnn}
	'B' decimal {
		//parser_out = b_parameter;
		(*prs[eBparam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
		};

	# g C  Stepper C position or angle {Cnnn}
	'C' decimal{
		//parser_out = c_parameter;
		(*prs[eCparam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
		};

	# g D  Adjust Diagonal Rod {D}
	'D' {
		//parser_out = d_parameter;
		(*prs[eDparam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
		};

	# g E coordinate
	'E' optional {
		//parser_out = e_parameter;
		(*prs[eEparam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
		};


	# g F Feed rate parameter in G-command
	'F' decimal {
		//parser_out = f_parameter;
		(*prs[eFparam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
		};

	# g I X offset for arcs and G87 canned cycles
	'I' optional {
		//parser_out = i_parameter;
		(*prs[eIparam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
		};

	# g J Y offset for arcs and G87 canned cycles
	'J' decimal {
		//parser_out = j_parameter;
		(*prs[eJparam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
		};

	# g K Z offset for arcs and G87 canned cycles.
	'K' decimal {
		//parser_out = k_parameter;
		(*prs[eKparam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
		};
	
	
	# g L generic parameter word for G10, M66 and others
	'L' decimal {
		//parser_out = l_parameter;
		(*prs[eLparam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
		};
	
	# g M Code Modal Groups
	'M'  digit+ {
		//parser_out = m_parameter;
		(*prs[eMparam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
		};

	# g N Line number 
	'N'  digit+ {
		//parser_out = n_parameter;
		(*prs[eNparam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
		};

	# g P  	Command parameter, such as time in milliseconds; proportional (Kp) in PID Tuning 
	#		Dwell time in canned cycles and with G4. Key used with G10.
	'P' alnum_u*  {
		//parser_out = p_parameter;
		(*prs[ePparam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
		};

	# g R Arc radius or canned cycle plane
	#	R Relative move flag 
	'R' optional {
		//parser_out = r_parameter;
		(*prs[eRparam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
		};

	# g S Spindle speed; Command parameter, such as time in seconds; temperatures; voltage to send to a motor 
	'S'  optional   {
		//parser_out = s_parameter;
		(*prs[eSparam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
		};
		
	# g T Tool selection
	'T'  digit? {
		//parser_out = t_parameter;
		(*prs[eTpaam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
		};

	# g U  	U axis of machine;
	#		Un <bool> with a non-zero value will apply the result to current zprobe_zoffset 
	'U' optional {
		//parser_out = u_parameter;
		(*prs[eUparam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
		};
		
	# g V  	V axis of machine;
	'V' optional {
		//parser_out = v_parameter;
		(*prs[eVparam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
		};
		
	# g W  	W axis of machine;
	'W' optional {
		//parser_out = w_parameter;
		(*prs[eWparam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
		};

	# g * Checksum 
	'*' digit{2} {
		//parser_out = star_parameter;
		(*prs[eStarparam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
		};

	# Whitespace is standard ws, newlines and control codes.
	any_count_line - 0x21..0x7e;

	# Symbols. Upon entering clear the buffer. On all transitions
	# buffer a character. Upon leaving dump the symbol.
	( punct - [_'"()] ) {
		fprintf(flog, "symbol(%i): %c\n", fsm->curline, fsm->ts[0] );
	};


	# Describe both c style comments and c++ style comments. The
	# priority bump on tne terminator of the comments brings us
	# out of the extend* which matches everything.
	# eof string
	'\n'* newline;
#	'\n'* newline $!finish_ok;


	*|;
	
#	main :=  ( )* @/ fcall gparcer ;
}%%

%% write data nofinal;


struct format fsm;



int format_finish( struct format *fsmp )
{
	if ( fsmp->cs == format_error )
		return -1;
	if ( fsmp->cs >= format_first_final )
		return 1;
	return 0;
}

void format_init( struct format *fsm )
{
	fsm->buflen = 0;
	fsm->done = 0;
	//int cs, act, have = 0, curline = 1;
	fsm->have = 0;
	fsm->curline = 1;
	fsm->state = 0;
	%% write init;
}

void format_execute( struct format *fsm, char *data, int len, int isEof )
{
//	const char *p = data;
//	const char *pe = data + len;
//	const char *eof = isEof ? pe : 0;
	fsm->p = data;
	fsm->pe = data+len;
	fsm->eof = isEof ? fsm->pe : 0;
	if(len == 0)
		return;
	
	%% write exec;
	
		if ( format_finish( fsm ) <= 0 )
		printf("[602] FAIL  %-10s \n", data);

	
}



void scanner(){
scannerstart:
	switch (fsm.state)
	{
	case 0:
		fsm.space = INPUT_BUFSIZE - fsm.have;
		fsm.p = fsm.buf + fsm.have;
		
		if ( fsm.space == 0 ) {
			/* We've used up the entire buffer storing an already-parsed token
			 * prefix that must be preserved. */
			fprintf(stderr, "OUT OF BUFFER SPACE\n" );
			exit(1);
		}
	
		fsm.lenfile = fread( fsm.buf+fsm.have, 1, fsm.space, fp );
		
		fsm.eofile = fsm.lenfile != fsm.space;
		
		format_execute( &fsm, fsm.p, fsm.lenfile, fsm.eofile );
		fsm.state = 1;
		 return;
	
	case 1:
		if(fsm.done)
		{
			fsm.done = 0;
			fsm.lenfile = INPUT_BUFSIZE - (fsm.pe - fsm.buf);
			format_execute( &fsm, fsm.pe, fsm.lenfile, fsm.eofile );
			return;
		}
	case 3:
//		printf("[646] done:  %i \n", fsm.done);
		if ( fsm.eofile ){
//			fprintf(stderr, " [650] EOF lenfile:%i  space:%i \n", fsm.lenfile , fsm.space);
			return;
		//	break;
		}	
		
		if ( fsm.ts == 0 ){
			fsm.have = 0;
		}
		else {
			/* There is a prefix to preserve, shift it over. */
			fsm.have = fsm.pe - fsm.ts;
			memmove( fsm.buf, fsm.ts, fsm.have );
			fsm.te = fsm.buf + (fsm.te-fsm.ts);
			fsm.ts = fsm.buf;
		}
	
	}
	
	fsm.state = 0;
	goto scannerstart;

}

#ifndef SCANNER
int main()
{

//	int eofile;
//	int len;

	fsm.buf = buf;
	format_init( &fsm );

	fp = fopen("exmple.gcode","r");
	   if (fp==NULL) {fputs ("File error",stderr); exit (1);}
	flog = fopen("gParcer.log","w");
	   if (flog==NULL) {fputs ("File error",stderr); exit (1);}


	while(!fsm.eof)
	{	
		scanner();
	}
	
	if ( format_finish( &fsm ) <= 0 )
		printf("[679] FAIL  %li \n", (unsigned long)&fsm);

	
	fclose(fp);
	fclose(flog);
	return 0;
}
#endif
