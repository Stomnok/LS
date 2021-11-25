import numpy as np
import scipy.stats
import statistics

n = 32
medians=[]
mins=[]
maxs=[]
for symbol in range(n):
    all_datasets = []
    spearmanr_list = []
    for i in range(n):
        filename = 'LS_' + str(i).zfill(4) + '.txt'
        dataset = []
        with open(filename, 'r') as LS:
            for line in LS:
                line_list = [x for x in line.split(' ') if len(x) > 0]
                dataset.append(line_list.index(str(symbol)))
            all_datasets.append(dataset)

    for i in range(n - 1):
        x = np.array(all_datasets[i])
        for j in range(i + 1, n):
            y = np.array(all_datasets[j])
            spearmanr_list.append(abs(scipy.stats.spearmanr(x, y).correlation))

    print('median value of Spearman correlation for ' + str(symbol) + ': ' + '{0:.10f}'.format(
        statistics.median(spearmanr_list)))
    medians.append(statistics.median(spearmanr_list))
    mins.append(min(spearmanr_list))
    maxs.append(max(spearmanr_list))
    
print('Result median of medians: {0:.10f}'.format(statistics.median(medians)))
print('Result median of mins: {0:.10f}'.format(statistics.median(mins)))
print('Result median of maxs: {0:.10f}'.format(statistics.median(maxs)))
        
