
#line 1 "gParcer.rl"
/*
 * A mini G_Code language scanner.
 */


#include "gParcer.h"

#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//#include <string.h>
//#include <stddef.h>


//#define BUFLEN 512

typedef void (*gfunction)(size_t, char *, size_t );  // Declare typedef

//#define INPUT_BUFSIZE 1024





//enum prsCmd{
//    eCommand, eComment, eGcommand, eXparam, eYparam, eZparam, eAparam
//    , eBparam, eCparam, eDparam, eEparam, eFparam, eIparam, eJparam
//    , eKparam, eLparam, eMparam, eNparam, ePparam, eRparam, eSparam
//    , eTpaam, eUparam, eVparam, eWparam, eStarparam,ePunct

//};

/*
struct sGParam{
    char group;
    int  value;
};

struct sGcode{
    char group;
    int	 value;
    int index; // params caounter.
    struct sGParam params[10];
};

*/
/*
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
*/
//#define curline	fsm->curline

//------------------- vars

static const int format_start = 11;
static const int format_first_final = 11;
static const int format_error = 0;

char buf[INPUT_BUFSIZE];


//	int have = 0, curline = 1;
//	char *ts, *te = 0;
//	int done = 0;


//static    FILE *fp;
//static    FILE *flog;
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
 void gpunct(size_t curline, char * param, size_t len);

gfunction prs[] = {&command,&gcomment,&g_command,&x_coordinate
    , &y_coordinate	,&z_coordinate,&a_parameter, &b_parameter
    , &c_parameter, &d_parameter, &e_parameter, &f_parameter
    , &i_parameter, &j_parameter, &k_parameter, &l_parameter
    , &m_parameter, &n_parameter, &p_parameter, &r_parameter
    , &s_parameter, &t_parameter, &u_parameter, &v_parameter
    , &w_parameter, &star_parameter, &gpunct  };


// g Command
 void command (size_t curline, char * param, size_t len){
#ifdef FLOG
        fprintf(flog, "Command(%lu): ", curline );
        fwrite( param, 1, len, flog );
        fprintf(flog,"\n");
#endif
#ifdef SCANNER
        b_command(curline,param,len);
#endif
}




// g comment
 void gcomment (size_t curline, char * param, size_t len){
#ifdef FLOG
        fprintf(flog, "gcomment(%lu): ", curline );
        fwrite( param, 1, len, flog );
        fprintf(flog,"\n");
#endif
#ifdef SCANNER
        b_gcomment(curline,param,len);
#endif
}

// g GXX.X digit 		=command=	command GXX.X
 void g_command (size_t curline, char * param, size_t len){
#ifdef FLOG
     fprintf(flog, "G command(%lu): ", curline );
        fwrite( param, 1, len, flog );
        fprintf(flog,"\n");
#endif
#ifdef SCANNER
        b_g_command (curline, param, len);
#endif
}

// g X coordinate
 void x_coordinate(size_t curline, char * param, size_t len)
{
#ifdef FLOG
     fprintf(flog, "\tX parameter(%lu): ", curline );
        fwrite( param, 1, len, flog );
        fprintf(flog,"\n");
#endif
#ifdef SCANNER
        b_x_coordinate (curline, param, len);
#endif
}

// g Y 	coordinat
 void y_coordinate(size_t curline, char * param, size_t len)
{
#ifdef FLOG
     fprintf(flog, "\tY parameter(%lu): ", curline );
        fwrite( param, 1, len, flog );
        fprintf(flog,"\n");
#endif
#ifdef SCANNER
        b_y_coordinate (curline, param, len);
#endif
}

// g Z 	coordiane Line78
 void z_coordinate(size_t curline, char * param, size_t len)
{
#ifdef FLOG
     fprintf(flog, "\tZ parameter(%lu): ", curline );
        fwrite( param, 1, len, flog );
        fprintf(flog,"\n");
#endif
#ifdef SCANNER
        b_z_coordinate (curline, param, len);
#endif
}

// g A	 decimal   Stepper A position or angle {Annn]

 void a_parameter(size_t curline, char * param, size_t len)
{
#ifdef FLOG
     fprintf(flog, "\tA parameter(%lu): ", curline );
        fwrite( param, 1, len, flog );
        fprintf(flog,"\n");
#endif
#ifdef SCANNER
        b_a_parameter (curline, param, len);
#endif
}

// g B	 decimal Stepper B position or angle {Bnnn}
 void b_parameter(size_t curline, char * param, size_t len)
{
#ifdef FLOG
     fprintf(flog, "\tB parameter(%lu): ", curline );
        fwrite( param, 1, len, flog );
        fprintf(flog,"\n");
#endif
#ifdef SCANNER
        b_b_parameter (curline, param, len);
#endif
}

// g C	 decimal Stepper C position or angle {Cnnn}
 void c_parameter(size_t curline, char * param, size_t len)
{
#ifdef FLOG
     fprintf(flog, "\tC parameter(%lu): ", curline );
        fwrite( param, 1, len, flog );
        fprintf(flog,"\n");
#endif
#ifdef SCANNER
        b_c_parameter (curline, param, len);
#endif
}

