#include <vmprofiler.hpp>

namespace vm::handler::profile
{

vm::handler::profile_t crc = {
    // MOV RDX, [RBP]
    // ADD RBP, 0x8
    // XOR EAX, EAX or SUB EAX, EAX
    // MOV ECX, EAX
    // SHL EAX, 0x7
    // SHR ECX, 0x19
    // OR EAX, ECX
    // XOR AL, [RDX]
    // ADD RDX, 0x1
    // DEC dword ptr [RBP]
    // (any conditional jump)         ; loop
    // MOV [RBP], EAX                 ; exit path
    "CRC",
     CRC,
    NULL,
    { {
        // MOV RDX, [RBP]
        [](const zydis_decoded_instr_t& i)->bool {
            return i.mnemonic == ZYDIS_MNEMONIC_MOV &&
                   i.operands[0].type == ZYDIS_OPERAND_TYPE_REGISTER &&
                   i.operands[0].reg.value == ZYDIS_REGISTER_RDX &&
                   i.operands[1].type == ZYDIS_OPERAND_TYPE_MEMORY &&
                   i.operands[1].mem.base == ZYDIS_REGISTER_RBP;
        },
        // ADD RBP, 8
            []( const zydis_decoded_instr_t &i ) -> bool
            {
                if ( i.mnemonic == ZYDIS_MNEMONIC_ADD )
                    return i.operands[ 0 ].type == ZYDIS_OPERAND_TYPE_REGISTER &&
                           i.operands[ 0 ].reg.value == ZYDIS_REGISTER_RBP &&
                           i.operands[ 1 ].type == ZYDIS_OPERAND_TYPE_IMMEDIATE && 
                           i.operands[ 1 ].imm.value.u == 0x8;
                if ( i.mnemonic == ZYDIS_MNEMONIC_LEA )
                    return i.operands[ 0 ].type == ZYDIS_OPERAND_TYPE_REGISTER &&
                           i.operands[ 0 ].reg.value == ZYDIS_REGISTER_RBP &&
                           i.operands[ 1 ].type == ZYDIS_OPERAND_TYPE_MEMORY &&
                           i.operands[ 1 ].mem.base == ZYDIS_REGISTER_RBP && 
                           i.operands[ 1 ].mem.disp.has_displacement &&
                           i.operands[ 1 ].mem.disp.value == 0x8;         
        },
        // XOR EAX, EAX or SUB EAX, EAX
        [](const zydis_decoded_instr_t& i)->bool {
            return (i.mnemonic == ZYDIS_MNEMONIC_XOR || i.mnemonic == ZYDIS_MNEMONIC_SUB) &&
                   i.operands[0].type == ZYDIS_OPERAND_TYPE_REGISTER &&
                   i.operands[0].reg.value == ZYDIS_REGISTER_EAX &&
                   i.operands[1].type == ZYDIS_OPERAND_TYPE_REGISTER &&
                   i.operands[1].reg.value == ZYDIS_REGISTER_EAX;
        },
        // MOV ECX, EAX
        [](const zydis_decoded_instr_t& i)->bool {
            return i.mnemonic == ZYDIS_MNEMONIC_MOV &&
                   i.operands[0].type == ZYDIS_OPERAND_TYPE_REGISTER &&
                   i.operands[0].reg.value == ZYDIS_REGISTER_ECX &&
                   i.operands[1].type == ZYDIS_OPERAND_TYPE_REGISTER &&
                   i.operands[1].reg.value == ZYDIS_REGISTER_EAX;
        },
        // SHL EAX, 7
        [](const zydis_decoded_instr_t& i)->bool {
            return i.mnemonic == ZYDIS_MNEMONIC_SHL &&
                   i.operands[0].type == ZYDIS_OPERAND_TYPE_REGISTER &&
                   i.operands[0].reg.value == ZYDIS_REGISTER_EAX &&
                   i.operands[1].type == ZYDIS_OPERAND_TYPE_IMMEDIATE &&
                   i.operands[1].imm.value.u == 7;
        },
        // SHR ECX, 0x19
        [](const zydis_decoded_instr_t& i)->bool {
            return i.mnemonic == ZYDIS_MNEMONIC_SHR &&
                   i.operands[0].type == ZYDIS_OPERAND_TYPE_REGISTER &&
                   i.operands[0].reg.value == ZYDIS_REGISTER_ECX &&
                   i.operands[1].type == ZYDIS_OPERAND_TYPE_IMMEDIATE &&
                   i.operands[1].imm.value.u == 0x19;
        },
        // OR EAX, ECX
        [](const zydis_decoded_instr_t& i)->bool {
            return i.mnemonic == ZYDIS_MNEMONIC_OR &&
                   i.operands[0].type == ZYDIS_OPERAND_TYPE_REGISTER &&
                   i.operands[0].reg.value == ZYDIS_REGISTER_EAX &&
                   i.operands[1].type == ZYDIS_OPERAND_TYPE_REGISTER &&
                   i.operands[1].reg.value == ZYDIS_REGISTER_ECX;
        },
        // XOR AL, [RDX]
        [](const zydis_decoded_instr_t& i)->bool {
            return i.mnemonic == ZYDIS_MNEMONIC_XOR &&
                   i.operands[0].type == ZYDIS_OPERAND_TYPE_REGISTER &&
                   i.operands[0].reg.value == ZYDIS_REGISTER_AL &&
                   i.operands[1].type == ZYDIS_OPERAND_TYPE_MEMORY &&
                   i.operands[1].mem.base == ZYDIS_REGISTER_RDX;
        },
        // ADD RDX, 1
        [](const zydis_decoded_instr_t& i)->bool {
            return i.mnemonic == ZYDIS_MNEMONIC_ADD &&
                   i.operands[0].type == ZYDIS_OPERAND_TYPE_REGISTER &&
                   i.operands[0].reg.value == ZYDIS_REGISTER_RDX &&
                   i.operands[1].type == ZYDIS_OPERAND_TYPE_IMMEDIATE &&
                   i.operands[1].imm.value.u == 1;
        },
        // DEC dword ptr [RBP]   (loop counter)
        [](const zydis_decoded_instr_t& i)->bool {
            return i.mnemonic == ZYDIS_MNEMONIC_DEC &&
                   i.operands[0].type == ZYDIS_OPERAND_TYPE_MEMORY &&
                   i.operands[0].mem.base == ZYDIS_REGISTER_RBP &&
                   i.operands[ 0 ].size == 32 &&
                   ( !i.operands[ 0 ].mem.disp.has_displacement || i.operands[ 0 ].mem.disp.value == 0 );
        }
    } }
};
}