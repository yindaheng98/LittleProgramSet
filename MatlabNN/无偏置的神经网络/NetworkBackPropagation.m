function [weightfirst,weighthide,weightfinal]=NetworkBackPropagation(input,weightfirst,weighthide,weightfinal,output,degree)
%进行反向传播,degree为学习率
%与代价函数和激活函数的形式都有关
[costs,errors]=NetworkCosts(input,weightfirst,weighthide,weightfinal,output);
[costnum,~]=size(costs);
%计算代价值
[hidenum,inputnum]=size(weightfirst);
[layernum,~,~]=size(weighthide);
[outputnum,~]=size(weightfinal);
%获取输入矩阵的行列数信息
difffirst=zeros(hidenum,inputnum);
diffhide=zeros(layernum,hidenum,hidenum);
difffinal=zeros(outputnum,hidenum);
%初始化对激活函数的微分值矩阵
ly=layer(weightfirst,input);
for i=1:layernum
   ly=layer(weighthide(i),ly); 
end
output=layer(weightfinal,ly);
end

for i=1:outputnum
    for j=1:hidenum
        difffinal(i,j)=
    end
end
%计算每个点激活函数的微分对应值
for i=1:costnum
    
end
%反向传播求微分值
weightfirst=weightfirst-degree*difffirst;
weighthide=weighthide-degree*diffhide;
weightfinal=weightfinal-degree*difffinal;
end