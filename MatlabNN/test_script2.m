clear;
K=1;%����10��
MAX=1000;%ÿ��������
LearningDegree=0.05;%ѧϰ��
INPUTN=2;
OUTPUTN=2;
LAYERN=1;
HIDEN=100;

x=1:MAX;
y=zeros(OUTPUTN,MAX,K);
for k=1:K
    nw=Network2(INPUTN,OUTPUTN,HIDEN,LAYERN);
    for i=1:MAX
        input=rand(INPUTN,1);
        output=test_func(input,INPUTN);
        nw=nw.BackPropagation(input,output,LearningDegree);
        y(:,i,k)=nw.costs;
    end
end

for i=1:OUTPUTN
    subplot(1,OUTPUTN,i);
    for k=1:K
        hold on;
        plot(x,y(i,:,k));
    end
end
nw.record('record.txt');