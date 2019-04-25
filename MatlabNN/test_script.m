K=1;%运行10次
MAX=10000;%每次数据量
LearningDegree=0.0005;%学习率
INPUTN=2;
OUTPUTN=1;
LAYERN=3;
HIDEN=7;
%HAVE_OFFSET='no offset';
HAVE_OFFSET='have offset';

x=1:MAX;
y=zeros(OUTPUTN,MAX,K);
for k=1:K
    nw=Network(INPUTN,OUTPUTN,HIDEN,LAYERN,HAVE_OFFSET);
    for i=1:MAX
        input=rand(INPUTN,1);
        output=test_func(input,INPUTN);
        nw=nw.BackPropagation(input,output,LearningDegree);
        y(:,i,k)=min(nw.costs,0.5);
        %y(:,i,k)=nw.costs;
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