// g D	 none Adjust Diagonal Rod {D}
 void d_parameter(size_t curline, char * param, size_t len)
{
#ifdef FLOG
     fprintf(flog, "\tD parameter(%lu): ", curline );
        fwrite( param, 1, len, flog );
        fprintf(flog,"\n");
#endif
#ifdef SCANNER
        b_d_parameter (curline, param, len);
#endif
}

// g E	 optional coordinate
 void e_parameter(size_t curline, char * param, size_t len)
{
#ifdef FLOG
     fprintf(flog, "\tE parameter(%lu): ", curline );
        fwrite( param, 1, len, flog );
        fprintf(flog,"\n");
#endif
#ifdef SCANNER
        b_e_parameter (curline, param, len);
#endif
}

// g F 	decimal Feed rate parameter in G-command
 void f_parameter(size_t curline, char * param, size_t len)
{
#ifdef FLOG
     fprintf(flog, "\tF parameter(%lu): ", curline );
        fwrite( param, 1, len, flog );
        fprintf(flog,"\n");
#endif
#ifdef SCANNER
        b_f_parameter (curline, param, len);
#endif
}

// g I 	optional X offset for arcs and G87 canned cycles
 void i_parameter(size_t curline, char * param, size_t len)
{
#ifdef FLOG
     fprintf(flog, "\tI parameter(%lu): ", curline );
        fwrite( param, 1, len, flog );
        fprintf(flog,"\n");
#endif
#ifdef SCANNER
        b_i_parameter (curline, param, len);
#endif
}

// g J	 decimal Y offset for arcs and G87 canned cycles
 void j_parameter(size_t curline, char * param, size_t len)
{
#ifdef FLOG
     fprintf(flog, "\tJ parameter(%lu): ", curline );
        fwrite( param, 1, len, flog );
        fprintf(flog,"\n");
#endif
#ifdef SCANNER
        b_j_parameter (curline, param, len);
#endif
}

// g K 	decimal Z offset for arcs and G87 canned cycles.
 void k_parameter(size_t curline, char * param, size_t len)
{
#ifdef FLOG
     fprintf(flog, "\tK parameter(%lu): ", curline );
        fwrite( param, 1, len, flog );
        fprintf(flog,"\n");
#endif
#ifdef SCANNER
        b_k_parameter (curline, param, len);
#endif
}

// g L 			decimal	 generic parameter word for G10, M66 and others
 void l_parameter(size_t curline, char * param, size_t len)
{
#ifdef FLOG
     fprintf(flog, "\tL parameter(%lu): ", curline );
        fwrite( param, 1, len, flog );
        fprintf(flog,"\n");
#endif
#ifdef SCANNER
        b_l_parameter (curline, param, len);
#endif
}

// g M 	digit 	= command= Code Modal Groups
 void m_parameter(size_t curline, char * param, size_t len)
{
#ifdef FLOG
     fprintf(flog, "M command(%lu): ", curline );
        fwrite( param, 1, len, flog );
        fprintf(flog,"\n");
#endif
#ifdef SCANNER
        b_m_parameter (curline, param, len);
#endif
}

// g N digit				Line number
 void n_parameter(size_t curline, char * param, size_t len)
{
#ifdef FLOG
     fprintf(flog, "\tN parameter(%lu): ", curline );
        fwrite( param, 1, len, flog );
        fprintf(flog,"\n");
#endif
#ifdef SCANNER
        b_n_parameter (curline, param, len);
#endif
}

// g P	alnum_u		Command parameter, such as time in milliseconds; proportional (Kp) in PID Tuning
 void p_parameter(size_t curline, char * param, size_t len)
{
#ifdef FLOG
     fprintf(flog, "\tP parameter(%lu): ", curline );
        fwrite( param, 1, len, flog );
        fprintf(flog,"\n");
#endif
#ifdef SCANNER
        b_p_parameter (curline, param, len);
#endif
}

// g R 	optional	Arc radius or canned cycle plane
 void r_parameter(size_t curline, char * param, size_t len)
{
#ifdef FLOG
     fprintf(flog, "\tR parameter(%lu): ", curline );
        fwrite( param, 1, len, flog );
        fprintf(flog,"\n");
#endif
#ifdef SCANNER
        b_r_parameter (curline, param, len);
#endif
}

// g S	optional	Spindle speed; Command parameter, such as time in seconds; temperatures; voltage to send to a motor
 void s_parameter(size_t curline, char * param, size_t len)
{
#ifdef FLOG
     fprintf(flog, "\tS parameter(%lu): ", curline );
        fwrite( param, 1, len, flog );
        fprintf(flog,"\n");
#endif
#ifdef SCANNER
        b_s_parameter (curline, param, len);
#endif
}

// g T	digit	=command= 	Tool selection
 void t_parameter(size_t curline, char * param, size_t len)
{
#ifdef FLOG
     fprintf(flog, "\tT parameter(%lu): ", curline );
        fwrite( param, 1, len, flog );
        fprintf(flog,"\n");
#endif
#ifdef SCANNER
        b_t_parameter (curline, param, len);
#endif
}

// g U	optional  	U axis of machine;
 void u_parameter(size_t curline, char * param, size_t len)
{
#ifdef FLOG
     fprintf(flog, "\tU parameter(%lu): ", curline );
        fwrite( param, 1, len, flog );
        fprintf(flog,"\n");
#endif
#ifdef SCANNER
        b_u_parameter (curline, param, len);
#endif
}

