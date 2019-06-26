from datetime import datetime


def ReadData_MultiTable(engine, path, func_DataLineJudge, func_DataLineToDict, func_DataDictToTablename):
    # 本函数从原始数据中读取数据，并写入不同表中
    # func_DataLineJudge为自定义的判断函数，如果此行为数据行，则返回True
    # func_DataLineToTablename为自定义的命名规则
    # func_DataLineToDict为自定义的转码函数，把数据行转换为数据dict

    # 打开文件
    f = open(path)

    # 先找出一个数据行作例子，利用参数table_name和DataLineToDict函数返回字典值的索引确定出SQL后半部分语句格式VALUEForm
    VALUEForm = ''
    lines = f.readlines()
    for line in lines:
        if func_DataLineJudge(line):
            dic = func_DataLineToDict(line)
            VALUEForm = ' (' + ','.join(dic) + ') ' + 'VALUES('
            for indx in dic:
                if isinstance(dic[indx], str):
                    VALUEForm = VALUEForm + '\"%(' + indx + ')s\",'
                else:
                    VALUEForm = VALUEForm + '%(' + indx + ')s,'
            VALUEForm = VALUEForm[0:-1] + ')'
            break

    f.seek(0)
    # 存储数据
    lines = f.readlines()
    for line in lines:
        # 逐行扫描数据文件
        if func_DataLineJudge(line):
            # 检查数据行
            dic = func_DataLineToDict(line)  # 将数据行转换成字典
            tb_name = func_DataDictToTablename(dic)  # 判断该数据行应该插入到哪个表里面
            SQLForm = 'INSERT INTO ' + tb_name + VALUEForm
            SQL = SQLForm % dic  # 生成SQL语句
            # print(SQL)
            engine.execute(SQL)


def ReadData_SingleTable(engine, table_name, path, func_DataLineJudge, func_DataLineToDict):
    # 本函数从原始数据中读取数据，并保留ID写入同一表中
    # func_DataLineJudge为自定义的判断函数，如果此行为数据行，则返回True
    # func_DataLineToDict为自定义的转码函数，把数据行转换为数据dict

    # 打开文件
    f = open(path)

    # 先找出一个数据行作例子，利用参数table_name和DataLineToDict函数返回字典值的索引确定出SQL语句格式SQLForm
    SQLForm = ''
    lines = f.readlines()
    for line in lines:
        if func_DataLineJudge(line):
            dic = func_DataLineToDict(line)
            SQLForm = 'REPLACE INTO ' + table_name + ' (' + ','.join(dic) + ') ' + 'VALUES('
            for indx in dic:
                if isinstance(dic[indx], str) | isinstance(dic[indx], datetime):
                    SQLForm = SQLForm + '\"%(' + indx + ')s\",'
                else:
                    SQLForm = SQLForm + '%(' + indx + ')s,'
            SQLForm = SQLForm[0:-1] + ');'
            break

    f.seek(0)
    # 存储数据

    SQLlog = open('D:/lifterdatasql.sql', 'w')

    lines = f.readlines()
    for line in lines:
        # 逐行扫描数据文件
        if func_DataLineJudge(line):
            # 检查数据行
            dic = func_DataLineToDict(line)  # 将数据行转换成字典
            SQL = SQLForm % dic  # 生成SQL语句
            print(SQL)
            # engine.execute(SQL)
            SQLlog.write(SQL)
    SQLlog.close()
