library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity TopModules_wrapper is
    Port ( clk         : in  STD_ULOGIC;
           rst         : in  STD_ULOGIC;
           a           : in  STD_ULOGIC_VECTOR(31 downto 0);
           b           : in  STD_ULOGIC_VECTOR(31 downto 0);
           funct       : in  STD_ULOGIC_VECTOR(4 downto 0);
           fmt         : in  STD_ULOGIC_VECTOR(1 downto 0);
           rm          : in  STD_ULOGIC_VECTOR(2 downto 0);
           stateCross  : out STD_ULOGIC_VECTOR(3 downto 0);
           result      : out STD_ULOGIC_VECTOR(31 downto 0);
           flag1       : out STD_ULOGIC;
           flag2       : out STD_ULOGIC
			  );
end TopModules_wrapper;

architecture Behavioral of TopModules_wrapper is
    component IALU
        port (
            clk         : in  std_ulogic;
            rst         : in  std_ulogic;
            a           : in  std_ulogic_vector(31 downto 0);
            b           : in  std_ulogic_vector(31 downto 0);
            funct       : in  std_ulogic_vector(4 downto 0);
            fmt         : in  std_ulogic_vector(1 downto 0);
            rm          : in  std_ulogic_vector(2 downto 0);
            stateCross  : out std_ulogic_vector(3 downto 0);
            result      : out std_ulogic_vector(31 downto 0);
            flag1       : out std_ulogic;
            flag2       : out std_ulogic;
            dual        : out std_ulogic
        );
    end component;

begin


    IALU_inst : IALU
        Port map (
            clk => clk,
            rst => rst,
            a   => a,
            b   => b,
            funct => funct,
            fmt => fmt,
            rm => rm,
            stateCross => stateCross,
            result => result,
            flag1 => flag1,
            flag2 => flag2
        );


end Behavioral;