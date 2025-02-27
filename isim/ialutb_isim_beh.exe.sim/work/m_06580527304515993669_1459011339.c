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
static unsigned int ng1[] = {2U, 0U};
static unsigned int ng2[] = {0U, 0U};
static unsigned int ng3[] = {0U, 1U};
static unsigned int ng4[] = {4U, 0U};
static int ng5[] = {0, 0};
static unsigned int ng6[] = {5U, 0U};
static unsigned int ng7[] = {6U, 0U};
static unsigned int ng8[] = {1U, 0U};
static unsigned int ng9[] = {0U, 65535U};
static int ng10[] = {16, 0};
static int ng11[] = {1, 0};



static void Always_527_0(char *t0)
{
    char t4[8];
    char t5[8];
    char t8[8];
    char t43[8];
    char t47[8];
    char t55[8];
    char *t1;
    char *t2;
    char *t3;
    char *t6;
    char *t7;
    char *t9;
    char *t10;
    unsigned int t11;
    unsigned int t12;
    unsigned int t13;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    unsigned int t20;
    unsigned int t21;
    unsigned int t22;
    char *t23;
    char *t24;
    unsigned int t25;
    unsigned int t26;
    unsigned int t27;
    unsigned int t28;
    unsigned int t29;
    char *t30;
    char *t31;
    unsigned int t32;
    unsigned int t33;
    unsigned int t34;
    char *t35;
    unsigned int t36;
    unsigned int t37;
    unsigned int t38;
    unsigned int t39;
    char *t40;
    char *t41;
    int t42;
    char *t44;
    char *t45;
    char *t46;
    unsigned int t48;
    unsigned int t49;
    unsigned int t50;
    unsigned int t51;
    unsigned int t52;
    unsigned int t53;
    unsigned int t54;
    unsigned int t56;
    unsigned int t57;
    unsigned int t58;
    unsigned int t59;
    unsigned int t60;
    unsigned int t61;

LAB0:    t1 = (t0 + 7936U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(527, ng0);
    t2 = (t0 + 10240);
    *((int *)t2) = 1;
    t3 = (t0 + 7968);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(527, ng0);

LAB5:    xsi_set_current_line(529, ng0);
    t6 = (t0 + 1984U);
    t7 = *((char **)t6);
    t6 = ((char*)((ng1)));
    memset(t8, 0, 8);
    t9 = (t7 + 4);
    t10 = (t6 + 4);
    t11 = *((unsigned int *)t7);
    t12 = *((unsigned int *)t6);
    t13 = (t11 ^ t12);
    t14 = *((unsigned int *)t9);
    t15 = *((unsigned int *)t10);
    t16 = (t14 ^ t15);
    t17 = (t13 | t16);
    t18 = *((unsigned int *)t9);
    t19 = *((unsigned int *)t10);
    t20 = (t18 | t19);
    t21 = (~(t20));
    t22 = (t17 & t21);
    if (t22 != 0)
        goto LAB9;

LAB6:    if (t20 != 0)
        goto LAB8;

LAB7:    *((unsigned int *)t8) = 1;

LAB9:    memset(t5, 0, 8);
    t24 = (t8 + 4);
    t25 = *((unsigned int *)t24);
    t26 = (~(t25));
    t27 = *((unsigned int *)t8);
    t28 = (t27 & t26);
    t29 = (t28 & 1U);
    if (t29 != 0)
        goto LAB10;

LAB11:    if (*((unsigned int *)t24) != 0)
        goto LAB12;

LAB13:    t31 = (t5 + 4);
    t32 = *((unsigned int *)t5);
    t33 = *((unsigned int *)t31);
    t34 = (t32 || t33);
    if (t34 > 0)
        goto LAB14;

LAB15:    t36 = *((unsigned int *)t5);
    t37 = (~(t36));
    t38 = *((unsigned int *)t31);
    t39 = (t37 || t38);
    if (t39 > 0)
        goto LAB16;

LAB17:    if (*((unsigned int *)t31) > 0)
        goto LAB18;

LAB19:    if (*((unsigned int *)t5) > 0)
        goto LAB20;

LAB21:    memcpy(t4, t40, 8);

LAB22:    t41 = (t0 + 5424);
    xsi_vlogvar_wait_assign_value(t41, t4, 0, 0, 1, 0LL);
    xsi_set_current_line(531, ng0);
    t2 = (t0 + 6544);
    t3 = (t2 + 56U);
    t6 = *((char **)t3);
    t7 = (t0 + 2144U);
    t9 = *((char **)t7);
    xsi_vlogtype_concat(t4, 3, 3, 2U, t9, 1, t6, 2);

LAB23:    t7 = ((char*)((ng4)));
    t42 = xsi_vlog_unsigned_case_compare(t4, 3, t7, 3);
    if (t42 == 1)
        goto LAB24;

LAB25:    t2 = ((char*)((ng6)));
    t42 = xsi_vlog_unsigned_case_compare(t4, 3, t2, 3);
    if (t42 == 1)
        goto LAB26;

LAB27:    t2 = ((char*)((ng7)));
    t42 = xsi_vlog_unsigned_case_compare(t4, 3, t2, 3);
    if (t42 == 1)
        goto LAB28;

LAB29:
LAB31:
LAB30:    xsi_set_current_line(554, ng0);

LAB214:    xsi_set_current_line(555, ng0);
    t2 = (t0 + 1344U);
    t3 = *((char **)t2);
    memset(t5, 0, 8);
    t2 = (t5 + 4);
    t6 = (t3 + 4);
    t11 = *((unsigned int *)t3);
    t12 = (t11 >> 15);
    t13 = (t12 & 1);
    *((unsigned int *)t5) = t13;
    t14 = *((unsigned int *)t6);
    t15 = (t14 >> 15);
    t16 = (t15 & 1);
    *((unsigned int *)t2) = t16;
    t7 = (t0 + 5584);
    xsi_vlogvar_wait_assign_value(t7, t5, 0, 0, 1, 0LL);
    xsi_set_current_line(556, ng0);
    t2 = (t0 + 1504U);
    t3 = *((char **)t2);
    memset(t5, 0, 8);
    t2 = (t5 + 4);
    t6 = (t3 + 4);
    t11 = *((unsigned int *)t3);
    t12 = (t11 >> 15);
    t13 = (t12 & 1);
    *((unsigned int *)t5) = t13;
    t14 = *((unsigned int *)t6);
    t15 = (t14 >> 15);
    t16 = (t15 & 1);
    *((unsigned int *)t2) = t16;
    t7 = (t0 + 5744);
    xsi_vlogvar_wait_assign_value(t7, t5, 0, 0, 1, 0LL);
    xsi_set_current_line(557, ng0);
    t2 = (t0 + 1344U);
    t3 = *((char **)t2);
    memset(t5, 0, 8);
    t2 = (t5 + 4);
    t6 = (t3 + 4);
    t11 = *((unsigned int *)t3);
    t12 = (t11 >> 10);
    *((unsigned int *)t5) = t12;
    t13 = *((unsigned int *)t6);
    t14 = (t13 >> 10);
    *((unsigned int *)t2) = t14;
    t15 = *((unsigned int *)t5);
    *((unsigned int *)t5) = (t15 & 31U);
    t16 = *((unsigned int *)t2);
    *((unsigned int *)t2) = (t16 & 31U);
    t7 = (t0 + 5904);
    xsi_vlogvar_wait_assign_value(t7, t5, 0, 0, 5, 0LL);
    xsi_set_current_line(558, ng0);
    t2 = (t0 + 1504U);
    t3 = *((char **)t2);
    memset(t5, 0, 8);
    t2 = (t5 + 4);
    t6 = (t3 + 4);
    t11 = *((unsigned int *)t3);
    t12 = (t11 >> 10);
    *((unsigned int *)t5) = t12;
    t13 = *((unsigned int *)t6);
    t14 = (t13 >> 10);
    *((unsigned int *)t2) = t14;
    t15 = *((unsigned int *)t5);
    *((unsigned int *)t5) = (t15 & 31U);
    t16 = *((unsigned int *)t2);
    *((unsigned int *)t2) = (t16 & 31U);
    t7 = (t0 + 6064);
    xsi_vlogvar_wait_assign_value(t7, t5, 0, 0, 5, 0LL);
    xsi_set_current_line(559, ng0);
    t2 = (t0 + 1344U);
    t3 = *((char **)t2);
    memset(t5, 0, 8);
    t2 = (t5 + 4);
    t6 = (t3 + 4);
    t11 = *((unsigned int *)t3);
    t12 = (t11 >> 0);
    *((unsigned int *)t5) = t12;
    t13 = *((unsigned int *)t6);
    t14 = (t13 >> 0);
    *((unsigned int *)t2) = t14;
    t15 = *((unsigned int *)t5);
    *((unsigned int *)t5) = (t15 & 1023U);
    t16 = *((unsigned int *)t2);
    *((unsigned int *)t2) = (t16 & 1023U);
    t7 = (t0 + 6224);
    xsi_vlogvar_wait_assign_value(t7, t5, 0, 0, 10, 0LL);
    xsi_set_current_line(560, ng0);
    t2 = (t0 + 1504U);
    t3 = *((char **)t2);
    memset(t5, 0, 8);
    t2 = (t5 + 4);
    t6 = (t3 + 4);
    t11 = *((unsigned int *)t3);
    t12 = (t11 >> 0);
    *((unsigned int *)t5) = t12;
    t13 = *((unsigned int *)t6);
    t14 = (t13 >> 0);
    *((unsigned int *)t2) = t14;
    t15 = *((unsigned int *)t5);
    *((unsigned int *)t5) = (t15 & 1023U);
    t16 = *((unsigned int *)t2);
    *((unsigned int *)t2) = (t16 & 1023U);
    t7 = (t0 + 6384);
    xsi_vlogvar_wait_assign_value(t7, t5, 0, 0, 10, 0LL);
    xsi_set_current_line(561, ng0);
    t2 = (t0 + 1984U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng1)));
    memset(t43, 0, 8);
    t6 = (t3 + 4);
    t7 = (t2 + 4);
    t11 = *((unsigned int *)t3);
    t12 = *((unsigned int *)t2);
    t13 = (t11 ^ t12);
    t14 = *((unsigned int *)t6);
    t15 = *((unsigned int *)t7);
    t16 = (t14 ^ t15);
    t17 = (t13 | t16);
    t18 = *((unsigned int *)t6);
    t19 = *((unsigned int *)t7);
    t20 = (t18 | t19);
    t21 = (~(t20));
    t22 = (t17 & t21);
    if (t22 != 0)
        goto LAB218;

