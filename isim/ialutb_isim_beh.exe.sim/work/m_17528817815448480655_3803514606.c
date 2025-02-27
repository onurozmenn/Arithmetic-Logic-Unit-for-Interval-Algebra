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
static unsigned int ng1[] = {1U, 0U};
static int ng2[] = {1, 0};
static unsigned int ng3[] = {30U, 0U};
static const char *ng4 = "Overflow error rounding";
static unsigned int ng5[] = {0U, 0U};
static unsigned int ng6[] = {4U, 0U};
static unsigned int ng7[] = {5U, 0U};
static int ng8[] = {0, 0};
static unsigned int ng9[] = {6U, 0U};



static void Always_648_0(char *t0)
{
    char t6[8];
    char t18[8];
    char t29[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    unsigned int t7;
    unsigned int t8;
    unsigned int t9;
    unsigned int t10;
    unsigned int t11;
    unsigned int t12;
    unsigned int t13;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    char *t19;
    char *t20;
    char *t21;
    unsigned int t22;
    unsigned int t23;
    unsigned int t24;
    unsigned int t25;
    unsigned int t26;
    unsigned int t27;
    char *t28;
    char *t30;
    unsigned int t31;
    char *t32;
    unsigned int t33;
    unsigned int t34;
    unsigned int t35;
    unsigned int t36;
    unsigned int t37;
    char *t38;
    char *t39;
    char *t40;
    char *t41;
    char *t42;
    int t43;

LAB0:    t1 = (t0 + 4280U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(648, ng0);
    t2 = (t0 + 4600);
    *((int *)t2) = 1;
    t3 = (t0 + 4312);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(648, ng0);

LAB5:    xsi_set_current_line(649, ng0);
    t4 = (t0 + 1208U);
    t5 = *((char **)t4);
    t4 = (t0 + 3208);
    xsi_vlogvar_assign_value(t4, t5, 0, 0, 5);
    xsi_set_current_line(650, ng0);
    t2 = (t0 + 1048U);
    t3 = *((char **)t2);
    memset(t6, 0, 8);
    t2 = (t6 + 4);
    t4 = (t3 + 4);
    t7 = *((unsigned int *)t3);
    t8 = (t7 >> 10);
    *((unsigned int *)t6) = t8;
    t9 = *((unsigned int *)t4);
    t10 = (t9 >> 10);
    *((unsigned int *)t2) = t10;
    t11 = *((unsigned int *)t6);
    *((unsigned int *)t6) = (t11 & 4095U);
    t12 = *((unsigned int *)t2);
    *((unsigned int *)t2) = (t12 & 4095U);
    t5 = (t0 + 2888);
    xsi_vlogvar_assign_value(t5, t6, 0, 0, 12);
    xsi_set_current_line(651, ng0);
    t2 = (t0 + 1048U);
    t3 = *((char **)t2);
    memset(t6, 0, 8);
    t2 = (t6 + 4);
    t4 = (t3 + 4);
    t7 = *((unsigned int *)t3);
    t8 = (t7 >> 2);
    t9 = (t8 & 1);
    *((unsigned int *)t6) = t9;
    t10 = *((unsigned int *)t4);
    t11 = (t10 >> 2);
    t12 = (t11 & 1);
    *((unsigned int *)t2) = t12;
    t5 = (t6 + 4);
    t13 = *((unsigned int *)t5);
    t14 = (~(t13));
    t15 = *((unsigned int *)t6);
    t16 = (t15 & t14);
    t17 = (t16 != 0);
    if (t17 > 0)
        goto LAB6;

LAB7:
LAB8:    xsi_set_current_line(663, ng0);
    t2 = (t0 + 2888);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    memset(t6, 0, 8);
    t5 = (t6 + 4);
    t19 = (t4 + 4);
    t7 = *((unsigned int *)t4);
    t8 = (t7 >> 0);
    *((unsigned int *)t6) = t8;
    t9 = *((unsigned int *)t19);
    t10 = (t9 >> 0);
    *((unsigned int *)t5) = t10;
    t11 = *((unsigned int *)t6);
    *((unsigned int *)t6) = (t11 & 1023U);
    t12 = *((unsigned int *)t5);
    *((unsigned int *)t5) = (t12 & 1023U);
    t20 = (t0 + 3368);
    xsi_vlogvar_assign_value(t20, t6, 0, 0, 10);
    xsi_set_current_line(664, ng0);
    t2 = (t0 + 1528U);
    t3 = *((char **)t2);
    t2 = (t3 + 4);
    t7 = *((unsigned int *)t2);
    t8 = (~(t7));
    t9 = *((unsigned int *)t3);
    t10 = (t9 & t8);
    t11 = (t10 != 0);
    if (t11 > 0)
        goto LAB25;

LAB26:    xsi_set_current_line(666, ng0);

LAB29:    xsi_set_current_line(667, ng0);
    t2 = ((char*)((ng5)));
    t3 = (t0 + 2728);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, 0, 2, 0LL);

LAB27:    xsi_set_current_line(670, ng0);
    t2 = (t0 + 2728);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t0 + 1528U);
    t19 = *((char **)t5);
    xsi_vlogtype_concat(t6, 3, 3, 2U, t19, 1, t4, 2);

LAB30:    t5 = ((char*)((ng6)));
    t43 = xsi_vlog_unsigned_case_compare(t6, 3, t5, 3);
    if (t43 == 1)
        goto LAB31;

LAB32:    t2 = ((char*)((ng7)));
    t43 = xsi_vlog_unsigned_case_compare(t6, 3, t2, 3);
    if (t43 == 1)
        goto LAB33;

LAB34:    t2 = ((char*)((ng9)));
    t43 = xsi_vlog_unsigned_case_compare(t6, 3, t2, 3);
    if (t43 == 1)
        goto LAB35;

LAB36:
LAB38:
LAB37:    xsi_set_current_line(682, ng0);

LAB43:    xsi_set_current_line(683, ng0);
    t2 = (t0 + 3368);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t0 + 3208);
    t19 = (t5 + 56U);
    t20 = *((char **)t19);
    t21 = (t0 + 1368U);
    t28 = *((char **)t21);
    xsi_vlogtype_concat(t18, 16, 16, 3U, t28, 1, t20, 5, t4, 10);
    t21 = (t0 + 2248);
    xsi_vlogvar_assign_value(t21, t18, 0, 0, 16);
    xsi_set_current_line(684, ng0);
    t2 = ((char*)((ng8)));
    t3 = (t0 + 2568);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 16);
    xsi_set_current_line(685, ng0);
    t2 = ((char*)((ng8)));
    t3 = (t0 + 2408);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 16);

