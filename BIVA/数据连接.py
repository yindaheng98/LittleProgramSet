from G.convert import SQL_to_pandas


def allComp(cursor):
    SQL = 'SELECT DISTINCT 成分 FROM 血液成分原始数据'
    cursor.execute(SQL)
    return [d[0] for d in cursor.fetchall()]


SQLf = "SELECT \
T1.姓名,T1.项目,T1.结果,T1.单位,T1.情况, \
ROUND(abs(TIMESTAMPDIFF(DAY, T2.出生日期, T2.检测日期))/365) AS 年龄, \
TIMESTAMPDIFF(HOUR, T2.检测日期, T1.时间) AS BCM化验时间差, \
T2.性别,T2.体重,T2.身高,T2.Z,T2.Phi,\
(T2.体重/POW(T2.身高/100,2)) AS BMI \
FROM (血液成分原始数据 AS T1) INNER JOIN (bcm原始数据 AS T2) ON \
T1.姓名=T2.姓名 AND 0<TIMESTAMPDIFF(HOUR, 检测日期, 时间) AND TIMESTAMPDIFF(HOUR, 检测日期, 时间)<72 \
WHERE T1.成分='%s' AND T2.性别='%s'"


def dataSelect(COMP, SEX, cursor):
    cursor.execute(SQLf % (COMP, SEX))
    return SQL_to_pandas(cursor)


data_dir = '原始数据/'

if __name__ == '__main__':
    from G.connection import connection

    cursor = connection.cursor()
    for COMP in allComp(cursor):
        for SEX in ['男', '女']:
            data = dataSelect(COMP, SEX, cursor)
            data.to_csv(data_dir + COMP + '-' + SEX + '.csv', encoding='utf8')

    cursor.close()

    SQL = "SELECT 姓名,'BMI' AS 项目, 体重*10000/(身高*身高) AS 结果,\
    'kg/m2' AS 单位,NULL AS 情况, \
    ROUND(abs(TIMESTAMPDIFF(DAY, 出生日期, 检测日期))/365) AS 年龄, \
    0 AS BCM化验时间差, \
    性别,体重,身高, Z, Phi FROM bcm原始数据 WHERE 性别='%s'"

    from G.connection import connection
    from G.convert import SQL_to_pandas

    cursor = connection.cursor()
    for SEX in ['男', '女']:
        cursor.execute(SQL % SEX)
        data = SQL_to_pandas(cursor)
        data.to_csv(data_dir + 'BMI' + '-' + SEX + '.csv', encoding='utf8')

    cursor.close()
    connection.close()
