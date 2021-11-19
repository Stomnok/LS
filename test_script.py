import subprocess
import os

order=int(input('Enter order (power of 2): '))
filename='LS_'

path_to_program=os.path.abspath("makeLS")

for i in range(50):
	new_filename=filename+str(i).zfill(4)+'.txt'
	with open(new_filename,'w') as empty_file:
		empty_file.write(' ')
	subprocess.call([path_to_program,str(order),new_filename])
