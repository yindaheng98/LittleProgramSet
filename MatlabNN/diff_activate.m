function output=diff_activate(input)
%������ļ�����ĵ���
%output=sinh(input)./cosh(input);
%output=stepfun(input,0);
t=exp(1).^(-input);output=t./(1+t).^2;
end

