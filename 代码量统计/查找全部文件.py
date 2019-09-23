lst={
    'tex':'Latex',
    'm':'matlab',
    'py':'Python',
    'js':'Javascript',
    'java':'Java',
    'php':'PHP',
    'sql':'SQL',
    'html':'HTML',
    'c':'C/C++',
    'h':'C/C++',
    'cpp':'C/C++',
    'cs':'C#'
}

files={lst[k]:[] for k in lst}

import os
import re
for dirs in os.walk('..\\'):
    for f in dirs[2]:
        ftype=f.split('.')[-1]
        if(ftype in lst):
            fil=dirs[0]+'\\'+f
            files[lst[ftype]].append(fil)

with open('all_files.txt','w') as f:
    for ftype in files:
        for file in files[ftype]:
            f.writelines(file+'\n')