// g V	optional  	V axis of machine;
 void v_parameter(size_t curline, char * param, size_t len)
{
#ifdef FLOG
     fprintf(flog, "\tV parameter(%lu): ", curline );
        fwrite( param, 1, len, flog );
        fprintf(flog,"\n");
#endif
#ifdef SCANNER
        b_v_parameter (curline, param, len);
#endif
}

// g W	optional  	W axis of machine;
 void w_parameter(size_t curline, char * param, size_t len)
{
#ifdef FLOG
     fprintf(flog, "\tW parameter(%lu): ", curline );
        fwrite( param, 1, len, flog );
        fprintf(flog,"\n");
#endif
#ifdef SCANNER
        b_w_parameter (curline, param, len);
#endif
}

// g *	digit		Checksum
 void star_parameter(size_t curline, char * param, size_t len)
{
#ifdef FLOG
     fprintf(flog, "\tchecksum_lit(%lu): ", curline );
        fwrite( param, 1, len, flog );
        fprintf(flog,"\n");
#endif
#ifdef SCANNER
        b_star_parameter (curline, param, len);
#endif
}

 void gpunct(size_t curline, char * param, size_t len)
 {
#ifdef FLOG
     fprintf(flog, "symbol(%lu): %c\n", curline, *param );
#endif
 #ifdef SCANNER
     b_punct(curline, param, len);
 #endif
}

// 		punct			Symbols.


#line 660 "gParcer.rl"



#line 435 "gParcer.c"
static const char _gparcer_actions[] = {
    0, 1, 1, 1, 2, 1, 3, 1,
    6, 1, 7, 1, 8, 1, 9, 1,
    10, 1, 11, 1, 12, 1, 13, 1,
    14, 1, 15, 1, 16, 1, 17, 1,
    18, 1, 19, 1, 20, 1, 21, 1,
    22, 1, 23, 1, 24, 1, 25, 1,
    26, 1, 27, 1, 28, 1, 29, 1,
    30, 1, 31, 1, 32, 1, 33, 1,
    34, 1, 35, 1, 36, 1, 37, 1,
    38, 1, 39, 1, 40, 1, 41, 1,
    42, 1, 43, 1, 44, 1, 45, 1,
    46, 1, 47, 1, 48, 1, 49, 1,
    50, 1, 51, 1, 52, 1, 53, 1,
    54, 1, 55, 3, 3, 0, 4, 3,
    3, 0, 5
};

static const short _gparcer_key_offsets[] = {
    0, 0, 1, 3, 7, 9, 11, 15,
    17, 19, 23, 25, 27, 29, 31, 35,
    37, 39, 41, 43, 45, 47, 51, 53,
    55, 59, 61, 63, 67, 69, 71, 73,
    75, 77, 79, 81, 83, 85, 87, 89,
    91, 93, 95, 97, 99, 101, 103, 105,
    107, 151, 152, 154, 155, 158, 160, 163,
    165, 168, 170, 174, 177, 179, 182, 184,
    187, 189, 190, 194, 197, 199, 202, 204,
    207, 209, 212, 214, 216, 218, 225, 229,
    232, 234, 238, 241, 243, 245, 249, 252,
    254, 258, 261, 263, 267, 270, 272, 276,
    279, 281, 285, 288, 290, 294, 297
};

static const char _gparcer_trans_keys[] = {
    41, 48, 57, 43, 45, 48, 57, 48,
    57, 48, 57, 43, 45, 48, 57, 48,
    57, 48, 57, 43, 45, 48, 57, 48,
    57, 48, 57, 48, 57, 48, 57, 43,
    45, 48, 57, 48, 57, 48, 57, 48,
    57, 48, 57, 48, 57, 48, 57, 43,
    45, 48, 57, 48, 57, 48, 57, 43,
    45, 48, 57, 48, 57, 48, 57, 43,
    45, 48, 57, 48, 57, 48, 57, 48,
    57, 48, 57, 48, 57, 48, 57, 48,
    57, 48, 57, 48, 57, 48, 57, 48,
    57, 48, 57, 48, 57, 48, 57, 48,
    57, 48, 57, 48, 57, 48, 57, 48,
    57, 48, 57, 10, 34, 39, 40, 41,
    42, 59, 65, 66, 67, 68, 69, 70,
    71, 72, 73, 74, 75, 76, 77, 78,
    79, 80, 81, 82, 83, 84, 85, 86,
    87, 88, 89, 90, 95, 33, 47, 48,
    57, 58, 96, 97, 122, 123, 126, 10,
    48, 57, 10, 46, 48, 57, 48, 57,
    46, 48, 57, 48, 57, 46, 48, 57,
    48, 57, 43, 45, 48, 57, 46, 48,
    57, 48, 57, 46, 48, 57, 48, 57,
    46, 48, 57, 48, 57, 46, 43, 45,
    48, 57, 46, 48, 57, 48, 57, 46,
    48, 57, 48, 57, 46, 48, 57, 48,
    57, 46, 48, 57, 48, 57, 48, 57,
    48, 57, 95, 48, 57, 65, 90, 97,
    122, 43, 45, 48, 57, 46, 48, 57,
    48, 57, 43, 45, 48, 57, 46, 48,
    57, 48, 57, 48, 57, 43, 45, 48,
    57, 46, 48, 57, 48, 57, 43, 45,
    48, 57, 46, 48, 57, 48, 57, 43,
    45, 48, 57, 46, 48, 57, 48, 57,
    43, 45, 48, 57, 46, 48, 57, 48,
    57, 43, 45, 48, 57, 46, 48, 57,
    48, 57, 43, 45, 48, 57, 46, 48,
    57, 48, 57, 0
};

