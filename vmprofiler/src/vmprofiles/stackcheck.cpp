#include <vmprofiler.hpp>

namespace vm::handler::profile
{

vm::handler::profile_t stackcheck = {
    "STACKCHECK", 
	STACKCHECK, 
	NULL, { {
        // MOV EBP, [RBP]  (or [RBP+0])
        [](const zydis_decoded_instr_t& i){
            return i.mnemonic==ZYDIS_MNEMONIC_MOV &&
                   i.operands[0].type==ZYDIS_OPERAND_TYPE_REGISTER &&
                   i.operands[0].reg.value==ZYDIS_REGISTER_EBP &&
                   i.operands[1].type==ZYDIS_OPERAND_TYPE_MEMORY &&
                   i.operands[1].mem.base==ZYDIS_REGISTER_RBP &&
                   ( !i.operands[ 0 ].mem.disp.has_displacement || i.operands[ 0 ].mem.disp.value == 0 );
        }
    } }
};
}