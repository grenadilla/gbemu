import json

include = '#include "cpu.h"'
unprefixed = 'CPU::Opcode CPU::opcode_table[] = {'
prefixed = 'CPU::Opcode CPU::opcode_prefixed_table[] = {'

with open('opcodes.json') as json_file:
    data = json.load(json_file)
    with open('opcode_mappings.cpp', 'w') as opcode_file:
        opcode_file.write(include + '\n\n')
        opcode_file.write(unprefixed + '\n')

        for opcode, op_data in data['unprefixed'].items():
            debug_string = op_data['mnemonic']
            for operand in op_data['operands']:
                if operand['immediate']:
                    debug_string += F" {operand['name']}"
                else:
                    debug_string += F" ({operand['name']})"
            cycle_arr = op_data['cycles']
            cycles = cycle_arr[0]
            not_taken_cycles = cycle_arr[1] if len(cycle_arr) == 2 else cycle_arr[0]

            if op_data['mnemonic'][:7] == 'ILLEGAL':
                op_func = '&CPU::opcode_illegal'
            elif opcode == '0xCB':
                op_func = '&CPU::opcode_prefix'
            else:
                op_func = f'&CPU::opcode_{opcode[2:]}'

            op_string = f'    {{{opcode}, false, "{debug_string}", ' \
                        f'{cycles}, {not_taken_cycles}, {op_func}}},\n'
            opcode_file.write(op_string)

        opcode_file.write('};\n')
        opcode_file.write(prefixed + '\n')

        for opcode, op_data in data['cbprefixed'].items():
            debug_string = op_data['mnemonic']
            for operand in op_data['operands']:
                if operand['immediate']:
                    debug_string += F" {operand['name']}"
                else:
                    debug_string += F" ({operand['name']})"
            
            cycle_arr = op_data['cycles']
            cycles = cycle_arr[0]
            not_taken_cycles = cycle_arr[1] if len(cycle_arr) == 2 else cycle_arr[0]
            op_func = f'&CPU::opcode_CB{opcode[2:]}'

            op_string = f'    {{{opcode}, true, "{debug_string}", ' \
                        f'{cycles}, {not_taken_cycles}, {op_func}}},\n'
            opcode_file.write(op_string)

        opcode_file.write('};\n')

        opcode_file.close();
    json_file.close()