LAB215:    if (t20 != 0)
        goto LAB217;

LAB216:    *((unsigned int *)t43) = 1;

LAB218:    memset(t8, 0, 8);
    t10 = (t43 + 4);
    t25 = *((unsigned int *)t10);
    t26 = (~(t25));
    t27 = *((unsigned int *)t43);
    t28 = (t27 & t26);
    t29 = (t28 & 1U);
    if (t29 != 0)
        goto LAB219;

LAB220:    if (*((unsigned int *)t10) != 0)
        goto LAB221;

LAB222:    t24 = (t8 + 4);
    t32 = *((unsigned int *)t8);
    t33 = *((unsigned int *)t24);
    t34 = (t32 || t33);
    if (t34 > 0)
        goto LAB223;

LAB224:    t36 = *((unsigned int *)t8);
    t37 = (~(t36));
    t38 = *((unsigned int *)t24);
    t39 = (t37 || t38);
    if (t39 > 0)
        goto LAB225;

LAB226:    if (*((unsigned int *)t24) > 0)
        goto LAB227;

LAB228:    if (*((unsigned int *)t8) > 0)
        goto LAB229;

LAB230:    memcpy(t5, t30, 8);

LAB231:    t35 = (t0 + 5264);
    xsi_vlogvar_wait_assign_value(t35, t5, 0, 0, 16, 0LL);
    xsi_set_current_line(562, ng0);
    t2 = (t0 + 1984U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng1)));
    memset(t43, 0, 8);
    t6 = (t3 + 4);
    t7 = (t2 + 4);
    t11 = *((unsigned int *)t3);
    t12 = *((unsigned int *)t2);
    t13 = (t11 ^ t12);
    t14 = *((unsigned int *)t6);
    t15 = *((unsigned int *)t7);
    t16 = (t14 ^ t15);
    t17 = (t13 | t16);
    t18 = *((unsigned int *)t6);
    t19 = *((unsigned int *)t7);
    t20 = (t18 | t19);
    t21 = (~(t20));
    t22 = (t17 & t21);
    if (t22 != 0)
        goto LAB235;

LAB232:    if (t20 != 0)
        goto LAB234;

LAB233:    *((unsigned int *)t43) = 1;

LAB235:    memset(t8, 0, 8);
    t10 = (t43 + 4);
    t25 = *((unsigned int *)t10);
    t26 = (~(t25));
    t27 = *((unsigned int *)t43);
    t28 = (t27 & t26);
    t29 = (t28 & 1U);
    if (t29 != 0)
        goto LAB236;

LAB237:    if (*((unsigned int *)t10) != 0)
        goto LAB238;

LAB239:    t24 = (t8 + 4);
    t32 = *((unsigned int *)t8);
    t33 = *((unsigned int *)t24);
    t34 = (t32 || t33);
    if (t34 > 0)
        goto LAB240;

LAB241:    t36 = *((unsigned int *)t8);
    t37 = (~(t36));
    t38 = *((unsigned int *)t24);
    t39 = (t37 || t38);
    if (t39 > 0)
        goto LAB242;

LAB243:    if (*((unsigned int *)t24) > 0)
        goto LAB244;

LAB245:    if (*((unsigned int *)t8) > 0)
        goto LAB246;

LAB247:    memcpy(t5, t31, 8);

LAB248:    t35 = (t0 + 5424);
    xsi_vlogvar_wait_assign_value(t35, t5, 0, 0, 1, 0LL);

LAB32:    goto LAB2;

LAB8:    t23 = (t8 + 4);
    *((unsigned int *)t8) = 1;
    *((unsigned int *)t23) = 1;
    goto LAB9;

LAB10:    *((unsigned int *)t5) = 1;
    goto LAB13;

LAB12:    t30 = (t5 + 4);
    *((unsigned int *)t5) = 1;
    *((unsigned int *)t30) = 1;
    goto LAB13;

LAB14:    t35 = ((char*)((ng2)));
    goto LAB15;

LAB16:    t40 = ((char*)((ng3)));
    goto LAB17;

LAB18:    xsi_vlog_unsigned_bit_combine(t4, 1, t35, 1, t40, 1);
    goto LAB22;

LAB20:    memcpy(t4, t35, 8);
    goto LAB22;

LAB24:    xsi_set_current_line(532, ng0);

LAB33:    xsi_set_current_line(533, ng0);
    t10 = (t0 + 1984U);
    t23 = *((char **)t10);
    t10 = ((char*)((ng1)));
    memset(t43, 0, 8);
    t24 = (t23 + 4);
    t30 = (t10 + 4);
    t11 = *((unsigned int *)t23);
    t12 = *((unsigned int *)t10);
    t13 = (t11 ^ t12);
    t14 = *((unsigned int *)t24);
    t15 = *((unsigned int *)t30);
    t16 = (t14 ^ t15);
    t17 = (t13 | t16);
    t18 = *((unsigned int *)t24);
    t19 = *((unsigned int *)t30);
    t20 = (t18 | t19);
    t21 = (~(t20));
    t22 = (t17 & t21);
    if (t22 != 0)
        goto LAB37;

LAB34:    if (t20 != 0)
        goto LAB36;

LAB35:    *((unsigned int *)t43) = 1;

LAB37:    memset(t8, 0, 8);
    t35 = (t43 + 4);
    t25 = *((unsigned int *)t35);
    t26 = (~(t25));
    t27 = *((unsigned int *)t43);
    t28 = (t27 & t26);
    t29 = (t28 & 1U);
    if (t29 != 0)
        goto LAB38;

LAB39:    if (*((unsigned int *)t35) != 0)
        goto LAB40;

LAB41:    t41 = (t8 + 4);
    t32 = *((unsigned int *)t8);
    t33 = *((unsigned int *)t41);
    t34 = (t32 || t33);
    if (t34 > 0)
        goto LAB42;

LAB43:    t36 = *((unsigned int *)t8);
    t37 = (~(t36));
    t38 = *((unsigned int *)t41);
    t39 = (t37 || t38);
    if (t39 > 0)
        goto LAB44;

LAB45:    if (*((unsigned int *)t41) > 0)
        goto LAB46;

LAB47:    if (*((unsigned int *)t8) > 0)
        goto LAB48;

LAB49:    memcpy(t5, t45, 8);

LAB50:    t46 = (t0 + 5424);
    xsi_vlogvar_wait_assign_value(t46, t5, 0, 0, 1, 0LL);
    xsi_set_current_line(534, ng0);
    t2 = ((char*)((ng5)));
    t3 = (t0 + 5264);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, 0, 16, 0LL);
    xsi_set_current_line(535, ng0);
    t2 = ((char*)((ng2)));
    memset(t43, 0, 8);
    t3 = (t2 + 4);
    t11 = *((unsigned int *)t3);
    t12 = (~(t11));
    t13 = *((unsigned int *)t2);
    t14 = (t13 & t12);
    t15 = (t14 & 1U);
    if (t15 != 0)
        goto LAB54;

LAB52:    if (*((unsigned int *)t3) == 0)
        goto LAB51;

LAB53:    t6 = (t43 + 4);
    *((unsigned int *)t43) = 1;
    *((unsigned int *)t6) = 1;

LAB54:    t7 = (t43 + 4);
    t9 = (t2 + 4);
    t16 = *((unsigned int *)t2);
    t17 = (~(t16));
    *((unsigned int *)t43) = t17;
    *((unsigned int *)t7) = 0;
    if (*((unsigned int *)t9) != 0)
        goto LAB56;

LAB55:    t22 = *((unsigned int *)t43);
    *((unsigned int *)t43) = (t22 & 1U);
    t25 = *((unsigned int *)t7);
    *((unsigned int *)t7) = (t25 & 1U);
    memset(t8, 0, 8);
    t10 = (t43 + 4);
    t26 = *((unsigned int *)t10);
    t27 = (~(t26));
    t28 = *((unsigned int *)t43);
    t29 = (t28 & t27);
    t32 = (t29 & 1U);
    if (t32 != 0)
        goto LAB57;

LAB58:    if (*((unsigned int *)t10) != 0)
        goto LAB59;

LAB60:    t24 = (t8 + 4);
    t33 = *((unsigned int *)t8);
    t34 = *((unsigned int *)t24);
    t36 = (t33 || t34);
    if (t36 > 0)
        goto LAB61;

LAB62:    t51 = *((unsigned int *)t8);
    t52 = (~(t51));
    t53 = *((unsigned int *)t24);
    t54 = (t52 || t53);
    if (t54 > 0)
        goto LAB63;

LAB64:    if (*((unsigned int *)t24) > 0)
        goto LAB65;

