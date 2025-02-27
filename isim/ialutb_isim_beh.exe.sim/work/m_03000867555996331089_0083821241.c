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
static unsigned int ng2[] = {1U, 0U};
static unsigned int ng3[] = {4U, 0U};
static unsigned int ng4[] = {2U, 0U};
static unsigned int ng5[] = {208U, 0U};
static unsigned int ng6[] = {3U, 0U};
static unsigned int ng7[] = {80U, 0U};
static unsigned int ng8[] = {65U, 0U};
static unsigned int ng9[] = {5U, 0U};
static unsigned int ng10[] = {88U, 0U};
static unsigned int ng11[] = {6U, 0U};
static unsigned int ng12[] = {9U, 0U};
static unsigned int ng13[] = {7U, 0U};
static unsigned int ng14[] = {240U, 0U};
static unsigned int ng15[] = {8U, 0U};
static unsigned int ng16[] = {210U, 0U};
static unsigned int ng17[] = {64U, 0U};
static unsigned int ng18[] = {10U, 0U};
static unsigned int ng19[] = {192U, 0U};
static unsigned int ng20[] = {11U, 0U};
static unsigned int ng21[] = {193U, 0U};
static unsigned int ng22[] = {12U, 0U};
static unsigned int ng23[] = {72U, 0U};
static unsigned int ng24[] = {13U, 0U};
static unsigned int ng25[] = {14U, 0U};



