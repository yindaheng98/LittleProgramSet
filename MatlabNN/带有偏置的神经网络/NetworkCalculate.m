function output=NetworkCalculate(input,weightfirst,weighthide,weightfinal,offsetfirst,offsethide,offsetfinal)
%���������һ�ν��
layernum=size(weighthide,1);
ly=layer(weightfirst,offsetfirst,input);
for i=1:layernum
   ly=layer(weighthide(i),offsethide(i),ly); 
end
output=layer(weightfinal,offsetfinal,ly);
end