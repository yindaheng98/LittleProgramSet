function [weightfirst,weighthide,weightfinal]=NetworkBackPropagation(input,weightfirst,weighthide,weightfinal,output,degree)
%���з��򴫲�,degreeΪѧϰ��
%����ۺ����ͼ��������ʽ���й�
[costs,errors]=NetworkCosts(input,weightfirst,weighthide,weightfinal,output);
[costnum,~]=size(costs);
%�������ֵ
[hidenum,inputnum]=size(weightfirst);
[layernum,~,~]=size(weighthide);
[outputnum,~]=size(weightfinal);
%��ȡ����������������Ϣ
difffirst=zeros(hidenum,inputnum);
diffhide=zeros(layernum,hidenum,hidenum);
difffinal=zeros(outputnum,hidenum);
%��ʼ���Լ������΢��ֵ����
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
%����ÿ���㼤�����΢�ֶ�Ӧֵ
for i=1:costnum
    
end
%���򴫲���΢��ֵ
weightfirst=weightfirst-degree*difffirst;
weighthide=weighthide-degree*diffhide;
weightfinal=weightfinal-degree*difffinal;
end