
def fact(x): return (1 if x==0 else x * fact(x-1))

lines_str = raw_input() 'get input
lines_int = int(lines_str)  'convert str to int

list_inputs = []

for i in range(0, lines_int):
    num_str = raw_input()
    num_int = int(num_str)
    list_inputs.append(num_int)
    
