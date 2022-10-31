lst={
    'tex':'Latex',
    'm':'matlab',
    'py':'Python',
    'js':'Javascript',
    'java':'Java',
    'php':'PHP',
    'html':'HTML',
    'c':'C/C++',
    'h':'C/C++',
    'cpp':'C/C++',
    'cs':'C#'
}

files={lst[k]:[] for k in lst}

#排除过滤用的判断器
def is_except(what,except_list):
    for f in except_list:
        if(re.search(f,what)!=None):
            return True
    return False

dir_excepts=[#排除以下目录
    r'CameraCheck',
    r'arbor-master',
    r'Python/TheCalenders',
    r'wordatas/test/official_example',
    r'CUDA Samples',
    r'py/ganomaly',
    r'pycv-master',
    r'bin/Debug',
    r'bin/Release',
    r'swiper-4.2.2',
    r'/build.*[Ww]ebapp',
    r'/build/.*/js',
    r'node_modules',
    r'bootstrap-3.3.7',
    r'qrcode-generator-master',
    r'Mobile-Detect-2.8.31',
    r'/QRCode/',
    r'BricktronicsMotor-master',
    r'BricktronicsShield-master',
    r'MCBSTM32E',
    r'cmake-build-debug',
    r'AssetStudio-master',
    r'obj/Debug',
    r'obj/Release',
    r'/Properties',
    r'DCGAN-tensorflow',
    r'lifter/chapter7',
    r'/jsqrcode',
    r'The Calendars V2.0/Charts',
    r'The Calendars V2.0/lib',
    r'Three-effect-reaction-Simulator/src/main/webapp/js',
    r'The Calendars V2.0/phps',
    r'idea',
    r'RTE',
    r'lib',
    r'CUMCMThesis-master',
    r'MATLAB/BigData',
    r'SQList',
    r'/Latex/模板',
    r'StdPeriphDriver',
    r'uCOSII',
    r'CMSIS',
    r'Users/Inc',
    r'darknet',
    r'Calendars/Charts',
    r'Calendars/phps',
    r'数学建模培训/新建文件夹',
    r'build/'
    ]

file_excepts=[
    r'WebSiteAnalysisKit/python/ditu_analysis.py',
    r'.min',
    r'vue.js',
    r'jquery',
    r'echarts',
    r'stdafx',
    r'StdAfx',
    r'targetver',
    r'resource.h',
    r'stm32f10x_it',
    r'Designer',
    r'Doc.h',
    r'Doc.cpp',
    r'View.h',
    r'View.cpp',
    r'Dlg.h',
    r'Dlg.cpp',
    r'Frm.h',
    r'Frm.cpp',
    r'Resource.h',
    r'targetver.h',
    r'Form.*cs',
    r'2017B/Table[0-9]',
    r'MCM2019/render.html',
    r'WebSiteAnalysisKit/src/main/webapp/js/huan.js',
    r'WebSiteAnalysisKit/src/main/webapp/js/ditu.js',
    r'app/routes/upload.js',
    r'Calendars/js/home_autoload.js',
    r'Calendars/js/ac_event.js',
    r'Calendars/js/home_event.js',
    r'Calendars/change_course.php',
    r'Calendars/functions/load_courses.php'
]

import os
import re
for dirs in os.walk('..\\'):
    if(not is_except(dirs[0].replace('\\','/'),dir_excepts)):#没匹配到就开始记录文件
        for f in dirs[2]:
            ftype=f.split('.')[-1]
            if(ftype in lst):
                fil=dirs[0]+'\\'+f
                if(not is_except(fil.replace('\\','/'),file_excepts)):
                    files[lst[ftype]].append(fil)

with open('selected_files.txt','w', encoding="utf8") as f:
    for ftype in files:
        for file in files[ftype]:
            f.writelines(file+'\n')
