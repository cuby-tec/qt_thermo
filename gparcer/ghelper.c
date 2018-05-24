#include "ghelper.h"
#include <string.h>


//--------------------- vars

struct sGcode sgcode;

//----------------------- function


struct sGcode* getSgcode()
{
    return &sgcode;
}


// Очистка полей для новыъх данных
void clear_sgcode()
{
    struct sGparam* param;

    memset(sgcode.comment,0,sizeof(sgcode.comment));
    sgcode.group = ' ';
    sgcode.line = 0;

    //sgcode.value = 0;
    memset(sgcode.value,0,sizeof(sgcode.value));

    for(int i=0;i<sizeof(sgcode.param);i++)
    {
        param = &sgcode.param[i];
        param->group = ' ';
        //param->value
        memset(param->value,0,sizeof(param->value));
    }

}


void b_command (size_t curline, char * param, size_t len)
{

}

void b_gcomment (size_t curline, char * param, size_t len)
{

}

void b_g_command (size_t curline, char * param, size_t len)
{

}

void b_x_coordinate(size_t curline, char * param, size_t len)
{

}

void b_y_coordinate(size_t curline, char * param, size_t len)
{

}

void b_z_coordinate(size_t curline, char * param, size_t len)
{

}

void b_a_parameter(size_t curline, char * param, size_t len)
{

}

void b_b_parameter(size_t curline, char * param, size_t len)
{

}

void b_c_parameter(size_t curline, char * param, size_t len)
{

}
void b_d_parameter(size_t curline, char * param, size_t len)
{

}

void b_e_parameter(size_t curline, char * param, size_t len)
{
}

void b_f_parameter(size_t curline, char * param, size_t len)
{
}

void b_i_parameter(size_t curline, char * param, size_t len)
{
}

void b_j_parameter(size_t curline, char * param, size_t len)
{
}

void b_k_parameter(size_t curline, char * param, size_t len)
{
}

void b_l_parameter(size_t curline, char * param, size_t len)
{
}

void b_m_parameter(size_t curline, char * param, size_t len)
{
}

void b_n_parameter(size_t curline, char * param, size_t len)
{
}

void b_p_parameter(size_t curline, char * param, size_t len)
{
}

void b_r_parameter(size_t curline, char * param, size_t len)
{
}

void b_s_parameter(size_t curline, char * param, size_t len)
{
}

void b_t_parameter(size_t curline, char * param, size_t len)
{

}

void b_u_parameter(size_t curline, char * param, size_t len)
{
}

void b_v_parameter(size_t curline, char * param, size_t len)
{

}

void b_w_parameter(size_t curline, char * param, size_t len)
{

}

void b_star_parameter(size_t curline, char * param, size_t len)
{
}



