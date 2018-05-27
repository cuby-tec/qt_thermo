#include "ghelper.h"
#include <string.h>


//--------------------- vars

struct sGcode sgcode;

//----------------------- function


struct sGcode* getSgcode()
{
    return &sgcode;
}

void ghelper_setParam(struct sGparam *pr, char * param, size_t len)
{
//    struct sGparam *pr =  &sgcode.param[sgcode.param_number];
    pr->group = param[0];
    strncpy(pr->value,param+1,(len<10)?len-1:9);
    pr->value[(len<10)?len-1:9] = '\0';
}

// Очистка полей для новыъх данных
void clear_sgcode()
{
    struct sGparam* param;

    memset(sgcode.comment,0,sizeof(sgcode.comment));
    sgcode.group = ' ';
    sgcode.line = 0;
    sgcode.param_number = 0;

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

// It's an End of build command.
void b_command (size_t curline, char * param, size_t len)
{
    sgcode.line = curline;
}

void b_gcomment (size_t curline, char * param, size_t len)
{
//sgcode.comment
    memcpy(sgcode.comment, param, (len<79)?len:79);
}

void b_g_command (size_t curline, char * param, size_t len)
{
//    char buf;
//     'G':
        sgcode.group = param[0];
        strncpy(sgcode.value,&param[1],(len<10)?len-1:9);
        sgcode.value[len-1] = '\0';

}

void b_x_coordinate(size_t curline, char * param, size_t len)
{
    struct sGparam *pr =  &sgcode.param[sgcode.param_number];
//    pr->group = param[0];
//    strncpy(pr->value,param+1,(len<10)?len-1:9);
//    pr->value[(len<10)?len-1:9] = '\0';
    ghelper_setParam(pr,param,len);
    sgcode.param_number++;
}

void b_y_coordinate(size_t curline, char * param, size_t len)
{
    struct sGparam *pr =  &sgcode.param[sgcode.param_number];
//    pr->group = param[0];
//    strncpy(pr->value,param+1,(len<10)?len-1:9);
//    pr->value[(len<10)?len-1:9] = '\0';
    ghelper_setParam(pr,param,len);
    sgcode.param_number++;
}

void b_z_coordinate(size_t curline, char * param, size_t len)
{
    struct sGparam *pr =  &sgcode.param[sgcode.param_number];
//    pr->group = param[0];
//    strncpy(pr->value,param+1,(len<10)?len-1:9);
//    pr->value[(len<10)?len-1:9] = '\0';
    ghelper_setParam(pr,param,len);
    sgcode.param_number++;
}

void b_a_parameter(size_t curline, char * param, size_t len)
{
    struct sGparam *pr =  &sgcode.param[sgcode.param_number];
    ghelper_setParam(pr,param,len);
    sgcode.param_number++;
}

void b_b_parameter(size_t curline, char * param, size_t len)
{
    struct sGparam *pr =  &sgcode.param[sgcode.param_number];
    ghelper_setParam(pr,param,len);
    sgcode.param_number++;
}

void b_c_parameter(size_t curline, char * param, size_t len)
{
    struct sGparam *pr =  &sgcode.param[sgcode.param_number];
    ghelper_setParam(pr,param,len);
    sgcode.param_number++;
}
void b_d_parameter(size_t curline, char * param, size_t len)
{
    struct sGparam *pr =  &sgcode.param[sgcode.param_number];
    ghelper_setParam(pr,param,len);
    sgcode.param_number++;
}

void b_e_parameter(size_t curline, char * param, size_t len)
{
    struct sGparam *pr =  &sgcode.param[sgcode.param_number];
    ghelper_setParam(pr,param,len);
    sgcode.param_number++;
}

void b_f_parameter(size_t curline, char * param, size_t len)
{
    struct sGparam *pr =  &sgcode.param[sgcode.param_number];
    ghelper_setParam(pr,param,len);
    sgcode.param_number++;
}

void b_i_parameter(size_t curline, char * param, size_t len)
{
    struct sGparam *pr =  &sgcode.param[sgcode.param_number];
    ghelper_setParam(pr,param,len);
    sgcode.param_number++;
}

void b_j_parameter(size_t curline, char * param, size_t len)
{
    struct sGparam *pr =  &sgcode.param[sgcode.param_number];
    ghelper_setParam(pr,param,len);
    sgcode.param_number++;
}

void b_k_parameter(size_t curline, char * param, size_t len)
{
    struct sGparam *pr =  &sgcode.param[sgcode.param_number];
    ghelper_setParam(pr,param,len);
    sgcode.param_number++;
}

void b_l_parameter(size_t curline, char * param, size_t len)
{
    struct sGparam *pr =  &sgcode.param[sgcode.param_number];
    ghelper_setParam(pr,param,len);
    sgcode.param_number++;
}
// Command M
void b_m_parameter(size_t curline, char * param, size_t len)
{
    //     'M': Command
            sgcode.group = param[0];
            strncpy(sgcode.value,&param[1],(len<10)?len-1:9);
            sgcode.value[len-1] = '\0';

}

void b_n_parameter(size_t curline, char * param, size_t len)
{
    struct sGparam *pr =  &sgcode.param[sgcode.param_number];
    ghelper_setParam(pr,param,len);
    sgcode.param_number++;
}

void b_p_parameter(size_t curline, char * param, size_t len)
{
    struct sGparam *pr =  &sgcode.param[sgcode.param_number];
    ghelper_setParam(pr,param,len);
    sgcode.param_number++;

}

void b_r_parameter(size_t curline, char * param, size_t len)
{
    struct sGparam *pr =  &sgcode.param[sgcode.param_number];
    ghelper_setParam(pr,param,len);
    sgcode.param_number++;

}

void b_s_parameter(size_t curline, char * param, size_t len)
{
    struct sGparam *pr =  &sgcode.param[sgcode.param_number];
    ghelper_setParam(pr,param,len);
    sgcode.param_number++;
}

void b_t_parameter(size_t curline, char * param, size_t len)
{
    struct sGparam *pr =  &sgcode.param[sgcode.param_number];
    ghelper_setParam(pr,param,len);
    sgcode.param_number++;
}

void b_u_parameter(size_t curline, char * param, size_t len)
{
    struct sGparam *pr =  &sgcode.param[sgcode.param_number];
    ghelper_setParam(pr,param,len);
    sgcode.param_number++;
}

void b_v_parameter(size_t curline, char * param, size_t len)
{
    struct sGparam *pr =  &sgcode.param[sgcode.param_number];
    ghelper_setParam(pr,param,len);
    sgcode.param_number++;
}

void b_w_parameter(size_t curline, char * param, size_t len)
{
    struct sGparam *pr =  &sgcode.param[sgcode.param_number];
    ghelper_setParam(pr,param,len);
    sgcode.param_number++;
}

void b_star_parameter(size_t curline, char * param, size_t len)
{
    struct sGparam *pr =  &sgcode.param[sgcode.param_number];
    ghelper_setParam(pr,param,len);
    sgcode.param_number++;
}

void b_punct(size_t curline, char* param, size_t len)
{
    struct sGparam *pr =  &sgcode.param[sgcode.param_number];
    ghelper_setParam(pr,param,len);
    sgcode.param_number++;
}

