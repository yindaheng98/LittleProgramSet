function output=activate(input)
%神经网络的激活函数
%output=tanh(input);
%output=max(input,0);
output=1./(1+exp(1).^(-input));
%使用ReLU时
%最后一个神经元的input若是小于0的,则输出会为0
%造成反向传播无法更新连接权值
end