static const char _gparcer_single_lengths[] = {
    0, 1, 0, 2, 0, 0, 2, 0,
    0, 2, 0, 0, 0, 0, 2, 0,
    0, 0, 0, 0, 0, 2, 0, 0,
    2, 0, 0, 2, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    34, 1, 0, 1, 1, 0, 1, 0,
    1, 0, 2, 1, 0, 1, 0, 1,
    0, 1, 2, 1, 0, 1, 0, 1,
    0, 1, 0, 0, 0, 1, 2, 1,
    0, 2, 1, 0, 0, 2, 1, 0,
    2, 1, 0, 2, 1, 0, 2, 1,
    0, 2, 1, 0, 2, 1, 0
};

static const char _gparcer_range_lengths[] = {
    0, 0, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    5, 0, 1, 0, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 3, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1
};

static const short _gparcer_index_offsets[] = {
    0, 0, 2, 4, 8, 10, 12, 16,
    18, 20, 24, 26, 28, 30, 32, 36,
    38, 40, 42, 44, 46, 48, 52, 54,
    56, 60, 62, 64, 68, 70, 72, 74,
    76, 78, 80, 82, 84, 86, 88, 90,
    92, 94, 96, 98, 100, 102, 104, 106,
    108, 148, 150, 152, 154, 157, 159, 162,
    164, 167, 169, 173, 176, 178, 181, 183,
    186, 188, 190, 194, 197, 199, 202, 204,
    207, 209, 212, 214, 216, 218, 223, 227,
    230, 232, 236, 239, 241, 243, 247, 250,
    252, 256, 259, 261, 265, 268, 270, 274,
    277, 279, 283, 286, 288, 292, 295
};

static const char _gparcer_trans_targs[] = {
    48, 1, 48, 48, 4, 4, 52, 0,
    52, 0, 53, 48, 7, 7, 54, 0,
    54, 0, 55, 48, 10, 10, 56, 0,
    56, 0, 57, 48, 59, 48, 60, 48,
    15, 15, 61, 0, 61, 0, 62, 48,
    63, 0, 64, 48, 67, 48, 68, 48,
    22, 22, 69, 0, 69, 0, 70, 48,
    25, 25, 71, 0, 71, 0, 72, 48,
    28, 28, 73, 0, 73, 0, 74, 48,
    75, 0, 76, 0, 79, 48, 80, 48,
    82, 48, 83, 48, 86, 48, 87, 48,
    89, 48, 90, 48, 92, 48, 93, 48,
    95, 48, 96, 48, 98, 48, 99, 48,
    101, 48, 102, 48, 49, 0, 0, 1,
    0, 50, 51, 3, 6, 9, 48, 58,
    14, 17, 0, 66, 21, 24, 27, 30,
    31, 0, 77, 0, 78, 81, 84, 85,
    88, 91, 94, 97, 100, 0, 48, 0,
    48, 0, 48, 48, 49, 48, 2, 48,
    48, 51, 5, 52, 48, 53, 48, 8,
    54, 48, 55, 48, 11, 56, 48, 57,
    48, 12, 12, 59, 48, 13, 59, 48,
    60, 48, 16, 61, 48, 62, 48, 18,
    65, 48, 64, 48, 18, 48, 19, 19,
    67, 48, 20, 67, 48, 68, 48, 23,
    69, 48, 70, 48, 26, 71, 48, 72,
    48, 29, 73, 48, 74, 48, 75, 48,
    76, 48, 77, 77, 77, 77, 48, 32,
    32, 79, 48, 33, 79, 48, 80, 48,
    34, 34, 82, 48, 35, 82, 48, 83,
    48, 48, 48, 36, 36, 86, 48, 37,
    86, 48, 87, 48, 38, 38, 89, 48,
    39, 89, 48, 90, 48, 40, 40, 92,
    48, 41, 92, 48, 93, 48, 42, 42,
    95, 48, 43, 95, 48, 96, 48, 44,
    44, 98, 48, 45, 98, 48, 99, 48,
    46, 46, 101, 48, 47, 101, 48, 102,
    48, 48, 48, 48, 48, 48, 48, 48,
    48, 48, 48, 48, 48, 48, 48, 48,
    48, 48, 48, 48, 48, 48, 48, 48,
    48, 48, 48, 48, 48, 48, 48, 48,
    48, 48, 48, 48, 48, 48, 48, 48,
    48, 48, 48, 48, 48, 48, 48, 48,
    48, 48, 48, 48, 48, 48, 48, 48,
    48, 48, 48, 48, 48, 48, 48, 48,
    48, 48, 48, 48, 48, 48, 48, 48,
    48, 48, 48, 48, 48, 48, 48, 48,
    48, 48, 48, 48, 0
};