LAB66:    if (*((unsigned int *)t8) > 0)
        goto LAB67;

LAB68:    memcpy(t5, t55, 8);

LAB69:    t45 = (t0 + 5584);
    xsi_vlogvar_wait_assign_value(t45, t5, 0, 0, 1, 0LL);
    xsi_set_current_line(536, ng0);
    t2 = (t0 + 1504U);
    t3 = *((char **)t2);
    memset(t5, 0, 8);
    t2 = (t5 + 4);
    t6 = (t3 + 4);
    t11 = *((unsigned int *)t3);
    t12 = (t11 >> 15);
    t13 = (t12 & 1);
    *((unsigned int *)t5) = t13;
    t14 = *((unsigned int *)t6);
    t15 = (t14 >> 15);
    t16 = (t15 & 1);
    *((unsigned int *)t2) = t16;
    t7 = (t0 + 5744);
    xsi_vlogvar_wait_assign_value(t7, t5, 0, 0, 1, 0LL);
    xsi_set_current_line(537, ng0);
    t2 = ((char*)((ng2)));
    memset(t43, 0, 8);
    t3 = (t2 + 4);
    t11 = *((unsigned int *)t3);
    t12 = (~(t11));
    t13 = *((unsigned int *)t2);
    t14 = (t13 & t12);
    t15 = (t14 & 1U);
    if (t15 != 0)
        goto LAB73;

LAB71:    if (*((unsigned int *)t3) == 0)
        goto LAB70;

LAB72:    t6 = (t43 + 4);
    *((unsigned int *)t43) = 1;
    *((unsigned int *)t6) = 1;

LAB73:    t7 = (t43 + 4);
    t9 = (t2 + 4);
    t16 = *((unsigned int *)t2);
    t17 = (~(t16));
    *((unsigned int *)t43) = t17;
    *((unsigned int *)t7) = 0;
    if (*((unsigned int *)t9) != 0)
        goto LAB75;

LAB74:    t22 = *((unsigned int *)t43);
    *((unsigned int *)t43) = (t22 & 1U);
    t25 = *((unsigned int *)t7);
    *((unsigned int *)t7) = (t25 & 1U);
    memset(t8, 0, 8);
    t10 = (t43 + 4);
    t26 = *((unsigned int *)t10);
    t27 = (~(t26));
    t28 = *((unsigned int *)t43);
    t29 = (t28 & t27);
    t32 = (t29 & 1U);
    if (t32 != 0)
        goto LAB76;

LAB77:    if (*((unsigned int *)t10) != 0)
        goto LAB78;

LAB79:    t24 = (t8 + 4);
    t33 = *((unsigned int *)t8);
    t34 = *((unsigned int *)t24);
    t36 = (t33 || t34);
    if (t36 > 0)
        goto LAB80;

LAB81:    t51 = *((unsigned int *)t8);
    t52 = (~(t51));
    t53 = *((unsigned int *)t24);
    t54 = (t52 || t53);
    if (t54 > 0)
        goto LAB82;

LAB83:    if (*((unsigned int *)t24) > 0)
        goto LAB84;

LAB85:    if (*((unsigned int *)t8) > 0)
        goto LAB86;

LAB87:    memcpy(t5, t55, 8);

LAB88:    t45 = (t0 + 5904);
    xsi_vlogvar_wait_assign_value(t45, t5, 0, 0, 5, 0LL);
    xsi_set_current_line(538, ng0);
    t2 = (t0 + 1504U);
    t3 = *((char **)t2);
    memset(t5, 0, 8);
    t2 = (t5 + 4);
    t6 = (t3 + 4);
    t11 = *((unsigned int *)t3);
    t12 = (t11 >> 10);
    *((unsigned int *)t5) = t12;
    t13 = *((unsigned int *)t6);
    t14 = (t13 >> 10);
    *((unsigned int *)t2) = t14;
    t15 = *((unsigned int *)t5);
    *((unsigned int *)t5) = (t15 & 31U);
    t16 = *((unsigned int *)t2);
    *((unsigned int *)t2) = (t16 & 31U);
    t7 = (t0 + 6064);
    xsi_vlogvar_wait_assign_value(t7, t5, 0, 0, 5, 0LL);
    xsi_set_current_line(539, ng0);
    t2 = ((char*)((ng2)));
    memset(t43, 0, 8);
    t3 = (t2 + 4);
    t11 = *((unsigned int *)t3);
    t12 = (~(t11));
    t13 = *((unsigned int *)t2);
    t14 = (t13 & t12);
    t15 = (t14 & 1U);
    if (t15 != 0)
        goto LAB92;

LAB90:    if (*((unsigned int *)t3) == 0)
        goto LAB89;

LAB91:    t6 = (t43 + 4);
    *((unsigned int *)t43) = 1;
    *((unsigned int *)t6) = 1;

LAB92:    t7 = (t43 + 4);
    t9 = (t2 + 4);
    t16 = *((unsigned int *)t2);
    t17 = (~(t16));
    *((unsigned int *)t43) = t17;
    *((unsigned int *)t7) = 0;
    if (*((unsigned int *)t9) != 0)
        goto LAB94;

LAB93:    t22 = *((unsigned int *)t43);
    *((unsigned int *)t43) = (t22 & 1U);
    t25 = *((unsigned int *)t7);
    *((unsigned int *)t7) = (t25 & 1U);
    memset(t8, 0, 8);
    t10 = (t43 + 4);
    t26 = *((unsigned int *)t10);
    t27 = (~(t26));
    t28 = *((unsigned int *)t43);
    t29 = (t28 & t27);
    t32 = (t29 & 1U);
    if (t32 != 0)
        goto LAB95;

LAB96:    if (*((unsigned int *)t10) != 0)
        goto LAB97;

LAB98:    t24 = (t8 + 4);
    t33 = *((unsigned int *)t8);
    t34 = *((unsigned int *)t24);
    t36 = (t33 || t34);
    if (t36 > 0)
        goto LAB99;

LAB100:    t51 = *((unsigned int *)t8);
    t52 = (~(t51));
    t53 = *((unsigned int *)t24);
    t54 = (t52 || t53);
    if (t54 > 0)
        goto LAB101;

LAB102:    if (*((unsigned int *)t24) > 0)
        goto LAB103;

LAB104:    if (*((unsigned int *)t8) > 0)
        goto LAB105;

LAB106:    memcpy(t5, t55, 8);

LAB107:    t45 = (t0 + 6224);
    xsi_vlogvar_wait_assign_value(t45, t5, 0, 0, 10, 0LL);
    xsi_set_current_line(540, ng0);
    t2 = (t0 + 1504U);
    t3 = *((char **)t2);
    memset(t5, 0, 8);
    t2 = (t5 + 4);
    t6 = (t3 + 4);
    t11 = *((unsigned int *)t3);
    t12 = (t11 >> 0);
    *((unsigned int *)t5) = t12;
    t13 = *((unsigned int *)t6);
    t14 = (t13 >> 0);
    *((unsigned int *)t2) = t14;
    t15 = *((unsigned int *)t5);
    *((unsigned int *)t5) = (t15 & 1023U);
    t16 = *((unsigned int *)t2);
    *((unsigned int *)t2) = (t16 & 1023U);
    t7 = (t0 + 6384);
    xsi_vlogvar_wait_assign_value(t7, t5, 0, 0, 10, 0LL);
    goto LAB32;

LAB26:    xsi_set_current_line(542, ng0);

LAB108:    xsi_set_current_line(543, ng0);
    t3 = ((char*)((ng2)));
    memset(t43, 0, 8);
    t6 = (t3 + 4);
    t11 = *((unsigned int *)t6);
    t12 = (~(t11));
    t13 = *((unsigned int *)t3);
    t14 = (t13 & t12);
    t15 = (t14 & 1U);
    if (t15 != 0)
        goto LAB112;

LAB110:    if (*((unsigned int *)t6) == 0)
        goto LAB109;

LAB111:    t7 = (t43 + 4);
    *((unsigned int *)t43) = 1;
    *((unsigned int *)t7) = 1;

LAB112:    t9 = (t43 + 4);
    t10 = (t3 + 4);
    t16 = *((unsigned int *)t3);
    t17 = (~(t16));
    *((unsigned int *)t43) = t17;
    *((unsigned int *)t9) = 0;
    if (*((unsigned int *)t10) != 0)
        goto LAB114;

LAB113:    t22 = *((unsigned int *)t43);
    *((unsigned int *)t43) = (t22 & 1U);
    t25 = *((unsigned int *)t9);
    *((unsigned int *)t9) = (t25 & 1U);
    memset(t8, 0, 8);
    t23 = (t43 + 4);
    t26 = *((unsigned int *)t23);
    t27 = (~(t26));
    t28 = *((unsigned int *)t43);
    t29 = (t28 & t27);
    t32 = (t29 & 1U);
    if (t32 != 0)
        goto LAB115;

LAB116:    if (*((unsigned int *)t23) != 0)
        goto LAB117;

LAB118:    t30 = (t8 + 4);
    t33 = *((unsigned int *)t8);
    t34 = *((unsigned int *)t30);
    t36 = (t33 || t34);
    if (t36 > 0)
        goto LAB119;

LAB120:    t51 = *((unsigned int *)t8);
    t52 = (~(t51));
    t53 = *((unsigned int *)t30);
    t54 = (t52 || t53);
    if (t54 > 0)
        goto LAB121;

LAB122:    if (*((unsigned int *)t30) > 0)
        goto LAB123;

LAB124:    if (*((unsigned int *)t8) > 0)
        goto LAB125;

LAB126:    memcpy(t5, t55, 8);