static void Always_310_0(char *t0)
{
    char t7[8];
    char t40[8];
    char t73[8];
    char t110[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    unsigned int t8;
    unsigned int t9;
    unsigned int t10;
    char *t11;
    char *t12;
    unsigned int t13;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    char *t20;
    char *t21;
    unsigned int t22;
    unsigned int t23;
    unsigned int t24;
    unsigned int t25;
    unsigned int t26;
    unsigned int t27;
    unsigned int t28;
    unsigned int t29;
    int t30;
    int t31;
    unsigned int t32;
    unsigned int t33;
    unsigned int t34;
    unsigned int t35;
    unsigned int t36;
    unsigned int t37;
    char *t38;
    char *t39;
    unsigned int t41;
    unsigned int t42;
    unsigned int t43;
    char *t44;
    char *t45;
    unsigned int t46;
    unsigned int t47;
    unsigned int t48;
    unsigned int t49;
    unsigned int t50;
    unsigned int t51;
    unsigned int t52;
    char *t53;
    char *t54;
    unsigned int t55;
    unsigned int t56;
    unsigned int t57;
    unsigned int t58;
    unsigned int t59;
    unsigned int t60;
    unsigned int t61;
    unsigned int t62;
    int t63;
    int t64;
    unsigned int t65;
    unsigned int t66;
    unsigned int t67;
    unsigned int t68;
    unsigned int t69;
    unsigned int t70;
    char *t71;
    char *t72;
    unsigned int t74;
    unsigned int t75;
    unsigned int t76;
    char *t77;
    char *t78;
    unsigned int t79;
    unsigned int t80;
    unsigned int t81;
    unsigned int t82;
    unsigned int t83;
    unsigned int t84;
    unsigned int t85;
    char *t86;
    char *t87;
    unsigned int t88;
    unsigned int t89;
    unsigned int t90;
    unsigned int t91;
    unsigned int t92;
    unsigned int t93;
    unsigned int t94;
    unsigned int t95;
    int t96;
    int t97;
    unsigned int t98;
    unsigned int t99;
    unsigned int t100;
    unsigned int t101;
    unsigned int t102;
    unsigned int t103;
    char *t104;
    unsigned int t105;
    unsigned int t106;
    unsigned int t107;
    unsigned int t108;
    unsigned int t109;
    char *t111;
    char *t112;
    char *t113;
    char *t114;
    char *t115;
    char *t116;
    char *t117;
    char *t118;
    char *t119;
    int t120;
    char *t121;
    char *t122;

LAB0:    t1 = (t0 + 4760U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(310, ng0);
    t2 = (t0 + 5080);
    *((int *)t2) = 1;
    t3 = (t0 + 4792);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(310, ng0);

LAB5:    xsi_set_current_line(311, ng0);
    t4 = (t0 + 2968U);
    t5 = *((char **)t4);
    t4 = (t0 + 3128U);
    t6 = *((char **)t4);
    t8 = *((unsigned int *)t5);
    t9 = *((unsigned int *)t6);
    t10 = (t8 & t9);
    *((unsigned int *)t7) = t10;
    t4 = (t5 + 4);
    t11 = (t6 + 4);
    t12 = (t7 + 4);
    t13 = *((unsigned int *)t4);
    t14 = *((unsigned int *)t11);
    t15 = (t13 | t14);
    *((unsigned int *)t12) = t15;
    t16 = *((unsigned int *)t12);
    t17 = (t16 != 0);
    if (t17 == 1)
        goto LAB6;

LAB7:
LAB8:    t38 = (t0 + 3288U);
    t39 = *((char **)t38);
    t41 = *((unsigned int *)t7);
    t42 = *((unsigned int *)t39);
    t43 = (t41 & t42);
    *((unsigned int *)t40) = t43;
    t38 = (t7 + 4);
    t44 = (t39 + 4);
    t45 = (t40 + 4);
    t46 = *((unsigned int *)t38);
    t47 = *((unsigned int *)t44);
    t48 = (t46 | t47);
    *((unsigned int *)t45) = t48;
    t49 = *((unsigned int *)t45);
    t50 = (t49 != 0);
    if (t50 == 1)
        goto LAB9;

LAB10:
LAB11:    t71 = (t0 + 3448U);
    t72 = *((char **)t71);
    t74 = *((unsigned int *)t40);
    t75 = *((unsigned int *)t72);
    t76 = (t74 & t75);
    *((unsigned int *)t73) = t76;
    t71 = (t40 + 4);
    t77 = (t72 + 4);
    t78 = (t73 + 4);
    t79 = *((unsigned int *)t71);
    t80 = *((unsigned int *)t77);
    t81 = (t79 | t80);
    *((unsigned int *)t78) = t81;
    t82 = *((unsigned int *)t78);
    t83 = (t82 != 0);
    if (t83 == 1)
        goto LAB12;

LAB13:
LAB14:    t104 = (t73 + 4);
    t105 = *((unsigned int *)t104);
    t106 = (~(t105));
    t107 = *((unsigned int *)t73);
    t108 = (t107 & t106);
    t109 = (t108 != 0);
    if (t109 > 0)
        goto LAB15;

LAB16:    xsi_set_current_line(328, ng0);

LAB49:    xsi_set_current_line(329, ng0);
    t2 = ((char*)((ng25)));
    t3 = (t0 + 3848);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 4);

LAB17:    goto LAB2;

LAB6:    t18 = *((unsigned int *)t7);
    t19 = *((unsigned int *)t12);
    *((unsigned int *)t7) = (t18 | t19);
    t20 = (t5 + 4);
    t21 = (t6 + 4);
    t22 = *((unsigned int *)t5);
    t23 = (~(t22));
    t24 = *((unsigned int *)t20);
    t25 = (~(t24));
    t26 = *((unsigned int *)t6);
    t27 = (~(t26));
    t28 = *((unsigned int *)t21);
    t29 = (~(t28));
    t30 = (t23 & t25);
    t31 = (t27 & t29);
    t32 = (~(t30));
    t33 = (~(t31));
    t34 = *((unsigned int *)t12);
    *((unsigned int *)t12) = (t34 & t32);
    t35 = *((unsigned int *)t12);
    *((unsigned int *)t12) = (t35 & t33);
    t36 = *((unsigned int *)t7);
    *((unsigned int *)t7) = (t36 & t32);
    t37 = *((unsigned int *)t7);
    *((unsigned int *)t7) = (t37 & t33);
    goto LAB8;

LAB9:    t51 = *((unsigned int *)t40);
    t52 = *((unsigned int *)t45);
    *((unsigned int *)t40) = (t51 | t52);
    t53 = (t7 + 4);
    t54 = (t39 + 4);
    t55 = *((unsigned int *)t7);
    t56 = (~(t55));
    t57 = *((unsigned int *)t53);
    t58 = (~(t57));
    t59 = *((unsigned int *)t39);
    t60 = (~(t59));
    t61 = *((unsigned int *)t54);
    t62 = (~(t61));
    t63 = (t56 & t58);
    t64 = (t60 & t62);
    t65 = (~(t63));
    t66 = (~(t64));
    t67 = *((unsigned int *)t45);
    *((unsigned int *)t45) = (t67 & t65);
    t68 = *((unsigned int *)t45);
    *((unsigned int *)t45) = (t68 & t66);
    t69 = *((unsigned int *)t40);
    *((unsigned int *)t40) = (t69 & t65);
    t70 = *((unsigned int *)t40);
    *((unsigned int *)t40) = (t70 & t66);
    goto LAB11;

LAB12:    t84 = *((unsigned int *)t73);
    t85 = *((unsigned int *)t78);
    *((unsigned int *)t73) = (t84 | t85);
    t86 = (t40 + 4);
    t87 = (t72 + 4);
    t88 = *((unsigned int *)t40);
    t89 = (~(t88));
    t90 = *((unsigned int *)t86);
    t91 = (~(t90));
    t92 = *((unsigned int *)t72);
    t93 = (~(t92));
    t94 = *((unsigned int *)t87);
    t95 = (~(t94));
    t96 = (t89 & t91);
    t97 = (t93 & t95);
    t98 = (~(t96));
    t99 = (~(t97));
    t100 = *((unsigned int *)t78);
    *((unsigned int *)t78) = (t100 & t98);
    t101 = *((unsigned int *)t78);
    *((unsigned int *)t78) = (t101 & t99);
    t102 = *((unsigned int *)t73);
    *((unsigned int *)t73) = (t102 & t98);
    t103 = *((unsigned int *)t73);
    *((unsigned int *)t73) = (t103 & t99);
    goto LAB14;

LAB15:    xsi_set_current_line(311, ng0);

LAB18:    xsi_set_current_line(312, ng0);
    t111 = (t0 + 2808U);
    t112 = *((char **)t111);
    t111 = (t0 + 2648U);
    t113 = *((char **)t111);
    t111 = (t0 + 2488U);
    t114 = *((char **)t111);
    t111 = (t0 + 2328U);
    t115 = *((char **)t111);
    t111 = (t0 + 2168U);
    t116 = *((char **)t111);
    t111 = (t0 + 2008U);
    t117 = *((char **)t111);
    t111 = (t0 + 1848U);
    t118 = *((char **)t111);
    t111 = (t0 + 1688U);
    t119 = *((char **)t111);
    xsi_vlogtype_concat(t110, 8, 8, 8U, t119, 1, t118, 1, t117, 1, t116, 1, t115, 1, t114, 1, t113, 1, t112, 1);

LAB19:    t111 = ((char*)((ng1)));
    t120 = xsi_vlog_unsigned_case_compare(t110, 8, t111, 8);
    if (t120 == 1)
        goto LAB20;

LAB21:    t2 = ((char*)((ng3)));
    t30 = xsi_vlog_unsigned_case_compare(t110, 8, t2, 8);
    if (t30 == 1)
        goto LAB22;

LAB23:    t2 = ((char*)((ng5)));
    t30 = xsi_vlog_unsigned_case_compare(t110, 8, t2, 8);
    if (t30 == 1)
        goto LAB24;

LAB25:    t2 = ((char*)((ng7)));
    t30 = xsi_vlog_unsigned_case_compare(t110, 8, t2, 8);
    if (t30 == 1)
        goto LAB26;

LAB27:    t2 = ((char*)((ng8)));
    t30 = xsi_vlog_unsigned_case_compare(t110, 8, t2, 8);
    if (t30 == 1)
        goto LAB28;

LAB29:    t2 = ((char*)((ng10)));
    t30 = xsi_vlog_unsigned_case_compare(t110, 8, t2, 8);
    if (t30 == 1)
        goto LAB30;

LAB31:    t2 = ((char*)((ng12)));
    t30 = xsi_vlog_unsigned_case_compare(t110, 8, t2, 8);
    if (t30 == 1)
        goto LAB32;

LAB33:    t2 = ((char*)((ng14)));
    t30 = xsi_vlog_unsigned_case_compare(t110, 8, t2, 8);
    if (t30 == 1)
        goto LAB34;

LAB35:    t2 = ((char*)((ng16)));
    t30 = xsi_vlog_unsigned_case_compare(t110, 8, t2, 8);
    if (t30 == 1)
        goto LAB36;

LAB37:    t2 = ((char*)((ng17)));
    t30 = xsi_vlog_unsigned_case_compare(t110, 8, t2, 8);
    if (t30 == 1)
        goto LAB38;

LAB39:    t2 = ((char*)((ng19)));
    t30 = xsi_vlog_unsigned_case_compare(t110, 8, t2, 8);
    if (t30 == 1)
        goto LAB40;

LAB41:    t2 = ((char*)((ng21)));
    t30 = xsi_vlog_unsigned_case_compare(t110, 8, t2, 8);
    if (t30 == 1)
        goto LAB42;

LAB43:    t2 = ((char*)((ng23)));
    t30 = xsi_vlog_unsigned_case_compare(t110, 8, t2, 8);
    if (t30 == 1)
        goto LAB44;

LAB45:
LAB47:
LAB46:    xsi_set_current_line(326, ng0);
    t2 = ((char*)((ng1)));
    t3 = (t0 + 3848);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 4);

LAB48:    goto LAB17;

LAB20:    xsi_set_current_line(313, ng0);
    t121 = ((char*)((ng2)));
    t122 = (t0 + 3848);
    xsi_vlogvar_assign_value(t122, t121, 0, 0, 4);
    goto LAB48;

LAB22:    xsi_set_current_line(314, ng0);
    t3 = ((char*)((ng4)));
    t4 = (t0 + 3848);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 4);
    goto LAB48;

