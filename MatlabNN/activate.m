function output=activate(input)
%������ļ����
%output=tanh(input);
%output=max(input,0);
output=1./(1+exp(1).^(-input));
%ʹ��ReLUʱ
%���һ����Ԫ��input����С��0��,�������Ϊ0
%��ɷ��򴫲��޷���������Ȩֵ
end