LAB127:    t46 = (t0 + 5584);
    xsi_vlogvar_wait_assign_value(t46, t5, 0, 0, 1, 0LL);
    xsi_set_current_line(544, ng0);
    t2 = (t0 + 1824U);
    t3 = *((char **)t2);
    memset(t5, 0, 8);
    t2 = (t5 + 4);
    t6 = (t3 + 4);
    t11 = *((unsigned int *)t3);
    t12 = (t11 >> 15);
    t13 = (t12 & 1);
    *((unsigned int *)t5) = t13;
    t14 = *((unsigned int *)t6);
    t15 = (t14 >> 15);
    t16 = (t15 & 1);
    *((unsigned int *)t2) = t16;
    t7 = (t0 + 5744);
    xsi_vlogvar_wait_assign_value(t7, t5, 0, 0, 1, 0LL);
    xsi_set_current_line(545, ng0);
    t2 = ((char*)((ng2)));
    memset(t43, 0, 8);
    t3 = (t2 + 4);
    t11 = *((unsigned int *)t3);
    t12 = (~(t11));
    t13 = *((unsigned int *)t2);
    t14 = (t13 & t12);
    t15 = (t14 & 1U);
    if (t15 != 0)
        goto LAB131;

LAB129:    if (*((unsigned int *)t3) == 0)
        goto LAB128;

LAB130:    t6 = (t43 + 4);
    *((unsigned int *)t43) = 1;
    *((unsigned int *)t6) = 1;

LAB131:    t7 = (t43 + 4);
    t9 = (t2 + 4);
    t16 = *((unsigned int *)t2);
    t17 = (~(t16));
    *((unsigned int *)t43) = t17;
    *((unsigned int *)t7) = 0;
    if (*((unsigned int *)t9) != 0)
        goto LAB133;

LAB132:    t22 = *((unsigned int *)t43);
    *((unsigned int *)t43) = (t22 & 1U);
    t25 = *((unsigned int *)t7);
    *((unsigned int *)t7) = (t25 & 1U);
    memset(t8, 0, 8);
    t10 = (t43 + 4);
    t26 = *((unsigned int *)t10);
    t27 = (~(t26));
    t28 = *((unsigned int *)t43);
    t29 = (t28 & t27);
    t32 = (t29 & 1U);
    if (t32 != 0)
        goto LAB134;

LAB135:    if (*((unsigned int *)t10) != 0)
        goto LAB136;

LAB137:    t24 = (t8 + 4);
    t33 = *((unsigned int *)t8);
    t34 = *((unsigned int *)t24);
    t36 = (t33 || t34);
    if (t36 > 0)
        goto LAB138;

LAB139:    t51 = *((unsigned int *)t8);
    t52 = (~(t51));
    t53 = *((unsigned int *)t24);
    t54 = (t52 || t53);
    if (t54 > 0)
        goto LAB140;

LAB141:    if (*((unsigned int *)t24) > 0)
        goto LAB142;

LAB143:    if (*((unsigned int *)t8) > 0)
        goto LAB144;

LAB145:    memcpy(t5, t55, 8);

LAB146:    t45 = (t0 + 5904);
    xsi_vlogvar_wait_assign_value(t45, t5, 0, 0, 5, 0LL);
    xsi_set_current_line(546, ng0);
    t2 = (t0 + 1824U);
    t3 = *((char **)t2);
    memset(t5, 0, 8);
    t2 = (t5 + 4);
    t6 = (t3 + 4);
    t11 = *((unsigned int *)t3);
    t12 = (t11 >> 10);
    *((unsigned int *)t5) = t12;
    t13 = *((unsigned int *)t6);
    t14 = (t13 >> 10);
    *((unsigned int *)t2) = t14;
    t15 = *((unsigned int *)t5);
    *((unsigned int *)t5) = (t15 & 31U);
    t16 = *((unsigned int *)t2);
    *((unsigned int *)t2) = (t16 & 31U);
    t7 = (t0 + 6064);
    xsi_vlogvar_wait_assign_value(t7, t5, 0, 0, 5, 0LL);
    xsi_set_current_line(547, ng0);
    t2 = ((char*)((ng2)));
    memset(t43, 0, 8);
    t3 = (t2 + 4);
    t11 = *((unsigned int *)t3);
    t12 = (~(t11));
    t13 = *((unsigned int *)t2);
    t14 = (t13 & t12);
    t15 = (t14 & 1U);
    if (t15 != 0)
        goto LAB150;

LAB148:    if (*((unsigned int *)t3) == 0)
        goto LAB147;

LAB149:    t6 = (t43 + 4);
    *((unsigned int *)t43) = 1;
    *((unsigned int *)t6) = 1;

LAB150:    t7 = (t43 + 4);
    t9 = (t2 + 4);
    t16 = *((unsigned int *)t2);
    t17 = (~(t16));
    *((unsigned int *)t43) = t17;
    *((unsigned int *)t7) = 0;
    if (*((unsigned int *)t9) != 0)
        goto LAB152;

LAB151:    t22 = *((unsigned int *)t43);
    *((unsigned int *)t43) = (t22 & 1U);
    t25 = *((unsigned int *)t7);
    *((unsigned int *)t7) = (t25 & 1U);
    memset(t8, 0, 8);
    t10 = (t43 + 4);
    t26 = *((unsigned int *)t10);
    t27 = (~(t26));
    t28 = *((unsigned int *)t43);
    t29 = (t28 & t27);
    t32 = (t29 & 1U);
    if (t32 != 0)
        goto LAB153;

LAB154:    if (*((unsigned int *)t10) != 0)
        goto LAB155;

LAB156:    t24 = (t8 + 4);
    t33 = *((unsigned int *)t8);
    t34 = *((unsigned int *)t24);
    t36 = (t33 || t34);
    if (t36 > 0)
        goto LAB157;

LAB158:    t51 = *((unsigned int *)t8);
    t52 = (~(t51));
    t53 = *((unsigned int *)t24);
    t54 = (t52 || t53);
    if (t54 > 0)
        goto LAB159;

LAB160:    if (*((unsigned int *)t24) > 0)
        goto LAB161;

LAB162:    if (*((unsigned int *)t8) > 0)
        goto LAB163;

LAB164:    memcpy(t5, t55, 8);

LAB165:    t45 = (t0 + 6224);
    xsi_vlogvar_wait_assign_value(t45, t5, 0, 0, 10, 0LL);
    xsi_set_current_line(548, ng0);
    t2 = (t0 + 1824U);
    t3 = *((char **)t2);
    memset(t5, 0, 8);
    t2 = (t5 + 4);
    t6 = (t3 + 4);
    t11 = *((unsigned int *)t3);
    t12 = (t11 >> 0);
    *((unsigned int *)t5) = t12;
    t13 = *((unsigned int *)t6);
    t14 = (t13 >> 0);
    *((unsigned int *)t2) = t14;
    t15 = *((unsigned int *)t5);
    *((unsigned int *)t5) = (t15 & 1023U);
    t16 = *((unsigned int *)t2);
    *((unsigned int *)t2) = (t16 & 1023U);
    t7 = (t0 + 6384);
    xsi_vlogvar_wait_assign_value(t7, t5, 0, 0, 10, 0LL);
    goto LAB32;

LAB28:    xsi_set_current_line(550, ng0);

LAB166:    xsi_set_current_line(551, ng0);
    t3 = (t0 + 1984U);
    t6 = *((char **)t3);
    t3 = ((char*)((ng1)));
    memset(t43, 0, 8);
    t7 = (t6 + 4);
    t9 = (t3 + 4);
    t11 = *((unsigned int *)t6);
    t12 = *((unsigned int *)t3);
    t13 = (t11 ^ t12);
    t14 = *((unsigned int *)t7);
    t15 = *((unsigned int *)t9);
    t16 = (t14 ^ t15);
    t17 = (t13 | t16);
    t18 = *((unsigned int *)t7);
    t19 = *((unsigned int *)t9);
    t20 = (t18 | t19);
    t21 = (~(t20));
    t22 = (t17 & t21);
    if (t22 != 0)
        goto LAB170;

LAB167:    if (t20 != 0)
        goto LAB169;

LAB168:    *((unsigned int *)t43) = 1;

LAB170:    memset(t8, 0, 8);
    t23 = (t43 + 4);
    t25 = *((unsigned int *)t23);
    t26 = (~(t25));
    t27 = *((unsigned int *)t43);
    t28 = (t27 & t26);
    t29 = (t28 & 1U);
    if (t29 != 0)
        goto LAB171;

LAB172:    if (*((unsigned int *)t23) != 0)
        goto LAB173;

LAB174:    t30 = (t8 + 4);
    t32 = *((unsigned int *)t8);
    t33 = *((unsigned int *)t30);
    t34 = (t32 || t33);
    if (t34 > 0)
        goto LAB175;

LAB176:    t36 = *((unsigned int *)t8);
    t37 = (~(t36));
    t38 = *((unsigned int *)t30);
    t39 = (t37 || t38);
    if (t39 > 0)
        goto LAB177;

LAB178:    if (*((unsigned int *)t30) > 0)
        goto LAB179;

LAB180:    if (*((unsigned int *)t8) > 0)
        goto LAB181;

LAB182:    memcpy(t5, t35, 8);

