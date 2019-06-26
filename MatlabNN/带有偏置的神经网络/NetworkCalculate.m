function output=NetworkCalculate(input,weightfirst,weighthide,weightfinal,offsetfirst,offsethide,offsetfinal)
%神经网络计算一次结果
layernum=size(weighthide,1);
ly=layer(weightfirst,offsetfirst,input);
for i=1:layernum
   ly=layer(weighthide(i),offsethide(i),ly); 
end
output=layer(weightfinal,offsetfinal,ly);
end