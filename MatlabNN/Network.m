classdef Network
    properties(Access=public)
        %相关变量
        costs;
    end
    properties(GetAccess=public,SetAccess=private)
        %相关矩阵:权重和偏置
        weight_first;
        weight_hide;
        weight_final;
        offset_hide;
        offset_final;
    end
    properties(Access=public)
        %标记是否有偏置
        have_offset;
        %相关变量
        inputnum;%输入项个数
        outputnum;%输出项个数
        hidenum;%每一层的隐藏神经元个数
        layernum;%隐藏神经连接层数
        
        %相关矩阵:各神经元的激活值和未激活值
        input;%这个就是输入
        before_activate_hide;
        before_activate_final;
        after_activate_hide;
        after_activate_final;%这个就是计算结果
        %和神经元对应的值只有_hide和_final
        %和神经元连接对应的值有_first、_hide和_final
    end
    methods(Access=public)
        function obj=Network(inputnum,outputnum,hidenum,layernum,offset_option)
            %初始化,边值全部随机数,其他全零
            obj.have_offset=1;
            if strcmp(offset_option,'no offset')
                obj.have_offset=0;
            end
            obj.offset_hide=zeros(hidenum,layernum+1);
            obj.offset_final=zeros(outputnum,1);
            obj.input=zeros(inputnum,1);%这个就是输入
            obj.before_activate_hide=zeros(hidenum,layernum+1);
            obj.before_activate_final=zeros(outputnum,1);
            obj.after_activate_hide=zeros(hidenum,layernum+1);
            obj.after_activate_final=zeros(outputnum,1);%这个就是输出
            obj.inputnum=inputnum;
            obj.outputnum=outputnum;
            obj.hidenum=hidenum;
            obj.layernum=layernum;
            while(1)
                obj.weight_first=(rand(hidenum,inputnum)-0.5);
                obj.weight_hide=(rand(hidenum,hidenum,layernum)-0.5);%最后一位是层数，不然会出错
                obj.weight_final=(rand(outputnum,hidenum)-0.5);%(本层神经元个数,上一层神经元个数)
                if(sum(max(obj.Calculate(rand(inputnum,1)),0))>0)
                    break;
                end
            end
        end
        
        function record(obj,path)
            file=fopen(path,'wt');
            
            fprintf(file,'obj.have_offset=%d;\n',obj.have_offset);
            fprintf(file,'obj.inputnum=%d;\n',obj.inputnum);
            fprintf(file,'obj.outputnum=%d;\n',obj.outputnum);
            fprintf(file,'obj.hidenum=%d;\n',obj.hidenum);
            fprintf(file,'obj.layernum=%d;\n',obj.layernum);
            
            fprintf(file,'obj.weight_first=[');
            for i=1:obj.hidenum
                for j=1:obj.inputnum
                    fprintf(file,'%f ',obj.weight_first(i,j));
                end
                fprintf(file,';');
            end
            fprintf(file,'];\n');
            
            fprintf(file,'obj.weight_hide=zeros(obj.hidenum,obj.hidenum,obj.layernum);\n');
            for k=1:obj.layernum
                fprintf(file,'obj.weight_hide(:,:,%d)=[',k);
                for i=1:obj.hidenum
                    for j=1:obj.hidenum
                        fprintf(file,'%f ',obj.weight_hide(i,j,k));
                    end
                    fprintf(file,';');
                end
                fprintf(file,'];\n');
            end
            
            fprintf(file,'obj.weight_final=[');
            for i=1:obj.outputnum
                for j=1:obj.hidenum
                    fprintf(file,'%f ',obj.weight_final(i,j));
                end
                fprintf(file,';');
            end
            fprintf(file,'];\n');
            
            fprintf(file,'obj.offset_hide=[');
            for i=1:obj.hidenum
                for j=1:obj.layernum+1
                    fprintf(file,'%f ',obj.offset_hide(i,j));
                end
                fprintf(file,';');
            end
            fprintf(file,'];\n');
            
            fprintf(file,'obj.offset_final=[');
            for i=1:obj.outputnum
                fprintf(file,'%f;',obj.offset_final(i));
            end
            fprintf(file,'];\n');
            
            fclose(file);
        end
        function obj=Load(obj,path)
            file=fopen(path,'rt');
            while(~feof(file))
                str=fgets(file);
                eval(str);
            end
        end
        
        function output=Calculate(obj,input)
            %神经网络计算一次结果
            obj.input=input;
            obj.before_activate_hide(:,1)=obj.weight_first*obj.input+obj.offset_hide(:,1);
            obj.after_activate_hide(:,1)=activate(obj.before_activate_hide(:,1));%输入层
            for i=1:obj.layernum
                obj.before_activate_hide(:,i+1)=obj.weight_hide(:,:,i)*obj.after_activate_hide(:,i)+obj.offset_hide(:,i+1);
                obj.after_activate_hide(:,i+1)=activate(obj.before_activate_hide(:,i+1));%隐藏层
            end
            obj.before_activate_final=obj.weight_final*obj.after_activate_hide(:,i)+obj.offset_final;
            obj.after_activate_final=activate(obj.before_activate_final);
            output=obj.after_activate_final;%输出层
        end
        function obj=BackPropagation(obj,input,output_wehope,degree)
            %反向传播,输入的三个参数依次为输入,期望的输出,学习率
            weight_change_first=zeros(obj.hidenum,obj.inputnum);
            weight_change_hide=zeros(obj.hidenum,obj.hidenum,obj.layernum);
            weight_change_final=zeros(obj.outputnum,obj.hidenum);
            offset_change_hide=zeros(obj.hidenum,obj.layernum+1);
            offset_change_final=zeros(obj.outputnum,1);
            obj=obj.CalculateUpdate(input);
            %errors=obj.after_activate_final-output_wehope;%计算误差
            errors=(obj.after_activate_final-output_wehope)./output_wehope;
            obj.costs=0.5*errors.^2;%计算代价
            for i=1:obj.outputnum%对每个输出计算一次反向传播得到一个边weight_change矩阵
                %temp是可以递推的中间量,和神经元连接对应
                temp_final=repmat(obj.diff_activate(obj.before_activate_final(i)),1,obj.hidenum);
                %从输出边开始算,输出边可以直接算得,对每个输出单独计算
                temp_hide=zeros(obj.hidenum,obj.hidenum,obj.layernum);
                temp_hide(:,:,end)=repmat((temp_final.*obj.weight_final(i,:))'.*(obj.diff_activate(obj.before_activate_hide(:,end))),1,obj.hidenum);
                %算隐藏层的最后一层,每一行值都相同(连接指向同一个神经元的边的temp值相同)
                for k=obj.layernum-1:-1:1%算中间的隐藏层
                    temp_hide(:,:,k)=repmat(sum(temp_hide(:,:,k+1).*obj.weight_hide(:,:,k+1),1)'.*obj.diff_activate(obj.before_activate_hide(:,k+1)),1,obj.hidenum);
                end
                %算第一层中间量
                temp_first=repmat(sum(temp_hide(:,:,k).*obj.weight_hide(:,:,k),1)'.*obj.diff_activate(obj.before_activate_hide(:,k)),1,obj.inputnum);
                %算变化量
                weight_change_first=weight_change_first+errors(i)*temp_first.*repmat(obj.input',obj.hidenum,1);
                for k=1:obj.layernum
                    weight_change_hide(:,:,k)=weight_change_hide(:,:,k)+errors(i)*temp_hide(:,:,k).*repmat(obj.after_activate_hide(:,k)',obj.hidenum,1);
                end
                weight_change_final(i,:)=errors(i)*temp_final.*obj.after_activate_hide(:,k+1)';
                %对每个输出单独计算
                
                %偏置改变量%%%%%%%%%%%%%%%%%%%%%
                if obj.have_offset==1
                    offset_change_hide(:,1)=offset_change_hide(:,1)+errors(i)*temp_first(:,1);
                    offset_change_hide(:,2:end)=offset_change_hide(:,2:end)+errors(i)*reshape(temp_hide(:,1,:),obj.hidenum,obj.layernum);
                    offset_change_final(i)=errors(i)*temp_final(1);
                end
                %偏置改变量可选%%%%%%%%%%%%%%%%%
            end
            obj.weight_first=obj.weight_first-degree*weight_change_first;
            obj.weight_hide=obj.weight_hide-degree*weight_change_hide;
            obj.weight_final=obj.weight_final-degree*weight_change_final;
            obj.offset_hide=obj.offset_hide-degree*offset_change_hide;%/10;
            obj.offset_final=obj.offset_final-degree*offset_change_final;%/10;
            %有偏置改变的无法正常拟合过原点的数据
        end
    end
    methods(Access=private)
        function y=diff_activate(~,x)
            if(x==0)
                x=eps(1);
            end
            y=(activate(x+eps(1)*x)-activate(x))./(eps(1)*x);
        end
        function obj=CalculateUpdate(obj,input)
            %神经网络计算一次结果并返回更新后的obj
            obj.input=input;
            obj.before_activate_hide(:,1)=obj.weight_first*obj.input+obj.offset_hide(:,1);
            obj.after_activate_hide(:,1)=activate(obj.before_activate_hide(:,1));%输入层
            for i=1:obj.layernum
                obj.before_activate_hide(:,i+1)=obj.weight_hide(:,:,i)*obj.after_activate_hide(:,i)+obj.offset_hide(:,i+1);
                obj.after_activate_hide(:,i+1)=activate(obj.before_activate_hide(:,i+1));%隐藏层
            end
            obj.before_activate_final=obj.weight_final*obj.after_activate_hide(:,i)+obj.offset_final;
            obj.after_activate_final=activate(obj.before_activate_final);
        end
    end
end