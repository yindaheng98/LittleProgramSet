function output=diff_activate(input)
%神经网络的激活函数的导数
%output=sinh(input)./cosh(input);
%output=stepfun(input,0);
t=exp(1).^(-input);output=t./(1+t).^2;
end

