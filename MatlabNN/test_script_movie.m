K=1;%运行10次
MAX=20000;%每次数据量
LearningDegree=0.0005;%学习率
INPUTN=2;
OUTPUTN=1;
LAYERN=3;
HIDEN=7;
%HAVE_OFFSET='no offset';
HAVE_OFFSET='have offset';

N=10000;
d=0.001;
%M=moviein(n);
vidObj = VideoWriter('peaks.avi');
open(vidObj);
for n=1:N
    tfunc=@(input,INPUTN)linspace(1,2,INPUTN)*input+2+n*d;
    x=1:MAX;
    y=zeros(OUTPUTN,MAX,K);
    for k=1:K
        nw=Network(INPUTN,OUTPUTN,HIDEN,LAYERN,HAVE_OFFSET);
        for i=1:MAX
            input=rand(INPUTN,1);
            output=tfunc(input,INPUTN);
            nw=nw.BackPropagation(input,output,LearningDegree);
            y(:,i,k)=min(nw.costs,0.5);
            %y(:,i,k)=nw.costs;
        end
    end
    for i=1:OUTPUTN
        subplot(1,OUTPUTN,i);
        for k=1:K
            plot(x,y(i,:,k));
            hold on;
        end
    end
    legend(['目标偏移=',num2str(2+n*d)]);
    currFrame = getframe;
    writeVideo(vidObj,currFrame);
    %M(:,i) = getframe;
    hold off;
end
close(vidObj);
%movie(M,1,100);