static const char _gparcer_trans_actions[] = {
    7, 0, 13, 103, 0, 0, 5, 0,
    5, 0, 0, 75, 0, 0, 5, 0,
    5, 0, 0, 77, 0, 0, 5, 0,
    5, 0, 0, 79, 5, 81, 0, 81,
    0, 0, 5, 0, 5, 0, 0, 83,
    5, 0, 0, 67, 5, 85, 0, 85,
    0, 0, 5, 0, 5, 0, 0, 87,
    0, 0, 5, 0, 5, 0, 0, 89,
    0, 0, 5, 0, 5, 0, 0, 91,
    0, 0, 0, 0, 5, 93, 0, 93,
    5, 95, 0, 95, 5, 97, 0, 97,
    5, 99, 0, 99, 5, 101, 0, 101,
    5, 69, 0, 69, 5, 71, 0, 71,
    5, 73, 0, 73, 107, 0, 0, 0,
    0, 5, 0, 0, 0, 0, 9, 5,
    0, 0, 0, 5, 0, 0, 0, 0,
    0, 0, 0, 0, 5, 5, 0, 5,
    5, 5, 5, 5, 5, 0, 17, 0,
    17, 0, 17, 15, 111, 105, 0, 65,
    19, 0, 0, 5, 29, 0, 29, 0,
    5, 31, 0, 31, 0, 5, 33, 0,
    33, 0, 0, 5, 35, 0, 5, 35,
    0, 35, 0, 5, 37, 0, 37, 0,
    5, 21, 0, 21, 0, 21, 0, 0,
    5, 39, 0, 5, 39, 0, 39, 0,
    5, 41, 0, 41, 0, 5, 43, 0,
    43, 0, 5, 45, 0, 45, 0, 47,
    0, 49, 0, 0, 0, 0, 51, 0,
    0, 5, 53, 0, 5, 53, 0, 53,
    0, 0, 5, 55, 0, 5, 55, 0,
    55, 11, 57, 0, 0, 5, 59, 0,
    5, 59, 0, 59, 0, 0, 5, 61,
    0, 5, 61, 0, 61, 0, 0, 5,
    63, 0, 5, 63, 0, 63, 0, 0,
    5, 23, 0, 5, 23, 0, 23, 0,
    0, 5, 25, 0, 5, 25, 0, 25,
    0, 0, 5, 27, 0, 5, 27, 0,
    27, 103, 75, 77, 79, 81, 81, 83,
    67, 85, 85, 87, 89, 91, 93, 93,
    95, 95, 97, 97, 99, 99, 101, 101,
    69, 69, 71, 71, 73, 73, 105, 65,
    19, 29, 29, 31, 31, 33, 33, 35,
    35, 35, 37, 37, 21, 21, 21, 39,
    39, 39, 41, 41, 43, 43, 45, 45,
    47, 49, 51, 53, 53, 53, 55, 55,
    55, 57, 59, 59, 59, 61, 61, 61,
    63, 63, 63, 23, 23, 23, 25, 25,
    25, 27, 27, 27, 0
};

static const char _gparcer_to_state_actions[] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0
};

static const char _gparcer_from_state_actions[] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    3, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0
};

static const short _gparcer_eof_trans[] = {
    0, 0, 298, 0, 0, 299, 0, 0,
    300, 0, 0, 301, 303, 303, 0, 0,
    304, 0, 305, 307, 307, 0, 0, 308,
    0, 0, 309, 0, 0, 310, 0, 0,
    312, 312, 314, 314, 316, 316, 318, 318,
    320, 320, 322, 322, 324, 324, 326, 326,
    0, 327, 328, 329, 331, 331, 333, 333,
    335, 335, 338, 338, 338, 340, 340, 343,
    343, 343, 346, 346, 346, 348, 348, 350,
    350, 352, 352, 353, 354, 355, 358, 358,
    358, 361, 361, 361, 362, 365, 365, 365,
    368, 368, 368, 371, 371, 371, 374, 374,
    374, 377, 377, 377, 380, 380, 380
};

static const int gparcer_start = 48;
static const int gparcer_error = 0;

static const int gparcer_en_main = 48;


#line 663 "gParcer.rl"


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

#line 740 "gParcer.c"
    {
    ( fsm->cs) = gparcer_start;
     fsm->ts = 0;
     fsm->te = 0;
     fsm->act = 0;
    }

#line 687 "gParcer.rl"
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


