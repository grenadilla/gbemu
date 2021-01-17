#include "cpu.h"

CPU::Opcode CPU::opcode_table[] = {
    {0x00, false, "NOP", 4, 4, &CPU::opcode_00},
    {0x01, false, "LD BC d16", 12, 12, &CPU::opcode_01},
    {0x02, false, "LD (BC) A", 8, 8, &CPU::opcode_02},
    {0x03, false, "INC BC", 8, 8, &CPU::opcode_03},
    {0x04, false, "INC B", 4, 4, &CPU::opcode_04},
    {0x05, false, "DEC B", 4, 4, &CPU::opcode_05},
    {0x06, false, "LD B d8", 8, 8, &CPU::opcode_06},
    {0x07, false, "RLCA", 4, 4, &CPU::opcode_07},
    {0x08, false, "LD (a16) SP", 20, 20, &CPU::opcode_08},
    {0x09, false, "ADD HL BC", 8, 8, &CPU::opcode_09},
    {0x0A, false, "LD A (BC)", 8, 8, &CPU::opcode_0A},
    {0x0B, false, "DEC BC", 8, 8, &CPU::opcode_0B},
    {0x0C, false, "INC C", 4, 4, &CPU::opcode_0C},
    {0x0D, false, "DEC C", 4, 4, &CPU::opcode_0D},
    {0x0E, false, "LD C d8", 8, 8, &CPU::opcode_0E},
    {0x0F, false, "RRCA", 4, 4, &CPU::opcode_0F},
    {0x10, false, "STOP Ignored", 4, 4, &CPU::opcode_10},
    {0x11, false, "LD DE d16", 12, 12, &CPU::opcode_11},
    {0x12, false, "LD (DE) A", 8, 8, &CPU::opcode_12},
    {0x13, false, "INC DE", 8, 8, &CPU::opcode_13},
    {0x14, false, "INC D", 4, 4, &CPU::opcode_14},
    {0x15, false, "DEC D", 4, 4, &CPU::opcode_15},
    {0x16, false, "LD D d8", 8, 8, &CPU::opcode_16},
    {0x17, false, "RLA", 4, 4, &CPU::opcode_17},
    {0x18, false, "JR r8", 12, 12, &CPU::opcode_18},
    {0x19, false, "ADD HL DE", 8, 8, &CPU::opcode_19},
    {0x1A, false, "LD A (DE)", 8, 8, &CPU::opcode_1A},
    {0x1B, false, "DEC DE", 8, 8, &CPU::opcode_1B},
    {0x1C, false, "INC E", 4, 4, &CPU::opcode_1C},
    {0x1D, false, "DEC E", 4, 4, &CPU::opcode_1D},
    {0x1E, false, "LD E d8", 8, 8, &CPU::opcode_1E},
    {0x1F, false, "RRA", 4, 4, &CPU::opcode_1F},
    {0x20, false, "JR NZ r8", 12, 8, &CPU::opcode_20},
    {0x21, false, "LD HL d16", 12, 12, &CPU::opcode_21},
    {0x22, false, "LD (HL) A", 8, 8, &CPU::opcode_22},
    {0x23, false, "INC HL", 8, 8, &CPU::opcode_23},
    {0x24, false, "INC H", 4, 4, &CPU::opcode_24},
    {0x25, false, "DEC H", 4, 4, &CPU::opcode_25},
    {0x26, false, "LD H d8", 8, 8, &CPU::opcode_26},
    {0x27, false, "DAA", 4, 4, &CPU::opcode_27},
    {0x28, false, "JR Z r8", 12, 8, &CPU::opcode_28},
    {0x29, false, "ADD HL HL", 8, 8, &CPU::opcode_29},
    {0x2A, false, "LD A (HL)", 8, 8, &CPU::opcode_2A},
    {0x2B, false, "DEC HL", 8, 8, &CPU::opcode_2B},
    {0x2C, false, "INC L", 4, 4, &CPU::opcode_2C},
    {0x2D, false, "DEC L", 4, 4, &CPU::opcode_2D},
    {0x2E, false, "LD L d8", 8, 8, &CPU::opcode_2E},
    {0x2F, false, "CPL", 4, 4, &CPU::opcode_2F},
    {0x30, false, "JR NC r8", 12, 8, &CPU::opcode_30},
    {0x31, false, "LD SP d16", 12, 12, &CPU::opcode_31},
    {0x32, false, "LD (HL) A", 8, 8, &CPU::opcode_32},
    {0x33, false, "INC SP", 8, 8, &CPU::opcode_33},
    {0x34, false, "INC (HL)", 12, 12, &CPU::opcode_34},
    {0x35, false, "DEC (HL)", 12, 12, &CPU::opcode_35},
    {0x36, false, "LD (HL) d8", 12, 12, &CPU::opcode_36},
    {0x37, false, "SCF", 4, 4, &CPU::opcode_37},
    {0x38, false, "JR C r8", 12, 8, &CPU::opcode_38},
    {0x39, false, "ADD HL SP", 8, 8, &CPU::opcode_39},
    {0x3A, false, "LD A (HL)", 8, 8, &CPU::opcode_3A},
    {0x3B, false, "DEC SP", 8, 8, &CPU::opcode_3B},
    {0x3C, false, "INC A", 4, 4, &CPU::opcode_3C},
    {0x3D, false, "DEC A", 4, 4, &CPU::opcode_3D},
    {0x3E, false, "LD A d8", 8, 8, &CPU::opcode_3E},
    {0x3F, false, "CCF", 4, 4, &CPU::opcode_3F},
    {0x40, false, "LD B B", 4, 4, &CPU::opcode_40},
    {0x41, false, "LD B C", 4, 4, &CPU::opcode_41},
    {0x42, false, "LD B D", 4, 4, &CPU::opcode_42},
    {0x43, false, "LD B E", 4, 4, &CPU::opcode_43},
    {0x44, false, "LD B H", 4, 4, &CPU::opcode_44},
    {0x45, false, "LD B L", 4, 4, &CPU::opcode_45},
    {0x46, false, "LD B (HL)", 8, 8, &CPU::opcode_46},
    {0x47, false, "LD B A", 4, 4, &CPU::opcode_47},
    {0x48, false, "LD C B", 4, 4, &CPU::opcode_48},
    {0x49, false, "LD C C", 4, 4, &CPU::opcode_49},
    {0x4A, false, "LD C D", 4, 4, &CPU::opcode_4A},
    {0x4B, false, "LD C E", 4, 4, &CPU::opcode_4B},
    {0x4C, false, "LD C H", 4, 4, &CPU::opcode_4C},
    {0x4D, false, "LD C L", 4, 4, &CPU::opcode_4D},
    {0x4E, false, "LD C (HL)", 8, 8, &CPU::opcode_4E},
    {0x4F, false, "LD C A", 4, 4, &CPU::opcode_4F},
    {0x50, false, "LD D B", 4, 4, &CPU::opcode_50},
    {0x51, false, "LD D C", 4, 4, &CPU::opcode_51},
    {0x52, false, "LD D D", 4, 4, &CPU::opcode_52},
    {0x53, false, "LD D E", 4, 4, &CPU::opcode_53},
    {0x54, false, "LD D H", 4, 4, &CPU::opcode_54},
    {0x55, false, "LD D L", 4, 4, &CPU::opcode_55},
    {0x56, false, "LD D (HL)", 8, 8, &CPU::opcode_56},
    {0x57, false, "LD D A", 4, 4, &CPU::opcode_57},
    {0x58, false, "LD E B", 4, 4, &CPU::opcode_58},
    {0x59, false, "LD E C", 4, 4, &CPU::opcode_59},
    {0x5A, false, "LD E D", 4, 4, &CPU::opcode_5A},
    {0x5B, false, "LD E E", 4, 4, &CPU::opcode_5B},
    {0x5C, false, "LD E H", 4, 4, &CPU::opcode_5C},
    {0x5D, false, "LD E L", 4, 4, &CPU::opcode_5D},
    {0x5E, false, "LD E (HL)", 8, 8, &CPU::opcode_5E},
    {0x5F, false, "LD E A", 4, 4, &CPU::opcode_5F},
    {0x60, false, "LD H B", 4, 4, &CPU::opcode_60},
    {0x61, false, "LD H C", 4, 4, &CPU::opcode_61},
    {0x62, false, "LD H D", 4, 4, &CPU::opcode_62},
    {0x63, false, "LD H E", 4, 4, &CPU::opcode_63},
    {0x64, false, "LD H H", 4, 4, &CPU::opcode_64},
    {0x65, false, "LD H L", 4, 4, &CPU::opcode_65},
    {0x66, false, "LD H (HL)", 8, 8, &CPU::opcode_66},
    {0x67, false, "LD H A", 4, 4, &CPU::opcode_67},
    {0x68, false, "LD L B", 4, 4, &CPU::opcode_68},
    {0x69, false, "LD L C", 4, 4, &CPU::opcode_69},
    {0x6A, false, "LD L D", 4, 4, &CPU::opcode_6A},
    {0x6B, false, "LD L E", 4, 4, &CPU::opcode_6B},
    {0x6C, false, "LD L H", 4, 4, &CPU::opcode_6C},
    {0x6D, false, "LD L L", 4, 4, &CPU::opcode_6D},
    {0x6E, false, "LD L (HL)", 8, 8, &CPU::opcode_6E},
    {0x6F, false, "LD L A", 4, 4, &CPU::opcode_6F},
    {0x70, false, "LD (HL) B", 8, 8, &CPU::opcode_70},
    {0x71, false, "LD (HL) C", 8, 8, &CPU::opcode_71},
    {0x72, false, "LD (HL) D", 8, 8, &CPU::opcode_72},
    {0x73, false, "LD (HL) E", 8, 8, &CPU::opcode_73},
    {0x74, false, "LD (HL) H", 8, 8, &CPU::opcode_74},
    {0x75, false, "LD (HL) L", 8, 8, &CPU::opcode_75},
    {0x76, false, "HALT", 4, 4, &CPU::opcode_76},
    {0x77, false, "LD (HL) A", 8, 8, &CPU::opcode_77},
    {0x78, false, "LD A B", 4, 4, &CPU::opcode_78},
    {0x79, false, "LD A C", 4, 4, &CPU::opcode_79},
    {0x7A, false, "LD A D", 4, 4, &CPU::opcode_7A},
    {0x7B, false, "LD A E", 4, 4, &CPU::opcode_7B},
    {0x7C, false, "LD A H", 4, 4, &CPU::opcode_7C},
    {0x7D, false, "LD A L", 4, 4, &CPU::opcode_7D},
    {0x7E, false, "LD A (HL)", 8, 8, &CPU::opcode_7E},
    {0x7F, false, "LD A A", 4, 4, &CPU::opcode_7F},
    {0x80, false, "ADD A B", 4, 4, &CPU::opcode_80},
    {0x81, false, "ADD A C", 4, 4, &CPU::opcode_81},
    {0x82, false, "ADD A D", 4, 4, &CPU::opcode_82},
    {0x83, false, "ADD A E", 4, 4, &CPU::opcode_83},
    {0x84, false, "ADD A H", 4, 4, &CPU::opcode_84},
    {0x85, false, "ADD A L", 4, 4, &CPU::opcode_85},
    {0x86, false, "ADD A (HL)", 8, 8, &CPU::opcode_86},
    {0x87, false, "ADD A A", 4, 4, &CPU::opcode_87},
    {0x88, false, "ADC A B", 4, 4, &CPU::opcode_88},
    {0x89, false, "ADC A C", 4, 4, &CPU::opcode_89},
    {0x8A, false, "ADC A D", 4, 4, &CPU::opcode_8A},
    {0x8B, false, "ADC A E", 4, 4, &CPU::opcode_8B},
    {0x8C, false, "ADC A H", 4, 4, &CPU::opcode_8C},
    {0x8D, false, "ADC A L", 4, 4, &CPU::opcode_8D},
    {0x8E, false, "ADC A (HL)", 8, 8, &CPU::opcode_8E},
    {0x8F, false, "ADC A A", 4, 4, &CPU::opcode_8F},
    {0x90, false, "SUB B", 4, 4, &CPU::opcode_90},
    {0x91, false, "SUB C", 4, 4, &CPU::opcode_91},
    {0x92, false, "SUB D", 4, 4, &CPU::opcode_92},
    {0x93, false, "SUB E", 4, 4, &CPU::opcode_93},
    {0x94, false, "SUB H", 4, 4, &CPU::opcode_94},
    {0x95, false, "SUB L", 4, 4, &CPU::opcode_95},
    {0x96, false, "SUB (HL)", 8, 8, &CPU::opcode_96},
    {0x97, false, "SUB A", 4, 4, &CPU::opcode_97},
    {0x98, false, "SBC A B", 4, 4, &CPU::opcode_98},
    {0x99, false, "SBC A C", 4, 4, &CPU::opcode_99},
    {0x9A, false, "SBC A D", 4, 4, &CPU::opcode_9A},
    {0x9B, false, "SBC A E", 4, 4, &CPU::opcode_9B},
    {0x9C, false, "SBC A H", 4, 4, &CPU::opcode_9C},
    {0x9D, false, "SBC A L", 4, 4, &CPU::opcode_9D},
    {0x9E, false, "SBC A (HL)", 8, 8, &CPU::opcode_9E},
    {0x9F, false, "SBC A A", 4, 4, &CPU::opcode_9F},
    {0xA0, false, "AND B", 4, 4, &CPU::opcode_A0},
    {0xA1, false, "AND C", 4, 4, &CPU::opcode_A1},
    {0xA2, false, "AND D", 4, 4, &CPU::opcode_A2},
    {0xA3, false, "AND E", 4, 4, &CPU::opcode_A3},
    {0xA4, false, "AND H", 4, 4, &CPU::opcode_A4},
    {0xA5, false, "AND L", 4, 4, &CPU::opcode_A5},
    {0xA6, false, "AND (HL)", 8, 8, &CPU::opcode_A6},
    {0xA7, false, "AND A", 4, 4, &CPU::opcode_A7},
    {0xA8, false, "XOR B", 4, 4, &CPU::opcode_A8},
    {0xA9, false, "XOR C", 4, 4, &CPU::opcode_A9},
    {0xAA, false, "XOR D", 4, 4, &CPU::opcode_AA},
    {0xAB, false, "XOR E", 4, 4, &CPU::opcode_AB},
    {0xAC, false, "XOR H", 4, 4, &CPU::opcode_AC},
    {0xAD, false, "XOR L", 4, 4, &CPU::opcode_AD},
    {0xAE, false, "XOR (HL)", 8, 8, &CPU::opcode_AE},
    {0xAF, false, "XOR A", 4, 4, &CPU::opcode_AF},
    {0xB0, false, "OR B", 4, 4, &CPU::opcode_B0},
    {0xB1, false, "OR C", 4, 4, &CPU::opcode_B1},
    {0xB2, false, "OR D", 4, 4, &CPU::opcode_B2},
    {0xB3, false, "OR E", 4, 4, &CPU::opcode_B3},
    {0xB4, false, "OR H", 4, 4, &CPU::opcode_B4},
    {0xB5, false, "OR L", 4, 4, &CPU::opcode_B5},
    {0xB6, false, "OR (HL)", 8, 8, &CPU::opcode_B6},
    {0xB7, false, "OR A", 4, 4, &CPU::opcode_B7},
    {0xB8, false, "CP B", 4, 4, &CPU::opcode_B8},
    {0xB9, false, "CP C", 4, 4, &CPU::opcode_B9},
    {0xBA, false, "CP D", 4, 4, &CPU::opcode_BA},
    {0xBB, false, "CP E", 4, 4, &CPU::opcode_BB},
    {0xBC, false, "CP H", 4, 4, &CPU::opcode_BC},
    {0xBD, false, "CP L", 4, 4, &CPU::opcode_BD},
    {0xBE, false, "CP (HL)", 8, 8, &CPU::opcode_BE},
    {0xBF, false, "CP A", 4, 4, &CPU::opcode_BF},
    {0xC0, false, "RET NZ", 20, 8, &CPU::opcode_C0},
    {0xC1, false, "POP BC", 12, 12, &CPU::opcode_C1},
    {0xC2, false, "JP NZ a16", 16, 12, &CPU::opcode_C2},
    {0xC3, false, "JP a16", 16, 16, &CPU::opcode_C3},
    {0xC4, false, "CALL NZ a16", 24, 12, &CPU::opcode_C4},
    {0xC5, false, "PUSH BC", 16, 16, &CPU::opcode_C5},
    {0xC6, false, "ADD A d8", 8, 8, &CPU::opcode_C6},
    {0xC7, false, "RST 00H", 16, 16, &CPU::opcode_C7},
    {0xC8, false, "RET Z", 20, 8, &CPU::opcode_C8},
    {0xC9, false, "RET", 16, 16, &CPU::opcode_C9},
    {0xCA, false, "JP Z a16", 16, 12, &CPU::opcode_CA},
    {0xCB, false, "PREFIX", 4, 4, &CPU::run_opcode_prefix},
    {0xCC, false, "CALL Z a16", 24, 12, &CPU::opcode_CC},
    {0xCD, false, "CALL a16", 24, 24, &CPU::opcode_CD},
    {0xCE, false, "ADC A d8", 8, 8, &CPU::opcode_CE},
    {0xCF, false, "RST 08H", 16, 16, &CPU::opcode_CF},
    {0xD0, false, "RET NC", 20, 8, &CPU::opcode_D0},
    {0xD1, false, "POP DE", 12, 12, &CPU::opcode_D1},
    {0xD2, false, "JP NC a16", 16, 12, &CPU::opcode_D2},
    {0xD3, false, "ILLEGAL_D3", 4, 4, &CPU::opcode_illegal},
    {0xD4, false, "CALL NC a16", 24, 12, &CPU::opcode_D4},
    {0xD5, false, "PUSH DE", 16, 16, &CPU::opcode_D5},
    {0xD6, false, "SUB d8", 8, 8, &CPU::opcode_D6},
    {0xD7, false, "RST 10H", 16, 16, &CPU::opcode_D7},
    {0xD8, false, "RET C", 20, 8, &CPU::opcode_D8},
    {0xD9, false, "RETI", 16, 16, &CPU::opcode_D9},
    {0xDA, false, "JP C a16", 16, 12, &CPU::opcode_DA},
    {0xDB, false, "ILLEGAL_DB", 4, 4, &CPU::opcode_illegal},
    {0xDC, false, "CALL C a16", 24, 12, &CPU::opcode_DC},
    {0xDD, false, "ILLEGAL_DD", 4, 4, &CPU::opcode_illegal},
    {0xDE, false, "SBC A d8", 8, 8, &CPU::opcode_DE},
    {0xDF, false, "RST 18H", 16, 16, &CPU::opcode_DF},
    {0xE0, false, "LDH (a8) A", 12, 12, &CPU::opcode_E0},
    {0xE1, false, "POP HL", 12, 12, &CPU::opcode_E1},
    {0xE2, false, "LD (C) A", 8, 8, &CPU::opcode_E2},
    {0xE3, false, "ILLEGAL_E3", 4, 4, &CPU::opcode_illegal},
    {0xE4, false, "ILLEGAL_E4", 4, 4, &CPU::opcode_illegal},
    {0xE5, false, "PUSH HL", 16, 16, &CPU::opcode_E5},
    {0xE6, false, "AND d8", 8, 8, &CPU::opcode_E6},
    {0xE7, false, "RST 20H", 16, 16, &CPU::opcode_E7},
    {0xE8, false, "ADD SP r8", 16, 16, &CPU::opcode_E8},
    {0xE9, false, "JP HL", 4, 4, &CPU::opcode_E9},
    {0xEA, false, "LD (a16) A", 16, 16, &CPU::opcode_EA},
    {0xEB, false, "ILLEGAL_EB", 4, 4, &CPU::opcode_illegal},
    {0xEC, false, "ILLEGAL_EC", 4, 4, &CPU::opcode_illegal},
    {0xED, false, "ILLEGAL_ED", 4, 4, &CPU::opcode_illegal},
    {0xEE, false, "XOR d8", 8, 8, &CPU::opcode_EE},
    {0xEF, false, "RST 28H", 16, 16, &CPU::opcode_EF},
    {0xF0, false, "LDH A (a8)", 12, 12, &CPU::opcode_F0},
    {0xF1, false, "POP AF", 12, 12, &CPU::opcode_F1},
    {0xF2, false, "LD A (C)", 8, 8, &CPU::opcode_F2},
    {0xF3, false, "DI", 4, 4, &CPU::opcode_F3},
    {0xF4, false, "ILLEGAL_F4", 4, 4, &CPU::opcode_illegal},
    {0xF5, false, "PUSH AF", 16, 16, &CPU::opcode_F5},
    {0xF6, false, "OR d8", 8, 8, &CPU::opcode_F6},
    {0xF7, false, "RST 30H", 16, 16, &CPU::opcode_F7},
    {0xF8, false, "LD HL SP", 12, 12, &CPU::opcode_F8},
    {0xF9, false, "LD SP HL", 8, 8, &CPU::opcode_F9},
    {0xFA, false, "LD A (a16)", 16, 16, &CPU::opcode_FA},
    {0xFB, false, "EI", 4, 4, &CPU::opcode_FB},
    {0xFC, false, "ILLEGAL_FC", 4, 4, &CPU::opcode_illegal},
    {0xFD, false, "ILLEGAL_FD", 4, 4, &CPU::opcode_illegal},
    {0xFE, false, "CP d8", 8, 8, &CPU::opcode_FE},
    {0xFF, false, "RST 38H", 16, 16, &CPU::opcode_FF},
};
CPU::Opcode CPU::opcode_prefixed_table[] = {
    {0x00, true, "RLC B", 8, 8, &CPU::opcode_CB00},
    {0x01, true, "RLC C", 8, 8, &CPU::opcode_CB01},
    {0x02, true, "RLC D", 8, 8, &CPU::opcode_CB02},
    {0x03, true, "RLC E", 8, 8, &CPU::opcode_CB03},
    {0x04, true, "RLC H", 8, 8, &CPU::opcode_CB04},
    {0x05, true, "RLC L", 8, 8, &CPU::opcode_CB05},
    {0x06, true, "RLC (HL)", 16, 16, &CPU::opcode_CB06},
    {0x07, true, "RLC A", 8, 8, &CPU::opcode_CB07},
    {0x08, true, "RRC B", 8, 8, &CPU::opcode_CB08},
    {0x09, true, "RRC C", 8, 8, &CPU::opcode_CB09},
    {0x0A, true, "RRC D", 8, 8, &CPU::opcode_CB0A},
    {0x0B, true, "RRC E", 8, 8, &CPU::opcode_CB0B},
    {0x0C, true, "RRC H", 8, 8, &CPU::opcode_CB0C},
    {0x0D, true, "RRC L", 8, 8, &CPU::opcode_CB0D},
    {0x0E, true, "RRC (HL)", 16, 16, &CPU::opcode_CB0E},
    {0x0F, true, "RRC A", 8, 8, &CPU::opcode_CB0F},
    {0x10, true, "RL B", 8, 8, &CPU::opcode_CB10},
    {0x11, true, "RL C", 8, 8, &CPU::opcode_CB11},
    {0x12, true, "RL D", 8, 8, &CPU::opcode_CB12},
    {0x13, true, "RL E", 8, 8, &CPU::opcode_CB13},
    {0x14, true, "RL H", 8, 8, &CPU::opcode_CB14},
    {0x15, true, "RL L", 8, 8, &CPU::opcode_CB15},
    {0x16, true, "RL (HL)", 16, 16, &CPU::opcode_CB16},
    {0x17, true, "RL A", 8, 8, &CPU::opcode_CB17},
    {0x18, true, "RR B", 8, 8, &CPU::opcode_CB18},
    {0x19, true, "RR C", 8, 8, &CPU::opcode_CB19},
    {0x1A, true, "RR D", 8, 8, &CPU::opcode_CB1A},
    {0x1B, true, "RR E", 8, 8, &CPU::opcode_CB1B},
    {0x1C, true, "RR H", 8, 8, &CPU::opcode_CB1C},
    {0x1D, true, "RR L", 8, 8, &CPU::opcode_CB1D},
    {0x1E, true, "RR (HL)", 16, 16, &CPU::opcode_CB1E},
    {0x1F, true, "RR A", 8, 8, &CPU::opcode_CB1F},
    {0x20, true, "SLA B", 8, 8, &CPU::opcode_CB20},
    {0x21, true, "SLA C", 8, 8, &CPU::opcode_CB21},
    {0x22, true, "SLA D", 8, 8, &CPU::opcode_CB22},
    {0x23, true, "SLA E", 8, 8, &CPU::opcode_CB23},
    {0x24, true, "SLA H", 8, 8, &CPU::opcode_CB24},
    {0x25, true, "SLA L", 8, 8, &CPU::opcode_CB25},
    {0x26, true, "SLA (HL)", 16, 16, &CPU::opcode_CB26},
    {0x27, true, "SLA A", 8, 8, &CPU::opcode_CB27},
    {0x28, true, "SRA B", 8, 8, &CPU::opcode_CB28},
    {0x29, true, "SRA C", 8, 8, &CPU::opcode_CB29},
    {0x2A, true, "SRA D", 8, 8, &CPU::opcode_CB2A},
    {0x2B, true, "SRA E", 8, 8, &CPU::opcode_CB2B},
    {0x2C, true, "SRA H", 8, 8, &CPU::opcode_CB2C},
    {0x2D, true, "SRA L", 8, 8, &CPU::opcode_CB2D},
    {0x2E, true, "SRA (HL)", 16, 16, &CPU::opcode_CB2E},
    {0x2F, true, "SRA A", 8, 8, &CPU::opcode_CB2F},
    {0x30, true, "SWAP B", 8, 8, &CPU::opcode_CB30},
    {0x31, true, "SWAP C", 8, 8, &CPU::opcode_CB31},
    {0x32, true, "SWAP D", 8, 8, &CPU::opcode_CB32},
    {0x33, true, "SWAP E", 8, 8, &CPU::opcode_CB33},
    {0x34, true, "SWAP H", 8, 8, &CPU::opcode_CB34},
    {0x35, true, "SWAP L", 8, 8, &CPU::opcode_CB35},
    {0x36, true, "SWAP (HL)", 16, 16, &CPU::opcode_CB36},
    {0x37, true, "SWAP A", 8, 8, &CPU::opcode_CB37},
    {0x38, true, "SRL B", 8, 8, &CPU::opcode_CB38},
    {0x39, true, "SRL C", 8, 8, &CPU::opcode_CB39},
    {0x3A, true, "SRL D", 8, 8, &CPU::opcode_CB3A},
    {0x3B, true, "SRL E", 8, 8, &CPU::opcode_CB3B},
    {0x3C, true, "SRL H", 8, 8, &CPU::opcode_CB3C},
    {0x3D, true, "SRL L", 8, 8, &CPU::opcode_CB3D},
    {0x3E, true, "SRL (HL)", 16, 16, &CPU::opcode_CB3E},
    {0x3F, true, "SRL A", 8, 8, &CPU::opcode_CB3F},
    {0x40, true, "BIT 0 B", 8, 8, &CPU::opcode_CB40},
    {0x41, true, "BIT 0 C", 8, 8, &CPU::opcode_CB41},
    {0x42, true, "BIT 0 D", 8, 8, &CPU::opcode_CB42},
    {0x43, true, "BIT 0 E", 8, 8, &CPU::opcode_CB43},
    {0x44, true, "BIT 0 H", 8, 8, &CPU::opcode_CB44},
    {0x45, true, "BIT 0 L", 8, 8, &CPU::opcode_CB45},
    {0x46, true, "BIT 0 (HL)", 12, 12, &CPU::opcode_CB46},
    {0x47, true, "BIT 0 A", 8, 8, &CPU::opcode_CB47},
    {0x48, true, "BIT 1 B", 8, 8, &CPU::opcode_CB48},
    {0x49, true, "BIT 1 C", 8, 8, &CPU::opcode_CB49},
    {0x4A, true, "BIT 1 D", 8, 8, &CPU::opcode_CB4A},
    {0x4B, true, "BIT 1 E", 8, 8, &CPU::opcode_CB4B},
    {0x4C, true, "BIT 1 H", 8, 8, &CPU::opcode_CB4C},
    {0x4D, true, "BIT 1 L", 8, 8, &CPU::opcode_CB4D},
    {0x4E, true, "BIT 1 (HL)", 12, 12, &CPU::opcode_CB4E},
    {0x4F, true, "BIT 1 A", 8, 8, &CPU::opcode_CB4F},
    {0x50, true, "BIT 2 B", 8, 8, &CPU::opcode_CB50},
    {0x51, true, "BIT 2 C", 8, 8, &CPU::opcode_CB51},
    {0x52, true, "BIT 2 D", 8, 8, &CPU::opcode_CB52},
    {0x53, true, "BIT 2 E", 8, 8, &CPU::opcode_CB53},
    {0x54, true, "BIT 2 H", 8, 8, &CPU::opcode_CB54},
    {0x55, true, "BIT 2 L", 8, 8, &CPU::opcode_CB55},
    {0x56, true, "BIT 2 (HL)", 12, 12, &CPU::opcode_CB56},
    {0x57, true, "BIT 2 A", 8, 8, &CPU::opcode_CB57},
    {0x58, true, "BIT 3 B", 8, 8, &CPU::opcode_CB58},
    {0x59, true, "BIT 3 C", 8, 8, &CPU::opcode_CB59},
    {0x5A, true, "BIT 3 D", 8, 8, &CPU::opcode_CB5A},
    {0x5B, true, "BIT 3 E", 8, 8, &CPU::opcode_CB5B},
    {0x5C, true, "BIT 3 H", 8, 8, &CPU::opcode_CB5C},
    {0x5D, true, "BIT 3 L", 8, 8, &CPU::opcode_CB5D},
    {0x5E, true, "BIT 3 (HL)", 12, 12, &CPU::opcode_CB5E},
    {0x5F, true, "BIT 3 A", 8, 8, &CPU::opcode_CB5F},
    {0x60, true, "BIT 4 B", 8, 8, &CPU::opcode_CB60},
    {0x61, true, "BIT 4 C", 8, 8, &CPU::opcode_CB61},
    {0x62, true, "BIT 4 D", 8, 8, &CPU::opcode_CB62},
    {0x63, true, "BIT 4 E", 8, 8, &CPU::opcode_CB63},
    {0x64, true, "BIT 4 H", 8, 8, &CPU::opcode_CB64},
    {0x65, true, "BIT 4 L", 8, 8, &CPU::opcode_CB65},
    {0x66, true, "BIT 4 (HL)", 12, 12, &CPU::opcode_CB66},
    {0x67, true, "BIT 4 A", 8, 8, &CPU::opcode_CB67},
    {0x68, true, "BIT 5 B", 8, 8, &CPU::opcode_CB68},
    {0x69, true, "BIT 5 C", 8, 8, &CPU::opcode_CB69},
    {0x6A, true, "BIT 5 D", 8, 8, &CPU::opcode_CB6A},
    {0x6B, true, "BIT 5 E", 8, 8, &CPU::opcode_CB6B},
    {0x6C, true, "BIT 5 H", 8, 8, &CPU::opcode_CB6C},
    {0x6D, true, "BIT 5 L", 8, 8, &CPU::opcode_CB6D},
    {0x6E, true, "BIT 5 (HL)", 12, 12, &CPU::opcode_CB6E},
    {0x6F, true, "BIT 5 A", 8, 8, &CPU::opcode_CB6F},
    {0x70, true, "BIT 6 B", 8, 8, &CPU::opcode_CB70},
    {0x71, true, "BIT 6 C", 8, 8, &CPU::opcode_CB71},
    {0x72, true, "BIT 6 D", 8, 8, &CPU::opcode_CB72},
    {0x73, true, "BIT 6 E", 8, 8, &CPU::opcode_CB73},
    {0x74, true, "BIT 6 H", 8, 8, &CPU::opcode_CB74},
    {0x75, true, "BIT 6 L", 8, 8, &CPU::opcode_CB75},
    {0x76, true, "BIT 6 (HL)", 12, 12, &CPU::opcode_CB76},
    {0x77, true, "BIT 6 A", 8, 8, &CPU::opcode_CB77},
    {0x78, true, "BIT 7 B", 8, 8, &CPU::opcode_CB78},
    {0x79, true, "BIT 7 C", 8, 8, &CPU::opcode_CB79},
    {0x7A, true, "BIT 7 D", 8, 8, &CPU::opcode_CB7A},
    {0x7B, true, "BIT 7 E", 8, 8, &CPU::opcode_CB7B},
    {0x7C, true, "BIT 7 H", 8, 8, &CPU::opcode_CB7C},
    {0x7D, true, "BIT 7 L", 8, 8, &CPU::opcode_CB7D},
    {0x7E, true, "BIT 7 (HL)", 12, 12, &CPU::opcode_CB7E},
    {0x7F, true, "BIT 7 A", 8, 8, &CPU::opcode_CB7F},
    {0x80, true, "RES 0 B", 8, 8, &CPU::opcode_CB80},
    {0x81, true, "RES 0 C", 8, 8, &CPU::opcode_CB81},
    {0x82, true, "RES 0 D", 8, 8, &CPU::opcode_CB82},
    {0x83, true, "RES 0 E", 8, 8, &CPU::opcode_CB83},
    {0x84, true, "RES 0 H", 8, 8, &CPU::opcode_CB84},
    {0x85, true, "RES 0 L", 8, 8, &CPU::opcode_CB85},
    {0x86, true, "RES 0 (HL)", 16, 16, &CPU::opcode_CB86},
    {0x87, true, "RES 0 A", 8, 8, &CPU::opcode_CB87},
    {0x88, true, "RES 1 B", 8, 8, &CPU::opcode_CB88},
    {0x89, true, "RES 1 C", 8, 8, &CPU::opcode_CB89},
    {0x8A, true, "RES 1 D", 8, 8, &CPU::opcode_CB8A},
    {0x8B, true, "RES 1 E", 8, 8, &CPU::opcode_CB8B},
    {0x8C, true, "RES 1 H", 8, 8, &CPU::opcode_CB8C},
    {0x8D, true, "RES 1 L", 8, 8, &CPU::opcode_CB8D},
    {0x8E, true, "RES 1 (HL)", 16, 16, &CPU::opcode_CB8E},
    {0x8F, true, "RES 1 A", 8, 8, &CPU::opcode_CB8F},
    {0x90, true, "RES 2 B", 8, 8, &CPU::opcode_CB90},
    {0x91, true, "RES 2 C", 8, 8, &CPU::opcode_CB91},
    {0x92, true, "RES 2 D", 8, 8, &CPU::opcode_CB92},
    {0x93, true, "RES 2 E", 8, 8, &CPU::opcode_CB93},
    {0x94, true, "RES 2 H", 8, 8, &CPU::opcode_CB94},
    {0x95, true, "RES 2 L", 8, 8, &CPU::opcode_CB95},
    {0x96, true, "RES 2 (HL)", 16, 16, &CPU::opcode_CB96},
    {0x97, true, "RES 2 A", 8, 8, &CPU::opcode_CB97},
    {0x98, true, "RES 3 B", 8, 8, &CPU::opcode_CB98},
    {0x99, true, "RES 3 C", 8, 8, &CPU::opcode_CB99},
    {0x9A, true, "RES 3 D", 8, 8, &CPU::opcode_CB9A},
    {0x9B, true, "RES 3 E", 8, 8, &CPU::opcode_CB9B},
    {0x9C, true, "RES 3 H", 8, 8, &CPU::opcode_CB9C},
    {0x9D, true, "RES 3 L", 8, 8, &CPU::opcode_CB9D},
    {0x9E, true, "RES 3 (HL)", 16, 16, &CPU::opcode_CB9E},
    {0x9F, true, "RES 3 A", 8, 8, &CPU::opcode_CB9F},
    {0xA0, true, "RES 4 B", 8, 8, &CPU::opcode_CBA0},
    {0xA1, true, "RES 4 C", 8, 8, &CPU::opcode_CBA1},
    {0xA2, true, "RES 4 D", 8, 8, &CPU::opcode_CBA2},
    {0xA3, true, "RES 4 E", 8, 8, &CPU::opcode_CBA3},
    {0xA4, true, "RES 4 H", 8, 8, &CPU::opcode_CBA4},
    {0xA5, true, "RES 4 L", 8, 8, &CPU::opcode_CBA5},
    {0xA6, true, "RES 4 (HL)", 16, 16, &CPU::opcode_CBA6},
    {0xA7, true, "RES 4 A", 8, 8, &CPU::opcode_CBA7},
    {0xA8, true, "RES 5 B", 8, 8, &CPU::opcode_CBA8},
    {0xA9, true, "RES 5 C", 8, 8, &CPU::opcode_CBA9},
    {0xAA, true, "RES 5 D", 8, 8, &CPU::opcode_CBAA},
    {0xAB, true, "RES 5 E", 8, 8, &CPU::opcode_CBAB},
    {0xAC, true, "RES 5 H", 8, 8, &CPU::opcode_CBAC},
    {0xAD, true, "RES 5 L", 8, 8, &CPU::opcode_CBAD},
    {0xAE, true, "RES 5 (HL)", 16, 16, &CPU::opcode_CBAE},
    {0xAF, true, "RES 5 A", 8, 8, &CPU::opcode_CBAF},
    {0xB0, true, "RES 6 B", 8, 8, &CPU::opcode_CBB0},
    {0xB1, true, "RES 6 C", 8, 8, &CPU::opcode_CBB1},
    {0xB2, true, "RES 6 D", 8, 8, &CPU::opcode_CBB2},
    {0xB3, true, "RES 6 E", 8, 8, &CPU::opcode_CBB3},
    {0xB4, true, "RES 6 H", 8, 8, &CPU::opcode_CBB4},
    {0xB5, true, "RES 6 L", 8, 8, &CPU::opcode_CBB5},
    {0xB6, true, "RES 6 (HL)", 16, 16, &CPU::opcode_CBB6},
    {0xB7, true, "RES 6 A", 8, 8, &CPU::opcode_CBB7},
    {0xB8, true, "RES 7 B", 8, 8, &CPU::opcode_CBB8},
    {0xB9, true, "RES 7 C", 8, 8, &CPU::opcode_CBB9},
    {0xBA, true, "RES 7 D", 8, 8, &CPU::opcode_CBBA},
    {0xBB, true, "RES 7 E", 8, 8, &CPU::opcode_CBBB},
    {0xBC, true, "RES 7 H", 8, 8, &CPU::opcode_CBBC},
    {0xBD, true, "RES 7 L", 8, 8, &CPU::opcode_CBBD},
    {0xBE, true, "RES 7 (HL)", 16, 16, &CPU::opcode_CBBE},
    {0xBF, true, "RES 7 A", 8, 8, &CPU::opcode_CBBF},
    {0xC0, true, "SET 0 B", 8, 8, &CPU::opcode_CBC0},
    {0xC1, true, "SET 0 C", 8, 8, &CPU::opcode_CBC1},
    {0xC2, true, "SET 0 D", 8, 8, &CPU::opcode_CBC2},
    {0xC3, true, "SET 0 E", 8, 8, &CPU::opcode_CBC3},
    {0xC4, true, "SET 0 H", 8, 8, &CPU::opcode_CBC4},
    {0xC5, true, "SET 0 L", 8, 8, &CPU::opcode_CBC5},
    {0xC6, true, "SET 0 (HL)", 16, 16, &CPU::opcode_CBC6},
    {0xC7, true, "SET 0 A", 8, 8, &CPU::opcode_CBC7},
    {0xC8, true, "SET 1 B", 8, 8, &CPU::opcode_CBC8},
    {0xC9, true, "SET 1 C", 8, 8, &CPU::opcode_CBC9},
    {0xCA, true, "SET 1 D", 8, 8, &CPU::opcode_CBCA},
    {0xCB, true, "SET 1 E", 8, 8, &CPU::opcode_CBCB},
    {0xCC, true, "SET 1 H", 8, 8, &CPU::opcode_CBCC},
    {0xCD, true, "SET 1 L", 8, 8, &CPU::opcode_CBCD},
    {0xCE, true, "SET 1 (HL)", 16, 16, &CPU::opcode_CBCE},
    {0xCF, true, "SET 1 A", 8, 8, &CPU::opcode_CBCF},
    {0xD0, true, "SET 2 B", 8, 8, &CPU::opcode_CBD0},
    {0xD1, true, "SET 2 C", 8, 8, &CPU::opcode_CBD1},
    {0xD2, true, "SET 2 D", 8, 8, &CPU::opcode_CBD2},
    {0xD3, true, "SET 2 E", 8, 8, &CPU::opcode_CBD3},
    {0xD4, true, "SET 2 H", 8, 8, &CPU::opcode_CBD4},
    {0xD5, true, "SET 2 L", 8, 8, &CPU::opcode_CBD5},
    {0xD6, true, "SET 2 (HL)", 16, 16, &CPU::opcode_CBD6},
    {0xD7, true, "SET 2 A", 8, 8, &CPU::opcode_CBD7},
    {0xD8, true, "SET 3 B", 8, 8, &CPU::opcode_CBD8},
    {0xD9, true, "SET 3 C", 8, 8, &CPU::opcode_CBD9},
    {0xDA, true, "SET 3 D", 8, 8, &CPU::opcode_CBDA},
    {0xDB, true, "SET 3 E", 8, 8, &CPU::opcode_CBDB},
    {0xDC, true, "SET 3 H", 8, 8, &CPU::opcode_CBDC},
    {0xDD, true, "SET 3 L", 8, 8, &CPU::opcode_CBDD},
    {0xDE, true, "SET 3 (HL)", 16, 16, &CPU::opcode_CBDE},
    {0xDF, true, "SET 3 A", 8, 8, &CPU::opcode_CBDF},
    {0xE0, true, "SET 4 B", 8, 8, &CPU::opcode_CBE0},
    {0xE1, true, "SET 4 C", 8, 8, &CPU::opcode_CBE1},
    {0xE2, true, "SET 4 D", 8, 8, &CPU::opcode_CBE2},
    {0xE3, true, "SET 4 E", 8, 8, &CPU::opcode_CBE3},
    {0xE4, true, "SET 4 H", 8, 8, &CPU::opcode_CBE4},
    {0xE5, true, "SET 4 L", 8, 8, &CPU::opcode_CBE5},
    {0xE6, true, "SET 4 (HL)", 16, 16, &CPU::opcode_CBE6},
    {0xE7, true, "SET 4 A", 8, 8, &CPU::opcode_CBE7},
    {0xE8, true, "SET 5 B", 8, 8, &CPU::opcode_CBE8},
    {0xE9, true, "SET 5 C", 8, 8, &CPU::opcode_CBE9},
    {0xEA, true, "SET 5 D", 8, 8, &CPU::opcode_CBEA},
    {0xEB, true, "SET 5 E", 8, 8, &CPU::opcode_CBEB},
    {0xEC, true, "SET 5 H", 8, 8, &CPU::opcode_CBEC},
    {0xED, true, "SET 5 L", 8, 8, &CPU::opcode_CBED},
    {0xEE, true, "SET 5 (HL)", 16, 16, &CPU::opcode_CBEE},
    {0xEF, true, "SET 5 A", 8, 8, &CPU::opcode_CBEF},
    {0xF0, true, "SET 6 B", 8, 8, &CPU::opcode_CBF0},
    {0xF1, true, "SET 6 C", 8, 8, &CPU::opcode_CBF1},
    {0xF2, true, "SET 6 D", 8, 8, &CPU::opcode_CBF2},
    {0xF3, true, "SET 6 E", 8, 8, &CPU::opcode_CBF3},
    {0xF4, true, "SET 6 H", 8, 8, &CPU::opcode_CBF4},
    {0xF5, true, "SET 6 L", 8, 8, &CPU::opcode_CBF5},
    {0xF6, true, "SET 6 (HL)", 16, 16, &CPU::opcode_CBF6},
    {0xF7, true, "SET 6 A", 8, 8, &CPU::opcode_CBF7},
    {0xF8, true, "SET 7 B", 8, 8, &CPU::opcode_CBF8},
    {0xF9, true, "SET 7 C", 8, 8, &CPU::opcode_CBF9},
    {0xFA, true, "SET 7 D", 8, 8, &CPU::opcode_CBFA},
    {0xFB, true, "SET 7 E", 8, 8, &CPU::opcode_CBFB},
    {0xFC, true, "SET 7 H", 8, 8, &CPU::opcode_CBFC},
    {0xFD, true, "SET 7 L", 8, 8, &CPU::opcode_CBFD},
    {0xFE, true, "SET 7 (HL)", 16, 16, &CPU::opcode_CBFE},
    {0xFF, true, "SET 7 A", 8, 8, &CPU::opcode_CBFF},
};
