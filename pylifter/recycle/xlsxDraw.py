from sqlalchemy import create_engine
engine = create_engine("mysql+mysqlconnector://"+\
                    'root:YHM19980228yhm'+\
                    '@127.0.0.1:3306/lifterdata?charset=utf8'\
                    ,encoding='utf-8')
from recycle.xlsxDrawData import xlsxDrawData
xlsxDrawData(engine,'originalrecord_d11')

