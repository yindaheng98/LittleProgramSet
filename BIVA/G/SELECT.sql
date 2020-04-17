USE Hospital;
SELECT
T1.姓名,T1.项目,T1.成分,T1.结果,T1.单位,T1.情况,
ROUND(abs(TIMESTAMPDIFF(DAY, T2.出生日期, T2.检测日期))/365) AS 年龄,
TIMESTAMPDIFF(HOUR, T2.检测日期, T1.时间) AS BCM化验时间差,
T2.性别,T2.体重,T2.身高,T2.Z,T2.Phi,
(T2.体重/POW(T2.身高/100,2)) AS BMI
FROM (血液成分原始数据 AS T1) INNER JOIN (bcm原始数据 AS T2) ON
T1.姓名=T2.姓名 AND 0<TIMESTAMPDIFF(HOUR, 检测日期, 时间) AND TIMESTAMPDIFF(HOUR, 检测日期, 时间)<48
WHERE T1.成分='25-羟维生素D' AND T2.性别='男';