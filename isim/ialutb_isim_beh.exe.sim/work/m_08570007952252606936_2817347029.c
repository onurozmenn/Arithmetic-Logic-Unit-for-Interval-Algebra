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
static unsigned int ng1[] = {0U, 0U};
static int ng2[] = {10, 0};
static int ng3[] = {0, 0};
static unsigned int ng4[] = {1U, 0U};
static int ng5[] = {1, 0};



static void Always_374_0(char *t0)
{
    char t6[8];
    char t7[8];
    char t43[8];
    char t47[8];
    char t61[8];
    char t101[8];
    char t105[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t8;
    unsigned int t9;
    unsigned int t10;
    unsigned int t11;
    unsigned int t12;
    unsigned int t13;
    unsigned int t14;
    char *t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    unsigned int t20;
    char *t21;
    char *t22;
    char *t23;
    unsigned int t24;
    unsigned int t25;
    unsigned int t26;
    unsigned int t27;
    unsigned int t28;
    unsigned int t29;
    unsigned int t30;
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
    char *t44;
    char *t45;
    char *t46;
    char *t48;
    char *t49;
    char *t50;
    char *t51;
    char *t52;
    char *t53;
    char *t54;
    unsigned int t55;
    unsigned int t56;
    unsigned int t57;
    unsigned int t58;
    unsigned int t59;
    unsigned int t60;
    unsigned int t62;
    unsigned int t63;
    unsigned int t64;
    char *t65;
    char *t66;
    char *t67;
    unsigned int t68;
    unsigned int t69;
    unsigned int t70;
    unsigned int t71;
    unsigned int t72;
    unsigned int t73;
    unsigned int t74;
    char *t75;
    char *t76;
    unsigned int t77;
    unsigned int t78;
    unsigned int t79;
    unsigned int t80;
    unsigned int t81;
    unsigned int t82;
    unsigned int t83;
    unsigned int t84;
    int t85;
    int t86;
    unsigned int t87;
    unsigned int t88;
    unsigned int t89;
    unsigned int t90;
    unsigned int t91;
    unsigned int t92;
    char *t93;
    unsigned int t94;
    unsigned int t95;
    unsigned int t96;
    unsigned int t97;
    unsigned int t98;
    char *t99;
    char *t100;
    char *t102;
    char *t103;
    char *t104;
    char *t106;

LAB0:    t1 = (t0 + 3640U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(374, ng0);
    t2 = (t0 + 3960);
    *((int *)t2) = 1;
    t3 = (t0 + 3672);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(374, ng0);

LAB5:    xsi_set_current_line(375, ng0);
    t4 = (t0 + 1208U);
    t5 = *((char **)t4);
    t4 = (t0 + 2728);
    xsi_vlogvar_assign_value(t4, t5, 0, 0, 12);
    xsi_set_current_line(376, ng0);
    t2 = ((char*)((ng1)));
    t3 = (t0 + 2568);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 1);
    xsi_set_current_line(377, ng0);
    t2 = (t0 + 1048U);
    t3 = *((char **)t2);
    t2 = (t0 + 1928);
    xsi_vlogvar_assign_value(t2, t3, 0, 0, 5);
    xsi_set_current_line(378, ng0);
    t2 = (t0 + 2728);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    memset(t7, 0, 8);
    t5 = (t7 + 4);
    t8 = (t4 + 4);
    t9 = *((unsigned int *)t4);
    t10 = (t9 >> 11);
    t11 = (t10 & 1);
    *((unsigned int *)t7) = t11;
    t12 = *((unsigned int *)t8);
    t13 = (t12 >> 11);
    t14 = (t13 & 1);
    *((unsigned int *)t5) = t14;
    memset(t6, 0, 8);
    t15 = (t7 + 4);
    t16 = *((unsigned int *)t15);
    t17 = (~(t16));
    t18 = *((unsigned int *)t7);
    t19 = (t18 & t17);
    t20 = (t19 & 1U);
    if (t20 != 0)
        goto LAB9;

LAB7:    if (*((unsigned int *)t15) == 0)
        goto LAB6;

LAB8:    t21 = (t6 + 4);
    *((unsigned int *)t6) = 1;
    *((unsigned int *)t21) = 1;

LAB9:    t22 = (t6 + 4);
    t23 = (t7 + 4);
    t24 = *((unsigned int *)t7);
    t25 = (~(t24));
    *((unsigned int *)t6) = t25;
    *((unsigned int *)t22) = 0;
    if (*((unsigned int *)t23) != 0)
        goto LAB11;

LAB10:    t30 = *((unsigned int *)t6);
    *((unsigned int *)t6) = (t30 & 1U);
    t31 = *((unsigned int *)t22);
    *((unsigned int *)t22) = (t31 & 1U);
    t32 = (t6 + 4);
    t33 = *((unsigned int *)t32);
    t34 = (~(t33));
    t35 = *((unsigned int *)t6);
    t36 = (t35 & t34);
    t37 = (t36 != 0);
    if (t37 > 0)
        goto LAB12;

LAB13:
LAB14:    xsi_set_current_line(389, ng0);
    t2 = (t0 + 2728);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    memset(t6, 0, 8);
    t5 = (t6 + 4);
    t8 = (t4 + 4);
    t9 = *((unsigned int *)t4);
    t10 = (t9 >> 0);
    t11 = (t10 & 1);
    *((unsigned int *)t6) = t11;
    t12 = *((unsigned int *)t8);
    t13 = (t12 >> 0);
    t14 = (t13 & 1);
    *((unsigned int *)t5) = t14;
    t15 = (t6 + 4);
    t16 = *((unsigned int *)t15);
    t17 = (~(t16));
    t18 = *((unsigned int *)t6);
    t19 = (t18 & t17);
    t20 = (t19 != 0);
    if (t20 > 0)
        goto LAB37;

LAB38:
LAB39:    xsi_set_current_line(393, ng0);
    t2 = (t0 + 2728);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    memset(t6, 0, 8);
    t5 = (t6 + 4);
    t8 = (t4 + 4);
    t9 = *((unsigned int *)t4);
    t10 = (t9 >> 1);
    *((unsigned int *)t6) = t10;
    t11 = *((unsigned int *)t8);
    t12 = (t11 >> 1);
    *((unsigned int *)t5) = t12;
    t13 = *((unsigned int *)t6);
    *((unsigned int *)t6) = (t13 & 1023U);
    t14 = *((unsigned int *)t5);
    *((unsigned int *)t5) = (t14 & 1023U);
    t15 = (t0 + 2088);
    xsi_vlogvar_assign_value(t15, t6, 0, 0, 10);
    xsi_set_current_line(394, ng0);
    t2 = (t0 + 2728);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    memset(t7, 0, 8);
    t5 = (t7 + 4);
    t8 = (t4 + 4);
    t9 = *((unsigned int *)t4);
    t10 = (t9 >> 11);
    t11 = (t10 & 1);
    *((unsigned int *)t7) = t11;
    t12 = *((unsigned int *)t8);
    t13 = (t12 >> 11);
    t14 = (t13 & 1);
    *((unsigned int *)t5) = t14;
    memset(t6, 0, 8);
    t15 = (t7 + 4);
    t16 = *((unsigned int *)t15);
    t17 = (~(t16));
    t18 = *((unsigned int *)t7);
    t19 = (t18 & t17);
    t20 = (t19 & 1U);
    if (t20 != 0)
        goto LAB44;

LAB42:    if (*((unsigned int *)t15) == 0)
        goto LAB41;

LAB43:    t21 = (t6 + 4);
    *((unsigned int *)t6) = 1;
    *((unsigned int *)t21) = 1;

LAB44:    t22 = (t6 + 4);
    t23 = (t7 + 4);
    t24 = *((unsigned int *)t7);
    t25 = (~(t24));
    *((unsigned int *)t6) = t25;
    *((unsigned int *)t22) = 0;
    if (*((unsigned int *)t23) != 0)
        goto LAB46;

LAB45:    t30 = *((unsigned int *)t6);
    *((unsigned int *)t6) = (t30 & 1U);
    t31 = *((unsigned int *)t22);
    *((unsigned int *)t22) = (t31 & 1U);
    t32 = (t6 + 4);
    t33 = *((unsigned int *)t32);
    t34 = (~(t33));
    t35 = *((unsigned int *)t6);
    t36 = (t35 & t34);
    t37 = (t36 != 0);
    if (t37 > 0)
        goto LAB47;

LAB48:
LAB49:    xsi_set_current_line(398, ng0);
    t2 = (t0 + 1368U);
    t3 = *((char **)t2);
    memset(t7, 0, 8);
    t2 = (t3 + 4);
    t9 = *((unsigned int *)t2);
    t10 = (~(t9));
    t11 = *((unsigned int *)t3);
    t12 = (t11 & t10);
    t13 = (t12 & 1U);
    if (t13 != 0)
        goto LAB51;

LAB52:    if (*((unsigned int *)t2) != 0)
        goto LAB53;

LAB54:    t5 = (t7 + 4);
    t14 = *((unsigned int *)t7);
    t16 = *((unsigned int *)t5);
    t17 = (t14 || t16);
    if (t17 > 0)
        goto LAB55;

LAB56:    t18 = *((unsigned int *)t7);
    t19 = (~(t18));
    t20 = *((unsigned int *)t5);
    t24 = (t19 || t20);
    if (t24 > 0)
        goto LAB57;

LAB58:    if (*((unsigned int *)t5) > 0)
        goto LAB59;

LAB60:    if (*((unsigned int *)t7) > 0)
        goto LAB61;

LAB62:    memcpy(t6, t15, 8);

LAB63:    t21 = (t0 + 1768);
    xsi_vlogvar_assign_value(t21, t6, 0, 0, 1);
    goto LAB2;

LAB6:    *((unsigned int *)t6) = 1;
    goto LAB9;

LAB11:    t26 = *((unsigned int *)t6);
    t27 = *((unsigned int *)t23);
    *((unsigned int *)t6) = (t26 | t27);
    t28 = *((unsigned int *)t22);
    t29 = *((unsigned int *)t23);
    *((unsigned int *)t22) = (t28 | t29);
    goto LAB10;

LAB12:    xsi_set_current_line(378, ng0);

LAB15:    xsi_set_current_line(379, ng0);
    xsi_set_current_line(379, ng0);
    t38 = ((char*)((ng2)));
    t39 = (t0 + 2248);
    xsi_vlogvar_assign_value(t39, t38, 0, 0, 32);

LAB16:    t2 = (t0 + 2248);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = ((char*)((ng3)));
    memset(t6, 0, 8);
    xsi_vlog_signed_greatereq(t6, 32, t4, 32, t5, 32);
    t8 = (t6 + 4);
    t9 = *((unsigned int *)t8);
    t10 = (~(t9));
    t11 = *((unsigned int *)t6);
    t12 = (t11 & t10);
    t13 = (t12 != 0);
    if (t13 > 0)
        goto LAB17;

LAB18:    xsi_set_current_line(385, ng0);
    t2 = (t0 + 2728);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t0 + 2408);
    t8 = (t5 + 56U);
    t15 = *((char **)t8);
    memset(t6, 0, 8);
    xsi_vlog_unsigned_lshift(t6, 12, t4, 12, t15, 32);
    t21 = (t0 + 2728);
    xsi_vlogvar_assign_value(t21, t6, 0, 0, 12);
    xsi_set_current_line(386, ng0);
    t2 = (t0 + 1048U);
    t3 = *((char **)t2);
    t2 = (t0 + 2408);
    t4 = (t2 + 56U);
    t5 = *((char **)t4);
    memset(t6, 0, 8);
    xsi_vlog_unsigned_minus(t6, 32, t3, 5, t5, 32);
    t8 = (t0 + 1928);
    xsi_vlogvar_assign_value(t8, t6, 0, 0, 5);
    goto LAB14;

LAB17:    xsi_set_current_line(379, ng0);

LAB19:    xsi_set_current_line(380, ng0);
    t15 = (t0 + 2728);
    t21 = (t15 + 56U);
    t22 = *((char **)t21);
    t23 = (t0 + 2728);
    t32 = (t23 + 72U);
    t38 = *((char **)t32);
    t39 = (t0 + 2248);
    t40 = (t39 + 56U);
    t41 = *((char **)t40);
    xsi_vlog_generic_get_index_select_value(t7, 1, t22, t38, 2, t41, 32, 1);
    t42 = ((char*)((ng4)));
    memset(t43, 0, 8);
    t44 = (t7 + 4);
    t45 = (t42 + 4);
    t14 = *((unsigned int *)t7);
    t16 = *((unsigned int *)t42);
    t17 = (t14 ^ t16);
    t18 = *((unsigned int *)t44);
    t19 = *((unsigned int *)t45);
    t20 = (t18 ^ t19);
    t24 = (t17 | t20);
    t25 = *((unsigned int *)t44);
    t26 = *((unsigned int *)t45);
    t27 = (t25 | t26);
    t28 = (~(t27));
    t29 = (t24 & t28);
    if (t29 != 0)
        goto LAB23;

LAB20:    if (t27 != 0)
        goto LAB22;

LAB21:    *((unsigned int *)t43) = 1;

LAB23:    t48 = (t0 + 2568);
    t49 = (t48 + 56U);
    t50 = *((char **)t49);
    memset(t47, 0, 8);
    t51 = (t50 + 4);
    t30 = *((unsigned int *)t51);
    t31 = (~(t30));
    t33 = *((unsigned int *)t50);
    t34 = (t33 & t31);
    t35 = (t34 & 1U);
    if (t35 != 0)
        goto LAB27;

LAB25:    if (*((unsigned int *)t51) == 0)
        goto LAB24;

LAB26:    t52 = (t47 + 4);
    *((unsigned int *)t47) = 1;
    *((unsigned int *)t52) = 1;

LAB27:    t53 = (t47 + 4);
    t54 = (t50 + 4);
    t36 = *((unsigned int *)t50);
    t37 = (~(t36));
    *((unsigned int *)t47) = t37;
    *((unsigned int *)t53) = 0;
    if (*((unsigned int *)t54) != 0)
        goto LAB29;

LAB28:    t59 = *((unsigned int *)t47);
    *((unsigned int *)t47) = (t59 & 1U);
    t60 = *((unsigned int *)t53);
    *((unsigned int *)t53) = (t60 & 1U);
    t62 = *((unsigned int *)t43);
    t63 = *((unsigned int *)t47);
    t64 = (t62 & t63);
    *((unsigned int *)t61) = t64;
    t65 = (t43 + 4);
    t66 = (t47 + 4);
    t67 = (t61 + 4);
    t68 = *((unsigned int *)t65);
    t69 = *((unsigned int *)t66);
    t70 = (t68 | t69);
    *((unsigned int *)t67) = t70;
    t71 = *((unsigned int *)t67);
    t72 = (t71 != 0);
    if (t72 == 1)
        goto LAB30;

LAB31:
LAB32:    t93 = (t61 + 4);
    t94 = *((unsigned int *)t93);
    t95 = (~(t94));
    t96 = *((unsigned int *)t61);
    t97 = (t96 & t95);
    t98 = (t97 != 0);
    if (t98 > 0)
        goto LAB33;

LAB34:
LAB35:    xsi_set_current_line(379, ng0);
    t2 = (t0 + 2248);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = ((char*)((ng5)));
    memset(t6, 0, 8);
    xsi_vlog_signed_minus(t6, 32, t4, 32, t5, 32);
    t8 = (t0 + 2248);
    xsi_vlogvar_assign_value(t8, t6, 0, 0, 32);
    goto LAB16;

LAB22:    t46 = (t43 + 4);
    *((unsigned int *)t43) = 1;
    *((unsigned int *)t46) = 1;
    goto LAB23;

LAB24:    *((unsigned int *)t47) = 1;
    goto LAB27;

LAB29:    t55 = *((unsigned int *)t47);
    t56 = *((unsigned int *)t54);
    *((unsigned int *)t47) = (t55 | t56);
    t57 = *((unsigned int *)t53);
    t58 = *((unsigned int *)t54);
    *((unsigned int *)t53) = (t57 | t58);
    goto LAB28;

LAB30:    t73 = *((unsigned int *)t61);
    t74 = *((unsigned int *)t67);
    *((unsigned int *)t61) = (t73 | t74);
    t75 = (t43 + 4);
    t76 = (t47 + 4);
    t77 = *((unsigned int *)t43);
    t78 = (~(t77));
    t79 = *((unsigned int *)t75);
    t80 = (~(t79));
    t81 = *((unsigned int *)t47);
    t82 = (~(t81));
    t83 = *((unsigned int *)t76);
    t84 = (~(t83));
    t85 = (t78 & t80);
    t86 = (t82 & t84);
    t87 = (~(t85));
    t88 = (~(t86));
    t89 = *((unsigned int *)t67);
    *((unsigned int *)t67) = (t89 & t87);
    t90 = *((unsigned int *)t67);
    *((unsigned int *)t67) = (t90 & t88);
    t91 = *((unsigned int *)t61);
    *((unsigned int *)t61) = (t91 & t87);
    t92 = *((unsigned int *)t61);
    *((unsigned int *)t61) = (t92 & t88);
    goto LAB32;

LAB33:    xsi_set_current_line(380, ng0);

LAB36:    xsi_set_current_line(381, ng0);
    t99 = ((char*)((ng2)));
    t100 = ((char*)((ng5)));
    memset(t101, 0, 8);
    xsi_vlog_signed_add(t101, 32, t99, 32, t100, 32);
    t102 = (t0 + 2248);
    t103 = (t102 + 56U);
    t104 = *((char **)t103);
    memset(t105, 0, 8);
    xsi_vlog_signed_minus(t105, 32, t101, 32, t104, 32);
    t106 = (t0 + 2408);
    xsi_vlogvar_assign_value(t106, t105, 0, 0, 32);
    xsi_set_current_line(382, ng0);
    t2 = ((char*)((ng4)));
    t3 = (t0 + 2568);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 1);
    goto LAB35;

