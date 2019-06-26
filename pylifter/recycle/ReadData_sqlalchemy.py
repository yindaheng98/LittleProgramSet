# -*- coding: utf-8 -*-
from sqlalchemy import create_engine
engine = create_engine("mysql+mysqlconnector://"+\
                    'root:YHM19980228yhm'+\
                    '@127.0.0.1:3306/lifterdata?charset=utf8'\
                    ,encoding='utf-8')
                    
from ReadData import xlsxReadData
xlsxReadData(engine,'originalrecord_d11',r"D:\D11.xlsx",0)
xlsxReadData(engine,'originalrecord_d11',r"D:\D12.xlsx",0)
xlsxReadData(engine,'originalrecord_d11',r"D:\D13.xlsx",0)