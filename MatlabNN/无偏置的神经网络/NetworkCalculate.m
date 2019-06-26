function [output,pre_act_first,pre_act_]=NetworkCalculate(input,weightfirst,weighthide,weightfinal)
%神经网络计算一次结果
layernum=size(weighthide,1);
ly=layer(weightfirst,input);
for i=1:layernum
   ly=layer(weighthide(i),ly); 
end
output=layer(weightfinal,ly);
end