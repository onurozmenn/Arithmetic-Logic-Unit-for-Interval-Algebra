# Arithmetic Logic Unit Design for Interval Algebra (I-ALU)

## About the Project

Uncertainties frequently encountered in engineering applications pose challenges for traditional arithmetic units. This project offers a hardware-based solution that treats uncertainties as interval values, allowing the deviation value in the result to be directly obtained without additional calculations.

The primary goal is to efficiently calculate the lower and upper bounds of interval results by designing two specialized Arithmetic Logic Units (ALUs) that operate in parallel and independently on an FPGA (Field Programmable Gate Arrays). This hardware approach aims to eliminate the performance loss caused by software-based solutions.

The project is supported by the TÜBİTAK 2209-B Undergraduate Research Projects Support Program for Industry.
Original Aspects

- Floating-Point Representation: Unlike fixed-point representation, the use of floating-point representation allows a wider range of numbers to be represented with the same number of bits, which is one of the original aspects of the design.

- Interval Algebra Functions: The design offers the ability to calculate interval algebra-specific statistical functions such as midpoint, width, and radius.

- Hardware Acceleration: Performance losses incurred by software are mitigated at the hardware level through the use of FPGAs, leading to more reliable and effective solutions in simulation and calculation programs.

- RISC-V Integration: The design is integrated as a Custom Function Unit (CFU) within the NEORV32 RISC-V processor core, known for its open-source and modular structure. This integration enables hardware-level acceleration of interval arithmetic operations, offering low latency and high processing performance.

## Architecture

The Interval ALU (I-ALU) design utilizes a sixteen-bit half-precision floating-point format, consisting of one sign bit, five exponent bits, and ten fraction bits. The lower and upper bounds of an interval are represented in a 32-bit format: the first sixteen bits represent the lower bound, and the last sixteen bits represent the upper bound.

The general design diagram (See Thesis Figure 9.1) illustrates that the "Operation Routing Module" directs the lower and upper bounds of the input intervals to the respective ALUs based on the operation to be performed. The outputs from the ALUs correspond to the lower and upper bounds of the result interval. The Operation Routing Module routes data according to the four operational rules of interval arithmetic, aiming to produce the widest possible result interval from the operation between two intervals.
Modules

The project consists of various modules designed to perform different arithmetic and logical operations:

- Temporal Interval Module: Determines and encodes into a 4-bit status signal the thirteen different relations between two intervals, according to James F. Allen's Interval Algebra principles.

- Operation Routing Module: Routes the boundary values to the appropriate ALUs by using interval arithmetic rules and statistical functions mentioned in the method part. For special cases like multiplication and division, it handles routing based on their position relative to zero and using tables like 2.1 and 2.2.

- Addition-Subtraction Module: Performs addition and subtraction operations for floating-point numbers within the same module, as binary subtraction can be achieved using two's complement. This includes steps such as equalizing exponent values, shifting fractional parts, and normalization.

- Multiplication Module: Carries out multiplication for floating-point numbers by adding exponent values and multiplying fraction values. It manages the nine different cases in interval multiplication, some requiring parallel operations and comparison.

- Division Module: Executes division operations by subtracting exponent values and uses a special algorithm for the fraction part based on decimal division principles. It addresses seven different cases of division and includes proper error handling for division by zero, defining the result range as [−inf,inf].

- Statistical Functions Module: Calculates statistical properties of intervals such as midpoint, width, radius, minimum, and maximum values based on interval arithmetic definitions. These functions can be used for conversion to affine forms.
    
## Development Environment

- Hardware Description Languages: Verilog and VHDL (for NEORV32)

- FPGA Development Kit: Xilinx Spartan-6 LX45 FPGA (compatible with Xilinx ISE)

- IDE/Tools: Xilinx ISE, other simulation tools.

- Software Compiler: C compiler for RISC-V based embedded systems.

## Hardware Integration (NEORV32 CFU)
- NEORV32 Core: The project uses the open-source NEORV32 RISC-V processor core. NEORV32 features an extensible and configurable architecture, making it highly suitable for FPGA applications.

- CFU Integration: The I-ALU module is integrated as a dedicated hardware unit within the NEORV32 core via its Custom Function Unit (CFU) interface. This allows the processor to directly access the I-ALU through custom function calls, eliminating the need for memory-mapped I/O access.

- Mixed Language Support: Since the I-ALU core is written in Verilog, Mixed Language support was enabled during the project build process to allow it to operate together with NEORV32's VHDL-based architecture.

## Power Consumption

An analysis using the Xilinx XPower Analyzer tool determined the total on-chip power consumption for the I-ALU design to be 317.42 mW. This figure includes 55.80 mW of static power and 261.62 mW of dynamic power. The dynamic power is primarily consumed by I/Os (173.90 mW), followed by signals (42.36 mW) and logic (28.45 mW). FPGA's parallel processing makes the I-ALU energy-efficient per operation compared to software.

## Future Work

Several directions can be explored to further expand the project's capabilities:

- Software-Based Advanced Functions: Trigonometric operations (sin, cos), exponential/logarithmic computations, and numerical differentiation/integration can be integrated at the software level, leveraging the existing I-ALU for interval-safe higher-order algorithms.

- Dynamic Precision Scaling: Beyond the current parameterizable bit width, future versions could include adaptive precision techniques, allowing dynamic adjustment of bit widths based on input data range or required output accuracy, thereby optimizing power and area consumption.

- Verification and Formal Methods: As the system scales, verifying correctness becomes crucial. Future work could include formal verification of interval operations for special cases like division by zero, NaN, or overflow/underflow, using appropriate tools.

- Hardware Scheduler and Pipelining: Introducing an instruction scheduling mechanism or pipelining the interval arithmetic units could significantly improve throughput, especially for workloads with many back-to-back interval operations.

- Multi-Core or Parallel Interval Processing: The design could be expanded to include multiple interval processing cores operating in parallel, targeting high-performance computing (HPC) or real-time data analysis scenarios where large-scale interval computations are required.

## License

The project has been developed using open-source components and properly referenced. For licensing information, please refer to the project's GitHub repository.

## Contributing

Your contributions will greatly enhance the development of this project. For bug reports, new feature suggestions, or code contributions, please open an issue or submit a pull request.

## Contributors

- Onur Özmen (Project Lead)

- Mehmet Onur Özcan (Project Lead)

- Assoc. Prof. Dr. Serkan GÜNEL (Advisor)
