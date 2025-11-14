#include <vmprofiler.hpp>

namespace vm::handler::profile
{
    vm::handler::profile_t mulq = {
        // MOV RAX, [RBP+0x8]
        // SUB RBP, 0x8
        // MUL RDX
        // MOV [RBP+0x8], RDX
        // MOV [RBP+0x10], RAX
        // PUSHFQ
        // POP [RBP]
        "MULQ",
        MULQ,
        NULL,
        { { // MOV RAX, [RBP+0x8]
            []( const zydis_decoded_instr_t &instr ) -> bool {
                return instr.mnemonic == ZYDIS_MNEMONIC_MOV &&
                       instr.operands[ 0 ].type == ZYDIS_OPERAND_TYPE_REGISTER &&
                       instr.operands[ 0 ].reg.value == ZYDIS_REGISTER_RAX &&
                       instr.operands[ 1 ].type == ZYDIS_OPERAND_TYPE_MEMORY &&
                       instr.operands[ 1 ].mem.base == ZYDIS_REGISTER_RBP && instr.operands[ 1 ].mem.disp.value == 0x8;
            },
            // SUB RBP, 0x8
            []( const zydis_decoded_instr_t &instr ) -> bool {
                return instr.mnemonic == ZYDIS_MNEMONIC_SUB &&
                       instr.operands[ 0 ].type == ZYDIS_OPERAND_TYPE_REGISTER &&
                       instr.operands[ 0 ].reg.value == ZYDIS_REGISTER_RBP &&
                       instr.operands[ 1 ].type == ZYDIS_OPERAND_TYPE_IMMEDIATE &&
                       instr.operands[ 1 ].imm.value.u == 0x8;
            },
            // MUL RDX
            []( const zydis_decoded_instr_t &instr ) -> bool {
                return instr.mnemonic == ZYDIS_MNEMONIC_MUL &&
                       instr.operands[ 0 ].type == ZYDIS_OPERAND_TYPE_REGISTER &&
                       instr.operands[ 0 ].reg.value == ZYDIS_REGISTER_RDX;
            },
            // MOV [RBP+0x8], RDX
            []( const zydis_decoded_instr_t &instr ) -> bool {
                return instr.mnemonic == ZYDIS_MNEMONIC_MOV && instr.operands[ 0 ].type == ZYDIS_OPERAND_TYPE_MEMORY &&
                       instr.operands[ 0 ].mem.base == ZYDIS_REGISTER_RBP &&
                       instr.operands[ 0 ].mem.disp.value == 0x8 &&
                       instr.operands[ 1 ].type == ZYDIS_OPERAND_TYPE_REGISTER &&
                       instr.operands[ 1 ].reg.value == ZYDIS_REGISTER_RDX;
            },
            // MOV [RBP+0x10], RAX
            []( const zydis_decoded_instr_t &instr ) -> bool {
                return instr.mnemonic == ZYDIS_MNEMONIC_MOV && instr.operands[ 0 ].type == ZYDIS_OPERAND_TYPE_MEMORY &&
                       instr.operands[ 0 ].mem.base == ZYDIS_REGISTER_RBP &&
                       instr.operands[ 0 ].mem.disp.value == 0x10 &&
                       instr.operands[ 1 ].type == ZYDIS_OPERAND_TYPE_REGISTER &&
                       instr.operands[ 1 ].reg.value == ZYDIS_REGISTER_RAX;
            },
            // PUSHFQ
            []( const zydis_decoded_instr_t &instr ) -> bool { return instr.mnemonic == ZYDIS_MNEMONIC_PUSHFQ; },
            // POP [RBP]
            []( const zydis_decoded_instr_t &instr ) -> bool {
                return instr.mnemonic == ZYDIS_MNEMONIC_POP && instr.operands[ 0 ].type == ZYDIS_OPERAND_TYPE_MEMORY &&
                       instr.operands[ 0 ].mem.base == ZYDIS_REGISTER_RBP;
            } } } };

