SELECT 姓名,检测日期,身高,体重,Z,Phi, R/身高 AS RH,X/身高 AS XH,R/BMI AS Rsp,X/BMI AS Xsp FROM (
SELECT *,Z*cos(Phi/180*pi()) AS R,Z*sin(Phi/180*pi()) AS X,身高*10000/(体重*体重) AS BMI FROM hospital.bcm原始数据
) AS T