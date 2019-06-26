def xlxsDatetimeToTuple(Datetime):#把excel文件里的日期符号转成元组
    if type(Datetime)!=type('str')\
       or len(Datetime)!=19\
       or Datetime[4]!='-'\
       or Datetime[7]!='-'\
       or Datetime[10]!='-'\
       or Datetime[13]!=':'\
       or Datetime[16]!=':':
        raise Exception('Invalid date!')#检查格式'''
    
    Datetime=Datetime.split('-')#‘-’切分日期

    time=Datetime[-1]
    time=time.split(':')#‘：’切分时间
    
    Datetime=Datetime[0:-1]
    Datetime.extend(time)#连接成新表
    
    for i in range(0,len(Datetime)):
        Datetime[i]=int(Datetime[i])#逐项转化成数字

    return tuple(Datetime)
  
