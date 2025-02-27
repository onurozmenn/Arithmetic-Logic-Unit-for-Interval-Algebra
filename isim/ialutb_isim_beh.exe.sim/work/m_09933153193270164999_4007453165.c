/**********************************************************************/
/*   ____  ____                                                       */
/*  /   /\/   /                                                       */
/* /___/  \  /                                                        */
/* \   \   \/                                                       */
/*  \   \        Copyright (c) 2003-2009 Xilinx, Inc.                */
/*  /   /          All Right Reserved.                                 */
/* /---/   /\                                                         */
/* \   \  /  \                                                      */
/*  \___\/\___\                                                    */
/***********************************************************************/

/* This file is designed for use with ISim build 0xfbc00daa */

#define XSI_HIDE_SYMBOL_SPEC true
#include "xsi.h"
#include <memory.h>
#ifdef __GNUC__
#include <stdlib.h>
#else
#include <malloc.h>
#define alloca _alloca
#endif
static const char *ng0 = "/home/onur/Desktop/Neorv/IALU.v";
static int ng1[] = {21, 0};
static int ng2[] = {0, 0};
static int ng3[] = {1, 0};
static unsigned int ng4[] = {1U, 0U};
static unsigned int ng5[] = {30U, 0U};
static const char *ng6 = "Overflow error normalize";
static unsigned int ng7[] = {0U, 0U};
static unsigned int ng8[] = {2U, 0U};
static unsigned int ng9[] = {3U, 0U};



static void Always_604_0(char *t0)
{
    char t6[8];
    char t14[8];
    char t32[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t7;
    char *t8;
    char *t9;
    char *t10;
    int t11;
    char *t12;
    char *t13;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    unsigned int t20;
    unsigned int t21;
    unsigned int t22;
    unsigned int t23;
    unsigned int t24;
    unsigned int t25;
    unsigned int t26;
    unsigned int t27;
    unsigned int t28;
    unsigned int t29;
    unsigned int t30;
    unsigned int t31;
    char *t33;

LAB0:    t1 = (t0 + 3640U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(604, ng0);
    t2 = (t0 + 3960);
    *((int *)t2) = 1;
    t3 = (t0 + 3672);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(604, ng0);

LAB5:    xsi_set_current_line(605, ng0);
    t4 = (t0 + 1048U);
    t5 = *((char **)t4);
    t4 = (t0 + 1008U);
    t7 = (t4 + 72U);
    t8 = *((char **)t7);
    t9 = ((char*)((ng1)));
    xsi_vlog_generic_get_index_select_value(t6, 32, t5, t8, 2, t9, 32, 1);

LAB6:    t10 = ((char*)((ng2)));
    t11 = xsi_vlog_unsigned_case_compare(t6, 32, t10, 32);
    if (t11 == 1)
        goto LAB7;

LAB8:    t2 = ((char*)((ng3)));
    t11 = xsi_vlog_unsigned_case_compare(t6, 32, t2, 32);
    if (t11 == 1)
        goto LAB9;

LAB10:
LAB11:    xsi_set_current_line(618, ng0);
    t2 = (t0 + 1528U);
    t3 = *((char **)t2);
    t2 = (t3 + 4);
    t15 = *((unsigned int *)t2);
    t16 = (~(t15));
    t17 = *((unsigned int *)t3);
    t18 = (t17 & t16);
    t19 = (t18 != 0);
    if (t19 > 0)
        goto LAB21;

LAB22:    xsi_set_current_line(625, ng0);

LAB48:    xsi_set_current_line(626, ng0);
    t2 = ((char*)((ng7)));
    t3 = (t0 + 2568);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, 0, 2, 0LL);

LAB23:    goto LAB2;

LAB7:    xsi_set_current_line(606, ng0);

LAB12:    xsi_set_current_line(607, ng0);
    t12 = (t0 + 1048U);
    t13 = *((char **)t12);
    t12 = (t0 + 2248);
    xsi_vlogvar_assign_value(t12, t13, 0, 0, 22);
    xsi_set_current_line(608, ng0);
    t2 = (t0 + 1208U);
    t3 = *((char **)t2);
    t2 = (t0 + 2408);
    xsi_vlogvar_assign_value(t2, t3, 0, 0, 5);
    goto LAB11;

LAB9:    xsi_set_current_line(610, ng0);

LAB13:    xsi_set_current_line(611, ng0);
    t3 = (t0 + 1048U);
    t4 = *((char **)t3);
    t3 = ((char*)((ng3)));
    memset(t14, 0, 8);
    xsi_vlog_unsigned_rshift(t14, 22, t4, 22, t3, 32);
    t5 = (t0 + 2248);
    xsi_vlogvar_assign_value(t5, t14, 0, 0, 22);
    xsi_set_current_line(612, ng0);
    t2 = (t0 + 1208U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng4)));
    memset(t14, 0, 8);
    xsi_vlog_unsigned_add(t14, 5, t3, 5, t2, 5);
    t4 = (t0 + 2408);
    xsi_vlogvar_assign_value(t4, t14, 0, 0, 5);
    xsi_set_current_line(613, ng0);
    t2 = (t0 + 1208U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng5)));
    memset(t14, 0, 8);
    t4 = (t3 + 4);
    t5 = (t2 + 4);
    t15 = *((unsigned int *)t3);
    t16 = *((unsigned int *)t2);
    t17 = (t15 ^ t16);
    t18 = *((unsigned int *)t4);
    t19 = *((unsigned int *)t5);
    t20 = (t18 ^ t19);
    t21 = (t17 | t20);
    t22 = *((unsigned int *)t4);
    t23 = *((unsigned int *)t5);
    t24 = (t22 | t23);
    t25 = (~(t24));
    t26 = (t21 & t25);
    if (t26 != 0)
        goto LAB17;

