function [costs,errors]=NetworkCosts(input,weightfirst,weighthide,weightfinal,output)
%����һ������������,outputΪ�������,������ۺͲ�ֵ
errors=output-NetworkCalculate(input,weightfirst,weighthide,weightfinal);
costs=0.5*errors.^2;
end