LAB183:    t40 = (t0 + 5424);
    xsi_vlogvar_wait_assign_value(t40, t5, 0, 0, 1, 0LL);
    xsi_set_current_line(552, ng0);
    t2 = (t0 + 1984U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng1)));
    memset(t43, 0, 8);
    t6 = (t3 + 4);
    t7 = (t2 + 4);
    t11 = *((unsigned int *)t3);
    t12 = *((unsigned int *)t2);
    t13 = (t11 ^ t12);
    t14 = *((unsigned int *)t6);
    t15 = *((unsigned int *)t7);
    t16 = (t14 ^ t15);
    t17 = (t13 | t16);
    t18 = *((unsigned int *)t6);
    t19 = *((unsigned int *)t7);
    t20 = (t18 | t19);
    t21 = (~(t20));
    t22 = (t17 & t21);
    if (t22 != 0)
        goto LAB187;

LAB184:    if (t20 != 0)
        goto LAB186;

LAB185:    *((unsigned int *)t43) = 1;

LAB187:    memset(t8, 0, 8);
    t10 = (t43 + 4);
    t25 = *((unsigned int *)t10);
    t26 = (~(t25));
    t27 = *((unsigned int *)t43);
    t28 = (t27 & t26);
    t29 = (t28 & 1U);
    if (t29 != 0)
        goto LAB188;

LAB189:    if (*((unsigned int *)t10) != 0)
        goto LAB190;

LAB191:    t24 = (t8 + 4);
    t32 = *((unsigned int *)t8);
    t33 = *((unsigned int *)t24);
    t34 = (t32 || t33);
    if (t34 > 0)
        goto LAB192;

LAB193:    t57 = *((unsigned int *)t8);
    t58 = (~(t57));
    t59 = *((unsigned int *)t24);
    t60 = (t58 || t59);
    if (t60 > 0)
        goto LAB194;

LAB195:    if (*((unsigned int *)t24) > 0)
        goto LAB196;

LAB197:    if (*((unsigned int *)t8) > 0)
        goto LAB198;

LAB199:    memcpy(t5, t41, 8);

LAB200:    t46 = (t0 + 5264);
    xsi_vlogvar_wait_assign_value(t46, t5, 0, 0, 16, 0LL);
    goto LAB32;

LAB36:    t31 = (t43 + 4);
    *((unsigned int *)t43) = 1;
    *((unsigned int *)t31) = 1;
    goto LAB37;

LAB38:    *((unsigned int *)t8) = 1;
    goto LAB41;

LAB40:    t40 = (t8 + 4);
    *((unsigned int *)t8) = 1;
    *((unsigned int *)t40) = 1;
    goto LAB41;

LAB42:    t44 = ((char*)((ng2)));
    goto LAB43;

LAB44:    t45 = ((char*)((ng3)));
    goto LAB45;

LAB46:    xsi_vlog_unsigned_bit_combine(t5, 1, t44, 1, t45, 1);
    goto LAB50;

LAB48:    memcpy(t5, t44, 8);
    goto LAB50;

LAB51:    *((unsigned int *)t43) = 1;
    goto LAB54;

LAB56:    t18 = *((unsigned int *)t43);
    t19 = *((unsigned int *)t9);
    *((unsigned int *)t43) = (t18 | t19);
    t20 = *((unsigned int *)t7);
    t21 = *((unsigned int *)t9);
    *((unsigned int *)t7) = (t20 | t21);
    goto LAB55;

LAB57:    *((unsigned int *)t8) = 1;
    goto LAB60;

LAB59:    t23 = (t8 + 4);
    *((unsigned int *)t8) = 1;
    *((unsigned int *)t23) = 1;
    goto LAB60;

LAB61:    t30 = (t0 + 1344U);
    t31 = *((char **)t30);
    memset(t47, 0, 8);
    t30 = (t47 + 4);
    t35 = (t31 + 4);
    t37 = *((unsigned int *)t31);
    t38 = (t37 >> 15);
    t39 = (t38 & 1);
    *((unsigned int *)t47) = t39;
    t48 = *((unsigned int *)t35);
    t49 = (t48 >> 15);
    t50 = (t49 & 1);
    *((unsigned int *)t30) = t50;
    goto LAB62;

LAB63:    t40 = (t0 + 1664U);
    t41 = *((char **)t40);
    memset(t55, 0, 8);
    t40 = (t55 + 4);
    t44 = (t41 + 4);
    t56 = *((unsigned int *)t41);
    t57 = (t56 >> 15);
    t58 = (t57 & 1);
    *((unsigned int *)t55) = t58;
    t59 = *((unsigned int *)t44);
    t60 = (t59 >> 15);
    t61 = (t60 & 1);
    *((unsigned int *)t40) = t61;
    goto LAB64;

LAB65:    xsi_vlog_unsigned_bit_combine(t5, 1, t47, 1, t55, 1);
    goto LAB69;

LAB67:    memcpy(t5, t47, 8);
    goto LAB69;

LAB70:    *((unsigned int *)t43) = 1;
    goto LAB73;

LAB75:    t18 = *((unsigned int *)t43);
    t19 = *((unsigned int *)t9);
    *((unsigned int *)t43) = (t18 | t19);
    t20 = *((unsigned int *)t7);
    t21 = *((unsigned int *)t9);
    *((unsigned int *)t7) = (t20 | t21);
    goto LAB74;

LAB76:    *((unsigned int *)t8) = 1;
    goto LAB79;

LAB78:    t23 = (t8 + 4);
    *((unsigned int *)t8) = 1;
    *((unsigned int *)t23) = 1;
    goto LAB79;

LAB80:    t30 = (t0 + 1344U);
    t31 = *((char **)t30);
    memset(t47, 0, 8);
    t30 = (t47 + 4);
    t35 = (t31 + 4);
    t37 = *((unsigned int *)t31);
    t38 = (t37 >> 10);
    *((unsigned int *)t47) = t38;
    t39 = *((unsigned int *)t35);
    t48 = (t39 >> 10);
    *((unsigned int *)t30) = t48;
    t49 = *((unsigned int *)t47);
    *((unsigned int *)t47) = (t49 & 31U);
    t50 = *((unsigned int *)t30);
    *((unsigned int *)t30) = (t50 & 31U);
    goto LAB81;

LAB82:    t40 = (t0 + 1664U);
    t41 = *((char **)t40);
    memset(t55, 0, 8);
    t40 = (t55 + 4);
    t44 = (t41 + 4);
    t56 = *((unsigned int *)t41);
    t57 = (t56 >> 10);
    *((unsigned int *)t55) = t57;
    t58 = *((unsigned int *)t44);
    t59 = (t58 >> 10);
    *((unsigned int *)t40) = t59;
    t60 = *((unsigned int *)t55);
    *((unsigned int *)t55) = (t60 & 31U);
    t61 = *((unsigned int *)t40);
    *((unsigned int *)t40) = (t61 & 31U);
    goto LAB83;

LAB84:    xsi_vlog_unsigned_bit_combine(t5, 5, t47, 5, t55, 5);
    goto LAB88;

LAB86:    memcpy(t5, t47, 8);
    goto LAB88;

LAB89:    *((unsigned int *)t43) = 1;
    goto LAB92;

LAB94:    t18 = *((unsigned int *)t43);
    t19 = *((unsigned int *)t9);
    *((unsigned int *)t43) = (t18 | t19);
    t20 = *((unsigned int *)t7);
    t21 = *((unsigned int *)t9);
    *((unsigned int *)t7) = (t20 | t21);
    goto LAB93;

LAB95:    *((unsigned int *)t8) = 1;
    goto LAB98;

LAB97:    t23 = (t8 + 4);
    *((unsigned int *)t8) = 1;
    *((unsigned int *)t23) = 1;
    goto LAB98;

LAB99:    t30 = (t0 + 1344U);
    t31 = *((char **)t30);
    memset(t47, 0, 8);
    t30 = (t47 + 4);
    t35 = (t31 + 4);
    t37 = *((unsigned int *)t31);
    t38 = (t37 >> 0);
    *((unsigned int *)t47) = t38;
    t39 = *((unsigned int *)t35);
    t48 = (t39 >> 0);
    *((unsigned int *)t30) = t48;
    t49 = *((unsigned int *)t47);
    *((unsigned int *)t47) = (t49 & 1023U);
    t50 = *((unsigned int *)t30);
    *((unsigned int *)t30) = (t50 & 1023U);
    goto LAB100;

LAB101:    t40 = (t0 + 1664U);
    t41 = *((char **)t40);
    memset(t55, 0, 8);
    t40 = (t55 + 4);
    t44 = (t41 + 4);
    t56 = *((unsigned int *)t41);
    t57 = (t56 >> 0);
    *((unsigned int *)t55) = t57;
    t58 = *((unsigned int *)t44);
    t59 = (t58 >> 0);
    *((unsigned int *)t40) = t59;
    t60 = *((unsigned int *)t55);
    *((unsigned int *)t55) = (t60 & 1023U);
    t61 = *((unsigned int *)t40);
    *((unsigned int *)t40) = (t61 & 1023U);
    goto LAB102;

LAB103:    xsi_vlog_unsigned_bit_combine(t5, 10, t47, 10, t55, 10);
    goto LAB107;

LAB105:    memcpy(t5, t47, 8);
    goto LAB107;

LAB109:    *((unsigned int *)t43) = 1;
    goto LAB112;

LAB114:    t18 = *((unsigned int *)t43);
    t19 = *((unsigned int *)t10);
    *((unsigned int *)t43) = (t18 | t19);
    t20 = *((unsigned int *)t9);
    t21 = *((unsigned int *)t10);
    *((unsigned int *)t9) = (t20 | t21);
    goto LAB113;

LAB115:    *((unsigned int *)t8) = 1;
    goto LAB118;

LAB117:    t24 = (t8 + 4);
    *((unsigned int *)t8) = 1;
    *((unsigned int *)t24) = 1;
    goto LAB118;

