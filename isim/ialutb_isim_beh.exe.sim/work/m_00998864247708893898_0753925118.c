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
static const char *ng1 = "Sonu 0 iaret yok";



static void Always_411_0(char *t0)
{
    char t4[8];
    char t29[8];
    char t33[8];
    char *t1;
    char *t2;
    char *t3;
    char *t5;
    char *t6;
    unsigned int t7;
    unsigned int t8;
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
    unsigned int t22;
    char *t23;
    unsigned int t24;
    unsigned int t25;
    unsigned int t26;
    unsigned int t27;
    unsigned int t28;
    char *t30;
    char *t31;
    char *t32;
    unsigned int t34;
    unsigned int t35;
    unsigned int t36;
    char *t37;
    char *t38;
    unsigned int t39;
    unsigned int t40;
    unsigned int t41;
    unsigned int t42;
    unsigned int t43;
    unsigned int t44;
    unsigned int t45;
    char *t46;
    unsigned int t47;
    unsigned int t48;
    unsigned int t49;
    unsigned int t50;
    unsigned int t51;
    char *t52;
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
    char *t63;
    unsigned int t64;
    unsigned int t65;
    unsigned int t66;
    unsigned int t67;
    unsigned int t68;
    char *t69;
    char *t70;

LAB0:    t1 = (t0 + 3000U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(411, ng0);
    t2 = (t0 + 3320);
    *((int *)t2) = 1;
    t3 = (t0 + 3032);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(412, ng0);

LAB5:    xsi_set_current_line(414, ng0);
    t5 = (t0 + 1688U);
    t6 = *((char **)t5);
    memset(t4, 0, 8);
    t5 = (t6 + 4);
    t7 = *((unsigned int *)t5);
    t8 = (~(t7));
    t9 = *((unsigned int *)t6);
    t10 = (t9 & t8);
    t11 = (t10 & 1U);
    if (t11 != 0)
        goto LAB9;

LAB7:    if (*((unsigned int *)t5) == 0)
        goto LAB6;

LAB8:    t12 = (t4 + 4);
    *((unsigned int *)t4) = 1;
    *((unsigned int *)t12) = 1;

LAB9:    t13 = (t4 + 4);
    t14 = (t6 + 4);
    t15 = *((unsigned int *)t6);
    t16 = (~(t15));
    *((unsigned int *)t4) = t16;
    *((unsigned int *)t13) = 0;
    if (*((unsigned int *)t14) != 0)
        goto LAB11;

LAB10:    t21 = *((unsigned int *)t4);
    *((unsigned int *)t4) = (t21 & 1U);
    t22 = *((unsigned int *)t13);
    *((unsigned int *)t13) = (t22 & 1U);
    t23 = (t4 + 4);
    t24 = *((unsigned int *)t23);
    t25 = (~(t24));
    t26 = *((unsigned int *)t4);
    t27 = (t26 & t25);
    t28 = (t27 != 0);
    if (t28 > 0)
        goto LAB12;

LAB13:    xsi_set_current_line(439, ng0);
    t2 = (t0 + 1688U);
    t3 = *((char **)t2);
    t2 = (t3 + 4);
    t7 = *((unsigned int *)t2);
    t8 = (~(t7));
    t9 = *((unsigned int *)t3);
    t10 = (t9 & t8);
    t11 = (t10 != 0);
    if (t11 > 0)
        goto LAB55;

LAB56:
LAB57:
LAB14:    goto LAB2;

LAB6:    *((unsigned int *)t4) = 1;
    goto LAB9;

LAB11:    t17 = *((unsigned int *)t4);
    t18 = *((unsigned int *)t14);
    *((unsigned int *)t4) = (t17 | t18);
    t19 = *((unsigned int *)t13);
    t20 = *((unsigned int *)t14);
    *((unsigned int *)t13) = (t19 | t20);
    goto LAB10;

LAB12:    xsi_set_current_line(414, ng0);

LAB15:    xsi_set_current_line(415, ng0);
    t30 = (t0 + 1368U);
    t31 = *((char **)t30);
    t30 = (t0 + 1528U);
    t32 = *((char **)t30);
    t34 = *((unsigned int *)t31);
    t35 = *((unsigned int *)t32);
    t36 = (t34 ^ t35);
    *((unsigned int *)t33) = t36;
    t30 = (t31 + 4);
    t37 = (t32 + 4);
    t38 = (t33 + 4);
    t39 = *((unsigned int *)t30);
    t40 = *((unsigned int *)t37);
    t41 = (t39 | t40);
    *((unsigned int *)t38) = t41;
    t42 = *((unsigned int *)t38);
    t43 = (t42 != 0);
    if (t43 == 1)
        goto LAB16;

LAB17:
LAB18:    memset(t29, 0, 8);
    t46 = (t33 + 4);
    t47 = *((unsigned int *)t46);
    t48 = (~(t47));
    t49 = *((unsigned int *)t33);
    t50 = (t49 & t48);
    t51 = (t50 & 1U);
    if (t51 != 0)
        goto LAB22;

LAB20:    if (*((unsigned int *)t46) == 0)
        goto LAB19;

LAB21:    t52 = (t29 + 4);
    *((unsigned int *)t29) = 1;
    *((unsigned int *)t52) = 1;

LAB22:    t53 = (t29 + 4);
    t54 = (t33 + 4);
    t55 = *((unsigned int *)t33);
    t56 = (~(t55));
    *((unsigned int *)t29) = t56;
    *((unsigned int *)t53) = 0;
    if (*((unsigned int *)t54) != 0)
        goto LAB24;

LAB23:    t61 = *((unsigned int *)t29);
    *((unsigned int *)t29) = (t61 & 1U);
    t62 = *((unsigned int *)t53);
    *((unsigned int *)t53) = (t62 & 1U);
    t63 = (t29 + 4);
    t64 = *((unsigned int *)t63);
    t65 = (~(t64));
    t66 = *((unsigned int *)t29);
    t67 = (t66 & t65);
    t68 = (t67 != 0);
    if (t68 > 0)
        goto LAB25;

LAB26:    xsi_set_current_line(417, ng0);
    t2 = (t0 + 1368U);
    t3 = *((char **)t2);
    t2 = (t0 + 1528U);
    t5 = *((char **)t2);
    t7 = *((unsigned int *)t3);
    t8 = *((unsigned int *)t5);
    t9 = (t7 ^ t8);
    *((unsigned int *)t4) = t9;
    t2 = (t3 + 4);
    t6 = (t5 + 4);
    t12 = (t4 + 4);
    t10 = *((unsigned int *)t2);
    t11 = *((unsigned int *)t6);
    t15 = (t10 | t11);
    *((unsigned int *)t12) = t15;
    t16 = *((unsigned int *)t12);
    t17 = (t16 != 0);
    if (t17 == 1)
        goto LAB29;

LAB30:
LAB31:    t13 = (t4 + 4);
    t20 = *((unsigned int *)t13);
    t21 = (~(t20));
    t22 = *((unsigned int *)t4);
    t24 = (t22 & t21);
    t25 = (t24 != 0);
    if (t25 > 0)
        goto LAB32;

LAB33:
LAB34:
LAB27:    goto LAB14;

LAB16:    t44 = *((unsigned int *)t33);
    t45 = *((unsigned int *)t38);
    *((unsigned int *)t33) = (t44 | t45);
    goto LAB18;

LAB19:    *((unsigned int *)t29) = 1;
    goto LAB22;

LAB24:    t57 = *((unsigned int *)t29);
    t58 = *((unsigned int *)t54);
    *((unsigned int *)t29) = (t57 | t58);
    t59 = *((unsigned int *)t53);
    t60 = *((unsigned int *)t54);
    *((unsigned int *)t53) = (t59 | t60);
    goto LAB23;

LAB25:    xsi_set_current_line(415, ng0);

LAB28:    xsi_set_current_line(416, ng0);
    t69 = (t0 + 1368U);
    t70 = *((char **)t69);
    t69 = (t0 + 2088);
    xsi_vlogvar_assign_value(t69, t70, 0, 0, 1);
    goto LAB27;

LAB29:    t18 = *((unsigned int *)t4);
    t19 = *((unsigned int *)t12);
    *((unsigned int *)t4) = (t18 | t19);
    goto LAB31;

LAB32:    xsi_set_current_line(417, ng0);

LAB35:    xsi_set_current_line(418, ng0);
    t14 = (t0 + 1048U);
    t23 = *((char **)t14);
    t14 = (t0 + 1208U);
    t30 = *((char **)t14);
    memset(t29, 0, 8);
    t14 = (t23 + 4);
    if (*((unsigned int *)t14) != 0)
        goto LAB37;

LAB36:    t31 = (t30 + 4);
    if (*((unsigned int *)t31) != 0)
        goto LAB37;

LAB40:    if (*((unsigned int *)t23) > *((unsigned int *)t30))
        goto LAB38;

LAB39:    t37 = (t29 + 4);
    t26 = *((unsigned int *)t37);
    t27 = (~(t26));
    t28 = *((unsigned int *)t29);
    t34 = (t28 & t27);
    t35 = (t34 != 0);
    if (t35 > 0)
        goto LAB41;

LAB42:    xsi_set_current_line(420, ng0);
    t2 = (t0 + 1048U);
    t3 = *((char **)t2);
    t2 = (t0 + 1208U);
    t5 = *((char **)t2);
    memset(t4, 0, 8);
    t2 = (t3 + 4);
    if (*((unsigned int *)t2) != 0)
        goto LAB46;

LAB45:    t6 = (t5 + 4);
    if (*((unsigned int *)t6) != 0)
        goto LAB46;

LAB49:    if (*((unsigned int *)t3) < *((unsigned int *)t5))
        goto LAB47;

LAB48:    t13 = (t4 + 4);
    t7 = *((unsigned int *)t13);
    t8 = (~(t7));
    t9 = *((unsigned int *)t4);
    t10 = (t9 & t8);
    t11 = (t10 != 0);
    if (t11 > 0)
        goto LAB50;

LAB51:    xsi_set_current_line(422, ng0);

LAB54:    xsi_set_current_line(434, ng0);
    xsi_vlogfile_write(1, 0, 0, ng1, 1, t0);

LAB52:
LAB43:    goto LAB34;

LAB37:    t32 = (t29 + 4);
    *((unsigned int *)t29) = 1;
    *((unsigned int *)t32) = 1;
    goto LAB39;

LAB38:    *((unsigned int *)t29) = 1;
    goto LAB39;

LAB41:    xsi_set_current_line(418, ng0);

LAB44:    xsi_set_current_line(419, ng0);
    t38 = (t0 + 1368U);
    t46 = *((char **)t38);
    t38 = (t0 + 2088);
    xsi_vlogvar_assign_value(t38, t46, 0, 0, 1);
    goto LAB43;

LAB46:    t12 = (t4 + 4);
    *((unsigned int *)t4) = 1;
    *((unsigned int *)t12) = 1;
    goto LAB48;

LAB47:    *((unsigned int *)t4) = 1;
    goto LAB48;

LAB50:    xsi_set_current_line(420, ng0);

LAB53:    xsi_set_current_line(421, ng0);
    t14 = (t0 + 1528U);
    t23 = *((char **)t14);
    t14 = (t0 + 2088);
    xsi_vlogvar_assign_value(t14, t23, 0, 0, 1);
    goto LAB52;

LAB55:    xsi_set_current_line(439, ng0);

LAB58:    xsi_set_current_line(441, ng0);
    t5 = (t0 + 1368U);
    t6 = *((char **)t5);
    t5 = (t0 + 1528U);
    t12 = *((char **)t5);
    t15 = *((unsigned int *)t6);
    t16 = *((unsigned int *)t12);
    t17 = (t15 ^ t16);
    *((unsigned int *)t4) = t17;
    t5 = (t6 + 4);
    t13 = (t12 + 4);
    t14 = (t4 + 4);
    t18 = *((unsigned int *)t5);
    t19 = *((unsigned int *)t13);
    t20 = (t18 | t19);
    *((unsigned int *)t14) = t20;
    t21 = *((unsigned int *)t14);
    t22 = (t21 != 0);
    if (t22 == 1)
        goto LAB59;

LAB60:
LAB61:    t23 = (t4 + 4);
    t26 = *((unsigned int *)t23);
    t27 = (~(t26));
    t28 = *((unsigned int *)t4);
    t34 = (t28 & t27);
    t35 = (t34 != 0);
    if (t35 > 0)
        goto LAB62;

LAB63:    xsi_set_current_line(444, ng0);
    t2 = (t0 + 1368U);
    t3 = *((char **)t2);
    t2 = (t0 + 1528U);
    t5 = *((char **)t2);
    t7 = *((unsigned int *)t3);
    t8 = *((unsigned int *)t5);
    t9 = (t7 ^ t8);
    *((unsigned int *)t29) = t9;
    t2 = (t3 + 4);
    t6 = (t5 + 4);
    t12 = (t29 + 4);
    t10 = *((unsigned int *)t2);
    t11 = *((unsigned int *)t6);
    t15 = (t10 | t11);
    *((unsigned int *)t12) = t15;
    t16 = *((unsigned int *)t12);
    t17 = (t16 != 0);
    if (t17 == 1)
        goto LAB66;

LAB67:
LAB68:    memset(t4, 0, 8);
    t13 = (t29 + 4);
    t20 = *((unsigned int *)t13);
    t21 = (~(t20));
    t22 = *((unsigned int *)t29);
    t24 = (t22 & t21);
    t25 = (t24 & 1U);
    if (t25 != 0)
        goto LAB72;

LAB70:    if (*((unsigned int *)t13) == 0)
        goto LAB69;

LAB71:    t14 = (t4 + 4);
    *((unsigned int *)t4) = 1;
    *((unsigned int *)t14) = 1;

LAB72:    t23 = (t4 + 4);
    t30 = (t29 + 4);
    t26 = *((unsigned int *)t29);
    t27 = (~(t26));
    *((unsigned int *)t4) = t27;
    *((unsigned int *)t23) = 0;
    if (*((unsigned int *)t30) != 0)
        goto LAB74;

LAB73:    t39 = *((unsigned int *)t4);
    *((unsigned int *)t4) = (t39 & 1U);
    t40 = *((unsigned int *)t23);
    *((unsigned int *)t23) = (t40 & 1U);
    t31 = (t4 + 4);
    t41 = *((unsigned int *)t31);
    t42 = (~(t41));
    t43 = *((unsigned int *)t4);
    t44 = (t43 & t42);
    t45 = (t44 != 0);
    if (t45 > 0)
        goto LAB75;

LAB76:
LAB77:
LAB64:    goto LAB57;

LAB59:    t24 = *((unsigned int *)t4);
    t25 = *((unsigned int *)t14);
    *((unsigned int *)t4) = (t24 | t25);
    goto LAB61;

LAB62:    xsi_set_current_line(441, ng0);

LAB65:    xsi_set_current_line(442, ng0);
    t30 = (t0 + 1368U);
    t31 = *((char **)t30);
    t30 = (t0 + 2088);
    xsi_vlogvar_assign_value(t30, t31, 0, 0, 1);
    goto LAB64;

LAB66:    t18 = *((unsigned int *)t29);
    t19 = *((unsigned int *)t12);
    *((unsigned int *)t29) = (t18 | t19);
    goto LAB68;

LAB69:    *((unsigned int *)t4) = 1;
    goto LAB72;

LAB74:    t28 = *((unsigned int *)t4);
    t34 = *((unsigned int *)t30);
    *((unsigned int *)t4) = (t28 | t34);
    t35 = *((unsigned int *)t23);
    t36 = *((unsigned int *)t30);
    *((unsigned int *)t23) = (t35 | t36);
    goto LAB73;

LAB75:    xsi_set_current_line(444, ng0);

LAB78:    xsi_set_current_line(446, ng0);
    t32 = (t0 + 1048U);
    t37 = *((char **)t32);
    t32 = (t0 + 1208U);
    t38 = *((char **)t32);
    memset(t33, 0, 8);
    t32 = (t37 + 4);
    if (*((unsigned int *)t32) != 0)
        goto LAB80;

LAB79:    t46 = (t38 + 4);
    if (*((unsigned int *)t46) != 0)
        goto LAB80;

LAB83:    if (*((unsigned int *)t37) > *((unsigned int *)t38))
        goto LAB81;

LAB82:    t53 = (t33 + 4);
    t47 = *((unsigned int *)t53);
    t48 = (~(t47));
    t49 = *((unsigned int *)t33);
    t50 = (t49 & t48);
    t51 = (t50 != 0);
    if (t51 > 0)
        goto LAB84;

LAB85:    xsi_set_current_line(449, ng0);
    t2 = (t0 + 1048U);
    t3 = *((char **)t2);
    t2 = (t0 + 1208U);
    t5 = *((char **)t2);
    memset(t4, 0, 8);
    t2 = (t3 + 4);
    if (*((unsigned int *)t2) != 0)
        goto LAB89;

LAB88:    t6 = (t5 + 4);
    if (*((unsigned int *)t6) != 0)
        goto LAB89;

LAB92:    if (*((unsigned int *)t3) < *((unsigned int *)t5))
        goto LAB90;

LAB91:    t13 = (t4 + 4);
    t7 = *((unsigned int *)t13);
    t8 = (~(t7));
    t9 = *((unsigned int *)t4);
    t10 = (t9 & t8);
    t11 = (t10 != 0);
    if (t11 > 0)
        goto LAB93;

LAB94:    xsi_set_current_line(452, ng0);

LAB103:    xsi_set_current_line(464, ng0);
    xsi_vlogfile_write(1, 0, 0, ng1, 1, t0);

LAB95:
LAB86:    goto LAB77;

LAB80:    t52 = (t33 + 4);
    *((unsigned int *)t33) = 1;
    *((unsigned int *)t52) = 1;
    goto LAB82;

LAB81:    *((unsigned int *)t33) = 1;
    goto LAB82;

LAB84:    xsi_set_current_line(446, ng0);

LAB87:    xsi_set_current_line(447, ng0);
    t54 = (t0 + 1368U);
    t63 = *((char **)t54);
    t54 = (t0 + 2088);
    xsi_vlogvar_assign_value(t54, t63, 0, 0, 1);
    goto LAB86;

LAB89:    t12 = (t4 + 4);
    *((unsigned int *)t4) = 1;
    *((unsigned int *)t12) = 1;
    goto LAB91;

LAB90:    *((unsigned int *)t4) = 1;
    goto LAB91;

LAB93:    xsi_set_current_line(449, ng0);

LAB96:    xsi_set_current_line(450, ng0);
    t14 = (t0 + 1368U);
    t23 = *((char **)t14);
    memset(t29, 0, 8);
    t14 = (t23 + 4);
    t15 = *((unsigned int *)t14);
    t16 = (~(t15));
    t17 = *((unsigned int *)t23);
    t18 = (t17 & t16);
    t19 = (t18 & 1U);
    if (t19 != 0)
        goto LAB100;

LAB98:    if (*((unsigned int *)t14) == 0)
        goto LAB97;

LAB99:    t30 = (t29 + 4);
    *((unsigned int *)t29) = 1;
    *((unsigned int *)t30) = 1;

LAB100:    t31 = (t29 + 4);
    t32 = (t23 + 4);
    t20 = *((unsigned int *)t23);
    t21 = (~(t20));
    *((unsigned int *)t29) = t21;
    *((unsigned int *)t31) = 0;
    if (*((unsigned int *)t32) != 0)
        goto LAB102;

LAB101:    t27 = *((unsigned int *)t29);
    *((unsigned int *)t29) = (t27 & 1U);
    t28 = *((unsigned int *)t31);
    *((unsigned int *)t31) = (t28 & 1U);
    t37 = (t0 + 2088);
    xsi_vlogvar_assign_value(t37, t29, 0, 0, 1);
    goto LAB95;

LAB97:    *((unsigned int *)t29) = 1;
    goto LAB100;

LAB102:    t22 = *((unsigned int *)t29);
    t24 = *((unsigned int *)t32);
    *((unsigned int *)t29) = (t22 | t24);
    t25 = *((unsigned int *)t31);
    t26 = *((unsigned int *)t32);
    *((unsigned int *)t31) = (t25 | t26);
    goto LAB101;

}


extern void work_m_00998864247708893898_0753925118_init()
{
	static char *pe[] = {(void *)Always_411_0};
	xsi_register_didat("work_m_00998864247708893898_0753925118", "isim/ialutb_isim_beh.exe.sim/work/m_00998864247708893898_0753925118.didat");
	xsi_register_executes(pe);
}