LAB37:    xsi_set_current_line(389, ng0);

LAB40:    xsi_set_current_line(390, ng0);
    t21 = (t0 + 2728);
    t22 = (t21 + 56U);
    t23 = *((char **)t22);
    t32 = ((char*)((ng5)));
    memset(t7, 0, 8);
    xsi_vlog_unsigned_add(t7, 32, t23, 12, t32, 32);
    t38 = (t0 + 2728);
    xsi_vlogvar_assign_value(t38, t7, 0, 0, 12);
    goto LAB39;

LAB41:    *((unsigned int *)t6) = 1;
    goto LAB44;

LAB46:    t26 = *((unsigned int *)t6);
    t27 = *((unsigned int *)t23);
    *((unsigned int *)t6) = (t26 | t27);
    t28 = *((unsigned int *)t22);
    t29 = *((unsigned int *)t23);
    *((unsigned int *)t22) = (t28 | t29);
    goto LAB45;

LAB47:    xsi_set_current_line(394, ng0);

LAB50:    xsi_set_current_line(395, ng0);
    t38 = (t0 + 1928);
    t39 = (t38 + 56U);
    t40 = *((char **)t39);
    t41 = ((char*)((ng5)));
    memset(t43, 0, 8);
    xsi_vlog_unsigned_minus(t43, 32, t40, 5, t41, 32);
    t42 = (t0 + 1928);
    xsi_vlogvar_assign_value(t42, t43, 0, 0, 5);
    xsi_set_current_line(396, ng0);
    t2 = ((char*)((ng3)));
    t3 = (t0 + 2088);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 10);
    goto LAB49;

LAB51:    *((unsigned int *)t7) = 1;
    goto LAB54;

LAB53:    t4 = (t7 + 4);
    *((unsigned int *)t7) = 1;
    *((unsigned int *)t4) = 1;
    goto LAB54;

LAB55:    t8 = ((char*)((ng3)));
    goto LAB56;

LAB57:    t15 = ((char*)((ng5)));
    goto LAB58;

LAB59:    xsi_vlog_unsigned_bit_combine(t6, 32, t8, 32, t15, 32);
    goto LAB63;

LAB61:    memcpy(t6, t8, 8);
    goto LAB63;

}


extern void work_m_08570007952252606936_2817347029_init()
{
	static char *pe[] = {(void *)Always_374_0};
	xsi_register_didat("work_m_08570007952252606936_2817347029", "isim/ialutb_isim_beh.exe.sim/work/m_08570007952252606936_2817347029.didat");
	xsi_register_executes(pe);
}