LAB119:    t31 = (t0 + 1664U);
    t35 = *((char **)t31);
    memset(t47, 0, 8);
    t31 = (t47 + 4);
    t40 = (t35 + 4);
    t37 = *((unsigned int *)t35);
    t38 = (t37 >> 15);
    t39 = (t38 & 1);
    *((unsigned int *)t47) = t39;
    t48 = *((unsigned int *)t40);
    t49 = (t48 >> 15);
    t50 = (t49 & 1);
    *((unsigned int *)t31) = t50;
    goto LAB120;

LAB121:    t41 = (t0 + 1344U);
    t44 = *((char **)t41);
    memset(t55, 0, 8);
    t41 = (t55 + 4);
    t45 = (t44 + 4);
    t56 = *((unsigned int *)t44);
    t57 = (t56 >> 15);
    t58 = (t57 & 1);
    *((unsigned int *)t55) = t58;
    t59 = *((unsigned int *)t45);
    t60 = (t59 >> 15);
    t61 = (t60 & 1);
    *((unsigned int *)t41) = t61;
    goto LAB122;

LAB123:    xsi_vlog_unsigned_bit_combine(t5, 1, t47, 1, t55, 1);
    goto LAB127;

LAB125:    memcpy(t5, t47, 8);
    goto LAB127;

LAB128:    *((unsigned int *)t43) = 1;
    goto LAB131;

LAB133:    t18 = *((unsigned int *)t43);
    t19 = *((unsigned int *)t9);
    *((unsigned int *)t43) = (t18 | t19);
    t20 = *((unsigned int *)t7);
    t21 = *((unsigned int *)t9);
    *((unsigned int *)t7) = (t20 | t21);
    goto LAB132;

LAB134:    *((unsigned int *)t8) = 1;
    goto LAB137;

LAB136:    t23 = (t8 + 4);
    *((unsigned int *)t8) = 1;
    *((unsigned int *)t23) = 1;
    goto LAB137;

LAB138:    t30 = (t0 + 1664U);
    t31 = *((char **)t30);
    memset(t47, 0, 8);
    t30 = (t47 + 4);
    t35 = (t31 + 4);
    t37 = *((unsigned int *)t31);
    t38 = (t37 >> 10);
    *((unsigned int *)t47) = t38;
    t39 = *((unsigned int *)t35);
    t48 = (t39 >> 10);
    *((unsigned int *)t30) = t48;
    t49 = *((unsigned int *)t47);
    *((unsigned int *)t47) = (t49 & 31U);
    t50 = *((unsigned int *)t30);
    *((unsigned int *)t30) = (t50 & 31U);
    goto LAB139;

LAB140:    t40 = (t0 + 1344U);
    t41 = *((char **)t40);
    memset(t55, 0, 8);
    t40 = (t55 + 4);
    t44 = (t41 + 4);
    t56 = *((unsigned int *)t41);
    t57 = (t56 >> 10);
    *((unsigned int *)t55) = t57;
    t58 = *((unsigned int *)t44);
    t59 = (t58 >> 10);
    *((unsigned int *)t40) = t59;
    t60 = *((unsigned int *)t55);
    *((unsigned int *)t55) = (t60 & 31U);
    t61 = *((unsigned int *)t40);
    *((unsigned int *)t40) = (t61 & 31U);
    goto LAB141;

LAB142:    xsi_vlog_unsigned_bit_combine(t5, 5, t47, 5, t55, 5);
    goto LAB146;

LAB144:    memcpy(t5, t47, 8);
    goto LAB146;

LAB147:    *((unsigned int *)t43) = 1;
    goto LAB150;

LAB152:    t18 = *((unsigned int *)t43);
    t19 = *((unsigned int *)t9);
    *((unsigned int *)t43) = (t18 | t19);
    t20 = *((unsigned int *)t7);
    t21 = *((unsigned int *)t9);
    *((unsigned int *)t7) = (t20 | t21);
    goto LAB151;

LAB153:    *((unsigned int *)t8) = 1;
    goto LAB156;

LAB155:    t23 = (t8 + 4);
    *((unsigned int *)t8) = 1;
    *((unsigned int *)t23) = 1;
    goto LAB156;

LAB157:    t30 = (t0 + 1664U);
    t31 = *((char **)t30);
    memset(t47, 0, 8);
    t30 = (t47 + 4);
    t35 = (t31 + 4);
    t37 = *((unsigned int *)t31);
    t38 = (t37 >> 0);
    *((unsigned int *)t47) = t38;
    t39 = *((unsigned int *)t35);
    t48 = (t39 >> 0);
    *((unsigned int *)t30) = t48;
    t49 = *((unsigned int *)t47);
    *((unsigned int *)t47) = (t49 & 1023U);
    t50 = *((unsigned int *)t30);
    *((unsigned int *)t30) = (t50 & 1023U);
    goto LAB158;

LAB159:    t40 = (t0 + 1344U);
    t41 = *((char **)t40);
    memset(t55, 0, 8);
    t40 = (t55 + 4);
    t44 = (t41 + 4);
    t56 = *((unsigned int *)t41);
    t57 = (t56 >> 0);
    *((unsigned int *)t55) = t57;
    t58 = *((unsigned int *)t44);
    t59 = (t58 >> 0);
    *((unsigned int *)t40) = t59;
    t60 = *((unsigned int *)t55);
    *((unsigned int *)t55) = (t60 & 1023U);
    t61 = *((unsigned int *)t40);
    *((unsigned int *)t40) = (t61 & 1023U);
    goto LAB160;

LAB161:    xsi_vlog_unsigned_bit_combine(t5, 10, t47, 10, t55, 10);
    goto LAB165;

LAB163:    memcpy(t5, t47, 8);
    goto LAB165;

LAB169:    t10 = (t43 + 4);
    *((unsigned int *)t43) = 1;
    *((unsigned int *)t10) = 1;
    goto LAB170;

LAB171:    *((unsigned int *)t8) = 1;
    goto LAB174;

LAB173:    t24 = (t8 + 4);
    *((unsigned int *)t8) = 1;
    *((unsigned int *)t24) = 1;
    goto LAB174;

LAB175:    t31 = ((char*)((ng8)));
    goto LAB176;

LAB177:    t35 = ((char*)((ng3)));
    goto LAB178;

LAB179:    xsi_vlog_unsigned_bit_combine(t5, 1, t31, 1, t35, 1);
    goto LAB183;

LAB181:    memcpy(t5, t31, 8);
    goto LAB183;

LAB186:    t9 = (t43 + 4);
    *((unsigned int *)t43) = 1;
    *((unsigned int *)t9) = 1;
    goto LAB187;

LAB188:    *((unsigned int *)t8) = 1;
    goto LAB191;

LAB190:    t23 = (t8 + 4);
    *((unsigned int *)t8) = 1;
    *((unsigned int *)t23) = 1;
    goto LAB191;

LAB192:    t30 = (t0 + 2784U);
    t31 = *((char **)t30);
    memset(t55, 0, 8);
    t30 = (t31 + 4);
    t36 = *((unsigned int *)t30);
    t37 = (~(t36));
    t38 = *((unsigned int *)t31);
    t39 = (t38 & t37);
    t48 = (t39 & 1U);
    if (t48 != 0)
        goto LAB201;

LAB202:    if (*((unsigned int *)t30) != 0)
        goto LAB203;

LAB204:    t40 = (t55 + 4);
    t49 = *((unsigned int *)t55);
    t50 = *((unsigned int *)t40);
    t51 = (t49 || t50);
    if (t51 > 0)
        goto LAB205;

LAB206:    t52 = *((unsigned int *)t55);
    t53 = (~(t52));
    t54 = *((unsigned int *)t40);
    t56 = (t53 || t54);
    if (t56 > 0)
        goto LAB207;

LAB208:    if (*((unsigned int *)t40) > 0)
        goto LAB209;

LAB210:    if (*((unsigned int *)t55) > 0)
        goto LAB211;

LAB212:    memcpy(t47, t45, 8);

LAB213:    goto LAB193;

LAB194:    t41 = ((char*)((ng9)));
    goto LAB195;

LAB196:    xsi_vlog_unsigned_bit_combine(t5, 16, t47, 16, t41, 16);
    goto LAB200;

LAB198:    memcpy(t5, t47, 8);
    goto LAB200;

LAB201:    *((unsigned int *)t55) = 1;
    goto LAB204;

LAB203:    t35 = (t55 + 4);
    *((unsigned int *)t55) = 1;
    *((unsigned int *)t35) = 1;
    goto LAB204;

LAB205:    t41 = (t0 + 4064U);
    t44 = *((char **)t41);
    goto LAB206;

LAB207:    t41 = (t0 + 4224U);
    t45 = *((char **)t41);
    goto LAB208;

LAB209:    xsi_vlog_unsigned_bit_combine(t47, 16, t44, 16, t45, 16);
    goto LAB213;

LAB211:    memcpy(t47, t44, 8);
    goto LAB213;

LAB217:    t9 = (t43 + 4);
    *((unsigned int *)t43) = 1;
    *((unsigned int *)t9) = 1;
    goto LAB218;

LAB219:    *((unsigned int *)t8) = 1;
    goto LAB222;

LAB221:    t23 = (t8 + 4);
    *((unsigned int *)t8) = 1;
    *((unsigned int *)t23) = 1;
    goto LAB222;

LAB223:    t30 = (t0 + 3904U);
    t31 = *((char **)t30);
    goto LAB224;

LAB225:    t30 = ((char*)((ng9)));
    goto LAB226;

LAB227:    xsi_vlog_unsigned_bit_combine(t5, 16, t31, 16, t30, 16);
    goto LAB231;

