function errors=NetworkErrors(input,weightfirst,weighthide,weightfinal,offsetfirst,offsethide,offsetfinal,output)
%����һ������������,outputΪ�������
errors=0.5.*(output-NetworkCalculate(input,weightfirst,weighthide,weightfinal,offsetfirst,offsethide,offsetfinal)).^2;
end