SELECT 成分,单位,AVG(结果) AS Mean,STD(结果) AS SD,性别 FROM
(SELECT
T1.姓名,T1.项目,T1.成分,T1.结果,T1.单位,T1.情况,
ROUND(abs(TIMESTAMPDIFF(DAY, T2.出生日期, T2.检测日期))/365) AS 年龄,
abs(TIMESTAMPDIFF(HOUR, T1.时间, T2.检测日期)) AS BCM化验时间差,
T2.性别,T2.体重,T2.身高,T2.Z,T2.Phi
FROM (血液成分原始数据 AS T1) INNER JOIN (bcm原始数据 AS T2) ON
T1.姓名=T2.姓名 AND
abs(TIMESTAMPDIFF(HOUR, 检测日期, 时间))<48) AS T
GROUP BY 成分,单位,性别;