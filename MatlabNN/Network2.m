classdef Network2
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
        function obj=Network2(inputnum,outputnum,hidenum,layernum)
            %初始化,边值全部随机数,其他全零
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
            obj=obj.CalculateUpdate(input);
            obj.costs=0.5*(obj.after_activate_final-output_wehope).^2;%计算代价
            %obj.costs=abs(errors);
            %计算导数值
            diff_activate_hide=diff_activate(obj.before_activate_hide);
            diff_activate_final=diff_activate(obj.before_activate_final);
            %计算误差值,误差值反向传播,与神经元节点对应
            error_final=obj.after_activate_final-output_wehope;
            error_hide=zeros(obj.hidenum,obj.layernum+1);
            error_hide(:,end)=obj.weight_final'*(error_final.*diff_activate_final);
            %算隐藏层的最后一层,每一行值都相同(连接指向同一个神经元的边的error值相同)
            for l=obj.layernum:-1:1%算中间的隐藏层
                error_hide(:,l)=obj.weight_hide(:,:,l)'*(error_hide(:,l+1).*diff_activate_hide(:,l+1));
            end
            %算变化量
            offset_change_final=error_final.*diff_activate_final;
            offset_change_hide=error_hide.*diff_activate_hide;
            weight_change_final=offset_change_final*obj.after_activate_hide(:,end)';
            weight_change_hide=zeros(obj.hidenum,obj.hidenum,obj.layernum);
            for l=obj.layernum:-1:2
                weight_change_hide(:,:,l)=offset_change_hide(:,l)*obj.after_activate_hide(:,l-1)';
            end
            weight_change_first=offset_change_hide(:,1)*obj.input';
            %对每个输出单独计算
            obj.weight_first=obj.weight_first-degree*weight_change_first;
            obj.weight_hide=obj.weight_hide-degree*weight_change_hide;
            obj.weight_final=obj.weight_final-degree*weight_change_final;
            obj.offset_hide=obj.offset_hide-degree*offset_change_hide;%/10;
            obj.offset_final=obj.offset_final-degree*offset_change_final;%/10;
            %有偏置改变的无法正常拟合过原点的数据
        end
    end
    methods(Access=private)
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