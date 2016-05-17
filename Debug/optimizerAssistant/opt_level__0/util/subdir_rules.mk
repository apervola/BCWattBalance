################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
util/cmdline.obj: ../util/cmdline.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.7/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me -O0 --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.7/include" --include_path="C:/ti/TivaWare_C_Series-2.1.2.111" -g --gcc --define=ccs="ccs" --define=PART_TM4C123GE6PM --diag_wrap=off --display_error_number --diag_warning=225 --preproc_with_compile --preproc_dependency="util/cmdline.pp" --obj_directory="util" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

util/uartstdio.obj: ../util/uartstdio.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.7/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me -O0 --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.7/include" --include_path="C:/ti/TivaWare_C_Series-2.1.2.111" -g --gcc --define=ccs="ccs" --define=PART_TM4C123GE6PM --diag_wrap=off --display_error_number --diag_warning=225 --preproc_with_compile --preproc_dependency="util/uartstdio.pp" --obj_directory="util" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

util/ustdlib.obj: ../util/ustdlib.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.7/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me -O0 --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.7/include" --include_path="C:/ti/TivaWare_C_Series-2.1.2.111" -g --gcc --define=ccs="ccs" --define=PART_TM4C123GE6PM --diag_wrap=off --display_error_number --diag_warning=225 --preproc_with_compile --preproc_dependency="util/ustdlib.pp" --obj_directory="util" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