LAB14:    if (t24 != 0)
        goto LAB16;

LAB15:    *((unsigned int *)t14) = 1;

LAB17:    t8 = (t14 + 4);
    t27 = *((unsigned int *)t8);
    t28 = (~(t27));
    t29 = *((unsigned int *)t14);
    t30 = (t29 & t28);
    t31 = (t30 != 0);
    if (t31 > 0)
        goto LAB18;

LAB19:
LAB20:    xsi_set_current_line(615, ng0);
    xsi_vlogfile_write(1, 0, 0, ng6, 1, t0);
    goto LAB11;

LAB16:    t7 = (t14 + 4);
    *((unsigned int *)t14) = 1;
    *((unsigned int *)t7) = 1;
    goto LAB17;

LAB18:    xsi_set_current_line(614, ng0);
    t9 = (t0 + 1368U);
    t10 = *((char **)t9);
    t9 = ((char*)((ng4)));
    xsi_vlogtype_concat(t32, 3, 3, 2U, t9, 2, t10, 1);
    t12 = (t0 + 2728);
    xsi_vlogvar_assign_value(t12, t32, 0, 0, 3);
    goto LAB20;

LAB21:    xsi_set_current_line(618, ng0);

LAB24:    xsi_set_current_line(619, ng0);
    t4 = (t0 + 1688U);
    t5 = *((char **)t4);

LAB25:    t4 = ((char*)((ng7)));
    t11 = xsi_vlog_unsigned_case_compare(t5, 2, t4, 2);
    if (t11 == 1)
        goto LAB26;

LAB27:    t2 = ((char*)((ng4)));
    t11 = xsi_vlog_unsigned_case_compare(t5, 2, t2, 2);
    if (t11 == 1)
        goto LAB28;

LAB29:    t2 = ((char*)((ng8)));
    t11 = xsi_vlog_unsigned_case_compare(t5, 2, t2, 2);
    if (t11 == 1)
        goto LAB30;

LAB31:    t2 = ((char*)((ng9)));
    t11 = xsi_vlog_unsigned_case_compare(t5, 2, t2, 2);
    if (t11 == 1)
        goto LAB32;

LAB33:
LAB34:    goto LAB23;

LAB26:    xsi_set_current_line(620, ng0);
    t7 = ((char*)((ng4)));
    t8 = (t0 + 2568);
    xsi_vlogvar_wait_assign_value(t8, t7, 0, 0, 2, 0LL);
    goto LAB34;

LAB28:    xsi_set_current_line(621, ng0);
    t3 = ((char*)((ng8)));
    t4 = (t0 + 2568);
    xsi_vlogvar_wait_assign_value(t4, t3, 0, 0, 2, 0LL);
    goto LAB34;

LAB30:    xsi_set_current_line(622, ng0);
    t3 = (t0 + 1848U);
    t4 = *((char **)t3);
    memset(t32, 0, 8);
    t3 = (t4 + 4);
    t15 = *((unsigned int *)t3);
    t16 = (~(t15));
    t17 = *((unsigned int *)t4);
    t18 = (t17 & t16);
    t19 = (t18 & 1U);
    if (t19 != 0)
        goto LAB35;

LAB36:    if (*((unsigned int *)t3) != 0)
        goto LAB37;

LAB38:    t8 = (t32 + 4);
    t20 = *((unsigned int *)t32);
    t21 = *((unsigned int *)t8);
    t22 = (t20 || t21);
    if (t22 > 0)
        goto LAB39;

LAB40:    t23 = *((unsigned int *)t32);
    t24 = (~(t23));
    t25 = *((unsigned int *)t8);
    t26 = (t24 || t25);
    if (t26 > 0)
        goto LAB41;

LAB42:    if (*((unsigned int *)t8) > 0)
        goto LAB43;

LAB44:    if (*((unsigned int *)t32) > 0)
        goto LAB45;

LAB46:    memcpy(t14, t13, 8);

LAB47:    t33 = (t0 + 2568);
    xsi_vlogvar_wait_assign_value(t33, t14, 0, 0, 2, 0LL);
    goto LAB34;

LAB32:    xsi_set_current_line(623, ng0);
    t3 = ((char*)((ng7)));
    t4 = (t0 + 2568);
    xsi_vlogvar_wait_assign_value(t4, t3, 0, 0, 2, 0LL);
    goto LAB34;

LAB35:    *((unsigned int *)t32) = 1;
    goto LAB38;

LAB37:    t7 = (t32 + 4);
    *((unsigned int *)t32) = 1;
    *((unsigned int *)t7) = 1;
    goto LAB38;

LAB39:    t9 = ((char*)((ng7)));
    goto LAB40;

LAB41:    t10 = (t0 + 2568);
    t12 = (t10 + 56U);
    t13 = *((char **)t12);
    goto LAB42;

LAB43:    xsi_vlog_unsigned_bit_combine(t14, 2, t9, 2, t13, 2);
    goto LAB47;

LAB45:    memcpy(t14, t9, 8);
    goto LAB47;

}


extern void work_m_09933153193270164999_4007453165_init()
{
	static char *pe[] = {(void *)Always_604_0};
	xsi_register_didat("work_m_09933153193270164999_4007453165", "isim/ialutb_isim_beh.exe.sim/work/m_09933153193270164999_4007453165.didat");
	xsi_register_executes(pe);
}
