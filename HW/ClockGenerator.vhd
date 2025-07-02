library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VComponents.all;

entity ClockGenerator is
    port (
        i_clk_100mhz : in  std_logic;  -- 100 MHz Atlys kart saati (L15'ten gelen)
        i_reset      : in  std_logic;  -- Sfrlama sinyali (T15'ten gelen)
        o_clk_200mhz : out std_logic;  -- retilen 200 MHz saat
        o_clk_locked : out std_logic   -- Saatin kilitlendiini gsteren sinyal
    );
end entity ClockGenerator;

architecture Behavioral of ClockGenerator is
    -- Kullanlmayan k portlar iin sinyaller
    signal unused_clk0_out     : std_logic;
    signal unused_clk90_out    : std_logic;
    signal unused_clk180_out   : std_logic;
    signal unused_clk270_out   : std_logic;
    signal unused_clk2x_out    : std_logic;
    signal unused_clk2x180_out : std_logic;
    signal unused_clkfx180_out : std_logic;
    signal unused_clkdv_out    : std_logic;
    signal unused_psdone_out   : std_logic;
    signal unused_status_out   : std_logic_vector(7 downto 0); 

    -- *** YEN: Dahili CLKFX sinyali ***
    signal clkfx_internal : std_logic; 

begin

    -- DCM_SP (Digital Clock Manager - Spartan-6 Primitive)
    DCM_SP_inst : DCM_SP
    generic map (
        CLKDV_DIVIDE        => 2.0,
        CLKFX_DIVIDE        => 10,
        CLKFX_MULTIPLY      => 2,
        CLKIN_DIVIDE_BY_2   => FALSE,    -- Dzeltildi: "FALSE" -> FALSE
        CLKIN_PERIOD        => 10.0,
        CLKOUT_PHASE_SHIFT  => "NONE",
        CLK_FEEDBACK        => "1X",
        DLL_FREQUENCY_MODE  => "HIGH",   -- Bu muhtemelen doru stringdir, hata devam ederse Xilinx dkmann kontrol edin.
        DSS_MODE            => "NONE",
        FACTORY_JF          => X"8080",
        STARTUP_WAIT        => FALSE     -- Dzeltildi: "FALSE" -> FALSE
    )
    port map (
        -- Output clocks
        CLKFB               => clkfx_internal,  -- Dzeltildi: Port'a deil dahili sinyale bala
        CLKFX               => clkfx_internal,  -- k saati dahili sinyale balanyor
        
        CLK0                => unused_clk0_out,
        CLK90               => unused_clk90_out,
        CLK180              => unused_clk180_out,
        CLK270              => unused_clk270_out,
        CLK2X               => unused_clk2x_out,
        CLK2X180            => unused_clk2x180_out,
        CLKDV               => unused_clkdv_out,

        -- Status and control signals
        LOCKED              => o_clk_locked,
        PSDONE              => unused_psdone_out,
        STATUS              => unused_status_out,
        RST                 => i_reset,
        PSCLK               => '0',
        PSEN                => '0',
        PSINCDEC            => '0',

        -- Input clock
        CLKIN               => i_clk_100mhz
    );

    -- Dahili DCM kn harici porta atayn
    o_clk_200mhz <= clkfx_internal;

end architecture Behavioral;