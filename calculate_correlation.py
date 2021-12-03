#!/usr/bin/python3

import numpy as np
import scipy.stats
import statistics
import sys

symbol=sys.argv[1]
amount_LS=int(sys.argv[2])

all_datasets=[]
spearmanr_list=[]
for i in range(amount_LS):
	filename='LS_'+str(i).zfill(4)+'.txt'
	dataset=[]
	with open(filename,'r') as LS:
		for line in LS:
			line_list=[x for x in line.split(' ') if len(x)>0]
			dataset.append(line_list.index(str(symbol)))
		all_datasets.append(dataset)

for i in range(amount_LS-1):
	x=np.array(all_datasets[i])
	for j in range(i+1,amount_LS):
		y=np.array(all_datasets[j])
		spearmanr_list.append(abs(scipy.stats.spearmanr(x, y).correlation))

print('{0:.10f}'.format(statistics.median(spearmanr_list)))

