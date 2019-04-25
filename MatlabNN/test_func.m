function output=test_func(input,INPUTN)
%TEST_FUNC 测试用的函数
%   此处显示详细说明
%output=sum(input);
%output=linspace(1,2,INPUTN)*input;
%output=sum(input)*7+1.3;
mat=[1,4;2,3];
output=mat*input+3;
output=output.^2./(mat*ones(length(input),1)+3);
%output=linspace(1,2,INPUTN)*input.^2+1.2;
%output=10*(linspace(1,2,INPUTN)*input).^2+12;
end

