function [output,pre_act_first,pre_act_]=NetworkCalculate(input,weightfirst,weighthide,weightfinal)
%���������һ�ν��
layernum=size(weighthide,1);
ly=layer(weightfirst,input);
for i=1:layernum
   ly=layer(weighthide(i),ly); 
end
output=layer(weightfinal,ly);
end