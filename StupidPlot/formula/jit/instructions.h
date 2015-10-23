#pragma once

#include <vector>
#include <string>
#include <formula/jit/types.h>

using std::vector;

namespace StupidPlot
{
    namespace Formula
    {
        namespace JIT
        {
            enum InstructionName
            {
                INS_MOVSD_XMM_MEM,
                INS_MOVSD_XMM_XMM,
                INS_MOVSD_MEM_XMM,

                INS_ADDSD_XMM_XMM,
                INS_SUBSD_XMM_XMM,
                INS_MULSD_XMM_XMM,
                INS_DIVSD_XMM_XMM,
                INS_SQRTSD_XMM_XMM,

                INS_FLD_ST0_MEM,
                INS_FST_MEM_ST0,

                INS_FSIN,
                INS_FCOS,
            };

            enum InstructionParameterType
            {
                INS_PARAM_MEM,
                INS_PARAM_XMM,
            };

            struct InstructionParameter
            {
                InstructionParameterType type;
                union InstructionParameterValue
                {
                    MEM mem;
                    XMM xmm;
                    InstructionParameterValue()
                    {
                    }
                } value;
                InstructionParameter(MEM mem)
                {
                    type = InstructionParameterType::INS_PARAM_MEM;
                    value.mem = mem;
                }
                InstructionParameter(XMM xmm)
                {
                    type = InstructionParameterType::INS_PARAM_XMM;
                    value.xmm = xmm;
                }
                wstring toString()
                {
                    if (type == InstructionParameterType::INS_PARAM_MEM)
                    {
                        return value.mem.toString();
                    }
                    else
                    {
                        return value.xmm.toString();
                    }
                }
            };

            struct Instruction
            {
                InstructionName name;
                vector<InstructionParameter> params;
                Instruction(InstructionName _name)
                {
                    name = _name;
                }
                wstring toString()
                {
                    wstring insName;
                    switch (name)
                    {
                    case INS_MOVSD_MEM_XMM: insName = L"MOVSD"; break;
                    case INS_MOVSD_XMM_XMM: insName = L"MOVSD"; break;
                    case INS_MOVSD_XMM_MEM: insName = L"MOVSD"; break;
                    case INS_ADDSD_XMM_XMM: insName = L"ADDSD"; break;
                    case INS_SUBSD_XMM_XMM: insName = L"SUBSD"; break;
                    case INS_MULSD_XMM_XMM: insName = L"MULSD"; break;
                    case INS_DIVSD_XMM_XMM: insName = L"DIVSD"; break;
                    case INS_FSIN: insName = L"FSIN"; break;
                    case INS_FCOS: insName = L"FCOS"; break;
                    case INS_FLD_ST0_MEM: insName = L"FLD"; break;
                    case INS_FST_MEM_ST0: insName = L"FST"; break;
                    }
                    for (auto param : params)
                    {
                        insName += L" " + param.toString();
                    }
                    return insName;
                }
            };
        }
    }
}