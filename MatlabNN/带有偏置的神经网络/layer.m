function output = layer( weight,offset,input)
%神经网络的某一层
%详细说明
output=activate(weight*input+offset);
end