LAB39:    goto LAB2;

LAB6:    xsi_set_current_line(651, ng0);

LAB9:    xsi_set_current_line(652, ng0);
    t19 = (t0 + 1048U);
    t20 = *((char **)t19);
    memset(t18, 0, 8);
    t19 = (t18 + 4);
    t21 = (t20 + 4);
    t22 = *((unsigned int *)t20);
    t23 = (t22 >> 9);
    *((unsigned int *)t18) = t23;
    t24 = *((unsigned int *)t21);
    t25 = (t24 >> 9);
    *((unsigned int *)t19) = t25;
    t26 = *((unsigned int *)t18);
    *((unsigned int *)t18) = (t26 & 8191U);
    t27 = *((unsigned int *)t19);
    *((unsigned int *)t19) = (t27 & 8191U);
    t28 = ((char*)((ng1)));
    memset(t29, 0, 8);
    xsi_vlog_unsigned_add(t29, 13, t18, 13, t28, 13);
    t30 = (t0 + 2888);
    xsi_vlogvar_assign_value(t30, t29, 0, 0, 12);
    xsi_set_current_line(654, ng0);
    t2 = (t0 + 2888);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    memset(t6, 0, 8);
    t5 = (t6 + 4);
    t19 = (t4 + 4);
    t7 = *((unsigned int *)t4);
    t8 = (t7 >> 11);
    t9 = (t8 & 1);
    *((unsigned int *)t6) = t9;
    t10 = *((unsigned int *)t19);
    t11 = (t10 >> 11);
    t12 = (t11 & 1);
    *((unsigned int *)t5) = t12;
    t20 = ((char*)((ng1)));
    memset(t18, 0, 8);
    t21 = (t6 + 4);
    t28 = (t20 + 4);
    t13 = *((unsigned int *)t6);
    t14 = *((unsigned int *)t20);
    t15 = (t13 ^ t14);
    t16 = *((unsigned int *)t21);
    t17 = *((unsigned int *)t28);
    t22 = (t16 ^ t17);
    t23 = (t15 | t22);
    t24 = *((unsigned int *)t21);
    t25 = *((unsigned int *)t28);
    t26 = (t24 | t25);
    t27 = (~(t26));
    t31 = (t23 & t27);
    if (t31 != 0)
        goto LAB13;

LAB10:    if (t26 != 0)
        goto LAB12;

LAB11:    *((unsigned int *)t18) = 1;

LAB13:    t32 = (t18 + 4);
    t33 = *((unsigned int *)t32);
    t34 = (~(t33));
    t35 = *((unsigned int *)t18);
    t36 = (t35 & t34);
    t37 = (t36 != 0);
    if (t37 > 0)
        goto LAB14;

LAB15:
LAB16:    goto LAB8;

LAB12:    t30 = (t18 + 4);
    *((unsigned int *)t18) = 1;
    *((unsigned int *)t30) = 1;
    goto LAB13;

LAB14:    xsi_set_current_line(655, ng0);

