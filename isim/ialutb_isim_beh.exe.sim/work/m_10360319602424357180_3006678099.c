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
static int ng1[] = {0, 0};
static int ng2[] = {1, 0};
static int ng3[] = {11, 0};
static int ng4[] = {10, 0};
static int ng5[] = {2, 0};
static unsigned int ng6[] = {1U, 0U};



static void Always_208_0(char *t0)
{
    char t6[8];
    char t7[8];
    char t8[8];
    char t28[8];
    char t36[8];
    char t37[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t9;
    char *t10;
    unsigned int t11;
    unsigned int t12;
    unsigned int t13;
    unsigned int t14;
    unsigned int t15;
    char *t16;
    char *t17;
    unsigned int t18;
    unsigned int t19;
    unsigned int t20;
    char *t21;
    unsigned int t22;
    unsigned int t23;
    unsigned int t24;
    unsigned int t25;
    char *t26;
    char *t27;
    char *t29;
    char *t30;
    char *t31;
    char *t32;
    char *t33;
    unsigned int t34;
    int t35;
    char *t38;

LAB0:    t1 = (t0 + 3000U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(208, ng0);
    t2 = (t0 + 3320);
    *((int *)t2) = 1;
    t3 = (t0 + 3032);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(208, ng0);

LAB5:    xsi_set_current_line(209, ng0);
    t4 = ((char*)((ng1)));
    t5 = (t0 + 1928);
    xsi_vlogvar_assign_value(t5, t4, 0, 0, 12);
    xsi_set_current_line(210, ng0);
    t2 = ((char*)((ng1)));
    t3 = (t0 + 2088);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 12);
    xsi_set_current_line(211, ng0);
    t2 = (t0 + 1048U);
    t3 = *((char **)t2);
    t2 = (t0 + 1208U);
    t4 = *((char **)t2);
    memset(t8, 0, 8);
    t2 = (t3 + 4);
    if (*((unsigned int *)t2) != 0)
        goto LAB7;

LAB6:    t5 = (t4 + 4);
    if (*((unsigned int *)t5) != 0)
        goto LAB7;

LAB10:    if (*((unsigned int *)t3) < *((unsigned int *)t4))
        goto LAB9;

LAB8:    *((unsigned int *)t8) = 1;

LAB9:    memset(t7, 0, 8);
    t10 = (t8 + 4);
    t11 = *((unsigned int *)t10);
    t12 = (~(t11));
    t13 = *((unsigned int *)t8);
    t14 = (t13 & t12);
    t15 = (t14 & 1U);
    if (t15 != 0)
        goto LAB11;

LAB12:    if (*((unsigned int *)t10) != 0)
        goto LAB13;

LAB14:    t17 = (t7 + 4);
    t18 = *((unsigned int *)t7);
    t19 = *((unsigned int *)t17);
    t20 = (t18 || t19);
    if (t20 > 0)
        goto LAB15;

LAB16:    t22 = *((unsigned int *)t7);
    t23 = (~(t22));
    t24 = *((unsigned int *)t17);
    t25 = (t23 || t24);
    if (t25 > 0)
        goto LAB17;

LAB18:    if (*((unsigned int *)t17) > 0)
        goto LAB19;

LAB20:    if (*((unsigned int *)t7) > 0)
        goto LAB21;

LAB22:    memcpy(t6, t26, 8);

LAB23:    t27 = (t0 + 1608);
    t29 = (t0 + 1608);
    t30 = (t29 + 72U);
    t31 = *((char **)t30);
    t32 = ((char*)((ng3)));
    xsi_vlog_generic_convert_bit_index(t28, t31, 2, t32, 32, 1);
    t33 = (t28 + 4);
    t34 = *((unsigned int *)t33);
    t35 = (!(t34));
    if (t35 == 1)
        goto LAB24;

LAB25:    xsi_set_current_line(212, ng0);
    t2 = (t0 + 1048U);
    t3 = *((char **)t2);
    t2 = (t0 + 1208U);
    t4 = *((char **)t2);
    memset(t8, 0, 8);
    t2 = (t3 + 4);
    if (*((unsigned int *)t2) != 0)
        goto LAB27;

LAB26:    t5 = (t4 + 4);
    if (*((unsigned int *)t5) != 0)
        goto LAB27;

LAB30:    if (*((unsigned int *)t3) < *((unsigned int *)t4))
        goto LAB29;

LAB28:    *((unsigned int *)t8) = 1;

LAB29:    memset(t7, 0, 8);
    t10 = (t8 + 4);
    t11 = *((unsigned int *)t10);
    t12 = (~(t11));
    t13 = *((unsigned int *)t8);
    t14 = (t13 & t12);
    t15 = (t14 & 1U);
    if (t15 != 0)
        goto LAB31;

LAB32:    if (*((unsigned int *)t10) != 0)
        goto LAB33;

LAB34:    t17 = (t7 + 4);
    t18 = *((unsigned int *)t7);
    t19 = *((unsigned int *)t17);
    t20 = (t18 || t19);
    if (t20 > 0)
        goto LAB35;

LAB36:    t22 = *((unsigned int *)t7);
    t23 = (~(t22));
    t24 = *((unsigned int *)t17);
    t25 = (t23 || t24);
    if (t25 > 0)
        goto LAB37;

LAB38:    if (*((unsigned int *)t17) > 0)
        goto LAB39;

LAB40:    if (*((unsigned int *)t7) > 0)
        goto LAB41;

LAB42:    memcpy(t6, t37, 8);

LAB43:    t31 = (t0 + 2088);
    xsi_vlogvar_assign_value(t31, t6, 0, 0, 12);
    xsi_set_current_line(213, ng0);
    xsi_set_current_line(213, ng0);
    t2 = ((char*)((ng2)));
    t3 = (t0 + 1768);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 32);

LAB44:    t2 = (t0 + 1768);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = ((char*)((ng4)));
    t9 = ((char*)((ng5)));
    memset(t6, 0, 8);
    xsi_vlog_signed_add(t6, 32, t5, 32, t9, 32);
    memset(t7, 0, 8);
    xsi_vlog_signed_less(t7, 32, t4, 32, t6, 32);
    t10 = (t7 + 4);
    t11 = *((unsigned int *)t10);
    t12 = (~(t11));
    t13 = *((unsigned int *)t7);
    t14 = (t13 & t12);
    t15 = (t14 != 0);
    if (t15 > 0)
        goto LAB45;

LAB46:    goto LAB2;

LAB7:    t9 = (t8 + 4);
    *((unsigned int *)t8) = 1;
    *((unsigned int *)t9) = 1;
    goto LAB9;

LAB11:    *((unsigned int *)t7) = 1;
    goto LAB14;

LAB13:    t16 = (t7 + 4);
    *((unsigned int *)t7) = 1;
    *((unsigned int *)t16) = 1;
    goto LAB14;

LAB15:    t21 = ((char*)((ng2)));
    goto LAB16;

LAB17:    t26 = ((char*)((ng1)));
    goto LAB18;

LAB19:    xsi_vlog_unsigned_bit_combine(t6, 32, t21, 32, t26, 32);
    goto LAB23;

LAB21:    memcpy(t6, t21, 8);
    goto LAB23;

LAB24:    xsi_vlogvar_assign_value(t27, t6, 0, *((unsigned int *)t28), 1);
    goto LAB25;

LAB27:    t9 = (t8 + 4);
    *((unsigned int *)t8) = 1;
    *((unsigned int *)t9) = 1;
    goto LAB29;

LAB31:    *((unsigned int *)t7) = 1;
    goto LAB34;

LAB33:    t16 = (t7 + 4);
    *((unsigned int *)t7) = 1;
    *((unsigned int *)t16) = 1;
    goto LAB34;

LAB35:    t21 = (t0 + 1048U);
    t26 = *((char **)t21);
    t21 = (t0 + 1208U);
    t27 = *((char **)t21);
    memset(t28, 0, 8);
    xsi_vlog_unsigned_minus(t28, 12, t26, 11, t27, 11);
    t21 = ((char*)((ng2)));
    memset(t36, 0, 8);
    xsi_vlog_unsigned_lshift(t36, 12, t28, 12, t21, 32);
    goto LAB36;

LAB37:    t29 = (t0 + 1048U);
    t30 = *((char **)t29);
    t29 = ((char*)((ng2)));
    memset(t37, 0, 8);
    xsi_vlog_unsigned_lshift(t37, 12, t30, 11, t29, 32);
    goto LAB38;

LAB39:    xsi_vlog_unsigned_bit_combine(t6, 12, t36, 12, t37, 12);
    goto LAB43;

LAB41:    memcpy(t6, t36, 8);
    goto LAB43;

LAB45:    xsi_set_current_line(213, ng0);

LAB47:    xsi_set_current_line(214, ng0);
    t16 = (t0 + 2088);
    t17 = (t16 + 56U);
    t21 = *((char **)t17);
    t26 = (t0 + 1208U);
    t27 = *((char **)t26);
    t26 = ((char*)((ng6)));
    xsi_vlogtype_concat(t8, 12, 12, 2U, t26, 1, t27, 11);
    memset(t28, 0, 8);
    xsi_vlog_unsigned_minus(t28, 12, t21, 12, t8, 12);
    t29 = (t0 + 1928);
    xsi_vlogvar_assign_value(t29, t28, 0, 0, 12);
    xsi_set_current_line(215, ng0);
    t2 = (t0 + 1928);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    memset(t6, 0, 8);
    t5 = (t6 + 4);
    t9 = (t4 + 4);
    t11 = *((unsigned int *)t4);
    t12 = (t11 >> 11);
    t13 = (t12 & 1);
    *((unsigned int *)t6) = t13;
    t14 = *((unsigned int *)t9);
    t15 = (t14 >> 11);
    t18 = (t15 & 1);
    *((unsigned int *)t5) = t18;
    t10 = (t6 + 4);
    t19 = *((unsigned int *)t10);
    t20 = (~(t19));
    t22 = *((unsigned int *)t6);
    t23 = (t22 & t20);
    t24 = (t23 != 0);
    if (t24 > 0)
        goto LAB48;

LAB49:    xsi_set_current_line(218, ng0);

LAB54:    xsi_set_current_line(219, ng0);
    t2 = ((char*)((ng1)));
    t3 = (t0 + 1608);
    t4 = (t0 + 1608);
    t5 = (t4 + 72U);
    t9 = *((char **)t5);
    t10 = ((char*)((ng4)));
    t16 = ((char*)((ng2)));
    memset(t7, 0, 8);
    xsi_vlog_signed_add(t7, 32, t10, 32, t16, 32);
    t17 = (t0 + 1768);
    t21 = (t17 + 56U);
    t26 = *((char **)t21);
    memset(t8, 0, 8);
    xsi_vlog_signed_minus(t8, 32, t7, 32, t26, 32);
    xsi_vlog_generic_convert_bit_index(t6, t9, 2, t8, 32, 1);
    t27 = (t6 + 4);
    t11 = *((unsigned int *)t27);
    t35 = (!(t11));
    if (t35 == 1)
        goto LAB55;

LAB56:    xsi_set_current_line(220, ng0);
    t2 = (t0 + 2088);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = ((char*)((ng2)));
    memset(t6, 0, 8);
    xsi_vlog_unsigned_lshift(t6, 12, t4, 12, t5, 32);
    t9 = (t0 + 2088);
    xsi_vlogvar_assign_value(t9, t6, 0, 0, 12);

LAB50:    xsi_set_current_line(213, ng0);
    t2 = (t0 + 1768);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = ((char*)((ng2)));
    memset(t6, 0, 8);
    xsi_vlog_signed_add(t6, 32, t4, 32, t5, 32);
    t9 = (t0 + 1768);
    xsi_vlogvar_assign_value(t9, t6, 0, 0, 32);
    goto LAB44;

LAB48:    xsi_set_current_line(215, ng0);

LAB51:    xsi_set_current_line(216, ng0);
    t16 = ((char*)((ng2)));
    t17 = (t0 + 1608);
    t21 = (t0 + 1608);
    t26 = (t21 + 72U);
    t27 = *((char **)t26);
    t29 = ((char*)((ng4)));
    t30 = ((char*)((ng2)));
    memset(t8, 0, 8);
    xsi_vlog_signed_add(t8, 32, t29, 32, t30, 32);
    t31 = (t0 + 1768);
    t32 = (t31 + 56U);
    t33 = *((char **)t32);
    memset(t28, 0, 8);
    xsi_vlog_signed_minus(t28, 32, t8, 32, t33, 32);
    xsi_vlog_generic_convert_bit_index(t7, t27, 2, t28, 32, 1);
    t38 = (t7 + 4);
    t25 = *((unsigned int *)t38);
    t35 = (!(t25));
    if (t35 == 1)
        goto LAB52;

LAB53:    xsi_set_current_line(217, ng0);
    t2 = (t0 + 2088);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t0 + 1208U);
    t9 = *((char **)t5);
    t5 = ((char*)((ng6)));
    xsi_vlogtype_concat(t6, 12, 12, 2U, t5, 1, t9, 11);
    memset(t7, 0, 8);
    xsi_vlog_unsigned_minus(t7, 12, t4, 12, t6, 12);
    t10 = ((char*)((ng2)));
    memset(t8, 0, 8);
    xsi_vlog_unsigned_lshift(t8, 12, t7, 12, t10, 32);
    t16 = (t0 + 2088);
    xsi_vlogvar_assign_value(t16, t8, 0, 0, 12);
    goto LAB50;

LAB52:    xsi_vlogvar_assign_value(t17, t16, 0, *((unsigned int *)t7), 1);
    goto LAB53;

LAB55:    xsi_vlogvar_assign_value(t3, t2, 0, *((unsigned int *)t6), 1);
    goto LAB56;

}


extern void work_m_10360319602424357180_3006678099_init()
{
	static char *pe[] = {(void *)Always_208_0};
	xsi_register_didat("work_m_10360319602424357180_3006678099", "isim/ialutb_isim_beh.exe.sim/work/m_10360319602424357180_3006678099.didat");
	xsi_register_executes(pe);
}