    vm::handler::profile_t muldw = {
        // MOV EDX, [RBP]
        // MOV EAX, [RBP+0x4]
        // SUB RBP, 0x8
        // MUL EDX
        // MOV [RBP+0x8], EDX
        // MOV [RBP+0xC], EAX
        // PUSHFQ
        // POP [RBP]
        "MULDW",
        MULDW,
        NULL,
        { { // MOV EDX, [RBP]
            []( const zydis_decoded_instr_t &instr ) -> bool {
                return instr.mnemonic == ZYDIS_MNEMONIC_MOV &&
                       instr.operands[ 0 ].type == ZYDIS_OPERAND_TYPE_REGISTER &&
                       instr.operands[ 0 ].reg.value == ZYDIS_REGISTER_EDX &&
                       instr.operands[ 1 ].type == ZYDIS_OPERAND_TYPE_MEMORY &&
                       instr.operands[ 1 ].mem.base == ZYDIS_REGISTER_RBP;
            },
            // MOV EAX, [RBP+0x4]
            []( const zydis_decoded_instr_t &instr ) -> bool {
                return instr.mnemonic == ZYDIS_MNEMONIC_MOV &&
                       instr.operands[ 0 ].type == ZYDIS_OPERAND_TYPE_REGISTER &&
                       instr.operands[ 0 ].reg.value == ZYDIS_REGISTER_EAX &&
                       instr.operands[ 1 ].type == ZYDIS_OPERAND_TYPE_MEMORY &&
                       instr.operands[ 1 ].mem.base == ZYDIS_REGISTER_RBP && instr.operands[ 1 ].mem.disp.value == 0x4;
            },
            // SUB RBP, 0x8
            []( const zydis_decoded_instr_t &instr ) -> bool {
                return instr.mnemonic == ZYDIS_MNEMONIC_SUB &&
                       instr.operands[ 0 ].type == ZYDIS_OPERAND_TYPE_REGISTER &&
                       instr.operands[ 0 ].reg.value == ZYDIS_REGISTER_RBP &&
                       instr.operands[ 1 ].type == ZYDIS_OPERAND_TYPE_IMMEDIATE &&
                       instr.operands[ 1 ].imm.value.u == 0x8;
            },
            // MUL EDX
            []( const zydis_decoded_instr_t &instr ) -> bool {
                return instr.mnemonic == ZYDIS_MNEMONIC_MUL &&
                       instr.operands[ 0 ].type == ZYDIS_OPERAND_TYPE_REGISTER &&
                       instr.operands[ 0 ].reg.value == ZYDIS_REGISTER_EDX;
            },
            // MOV [RBP+0x8], EDX
            []( const zydis_decoded_instr_t &instr ) -> bool {
                return instr.mnemonic == ZYDIS_MNEMONIC_MOV && instr.operands[ 0 ].type == ZYDIS_OPERAND_TYPE_MEMORY &&
                       instr.operands[ 0 ].mem.base == ZYDIS_REGISTER_RBP &&
                       instr.operands[ 0 ].mem.disp.value == 0x8 &&
                       instr.operands[ 1 ].type == ZYDIS_OPERAND_TYPE_REGISTER &&
                       instr.operands[ 1 ].reg.value == ZYDIS_REGISTER_EDX;
            },
            // MOV [RBP+0xC], EAX
            []( const zydis_decoded_instr_t &instr ) -> bool {
                return instr.mnemonic == ZYDIS_MNEMONIC_MOV && instr.operands[ 0 ].type == ZYDIS_OPERAND_TYPE_MEMORY &&
                       instr.operands[ 0 ].mem.base == ZYDIS_REGISTER_RBP &&
                       instr.operands[ 0 ].mem.disp.value == 0xC &&
                       instr.operands[ 1 ].type == ZYDIS_OPERAND_TYPE_REGISTER &&
                       instr.operands[ 1 ].reg.value == ZYDIS_REGISTER_EAX;
            },
            // PUSHFQ
            []( const zydis_decoded_instr_t &instr ) -> bool { return instr.mnemonic == ZYDIS_MNEMONIC_PUSHFQ; },
            // POP [RBP]
            []( const zydis_decoded_instr_t &instr ) -> bool {
                return instr.mnemonic == ZYDIS_MNEMONIC_POP && instr.operands[ 0 ].type == ZYDIS_OPERAND_TYPE_MEMORY &&
                       instr.operands[ 0 ].mem.base == ZYDIS_REGISTER_RBP;
            } } } };

