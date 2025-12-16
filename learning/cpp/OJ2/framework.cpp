#include <bits/stdc++.h>
#include <cassert>
#include <iostream>
#define bug cout << "bug " << __LINE__ << endl
#define index xedni

#define I_Type 1
#define R_Type 2
#define J_Type 3

const int MAXR = 10;
const int MAXM = 65536 + 10;
const int MAXN = 100000 + 10;

using namespace std;

int Instruction_Type;
int OP, OPR, SR1, SR2, DR, Imm16, PC_Offset_26;
int PC;

int reg[MAXR], mem[MAXM]; // mem[i] means the i-th byte since 0x30000000, e.g. mem[2] means the value store at 0x30000002
unsigned int prog[MAXN];  // prog[i] means the i-th line of program

inline int Modify_Mem_Addr(int Real_Addr) // Turn a real memory address to an array index of mem[]
{
    return Real_Addr & 0xFFFF;
}
inline int Modify_Prog_Addr(int Real_Addr) // Turn a real program address to the array index of prog[]
{
    return (Real_Addr - 0x40000000) / 4;
}

void Read_Instruction()
{
    unsigned int inst = prog[Modify_Prog_Addr(PC)];

    // TODO: Use bit operations to get OP
    OP = (inst >> 26) & 0x0000003Fu;

    if (OP == 0) // instruction is R_Type
    {
        Instruction_Type = R_Type;
        // TODO: Use bit operations to get these values
        OPR = (inst & 0x0000003Fu);
        SR1 = ((inst >> 21) & 0x0000001Fu);
        SR2 = ((inst >> 16) & 0x0000001Fu);
        DR = ((inst >> 11) & 0x0000001Fu);
        // END of this TODO block
        return;
    }

    if (OP == 0b101100 || OP == 0b110000) // instruction is J_Type
    {
        Instruction_Type = J_Type;
        // TODO: Use bit operations to get PC_Offset_26
        PC_Offset_26 = inst & 0x03FFFFFFu;
        // END of this TODO block
        return;
    }

    Instruction_Type = I_Type;
    // TODO: Use bit operations to get these values
    SR1 = ((inst >> 21) & 0x0000001Fu);
    DR = ((inst >> 16) & 0x0000001Fu);
    Imm16 = inst & 0x0000FFFFu;
    // END of this TODO block
    return;
}

inline int sign_extend(int I, int data_size) // extend sign bit of a data_size-bit int to a 32-bit int
{
    return ((0 - ((I >> (data_size - 1)) & 1)) << data_size) | (I & (0xFFFFFFFF >> (32 - data_size)));
}

