function errors=NetworkErrors(input,weightfirst,weighthide,weightfinal,offsetfirst,offsethide,offsetfinal,output)
%计算一次神经网络的误差,output为期望输出
errors=0.5.*(output-NetworkCalculate(input,weightfirst,weighthide,weightfinal,offsetfirst,offsethide,offsetfinal)).^2;
end