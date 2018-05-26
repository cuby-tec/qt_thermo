#ifndef GHELPER_H
#define GHELPER_H




#ifdef __cplusplus
   extern "C" {
#endif
//--------------------defs
#define SCANNER

#include "sgcode.h"


//#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

//---------------- var

extern struct sGcode sgcode;

//--------------- function

#ifdef SCANNER
extern void clear_sgcode();

extern struct sGcode* getSgcode();

extern void b_command (size_t curline, char * param, size_t len);
extern void b_gcomment (size_t curline, char * param, size_t len);
extern void b_g_command (size_t curline, char * param, size_t len);
extern void b_x_coordinate(size_t curline, char * param, size_t len);
extern void b_y_coordinate(size_t curline, char * param, size_t len);
extern void b_z_coordinate(size_t curline, char * param, size_t len);
extern void b_a_parameter(size_t curline, char * param, size_t len);
extern void b_b_parameter(size_t curline, char * param, size_t len);
extern void b_c_parameter(size_t curline, char * param, size_t len);
extern void b_d_parameter(size_t curline, char * param, size_t len);
extern void b_e_parameter(size_t curline, char * param, size_t len);
extern void b_f_parameter(size_t curline, char * param, size_t len);
extern void b_i_parameter(size_t curline, char * param, size_t len);
extern void b_j_parameter(size_t curline, char * param, size_t len);
extern void b_k_parameter(size_t curline, char * param, size_t len);
extern void b_l_parameter(size_t curline, char * param, size_t len);
extern void b_m_parameter(size_t curline, char * param, size_t len);
extern void b_n_parameter(size_t curline, char * param, size_t len);
extern void b_p_parameter(size_t curline, char * param, size_t len);
extern void b_r_parameter(size_t curline, char * param, size_t len);
extern void b_s_parameter(size_t curline, char * param, size_t len);
extern void b_t_parameter(size_t curline, char * param, size_t len);
extern void b_u_parameter(size_t curline, char * param, size_t len);
extern void b_v_parameter(size_t curline, char * param, size_t len);
extern void b_w_parameter(size_t curline, char * param, size_t len);
extern void b_star_parameter(size_t curline, char * param, size_t len);
extern void b_punct(size_t curline, char* param, size_t len);
#endif
#ifdef __cplusplus
   }
#endif


#endif // GHELPER_H
