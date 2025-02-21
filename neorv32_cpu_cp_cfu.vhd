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


  -- key storage (accessed via CFU CSRs) --
  type key_mem_t is array (0 to 3) of std_ulogic_vector(31 downto 0);
  signal key_mem : key_mem_t;
  signal funct5 : std_ulogic_vector(4 downto 0); -- funct5, 5 bit
  signal fmt    : std_ulogic_vector(1 downto 0); -- fmt, 2 bit
  -- processing logic --
  type xfint_t is record
    done : std_ulogic_vector(1 downto 0); -- multi-cycle done shift register; 2 stages = 2 cyles latency
    opa  : std_ulogic_vector(31 downto 0); -- input operand a
    opb  : std_ulogic_vector(31 downto 0); -- input operand b
    res  : std_ulogic_vector(31 downto 0); -- operation results
  end record;
  signal xfint : xfint_t;

  funct5 <= funct7_i(6 downto 2);
  fmt    <= funct7_i(1 downto 0);
begin

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


  -- XTEA Processing Core ------------------------------------------------------------------
  -- -------------------------------------------------------------------------------------------
  xfint_core: process(rstn_i, clk_i)
  begin
    if (rstn_i = '0') then
      xfint.done <= (others => '0');
      xfint.opa  <= (others => '0');
      xfint.opb  <= (others => '0');
      xfint.res  <= (others => '0');
    elsif rising_edge(clk_i) then
      if (funct5 = "00000") then
        -- "operation-done" shift register: module has 2 cycles latency --
        xfint.done(0) <= '0'; -- default: no operation trigger
        xfint.done(1) <= xfint.done(0);

        -- trigger new operation --
        if (start_i = '1') then --and (rtype_i = r3type_c) then-- execution trigger and correct instruction type
          xfint.opa     <= rs1_i; -- buffer input operand rs1 (for improved physical timing)
          xfint.opb     <= rs2_i; -- buffer input operand rs2 (for improved physical timing)
          xfint.done(0) <= '1'; -- trigger operation
        end if;

        -- data processing --
        if (xfint.done(0) = '1') then -- second-stage execution trigger
          -- update "sum" round key --
          if (funct3_i(2) = '1') then -- initialize
            xfint.res <= 3;
          elsif (funct3_i(1 downto 0) = rm1(1 downto 0)) then -- encrypt v0
            xfint.res <= 4;
          elsif (funct3_i(1 downto 0) = rm2(1 downto 0)) then -- decrypt v1
            xfint.res <= 5;
          end if;
        end if;

      end if;

    end if ;
  end process xfint_core;



  -- Function Result Select -----------------------------------------------------------------
  -- -------------------------------------------------------------------------------------------
  result_select: process(funct3_i, xfint) --process(rtype_i, funct3_i, xfint)
  begin
    --if (r3type_c = r3type_c) then -- R3-type instructions; function select via "funct3" and ""funct7
    -- ----------------------------------------------------------------------
      case funct3_i is -- just check "funct3" here; "funct7" bit-field is ignored in this example
        when rm1 | rm2 | rm3 | rm4 | rm5 | rm6 | rm7 | rm8 => -- xtea encryption/decryption
          result_o <= xfint.res; -- processing result
          valid_o  <= xfint.done(1); -- multi-cycle processing done when set
        when (rm8 = rm7) => -- xtea initialization
          result_o <= (others => '0'); -- just output zero
          valid_o  <= '1'; -- pure-combinatorial, so we are done "immediately"
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
