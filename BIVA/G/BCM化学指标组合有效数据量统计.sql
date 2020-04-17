USE Hospital;
SELECT 成分,COUNT(*) AS 有效数据量 
FROM (血液成分原始数据 AS T1) INNER JOIN (bcm原始数据 AS T2) ON
T1.姓名=T2.姓名 AND 0<TIMESTAMPDIFF(HOUR, 检测日期, 时间) AND TIMESTAMPDIFF(HOUR, 检测日期, 时间)<48
GROUP BY 成分 ORDER BY 有效数据量 DESC;