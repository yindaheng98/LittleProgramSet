from datetime import datetime

def autoCreateDataTable(engine,path,func_DataLineJudge,func_DataLineToDict,func_DataDictToTablename):
    #本函数根据原始数据为不同电梯创建表格
    #func_DataLineJudge为自定义的判断函数，如果此行为数据行，则返回True
    #func_DataLineToTablename为自定义的命名规则
    #func_DataLineToDict为自定义的转码函数，把数据行转换为数据dict
    #不推荐使用
    
    def Typeof(i):
        # 判断类型并输出类型名
        if (isinstance(i, str)):
            return 'str'
        elif (isinstance(i, int)):
            return 'int'
        elif (isinstance(i, float)):
            return 'float'
        elif (isinstance(i, datetime)):
            return 'datetime'
        
    f = open(path)

    tb_name=''
    lines = f.readlines()
    for line in lines:
        #逐行扫描数据文件
        if func_DataLineJudge(line):
            #检查数据行
            dic = func_DataLineToDict(line)#将数据行转换成字典
            if(tb_name==func_DataDictToTablename(dic)):#已为该编号的数据创建表格，则跳过
                continue
            else:#否则建表
                tb_name = func_DataDictToTablename(dic)
                SQL = 'CREATE TABLE IF NOT EXISTS ' + tb_name + ' ('
                for indx in dic:
                    SQL=SQL+indx+' '+Typeof(dic[indx])+','
                SQL=SQL[0:-1]+')'
                engine.execute(SQL)