LAB17:    xsi_set_current_line(656, ng0);
    t38 = (t0 + 2888);
    t39 = (t38 + 56U);
    t40 = *((char **)t39);
    t41 = ((char*)((ng2)));
    memset(t29, 0, 8);
    xsi_vlog_unsigned_rshift(t29, 12, t40, 12, t41, 32);
    t42 = (t0 + 2888);
    xsi_vlogvar_assign_value(t42, t29, 0, 0, 12);
    xsi_set_current_line(657, ng0);
    t2 = (t0 + 1208U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng1)));
    memset(t6, 0, 8);
    xsi_vlog_unsigned_add(t6, 5, t3, 5, t2, 5);
    t4 = (t0 + 3208);
    xsi_vlogvar_assign_value(t4, t6, 0, 0, 5);
    xsi_set_current_line(658, ng0);
    t2 = (t0 + 1208U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng3)));
    memset(t6, 0, 8);
    t4 = (t3 + 4);
    t5 = (t2 + 4);
    t7 = *((unsigned int *)t3);
    t8 = *((unsigned int *)t2);
    t9 = (t7 ^ t8);
    t10 = *((unsigned int *)t4);
    t11 = *((unsigned int *)t5);
    t12 = (t10 ^ t11);
    t13 = (t9 | t12);
    t14 = *((unsigned int *)t4);
    t15 = *((unsigned int *)t5);
    t16 = (t14 | t15);
    t17 = (~(t16));
    t22 = (t13 & t17);
    if (t22 != 0)
        goto LAB21;

LAB18:    if (t16 != 0)
        goto LAB20;

LAB19:    *((unsigned int *)t6) = 1;

LAB21:    t20 = (t6 + 4);
    t23 = *((unsigned int *)t20);
    t24 = (~(t23));
    t25 = *((unsigned int *)t6);
    t26 = (t25 & t24);
    t27 = (t26 != 0);
    if (t27 > 0)
        goto LAB22;

LAB23:
LAB24:    xsi_set_current_line(660, ng0);
    xsi_vlogfile_write(1, 0, 0, ng4, 1, t0);
    goto LAB16;

LAB20:    t19 = (t6 + 4);
    *((unsigned int *)t6) = 1;
    *((unsigned int *)t19) = 1;
    goto LAB21;

LAB22:    xsi_set_current_line(659, ng0);
    t21 = (t0 + 1368U);
    t28 = *((char **)t21);
    t21 = ((char*)((ng1)));
    xsi_vlogtype_concat(t18, 3, 3, 2U, t21, 2, t28, 1);
    t30 = (t0 + 3048);
    xsi_vlogvar_assign_value(t30, t18, 0, 0, 3);
    goto LAB24;

LAB25:    xsi_set_current_line(664, ng0);

LAB28:    xsi_set_current_line(665, ng0);
    t4 = (t0 + 1688U);
    t5 = *((char **)t4);
    t4 = (t0 + 2728);
    xsi_vlogvar_wait_assign_value(t4, t5, 0, 0, 2, 0LL);
    goto LAB27;

LAB31:    xsi_set_current_line(671, ng0);

LAB40:    xsi_set_current_line(672, ng0);
    t20 = (t0 + 3368);
    t21 = (t20 + 56U);
    t28 = *((char **)t21);
    t30 = (t0 + 3208);
    t32 = (t30 + 56U);
    t38 = *((char **)t32);
    t39 = (t0 + 1368U);
    t40 = *((char **)t39);
    xsi_vlogtype_concat(t18, 16, 16, 3U, t40, 1, t38, 5, t28, 10);
    t39 = (t0 + 2408);
    xsi_vlogvar_assign_value(t39, t18, 0, 0, 16);
    goto LAB39;

LAB33:    xsi_set_current_line(675, ng0);

LAB41:    xsi_set_current_line(676, ng0);
    t3 = (t0 + 3368);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t19 = (t0 + 3208);
    t20 = (t19 + 56U);
    t21 = *((char **)t20);
    t28 = (t0 + 1368U);
    t30 = *((char **)t28);
    xsi_vlogtype_concat(t18, 16, 16, 3U, t30, 1, t21, 5, t5, 10);
    t28 = (t0 + 2568);
    xsi_vlogvar_assign_value(t28, t18, 0, 0, 16);
    xsi_set_current_line(677, ng0);
    t2 = ((char*)((ng8)));
    t3 = (t0 + 2248);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 16);
    goto LAB39;

LAB35:    xsi_set_current_line(679, ng0);

LAB42:    xsi_set_current_line(680, ng0);
    t3 = ((char*)((ng8)));
    t4 = (t0 + 2248);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB39;

}


extern void work_m_17528817815448480655_3803514606_init()
{
	static char *pe[] = {(void *)Always_648_0};
	xsi_register_didat("work_m_17528817815448480655_3803514606", "isim/ialutb_isim_beh.exe.sim/work/m_17528817815448480655_3803514606.didat");
	xsi_register_executes(pe);
}