LAB229:    memcpy(t5, t31, 8);
    goto LAB231;

LAB234:    t9 = (t43 + 4);
    *((unsigned int *)t43) = 1;
    *((unsigned int *)t9) = 1;
    goto LAB235;

LAB236:    *((unsigned int *)t8) = 1;
    goto LAB239;

LAB238:    t23 = (t8 + 4);
    *((unsigned int *)t8) = 1;
    *((unsigned int *)t23) = 1;
    goto LAB239;

LAB240:    t30 = ((char*)((ng8)));
    goto LAB241;

LAB242:    t31 = ((char*)((ng3)));
    goto LAB243;

LAB244:    xsi_vlog_unsigned_bit_combine(t5, 1, t30, 1, t31, 1);
    goto LAB248;

LAB246:    memcpy(t5, t30, 8);
    goto LAB248;

}

static void Always_566_1(char *t0)
{
    char t7[16];
    char t13[16];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t8;
    char *t9;
    char *t10;
    char *t11;
    char *t12;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    char *t19;
    char *t20;

LAB0:    t1 = (t0 + 8184U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(566, ng0);
    t2 = (t0 + 10256);
    *((int *)t2) = 1;
    t3 = (t0 + 8216);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(566, ng0);

LAB5:    xsi_set_current_line(567, ng0);
    t4 = (t0 + 7024);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    t8 = (t0 + 1824U);
    t9 = *((char **)t8);
    t8 = (t0 + 1664U);
    t10 = *((char **)t8);
    t8 = (t0 + 1504U);
    t11 = *((char **)t8);
    t8 = (t0 + 1344U);
    t12 = *((char **)t8);
    xsi_vlogtype_concat(t7, 64, 64, 4U, t12, 16, t11, 16, t10, 16, t9, 16);
    xsi_vlog_unsigned_not_equal(t13, 64, t6, 64, t7, 64);
    t8 = (t13 + 4);
    t14 = *((unsigned int *)t8);
    t15 = (~(t14));
    t16 = *((unsigned int *)t13);
    t17 = (t16 & t15);
    t18 = (t17 != 0);
    if (t18 > 0)
        goto LAB6;

LAB7:    xsi_set_current_line(571, ng0);

LAB10:    xsi_set_current_line(572, ng0);
    t2 = ((char*)((ng2)));
    t3 = (t0 + 6864);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 1);
    xsi_set_current_line(573, ng0);
    t2 = (t0 + 2464U);
    t3 = *((char **)t2);
    t2 = (t0 + 6544);
    xsi_vlogvar_wait_assign_value(t2, t3, 0, 0, 2, 0LL);

LAB8:    goto LAB2;

LAB6:    xsi_set_current_line(567, ng0);

LAB9:    xsi_set_current_line(568, ng0);
    t19 = ((char*)((ng8)));
    t20 = (t0 + 6864);
    xsi_vlogvar_assign_value(t20, t19, 0, 0, 1);
    xsi_set_current_line(569, ng0);
    t2 = ((char*)((ng2)));
    t3 = (t0 + 6544);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, 0, 2, 0LL);
    xsi_set_current_line(570, ng0);
    t2 = (t0 + 1824U);
    t3 = *((char **)t2);
    t2 = (t0 + 1664U);
    t4 = *((char **)t2);
    t2 = (t0 + 1504U);
    t5 = *((char **)t2);
    t2 = (t0 + 1344U);
    t6 = *((char **)t2);
    xsi_vlogtype_concat(t7, 64, 64, 4U, t6, 16, t5, 16, t4, 16, t3, 16);
    t2 = (t0 + 7024);
    xsi_vlogvar_wait_assign_value(t2, t7, 0, 0, 64, 0LL);
    goto LAB8;

}