void Run_Prog()
{
    PC = 0x40000000; // Initialize PC

    while (1)
    {
        Read_Instruction();
        bool Jump_Flag = 0; // Whether this instruction is a Jump Instruction

        int Imm16_ext = sign_extend(Imm16, 16);
        int PC_Offset_26_ext = sign_extend(PC_Offset_26, 26);

        if (Instruction_Type == I_Type)
        {
            // TODO: We've finished ADDI and LB for you as examples, rest cases are for you
            switch (OP)

            {
            case 0b000001: // ADDI
                reg[DR] = reg[SR1] + Imm16_ext;
                break;

            case 0b000011: // SUBI
                reg[DR] = reg[SR1] - Imm16_ext;
                break;

            case 0b001001: // ANDI
                reg[DR] = reg[SR1] & Imm16_ext;
                break;

            case 0b001010: // ORI
                reg[DR] = reg[SR1] | Imm16_ext;
                break;

            case 0b001011: // XORI
                reg[DR] = reg[SR1] ^ Imm16_ext;
                break;

            case 0b001100: // LHI
                reg[DR] = Imm16_ext << 16;
                break;

            case 0b001101: // SLLI
                reg[DR] = reg[SR1] << Imm16_ext;
                break;

            case 0b001110: // SRLI
                reg[DR] = (reg[SR1] >> Imm16_ext) & (0xFFFFFFFFu >> (Imm16_ext));
                break;

            case 0b001111: // SRAI
                reg[DR] = reg[SR1] >> Imm16_ext;
                break;

            case 0b010000: // SLTI
                reg[DR] = (reg[SR1] < Imm16_ext);
                break;

            case 0b010010: // SLEI
                reg[DR] = (reg[SR1] <= Imm16_ext);
                break;

            case 0b010100: // SEQI
                reg[DR] = (reg[SR1] == Imm16_ext);
                break;

            case 0b010110: // LB
                reg[DR] = mem[Modify_Mem_Addr(reg[SR1] + Imm16_ext)];
                break;

            case 0b010111: // SB
                mem[Modify_Mem_Addr(reg[SR1] + Imm16_ext)] = reg[DR];
                break;

            case 0b011100: // LW
                reg[DR] = (mem[Modify_Mem_Addr(reg[SR1] + Imm16_ext + 0)]) | (mem[Modify_Mem_Addr(reg[SR1] + Imm16_ext + 1)]) << 8 | (mem[Modify_Mem_Addr(reg[SR1] + Imm16_ext + 2)]) << 16 | (mem[Modify_Mem_Addr(reg[SR1] + Imm16_ext + 3)]) << 24;
                break;

            case 0b011101: // SW
                mem[Modify_Mem_Addr(reg[SR1] + Imm16_ext + 0)] = (reg[DR]) & 0x000000FFu;
                mem[Modify_Mem_Addr(reg[SR1] + Imm16_ext + 1)] = (reg[DR] >> 8) & 0x000000FFu;
                mem[Modify_Mem_Addr(reg[SR1] + Imm16_ext + 2)] = (reg[DR] >> 16) & 0x000000FFu;
                mem[Modify_Mem_Addr(reg[SR1] + Imm16_ext + 3)] = (reg[DR] >> 24) & 0x000000FFu;
                break;

            case 0b101000: // BEQZ
                if (reg[SR1] == 0)
                {
                    PC = PC + Imm16_ext + 4;
                    Jump_Flag = 1;
                }
                break;

            case 0b101001: // BNEZ
                if (reg[SR1] != 0)
                {
                    PC = PC + Imm16_ext + 4;
                    Jump_Flag = 1;
                }

                break;
                // END of this TODO block

            default:
                assert(0 && "Invalid I_Type Instruction!");
                break;
            }
        }
        else if (Instruction_Type == R_Type)
        {
            // TODO: Go finish R_Type cases then
            switch (OPR)
            {
            case 0b000001: // ADD
                reg[DR] = reg[SR1] + reg[SR2];
                break;

            case 0b000011: // SUB
                reg[DR] = reg[SR1] - reg[SR2];
                break;

            case 0b001001: // AND
                reg[DR] = reg[SR1] & reg[SR2];
                break;

            case 0b001010: // OR
                reg[DR] = reg[SR1] | reg[SR2];
                break;

            case 0b001011: // XOR
                reg[DR] = reg[SR1] ^ reg[SR2];
                break;

            case 0b001101: // SLL
                reg[DR] = reg[SR1] << reg[SR2];
                break;

            case 0b001110: // SRL
                reg[DR] = (reg[SR1] >> reg[SR2]) & (0xFFFFFFFFu >> (reg[SR2]));
                break;

            case 0b001111: // SRA
                reg[DR] = reg[SR1] >> reg[SR2];
                break;

            case 0b010000: // SLT
                reg[DR] = (reg[SR1] < reg[SR2]);
                break;

            case 0b010010: // SLE
                reg[DR] = (reg[SR1] <= reg[SR2]);
                break;

            case 0b010100: // SEQ
                reg[DR] = (reg[SR1] == reg[SR2]);
                break;

            case 0b101101: // JR
                PC = reg[SR1];
                Jump_Flag = 1;
                break;
                // END of this TODO block

            default:
                assert(0 && "Invalid R_Type Instruction!");
                break;
            }
        }
        else if (Instruction_Type == J_Type)
        {
            // TODO: Only J is to be finished, TRAP goes back to main() directly
            switch (OP)
            {
            case 0b101100: // J
                PC = PC + PC_Offset_26_ext + 4;
                Jump_Flag = 1;
                break;
                // END of this TODO block

            case 0b110000: // TRAP
                return;

            default:
                assert(0 && "Invalid J_Type Instruction!");
                break;
            }
        }

        // TODO: Change PC if this is not a jump instruction
        if (!Jump_Flag)
            PC = PC + 4;
    }
}

signed main()
{
    // These two lines are used to speed up 'cin' and 'cout'.
    // But be careful! If you use these two lines, then you cannot use printf/scanf/puts/getchar... in <stdio.h>
    // You can try what will happen if you combine 'cin', 'cout' from <iostream> and 'printf', 'scanf' from <stdio.h> under these two lines, and search for why.
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, m, q;
    cin >> n >> m >> q;

    for (int i = 1; i <= m; i++)
    {
        char c;
        int p, v;
        cin >> c >> p >> v;

        if (c == 'R')
            reg[p] = v;
        if (c == 'M')
            mem[Modify_Mem_Addr(p)] = v;
    }

    for (int i = 1; i <= n; i++)
    {
        cin >> prog[i - 1];
    }

    // This is the function you need to implement
    Run_Prog();

    for (int i = 0; i <= 7; i++)
        cout << reg[i] << " ";
    cout << endl;

    for (int i = 1; i <= q; i++)
    {
        int qaddr;
        cin >> qaddr;
        cout << mem[Modify_Mem_Addr(qaddr)] << " ";
    }
    cout << endl;

    return 0;
}