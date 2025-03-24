-- ================================================================================ --
-- NEORV32 CPU - Co-Processor: Custom (RISC-V Instructions) Functions Unit (CFU)    --
-- -------------------------------------------------------------------------------- --
-- For custom/user-defined RISC-V instructions. See the CPU's documentation for     --
-- more information. Also take a look at the "software-counterpart" of this default --
-- CFU hardware example in 'sw/example/demo_cfu'.                                   --
-- -------------------------------------------------------------------------------- --
-- The NEORV32 RISC-V Processor - https://github.com/stnolting/neorv32              --
-- Copyright (c) NEORV32 contributors.                                              --
-- Copyright (c) 2020 - 2024 Stephan Nolting. All rights reserved.                  --
-- Licensed under the BSD-3-Clause license, see LICENSE for details.                --
-- SPDX-License-Identifier: BSD-3-Clause                                            --
-- ================================================================================ --

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

library neorv32;
use neorv32.neorv32_package.all;
entity neorv32_cpu_cp_cfu is
  port (
    -- global control --
    clk_i       : in  std_ulogic; -- global clock, rising edge
    rstn_i      : in  std_ulogic; -- global reset, low-active, async
    -- operation control --
    start_i     : in std_ulogic; -- operation trigger/strobe
    active_i    : in std_ulogic; -- operation in progress, CPU is waiting for CFU
    -- CSR interface --
    csr_we_i    : in  std_ulogic; -- write enable
    csr_addr_i  : in  std_ulogic_vector(1 downto 0); -- address (CSR address 0x800 to 0x803)
    csr_wdata_i : in  std_ulogic_vector(31 downto 0); -- write data
    csr_rdata_o : out std_ulogic_vector(31 downto 0); -- read data
    -- operands (form/via custom instruction word) --
    rtype_i     : in std_ulogic; -- instruction type (R3-type or R4-type); from instruction word's "opcode[5]" bit
    funct3_i    : in std_ulogic_vector(2 downto 0); -- "funct3" bit-field from custom instruction word
    funct7_i    : in std_ulogic_vector(6 downto 0); -- "funct7" bit-field from custom instruction word
    rs1_i       : in  std_ulogic_vector(31 downto 0); -- rf source 1 via "rs1" bit-field from custom instruction word
    rs2_i       : in  std_ulogic_vector(31 downto 0); -- rf source 2 via "rs2" bit-field from custom instruction word
    rs3_i       : in  std_ulogic_vector(31 downto 0); -- rf source 3 via "rs3" bit-field from custom instruction word
    -- result and status --
    result_o    : out std_ulogic_vector(31 downto 0); -- operation result
    valid_o     : out std_ulogic -- result valid, operation done; set one cycle before result_o is valid
  );
end neorv32_cpu_cp_cfu;


architecture neorv32_cpu_cp_cfu_rtl of neorv32_cpu_cp_cfu is

  -- CFU instruction type formats --
  constant r3type_c : std_ulogic := '0'; -- R3-type CFU instructions (custom-0 opcode)
  constant r4type_c : std_ulogic := '1'; -- R4-type CFU instructions (custom-1 opcode)

  -- instruction identifiers (funct3 bit-field) --
  constant rm1 : std_ulogic_vector(2 downto 0) := "000";
  constant rm2 : std_ulogic_vector(2 downto 0) := "001";
  constant rm3 : std_ulogic_vector(2 downto 0) := "010";
  constant rm4 : std_ulogic_vector(2 downto 0) := "011";
  constant rm5 : std_ulogic_vector(2 downto 0) := "100";
  constant rm6 : std_ulogic_vector(2 downto 0) := "101";
  constant rm7 : std_ulogic_vector(2 downto 0) := "110";
  constant rm8 : std_ulogic_vector(2 downto 0) := "111";

component TopModules_wrapper
    Port ( clk         : in  STD_ULOGIC;
           rst         : in  STD_ULOGIC;
           a           : in  STD_ULOGIC_VECTOR(31 downto 0);
           b           : in  STD_ULOGIC_VECTOR(31 downto 0);
           funct       : in  STD_ULOGIC_VECTOR(4 downto 0);
           fmt         : in  STD_ULOGIC_VECTOR(1 downto 0);
           rm          : in  STD_ULOGIC_VECTOR(2 downto 0);
           result      : out STD_ULOGIC_VECTOR(31 downto 0);
           flag       : out STD_ULOGIC
         );
end component;
  -- key storage (accessed via CFU CSRs) --
  type key_mem_t is array (0 to 3) of std_ulogic_vector(31 downto 0);
  signal key_mem : key_mem_t;
  signal funct5 : std_ulogic_vector(4 downto 0); -- funct5, 5 bit
  signal fmt    : std_ulogic_vector(1 downto 0); -- fmt, 2 bit
  signal result : std_ulogic_Vector(31 downto 0);
  -- processing logic --
  type xfint_t is record
    done : std_ulogic_vector(2 downto 0); -- multi-cycle done shift register; 2 stages = 2 cyles latency
    al  : std_ulogic_vector(15 downto 0); -- input operand a
    au  : std_ulogic_vector(15 downto 0); -- input operand b
    bl  : std_ulogic_vector(15 downto 0); -- input operand a
    bu  : std_ulogic_vector(15 downto 0); -- input operand b
    res  : std_ulogic_vector(31 downto 0); -- operation results
  end record;
  signal xfint : xfint_t;
  
  -- Signals for TopModules_wrapper
  signal ialu_clk        : std_ulogic;
  signal ialu_rst        : std_ulogic;
  signal ialu_a          : std_ulogic_vector(31 downto 0);
  signal ialu_b          : std_ulogic_vector(31 downto 0);
  signal ialu_funct      : std_ulogic_vector(4 downto 0);
  signal ialu_fmt        : std_ulogic_vector(1 downto 0);
  signal ialu_rm         : std_ulogic_vector(2 downto 0);
  signal ialu_result     : std_ulogic_vector(31 downto 0);
  signal ialu_flag      : std_ulogic;