static void Cont_577_2(char *t0)
{
    char t8[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;
    char *t9;
    char *t10;
    char *t11;
    char *t12;
    char *t13;
    unsigned int t14;
    unsigned int t15;
    char *t16;
    unsigned int t17;
    unsigned int t18;
    char *t19;
    unsigned int t20;
    unsigned int t21;
    char *t22;
    char *t23;
    char *t24;
    char *t25;
    char *t26;
    unsigned int t27;
    unsigned int t28;
    char *t29;
    unsigned int t30;
    unsigned int t31;
    char *t32;
    unsigned int t33;
    unsigned int t34;
    char *t35;

LAB0:    t1 = (t0 + 8432U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(577, ng0);
    t2 = (t0 + 5904);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t0 + 6064);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    memset(t8, 0, 8);
    xsi_vlog_unsigned_add(t8, 6, t4, 5, t7, 5);
    t9 = (t0 + 10512);
    t10 = (t9 + 56U);
    t11 = *((char **)t10);
    t12 = (t11 + 56U);
    t13 = *((char **)t12);
    memset(t13, 0, 8);
    t14 = 31U;
    t15 = t14;
    t16 = (t8 + 4);
    t17 = *((unsigned int *)t8);
    t14 = (t14 & t17);
    t18 = *((unsigned int *)t16);
    t15 = (t15 & t18);
    t19 = (t13 + 4);
    t20 = *((unsigned int *)t13);
    *((unsigned int *)t13) = (t20 | t14);
    t21 = *((unsigned int *)t19);
    *((unsigned int *)t19) = (t21 | t15);
    xsi_driver_vfirst_trans(t9, 0, 4);
    t22 = (t0 + 10448);
    t23 = (t22 + 56U);
    t24 = *((char **)t23);
    t25 = (t24 + 56U);
    t26 = *((char **)t25);
    memset(t26, 0, 8);
    t27 = 32U;
    t28 = t27;
    t29 = (t8 + 4);
    t30 = *((unsigned int *)t8);
    t27 = (t27 & t30);
    t31 = *((unsigned int *)t29);
    t28 = (t28 & t31);
    t27 = (t27 >> 5);
    t28 = (t28 >> 5);
    t32 = (t26 + 4);
    t33 = *((unsigned int *)t26);
    *((unsigned int *)t26) = (t33 | t27);
    t34 = *((unsigned int *)t32);
    *((unsigned int *)t32) = (t34 | t28);
    xsi_driver_vfirst_trans(t22, 0, 0);
    t35 = (t0 + 10272);
    *((int *)t35) = 1;

LAB1:    return;
}

static void Always_579_3(char *t0)
{
    char t4[8];
    char t9[8];
    char t10[8];
    char *t1;
    char *t2;
    char *t3;
    char *t5;
    char *t6;
    char *t7;
    char *t8;
    char *t11;

LAB0:    t1 = (t0 + 8680U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(579, ng0);
    t2 = (t0 + 10288);
    *((int *)t2) = 1;
    t3 = (t0 + 8712);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(579, ng0);

LAB5:    xsi_set_current_line(585, ng0);
    t5 = (t0 + 3104U);
    t6 = *((char **)t5);
    t5 = (t0 + 2624U);
    t7 = *((char **)t5);
    xsi_vlogtype_concat(t4, 32, 6, 2U, t7, 1, t6, 5);
    t5 = ((char*)((ng10)));
    t8 = ((char*)((ng11)));
    memset(t9, 0, 8);
    xsi_vlog_unsigned_minus(t9, 32, t5, 32, t8, 32);
    memset(t10, 0, 8);
    xsi_vlog_unsigned_minus(t10, 32, t4, 32, t9, 32);
    t11 = (t0 + 6704);
    xsi_vlogvar_assign_value(t11, t10, 0, 0, 5);
    goto LAB2;

}

static void Cont_588_4(char *t0)
{
    char t3[8];
    char t7[8];
    char t12[8];
    char *t1;
    char *t2;
    char *t4;
    char *t5;
    char *t6;
    char *t8;
    char *t9;
    char *t10;
    char *t11;
    char *t13;
    char *t14;
    char *t15;
    char *t16;
    char *t17;
    unsigned int t18;
    unsigned int t19;
    char *t20;
    unsigned int t21;
    unsigned int t22;
    char *t23;
    unsigned int t24;
    unsigned int t25;
    char *t26;

LAB0:    t1 = (t0 + 8928U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(588, ng0);
    t2 = (t0 + 6224);
    t4 = (t2 + 56U);
    t5 = *((char **)t4);
    t6 = ((char*)((ng8)));
    xsi_vlogtype_concat(t3, 22, 11, 2U, t6, 1, t5, 10);
    t8 = (t0 + 6384);
    t9 = (t8 + 56U);
    t10 = *((char **)t9);
    t11 = ((char*)((ng8)));
    xsi_vlogtype_concat(t7, 22, 11, 2U, t11, 1, t10, 10);
    memset(t12, 0, 8);
    xsi_vlog_unsigned_multiply(t12, 22, t3, 22, t7, 22);
    t13 = (t0 + 10576);
    t14 = (t13 + 56U);
    t15 = *((char **)t14);
    t16 = (t15 + 56U);
    t17 = *((char **)t16);
    memset(t17, 0, 8);
    t18 = 4194303U;
    t19 = t18;
    t20 = (t12 + 4);
    t21 = *((unsigned int *)t12);
    t18 = (t18 & t21);
    t22 = *((unsigned int *)t20);
    t19 = (t19 & t22);
    t23 = (t17 + 4);
    t24 = *((unsigned int *)t17);
    *((unsigned int *)t17) = (t24 | t18);
    t25 = *((unsigned int *)t23);
    *((unsigned int *)t23) = (t25 | t19);
    xsi_driver_vfirst_trans(t13, 0, 21);
    t26 = (t0 + 10304);
    *((int *)t26) = 1;

LAB1:    return;
}

static void implSig1_execute(char *t0)
{
    char t8[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;
    unsigned int t9;
    unsigned int t10;
    unsigned int t11;
    char *t12;
    char *t13;
    char *t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    unsigned int t20;
    unsigned int t21;
    char *t22;
    char *t23;
    char *t24;
    char *t25;
    char *t26;
    unsigned int t27;
    unsigned int t28;
    char *t29;
    unsigned int t30;
    unsigned int t31;
    char *t32;
    unsigned int t33;
    unsigned int t34;
    char *t35;

LAB0:    t1 = (t0 + 9176U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    t2 = (t0 + 5584);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t0 + 5744);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    t9 = *((unsigned int *)t4);
    t10 = *((unsigned int *)t7);
    t11 = (t9 ^ t10);
    *((unsigned int *)t8) = t11;
    t12 = (t4 + 4);
    t13 = (t7 + 4);
    t14 = (t8 + 4);
    t15 = *((unsigned int *)t12);
    t16 = *((unsigned int *)t13);
    t17 = (t15 | t16);
    *((unsigned int *)t14) = t17;
    t18 = *((unsigned int *)t14);
    t19 = (t18 != 0);
    if (t19 == 1)
        goto LAB4;

LAB5:
LAB6:    t22 = (t0 + 10640);
    t23 = (t22 + 56U);
    t24 = *((char **)t23);
    t25 = (t24 + 56U);
    t26 = *((char **)t25);
    memset(t26, 0, 8);
    t27 = 1U;
    t28 = t27;
    t29 = (t8 + 4);
    t30 = *((unsigned int *)t8);
    t27 = (t27 & t30);
    t31 = *((unsigned int *)t29);
    t28 = (t28 & t31);
    t32 = (t26 + 4);
    t33 = *((unsigned int *)t26);
    *((unsigned int *)t26) = (t33 | t27);
    t34 = *((unsigned int *)t32);
    *((unsigned int *)t32) = (t34 | t28);
    xsi_driver_vfirst_trans(t22, 0, 0);
    t35 = (t0 + 10320);
    *((int *)t35) = 1;

LAB1:    return;
LAB4:    t20 = *((unsigned int *)t8);
    t21 = *((unsigned int *)t14);
    *((unsigned int *)t8) = (t20 | t21);
    goto LAB6;

}

static void implSig2_execute(char *t0)
{
    char t8[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;
    unsigned int t9;
    unsigned int t10;
    unsigned int t11;
    char *t12;
    char *t13;
    char *t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    unsigned int t20;
    unsigned int t21;
    char *t22;
    char *t23;
    char *t24;
    char *t25;
    char *t26;
    unsigned int t27;
    unsigned int t28;
    char *t29;
    unsigned int t30;
    unsigned int t31;
    char *t32;
    unsigned int t33;
    unsigned int t34;
    char *t35;

LAB0:    t1 = (t0 + 9424U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    t2 = (t0 + 5584);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t0 + 5744);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    t9 = *((unsigned int *)t4);
    t10 = *((unsigned int *)t7);
    t11 = (t9 ^ t10);
    *((unsigned int *)t8) = t11;
    t12 = (t4 + 4);
    t13 = (t7 + 4);
    t14 = (t8 + 4);
    t15 = *((unsigned int *)t12);
    t16 = *((unsigned int *)t13);
    t17 = (t15 | t16);
    *((unsigned int *)t14) = t17;
    t18 = *((unsigned int *)t14);
    t19 = (t18 != 0);
    if (t19 == 1)
        goto LAB4;

LAB5:
LAB6:    t22 = (t0 + 10704);
    t23 = (t22 + 56U);
    t24 = *((char **)t23);
    t25 = (t24 + 56U);
    t26 = *((char **)t25);
    memset(t26, 0, 8);
    t27 = 1U;
    t28 = t27;
    t29 = (t8 + 4);
    t30 = *((unsigned int *)t8);
    t27 = (t27 & t30);
    t31 = *((unsigned int *)t29);
    t28 = (t28 & t31);
    t32 = (t26 + 4);
    t33 = *((unsigned int *)t26);
    *((unsigned int *)t26) = (t33 | t27);
    t34 = *((unsigned int *)t32);
    *((unsigned int *)t32) = (t34 | t28);
    xsi_driver_vfirst_trans(t22, 0, 0);
    t35 = (t0 + 10336);
    *((int *)t35) = 1;

LAB1:    return;
LAB4:    t20 = *((unsigned int *)t8);
    t21 = *((unsigned int *)t14);
    *((unsigned int *)t8) = (t20 | t21);
    goto LAB6;

}

static void implSig3_execute(char *t0)
{
    char t3[8];
    char t4[8];
    char *t1;
    char *t2;
    char *t5;
    char *t6;
    unsigned int t7;
    unsigned int t8;
    unsigned int t9;
    unsigned int t10;
    unsigned int t11;
    unsigned int t12;
    char *t13;
    char *t14;
    char *t15;
    char *t16;
    char *t17;
    char *t18;
    unsigned int t19;
    unsigned int t20;
    char *t21;
    unsigned int t22;
    unsigned int t23;
    char *t24;
    unsigned int t25;
    unsigned int t26;
    char *t27;

LAB0:    t1 = (t0 + 9672U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    t2 = (t0 + 4064U);
    t5 = *((char **)t2);
    memset(t4, 0, 8);
    t2 = (t4 + 4);
    t6 = (t5 + 4);
    t7 = *((unsigned int *)t5);
    t8 = (t7 >> 0);
    *((unsigned int *)t4) = t8;
    t9 = *((unsigned int *)t6);
    t10 = (t9 >> 0);
    *((unsigned int *)t2) = t10;
    t11 = *((unsigned int *)t4);
    *((unsigned int *)t4) = (t11 & 32767U);
    t12 = *((unsigned int *)t2);
    *((unsigned int *)t2) = (t12 & 32767U);
    t13 = ((char*)((ng2)));
    xsi_vlogtype_concat(t3, 16, 16, 2U, t13, 1, t4, 15);
    t14 = (t0 + 10768);
    t15 = (t14 + 56U);
    t16 = *((char **)t15);
    t17 = (t16 + 56U);
    t18 = *((char **)t17);
    memset(t18, 0, 8);
    t19 = 65535U;
    t20 = t19;
    t21 = (t3 + 4);
    t22 = *((unsigned int *)t3);
    t19 = (t19 & t22);
    t23 = *((unsigned int *)t21);
    t20 = (t20 & t23);
    t24 = (t18 + 4);
    t25 = *((unsigned int *)t18);
    *((unsigned int *)t18) = (t25 | t19);
    t26 = *((unsigned int *)t24);
    *((unsigned int *)t24) = (t26 | t20);
    xsi_driver_vfirst_trans(t14, 0, 15);
    t27 = (t0 + 10352);
    *((int *)t27) = 1;

LAB1:    return;
}

static void implSig4_execute(char *t0)
{
    char t3[8];
    char t4[8];
    char *t1;
    char *t2;
    char *t5;
    char *t6;
    unsigned int t7;
    unsigned int t8;
    unsigned int t9;
    unsigned int t10;
    unsigned int t11;
    unsigned int t12;
    char *t13;
    char *t14;
    char *t15;
    char *t16;
    char *t17;
    char *t18;
    unsigned int t19;
    unsigned int t20;
    char *t21;
    unsigned int t22;
    unsigned int t23;
    char *t24;
    unsigned int t25;
    unsigned int t26;
    char *t27;

LAB0:    t1 = (t0 + 9920U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    t2 = (t0 + 4224U);
    t5 = *((char **)t2);
    memset(t4, 0, 8);
    t2 = (t4 + 4);
    t6 = (t5 + 4);
    t7 = *((unsigned int *)t5);
    t8 = (t7 >> 0);
    *((unsigned int *)t4) = t8;
    t9 = *((unsigned int *)t6);
    t10 = (t9 >> 0);
    *((unsigned int *)t2) = t10;
    t11 = *((unsigned int *)t4);
    *((unsigned int *)t4) = (t11 & 32767U);
    t12 = *((unsigned int *)t2);
    *((unsigned int *)t2) = (t12 & 32767U);
    t13 = ((char*)((ng2)));
    xsi_vlogtype_concat(t3, 16, 16, 2U, t13, 1, t4, 15);
    t14 = (t0 + 10832);
    t15 = (t14 + 56U);
    t16 = *((char **)t15);
    t17 = (t16 + 56U);
    t18 = *((char **)t17);
    memset(t18, 0, 8);
    t19 = 65535U;
    t20 = t19;
    t21 = (t3 + 4);
    t22 = *((unsigned int *)t3);
    t19 = (t19 & t22);
    t23 = *((unsigned int *)t21);
    t20 = (t20 & t23);
    t24 = (t18 + 4);
    t25 = *((unsigned int *)t18);
    *((unsigned int *)t18) = (t25 | t19);
    t26 = *((unsigned int *)t24);
    *((unsigned int *)t24) = (t26 | t20);
    xsi_driver_vfirst_trans(t14, 0, 15);
    t27 = (t0 + 10368);
    *((int *)t27) = 1;

LAB1:    return;
}


extern void work_m_06580527304515993669_1459011339_init()
{
	static char *pe[] = {(void *)Always_527_0,(void *)Always_566_1,(void *)Cont_577_2,(void *)Always_579_3,(void *)Cont_588_4,(void *)implSig1_execute,(void *)implSig2_execute,(void *)implSig3_execute,(void *)implSig4_execute};
	xsi_register_didat("work_m_06580527304515993669_1459011339", "isim/ialutb_isim_beh.exe.sim/work/m_06580527304515993669_1459011339.didat");
	xsi_register_executes(pe);
}