#line 763 "gParcer.c"
    {
    int _klen;
    unsigned int _trans;
    const char *_acts;
    unsigned int _nacts;
    const char *_keys;

    if ( ( fsm->p) == ( fsm->pe) )
        goto _test_eof;
    if ( ( fsm->cs) == 0 )
        goto _out;
_resume:
    _acts = _gparcer_actions + _gparcer_from_state_actions[( fsm->cs)];
    _nacts = (unsigned int) *_acts++;
    while ( _nacts-- > 0 ) {
        switch ( *_acts++ ) {
    case 2:
#line 1 "NONE"
    { fsm->ts = ( fsm->p);}
    break;
#line 784 "gParcer.c"
        }
    }

    _keys = _gparcer_trans_keys + _gparcer_key_offsets[( fsm->cs)];
    _trans = _gparcer_index_offsets[( fsm->cs)];

    _klen = _gparcer_single_lengths[( fsm->cs)];
    if ( _klen > 0 ) {
        const char *_lower = _keys;
        const char *_mid;
        const char *_upper = _keys + _klen - 1;
        while (1) {
            if ( _upper < _lower )
                break;

            _mid = _lower + ((_upper-_lower) >> 1);
            if ( (*( fsm->p)) < *_mid )
                _upper = _mid - 1;
            else if ( (*( fsm->p)) > *_mid )
                _lower = _mid + 1;
            else {
                _trans += (unsigned int)(_mid - _keys);
                goto _match;
            }
        }
        _keys += _klen;
        _trans += _klen;
    }

    _klen = _gparcer_range_lengths[( fsm->cs)];
    if ( _klen > 0 ) {
        const char *_lower = _keys;
        const char *_mid;
        const char *_upper = _keys + (_klen<<1) - 2;
        while (1) {
            if ( _upper < _lower )
                break;

            _mid = _lower + (((_upper-_lower) >> 1) & ~1);
            if ( (*( fsm->p)) < _mid[0] )
                _upper = _mid - 2;
            else if ( (*( fsm->p)) > _mid[1] )
                _lower = _mid + 2;
            else {
                _trans += (unsigned int)((_mid - _keys)>>1);
                goto _match;
            }
        }
        _trans += _klen;
    }

_match:
_eof_trans:
    ( fsm->cs) = _gparcer_trans_targs[_trans];

    if ( _gparcer_trans_actions[_trans] == 0 )
        goto _again;

    _acts = _gparcer_actions + _gparcer_trans_actions[_trans];
    _nacts = (unsigned int) *_acts++;
    while ( _nacts-- > 0 )
    {
        switch ( *_acts++ )
        {
    case 0:
#line 444 "gParcer.rl"
    {
        //parser_out = command;
        (*prs[eCommand])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
        fsm->curline += 1;
        fsm->pe = fsm->te;
        fsm->done = 1;
//		fsm->eof = fsm->te;
        }
    break;
    case 3:
#line 1 "NONE"
    { fsm->te = ( fsm->p)+1;}
    break;
    case 4:
#line 640 "gParcer.rl"
    { fsm->act = 27;}
    break;
    case 5:
#line 653 "gParcer.rl"
    { fsm->act = 29;}
    break;
    case 6:
#line 485 "gParcer.rl"
    { fsm->te = ( fsm->p)+1;{
        //parser_out = gcomment;
        (*prs[eComment])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
        }}
    break;
    case 7:
#line 533 "gParcer.rl"
    { fsm->te = ( fsm->p)+1;{
        //parser_out = d_parameter;
        (*prs[eDparam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
        }}
    break;
    case 8:
#line 609 "gParcer.rl"
    { fsm->te = ( fsm->p)+1;{
        //parser_out = t_parameter;
        (*prs[eTpaam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
        }}
    break;
    case 9:
#line 634 "gParcer.rl"
    { fsm->te = ( fsm->p)+1;{
        //parser_out = star_parameter;
        (*prs[eStarparam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
        }}
    break;
    case 10:
#line 640 "gParcer.rl"
    { fsm->te = ( fsm->p)+1;}
    break;
    case 11:
#line 644 "gParcer.rl"
    { fsm->te = ( fsm->p)+1;{
        //fprintf(flog, "symbol(%i): %c\n", fsm->curline, fsm->ts[0] );
        (*prs[ePunct])(fsm->curline,fsm->ts,1);    }}
    break;
    case 12:
#line 481 "gParcer.rl"
    { fsm->te = ( fsm->p);( fsm->p)--;{
        //parser_out = gcomment;
        (*prs[eComment])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
        }}
    break;
    case 13:
#line 491 "gParcer.rl"
    { fsm->te = ( fsm->p);( fsm->p)--;{
        //parser_out = g_command;
        (*prs[eGcommand])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
        }}
    break;
    case 14:
#line 497 "gParcer.rl"
    { fsm->te = ( fsm->p);( fsm->p)--;{
        //parser_out = x_coordinate;
        (*prs[eXparam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
        }}
    break;
    case 15:
#line 503 "gParcer.rl"
    { fsm->te = ( fsm->p);( fsm->p)--;{
        //parser_out = y_coordinate;
        (*prs[eYparam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
        }}
    break;
    case 16:
#line 509 "gParcer.rl"
    { fsm->te = ( fsm->p);( fsm->p)--;{
        //parser_out = z_coordinate;
        (*prs[eZparam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
        }}
    break;
    case 17:
#line 515 "gParcer.rl"
    { fsm->te = ( fsm->p);( fsm->p)--;{
        //parser_out = a_parameter;
        (*prs[eAparam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
        }}
    break;
    case 18:
#line 521 "gParcer.rl"
    { fsm->te = ( fsm->p);( fsm->p)--;{
        //parser_out = b_parameter;
        (*prs[eBparam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
        }}
    break;
    case 19:
#line 527 "gParcer.rl"
    { fsm->te = ( fsm->p);( fsm->p)--;{
        //parser_out = c_parameter;
        (*prs[eCparam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
        }}
    break;
    case 20:
#line 539 "gParcer.rl"
    { fsm->te = ( fsm->p);( fsm->p)--;{
        //parser_out = e_parameter;
        (*prs[eEparam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
        }}
    break;
    case 21:
#line 546 "gParcer.rl"
    { fsm->te = ( fsm->p);( fsm->p)--;{
        //parser_out = f_parameter;
        (*prs[eFparam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
        }}
    break;
    case 22:
#line 552 "gParcer.rl"
    { fsm->te = ( fsm->p);( fsm->p)--;{
        //parser_out = i_parameter;
        (*prs[eIparam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
        }}
    break;
    case 23:
#line 558 "gParcer.rl"
    { fsm->te = ( fsm->p);( fsm->p)--;{
        //parser_out = j_parameter;
        (*prs[eJparam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
        }}
    break;
    case 24:
#line 564 "gParcer.rl"
    { fsm->te = ( fsm->p);( fsm->p)--;{
        //parser_out = k_parameter;
        (*prs[eKparam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
        }}
    break;
    case 25:
#line 571 "gParcer.rl"
    { fsm->te = ( fsm->p);( fsm->p)--;{
        //parser_out = l_parameter;
        (*prs[eLparam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
        }}
    break;
    case 26:
#line 577 "gParcer.rl"
    { fsm->te = ( fsm->p);( fsm->p)--;{
        //parser_out = m_parameter;
        (*prs[eMparam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
        }}
    break;
    case 27:
#line 583 "gParcer.rl"
    { fsm->te = ( fsm->p);( fsm->p)--;{
        //parser_out = n_parameter;
        (*prs[eNparam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
        }}
    break;
    case 28:
#line 590 "gParcer.rl"
    { fsm->te = ( fsm->p);( fsm->p)--;{
        //parser_out = p_parameter;
        (*prs[ePparam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
        }}
    break;
    case 29:
#line 597 "gParcer.rl"
    { fsm->te = ( fsm->p);( fsm->p)--;{
        //parser_out = r_parameter;
        (*prs[eRparam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
        }}
    break;
    case 30:
#line 603 "gParcer.rl"
    { fsm->te = ( fsm->p);( fsm->p)--;{
        //parser_out = s_parameter;
        (*prs[eSparam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
        }}
    break;
    case 31:
#line 609 "gParcer.rl"
    { fsm->te = ( fsm->p);( fsm->p)--;{
        //parser_out = t_parameter;
        (*prs[eTpaam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
        }}
    break;
    case 32:
#line 616 "gParcer.rl"
    { fsm->te = ( fsm->p);( fsm->p)--;{
        //parser_out = u_parameter;
        (*prs[eUparam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
        }}
    break;
    case 33:
#line 622 "gParcer.rl"
    { fsm->te = ( fsm->p);( fsm->p)--;{
        //parser_out = v_parameter;
        (*prs[eVparam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
        }}
    break;
    case 34:
#line 628 "gParcer.rl"
    { fsm->te = ( fsm->p);( fsm->p)--;{
        //parser_out = w_parameter;
        (*prs[eWparam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
        }}
    break;
    case 35:
#line 644 "gParcer.rl"
    { fsm->te = ( fsm->p);( fsm->p)--;{
        //fprintf(flog, "symbol(%i): %c\n", fsm->curline, fsm->ts[0] );
        (*prs[ePunct])(fsm->curline,fsm->ts,1);    }}
    break;
    case 36:
#line 491 "gParcer.rl"
    {{( fsm->p) = (( fsm->te))-1;}{
        //parser_out = g_command;
        (*prs[eGcommand])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
        }}
    break;
    case 37:
#line 497 "gParcer.rl"
    {{( fsm->p) = (( fsm->te))-1;}{
        //parser_out = x_coordinate;
        (*prs[eXparam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
        }}
    break;
    case 38:
#line 503 "gParcer.rl"
    {{( fsm->p) = (( fsm->te))-1;}{
        //parser_out = y_coordinate;
        (*prs[eYparam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
        }}
    break;
    case 39:
#line 509 "gParcer.rl"
    {{( fsm->p) = (( fsm->te))-1;}{
        //parser_out = z_coordinate;
        (*prs[eZparam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
        }}
    break;
    case 40:
#line 515 "gParcer.rl"
    {{( fsm->p) = (( fsm->te))-1;}{
        //parser_out = a_parameter;
        (*prs[eAparam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
        }}
    break;
    case 41:
#line 521 "gParcer.rl"
    {{( fsm->p) = (( fsm->te))-1;}{
        //parser_out = b_parameter;
        (*prs[eBparam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
        }}
    break;
    case 42:
#line 527 "gParcer.rl"
    {{( fsm->p) = (( fsm->te))-1;}{
        //parser_out = c_parameter;
        (*prs[eCparam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
        }}
    break;
    case 43:
#line 539 "gParcer.rl"
    {{( fsm->p) = (( fsm->te))-1;}{
        //parser_out = e_parameter;
        (*prs[eEparam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
        }}
    break;
    case 44:
#line 546 "gParcer.rl"
    {{( fsm->p) = (( fsm->te))-1;}{
        //parser_out = f_parameter;
        (*prs[eFparam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
        }}
    break;
    case 45:
#line 552 "gParcer.rl"
    {{( fsm->p) = (( fsm->te))-1;}{
        //parser_out = i_parameter;
        (*prs[eIparam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
        }}
    break;
    case 46:
#line 558 "gParcer.rl"
    {{( fsm->p) = (( fsm->te))-1;}{
        //parser_out = j_parameter;
        (*prs[eJparam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
        }}
    break;
    case 47:
#line 564 "gParcer.rl"
    {{( fsm->p) = (( fsm->te))-1;}{
        //parser_out = k_parameter;
        (*prs[eKparam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
        }}
    break;
    case 48:
#line 571 "gParcer.rl"
    {{( fsm->p) = (( fsm->te))-1;}{
        //parser_out = l_parameter;
        (*prs[eLparam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
        }}
    break;
    case 49:
#line 597 "gParcer.rl"
    {{( fsm->p) = (( fsm->te))-1;}{
        //parser_out = r_parameter;
        (*prs[eRparam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
        }}
    break;
    case 50:
#line 603 "gParcer.rl"
    {{( fsm->p) = (( fsm->te))-1;}{
        //parser_out = s_parameter;
        (*prs[eSparam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
        }}
    break;
    case 51:
#line 616 "gParcer.rl"
    {{( fsm->p) = (( fsm->te))-1;}{
        //parser_out = u_parameter;
        (*prs[eUparam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
        }}
    break;
    case 52:
#line 622 "gParcer.rl"
    {{( fsm->p) = (( fsm->te))-1;}{
        //parser_out = v_parameter;
        (*prs[eVparam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
        }}
    break;
    case 53:
#line 628 "gParcer.rl"
    {{( fsm->p) = (( fsm->te))-1;}{
        //parser_out = w_parameter;
        (*prs[eWparam])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
        }}
    break;
    case 54:
#line 644 "gParcer.rl"
    {{( fsm->p) = (( fsm->te))-1;}{
        //fprintf(flog, "symbol(%i): %c\n", fsm->curline, fsm->ts[0] );
        (*prs[ePunct])(fsm->curline,fsm->ts,1);    }}
    break;
    case 55:
#line 1 "NONE"
    {	switch(  fsm->act ) {
    default:
    {{( fsm->p) = (( fsm->te))-1;}}
    break;
    }
    }
    break;
#line 1218 "gParcer.c"
        }
    }

_again:
    _acts = _gparcer_actions + _gparcer_to_state_actions[( fsm->cs)];
    _nacts = (unsigned int) *_acts++;
    while ( _nacts-- > 0 ) {
        switch ( *_acts++ ) {
    case 1:
#line 1 "NONE"
    { fsm->ts = 0;}
    break;
#line 1231 "gParcer.c"
        }
    }

    if ( ( fsm->cs) == 0 )
        goto _out;
    if ( ++( fsm->p) != ( fsm->pe) )
        goto _resume;
    _test_eof: {}
    if ( ( fsm->p) == ( fsm->eof) )
    {
    if ( _gparcer_eof_trans[( fsm->cs)] > 0 ) {
        _trans = _gparcer_eof_trans[( fsm->cs)] - 1;
        goto _eof_trans;
    }
    }

    _out: {}
    }

#line 701 "gParcer.rl"

        if ( format_finish( fsm ) <= 0 ){
//        printf("[602] FAIL  %c {%X} ==\n", data[0], data[0]);
//           printf("[602] FAIL  :%-10s {%X} ==\n", data, data[30]);
          printf("[602] FAIL ==>> \n");
          for(int i=0;i<20;i++){
              printf("%c {%p}/ ", data[i], &data[i]);
          }
          printf("\n\n");
          printf("[1318]:%p\n",fsm->buf);
        }


}



int scanner(){
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

//        fsm.lenfile = fread( fsm.buf+fsm.have, 1, fsm.space, fp );
        fsm.state = 4;
        return (fsm.state);
case 4:
        fsm.eofile = fsm.lenfile != fsm.space;
printf("gParcer [1339] fsm.eofile:%i \n\n",fsm.eofile);
       format_execute( &fsm, fsm.p, fsm.lenfile, fsm.eofile );
        fsm.state = 1;
         return (fsm.state);

    case 1:
        if(fsm.done)
        {
            fsm.done = 0;
            fsm.lenfile = INPUT_BUFSIZE - (fsm.pe - fsm.buf);
            format_execute( &fsm, fsm.pe, fsm.lenfile, fsm.eofile );
            return (fsm.state);
        }else{
            fsm.state = 3;
        }
    case 3:
//		printf("[646] done:  %i \n", fsm.done);
        if ( fsm.eofile ){
//			fprintf(stderr, " [650] EOF lenfile:%i  space:%i \n", fsm.lenfile , fsm.space);
            return (fsm.state);
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

/*
 * 	static char buf[BUFSIZE];
    int cs, act, have = 0, curline = 1;
    char *ts, *te = 0;
    int done = 0;
*/
void initGparcer()
{
    fsm.buf = buf;
    fsm.state = 0;
    fsm.have = 0;
    fsm.curline = 1;
    fsm.te = 0;
    fsm.done = 0;
    format_init(&fsm);
}