begin
	 
  funct5 <= funct7_i(6 downto 2);
  fmt    <= funct7_i(1 downto 0);
  -- CFU-Internal Control and Status Registers (CFU-CSRs): 128-Bit Key Storage --------------
  -- -------------------------------------------------------------------------------------------
  -- synchronous write access --
  csr_write_access: process(rstn_i, clk_i)
  begin
    if (rstn_i = '0') then
      key_mem <= (others => (others => '0'));
    elsif rising_edge(clk_i) then
      if (csr_we_i = '1') then -- CSR write enable
        key_mem(to_integer(unsigned(csr_addr_i))) <= csr_wdata_i; -- write to CSR address
      end if;
    end if;
  end process csr_write_access;

  -- asynchronous read access --
  csr_rdata_o <= key_mem(to_integer(unsigned(csr_addr_i)));
  -- Instantiate TopModules_wrapper
	TopModules_inst : TopModules_wrapper
	  port map (
		 clk         => clk_i,            -- global clock
		 rst         => ialu_rst,           -- global reset
		 a           => ialu_a,            -- rs1_i'yi 'a'ya bala
		 b           => ialu_b,            -- rs2_i'yi 'b'ye bala
		 funct       => ialu_funct,           -- funct5'i 'funct'ye bala
		 fmt         => ialu_fmt,              -- fmt'i 'fmt'ye bala
		 rm          => ialu_rm,         -- funct3_i'yi 'rm'ye bala
		 result      => ialu_result,     -- ilem sonucu
		 flag         => ialu_flag      -- flag1 k
		   );


  -- CORE ------------------------------------------------------------------
  -- CORE ------------------------------------------------------------------
  xfint_core: process(rstn_i, clk_i)
  begin
    if (rstn_i = '0') then
      xfint.done <= (others => '0');
      xfint.al   <= (others => '0');
      xfint.au   <= (others => '0');
      xfint.bl   <= (others => '0');
      xfint.bu   <= (others => '0');
      xfint.res  <= (others => '0');
      ialu_rst   <= '1'; -- Reset the IALU initially
    elsif rising_edge(clk_i) then
        -- "operation-done" shift register: module has 2 cycles latency --
        xfint.done(0) <= '0'; -- default: no operation trigger
        xfint.done(1) <= xfint.done(0);
        xfint.done(2) <= xfint.done(1);

        -- trigger new operation --
        if (start_i = '1') then -- execution trigger and correct instruction type
          xfint.al      <= rs1_i(31 downto 16); -- buffer input operand rs1 (for improved physical timing)
          xfint.au      <= rs1_i(15 downto  0); -- buffer input operand rs1 (for improved physical timing)
          xfint.bl      <= rs2_i(31 downto 16); -- buffer input operand rs2 (for improved physical timing)
          xfint.bu      <= rs2_i(15 downto  0); -- buffer input operand rs2 (for improved physical timing)


          -- Connect inputs to IALU
          ialu_a     <= rs1_i; -- Pass rs1_i to IALU input a
          ialu_b     <= rs2_i; -- Pass rs2_i to IALU input b
          ialu_funct <= funct5; -- Pass funct5 to IALU input funct
          ialu_fmt   <= fmt;    -- Pass fmt to IALU input fmt
          ialu_rm    <= funct3_i; -- Pass funct3_i to IALU input rm
          ialu_rst   <= '0'; -- Deassert reset for IALU
        end if;

		  if (ialu_flag = '1') then
			 xfint.done(0) <= '1'; -- trigger operation
			 
		  end if;
        -- data processing --
        if (xfint.done(1) = '1') then -- second-stage execution trigger
          -- Use the result from IALU
				xfint.res <= ialu_result; -- Store the result from IALU
            ialu_rst   <= '1'; -- Deassert reset for IALU

        end if;

    end if;
  end process xfint_core;



  -- ENDCORE ------------------------------------------------------------------


  -- Function Result Select -----------------------------------------------------------------
  -- -------------------------------------------------------------------------------------------
  result_select: process(funct3_i, xfint) --process(rtype_i, funct3_i, xfint)
  begin
    --if (r3type_c = r3type_c) then -- R3-type instructions; function select via "funct3" and ""funct7
    -- ----------------------------------------------------------------------
      case funct3_i is -- just check "funct3" here; "funct7" bit-field is ignored in this example
        when rm1 | rm2 | rm3 | rm4 | rm5 | rm6 | rm7 | rm8 => -- xtea encryption/decryption
          result_o <= xfint.res; -- processing result
          valid_o  <= xfint.done(2); -- multi-cycle processing done when set
        when others => -- all unspecified operations
          result_o <= (others => '0'); -- no logic implemented
          valid_o  <= '0'; -- this will cause an illegal instruction exception after timeout
      end case;

    --else -- R4-type instructions; function select via "funct3" (but ignored here)
    -- ----------------------------------------------------------------------
    --  result_o <= (others => '0'); -- no logic implemented
     -- valid_o  <= '0'; -- this will cause an illegal instruction exception after timeout

    --end if;
  end process result_select;


end neorv32_cpu_cp_cfu_rtl;
