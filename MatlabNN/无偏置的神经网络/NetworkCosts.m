function [costs,errors]=NetworkCosts(input,weightfirst,weighthide,weightfinal,output)
%计算一次神经网络的误差,output为期望输出,输出代价和差值
errors=output-NetworkCalculate(input,weightfirst,weighthide,weightfinal);
costs=0.5*errors.^2;
end