-- ================================================================================ --
-- NEORV32 CPU - Co-Processor: Custom (RISC-V Instructions) Functions Unit (CFU)   --
-- -------------------------------------------------------------------------------- --
-- Integrates a custom ALU (TopModules_wrapper) for user-defined RISC-V instructions.
-- -------------------------------------------------------------------------------- --

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

library neorv32;
use neorv32.neorv32_package.all;

entity neorv32_cpu_cp_cfu is
  port (
    clk_i       : in  std_ulogic; -- Global clock
    rstn_i      : in  std_ulogic; -- Global reset (low-active)
    start_i     : in std_ulogic; -- Operation trigger
    active_i    : in std_ulogic; -- CPU waits for CFU
    csr_we_i    : in  std_ulogic; -- CSR write enable (not used for writing in this example)
    csr_addr_i  : in  std_ulogic_vector(1 downto 0); -- CSR address (0x800-0x803)
    csr_wdata_i : in  std_ulogic_vector(31 downto 0); -- CSR write data (not used)
    csr_rdata_o : out std_ulogic_vector(31 downto 0); -- CSR read data (error_reg)
    rtype_i     : in std_ulogic; -- Instruction type (R3/R4)
    funct3_i    : in std_ulogic_vector(2 downto 0); -- funct3 field
    funct7_i    : in std_ulogic_vector(6 downto 0); -- funct7 field
    rs1_i       : in  std_ulogic_vector(31 downto 0); -- Register source 1
    rs2_i       : in  std_ulogic_vector(31 downto 0); -- Register source 2
    rs3_i       : in  std_ulogic_vector(31 downto 0); -- Register source 3 (not used)
    result_o    : out std_ulogic_vector(31 downto 0); -- Operation result
    valid_o     : out std_ulogic -- Result valid, operation done
  );
end neorv32_cpu_cp_cfu;


architecture neorv32_cpu_cp_cfu_rtl of neorv32_cpu_cp_cfu is

  -- Instruction identifiers (funct3) --
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
           flag        : out STD_ULOGIC;
           error       : out STD_ULOGIC_VECTOR(2 downto 0);
           dual        : out STD_ULOGIC
         );
end component;

  signal funct5 : std_ulogic_vector(4 downto 0); -- Derived from funct7_i
  signal fmt    : std_ulogic_vector(1 downto 0); -- Derived from funct7_i

  -- Internal state for CFU processing --
  type xfint_t is record
    done : std_ulogic_vector(2 downto 0); -- Multi-cycle done shift register (2 cycles latency)
    res  : std_ulogic_vector(31 downto 0); -- Operation result
  end record;
  signal xfint : xfint_t;

  -- Signals for TopModules_wrapper instance --
  signal ialu_rst    : std_ulogic;
  signal ialu_a      : std_ulogic_vector(31 downto 0);
  signal ialu_b      : std_ulogic_vector(31 downto 0);
  signal ialu_funct  : std_ulogic_vector(4 downto 0);
  signal ialu_fmt    : std_ulogic_vector(1 downto 0);
  signal ialu_rm     : std_ulogic_vector(2 downto 0);
  signal ialu_result : std_ulogic_vector(31 downto 0);
  signal ialu_flag   : std_ulogic;
  signal ialu_error  : std_ulogic_vector(2 downto 0);
  signal ialu_dual   : std_ulogic;
  signal error_reg   : std_ulogic_vector(2 downto 0); -- Stores error status for CSR read
begin

  funct5 <= funct7_i(6 downto 2);
  fmt    <= funct7_i(1 downto 0);

  -- CSR Read: Provides the error_reg value --
  csr_read: process(csr_addr_i, error_reg)
  begin
    csr_rdata_o <= (31 downto 3 => '0') & error_reg;
  end process csr_read;

  -- Instantiate the custom ALU wrapper --
  TopModules_inst : TopModules_wrapper
    port map (
      clk         => clk_i,
      rst         => ialu_rst,
      a           => ialu_a,
      b           => ialu_b,
      funct       => ialu_funct,
      fmt         => ialu_fmt,
      rm          => ialu_rm,
      result      => ialu_result,
      flag        => ialu_flag,
      error       => ialu_error,
      dual        => ialu_dual
    );

  -- Main CFU Processing Logic --
  xfint_core: process(rstn_i, clk_i)
  begin
    if (rstn_i = '0') then
      xfint.done  <= (others => '0');
      xfint.res   <= (others => '0');
      ialu_rst    <= '1'; -- Assert IALU reset
      error_reg   <= (others => '0'); -- Reset error register
    elsif rising_edge(clk_i) then
      xfint.done(0) <= '0';
      xfint.done(1) <= xfint.done(0);
      xfint.done(2) <= xfint.done(1); -- 2-cycle latency tracking

      if (start_i = '1') then -- On operation trigger
        ialu_a      <= rs1_i;
        ialu_b      <= rs2_i;
        ialu_funct  <= funct5;
        ialu_fmt    <= fmt;
        ialu_rm     <= funct3_i;
        ialu_rst    <= '0'; -- Deassert IALU reset
      end if;

      if (ialu_flag = '1') then
        xfint.done(0) <= '1'; -- Signal start of done sequence
      end if;

      if (xfint.done(1) = '1') then -- After 2 cycles
        xfint.res <= ialu_result;   -- Capture result
        error_reg <= ialu_error;    -- Capture error status
        ialu_rst    <= '0'; -- Deassert IALU reset
      end if;
    end if;
  end process xfint_core;

  -- Select and output the result --
  result_select: process(funct3_i, xfint)
  begin
    case funct3_i is
      when rm1 | rm2 | rm3 | rm4 | rm5 | rm6 | rm7 | rm8 => -- Valid operations
        result_o <= xfint.res;
        valid_o  <= xfint.done(2);
      when others => -- Unspecified operations
        result_o <= (others => '0');
        valid_o  <= '0'; -- May cause illegal instruction exception
    end case;
  end process result_select;

end neorv32_cpu_cp_cfu_rtl;