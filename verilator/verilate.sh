#verilator -cc -exe --public --compiler msvc --converge-limit 2000 -Wno-WIDTH -Wno-IMPLICIT -Wno-MODDUP -Wno-UNSIGNED -Wno-CASEINCOMPLETE -Wno-CASEX -Wno-SYMRSVDWORD -Wno-COMBDLY -Wno-INITIALDLY -Wno-BLKANDNBLK -Wno-UNOPTFLAT -Wno-SELRANGE -Wno-CMPCONST -Wno-CASEOVERLAP -Wno-PINMISSING --top-module top      sim.v \
verilator -cc -exe --public --compiler msvc +define+SIMULATION=1 --converge-limit 2000 --top-module top sim.v \
../rtl/dpram.v \
../rtl/spram.v \
../rtl/JTFRAME/jtframe_vtimer.v \
../rtl/soc.v \
../rtl/tv80/tv80_core.v \
../rtl/tv80/tv80_alu.v \
../rtl/tv80/tv80_mcode.v \
../rtl/tv80/tv80_reg.v \
../rtl/tv80/tv80n.v \
../rtl/tv80/tv80s.v