LAB24:    xsi_set_current_line(315, ng0);
    t3 = ((char*)((ng6)));
    t4 = (t0 + 3848);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 4);
    goto LAB48;

LAB26:    xsi_set_current_line(316, ng0);
    t3 = ((char*)((ng3)));
    t4 = (t0 + 3848);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 4);
    goto LAB48;

LAB28:    xsi_set_current_line(317, ng0);
    t3 = ((char*)((ng9)));
    t4 = (t0 + 3848);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 4);
    goto LAB48;

LAB30:    xsi_set_current_line(318, ng0);
    t3 = ((char*)((ng11)));
    t4 = (t0 + 3848);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 4);
    goto LAB48;

LAB32:    xsi_set_current_line(319, ng0);
    t3 = ((char*)((ng13)));
    t4 = (t0 + 3848);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 4);
    goto LAB48;

LAB34:    xsi_set_current_line(320, ng0);
    t3 = ((char*)((ng15)));
    t4 = (t0 + 3848);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 4);
    goto LAB48;

LAB36:    xsi_set_current_line(321, ng0);
    t3 = ((char*)((ng12)));
    t4 = (t0 + 3848);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 4);
    goto LAB48;

LAB38:    xsi_set_current_line(322, ng0);
    t3 = ((char*)((ng18)));
    t4 = (t0 + 3848);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 4);
    goto LAB48;

LAB40:    xsi_set_current_line(323, ng0);
    t3 = ((char*)((ng20)));
    t4 = (t0 + 3848);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 4);
    goto LAB48;

LAB42:    xsi_set_current_line(324, ng0);
    t3 = ((char*)((ng22)));
    t4 = (t0 + 3848);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 4);
    goto LAB48;

LAB44:    xsi_set_current_line(325, ng0);
    t3 = ((char*)((ng24)));
    t4 = (t0 + 3848);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 4);
    goto LAB48;

}


extern void work_m_03000867555996331089_0083821241_init()
{
	static char *pe[] = {(void *)Always_310_0};
	xsi_register_didat("work_m_03000867555996331089_0083821241", "isim/ialutb_isim_beh.exe.sim/work/m_03000867555996331089_0083821241.didat");
	xsi_register_executes(pe);
}
