#男女人数比例
SELECT COUNT(DISTINCT(T.姓名)) AS 人数,T.性别,MAX(T.年龄) AS 最大年龄,MIN(T.年龄) AS 最小年龄 FROM
(SELECT abs(TIMESTAMPDIFF(DAY, 出生日期, 检测日期))/365 AS 年龄,性别,姓名 FROM hospital.bcm原始数据) AS T
GROUP BY T.性别;
#BCM数据总量男女比例
SELECT COUNT(*) AS 数据量,性别 FROM hospital.bcm原始数据 GROUP BY 性别;