    vm::handler::profile_t mulw = {
    // MOV DX, [RBP]
    // MOV AX, [RBP+0x2]
    // SUB RBP, 0x8
    // MUL DX               ; unsigned, implicit AX
    // MOV [RBP+0x8], DX    ; high
    // MOV [RBP+0xA], AX    ; low
    // PUSHFQ
    // POP [RBP]
    "MULW",
    MULW,
    NULL,
    { {
        [](const zydis_decoded_instr_t& i)->bool { // MOV DX, [RBP]
            return i.mnemonic == ZYDIS_MNEMONIC_MOV &&
                   i.operands[0].type == ZYDIS_OPERAND_TYPE_REGISTER &&
                   i.operands[0].reg.value == ZYDIS_REGISTER_DX &&
                   i.operands[1].type == ZYDIS_OPERAND_TYPE_MEMORY &&
                   i.operands[1].mem.base == ZYDIS_REGISTER_RBP;
        },
        [](const zydis_decoded_instr_t& i)->bool { // MOV AX, [RBP+0x2]
            return i.mnemonic == ZYDIS_MNEMONIC_MOV &&
                   i.operands[0].type == ZYDIS_OPERAND_TYPE_REGISTER &&
                   i.operands[0].reg.value == ZYDIS_REGISTER_AX &&
                   i.operands[1].type == ZYDIS_OPERAND_TYPE_MEMORY &&
                   i.operands[1].mem.base == ZYDIS_REGISTER_RBP &&
                   i.operands[1].mem.disp.value == 0x2;
        },
        [](const zydis_decoded_instr_t& i)->bool { // SUB RBP, 0x8  (allow LEA variant later if needed)
            return i.mnemonic == ZYDIS_MNEMONIC_SUB &&
                   i.operands[0].type == ZYDIS_OPERAND_TYPE_REGISTER &&
                   i.operands[0].reg.value == ZYDIS_REGISTER_RBP &&
                   i.operands[1].type == ZYDIS_OPERAND_TYPE_IMMEDIATE &&
                   i.operands[1].imm.value.u == 0x8;
        },
        [](const zydis_decoded_instr_t& i)->bool { // MUL DX
            return i.mnemonic == ZYDIS_MNEMONIC_MUL &&
                   i.operands[0].type == ZYDIS_OPERAND_TYPE_REGISTER &&
                   i.operands[0].reg.value == ZYDIS_REGISTER_DX;
        },
        [](const zydis_decoded_instr_t& i)->bool { // MOV [RBP+0x8], DX
            return i.mnemonic == ZYDIS_MNEMONIC_MOV &&
                   i.operands[0].type == ZYDIS_OPERAND_TYPE_MEMORY &&
                   i.operands[0].mem.base == ZYDIS_REGISTER_RBP &&
                   i.operands[0].mem.disp.value == 0x8 &&
                   i.operands[1].type == ZYDIS_OPERAND_TYPE_REGISTER &&
                   i.operands[1].reg.value == ZYDIS_REGISTER_DX;
        },
        [](const zydis_decoded_instr_t& i)->bool { // MOV [RBP+0xA], AX
            return i.mnemonic == ZYDIS_MNEMONIC_MOV &&
                   i.operands[0].type == ZYDIS_OPERAND_TYPE_MEMORY &&
                   i.operands[0].mem.base == ZYDIS_REGISTER_RBP &&
                   i.operands[0].mem.disp.value == 0xA &&
                   i.operands[1].type == ZYDIS_OPERAND_TYPE_REGISTER &&
                   i.operands[1].reg.value == ZYDIS_REGISTER_AX;
        },
        [](const zydis_decoded_instr_t& i)->bool { return i.mnemonic == ZYDIS_MNEMONIC_PUSHFQ; },
        [](const zydis_decoded_instr_t& i)->bool { // POP [RBP]
            return i.mnemonic == ZYDIS_MNEMONIC_POP &&
                   i.operands[0].type == ZYDIS_OPERAND_TYPE_MEMORY &&
                   i.operands[0].mem.base == ZYDIS_REGISTER_RBP;
        }
    } }
};

} // namespace vm::handler::profile