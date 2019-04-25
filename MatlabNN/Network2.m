classdef Network2
    properties(Access=public)
        %��ر���
        costs;
    end
    properties(GetAccess=public,SetAccess=private)
        %��ؾ���:Ȩ�غ�ƫ��
        weight_first;
        weight_hide;
        weight_final;
        offset_hide;
        offset_final;
    end
    properties(Access=public)
        %��ر���
        inputnum;%���������
        outputnum;%��������
        hidenum;%ÿһ���������Ԫ����
        layernum;%���������Ӳ���
        
        %��ؾ���:����Ԫ�ļ���ֵ��δ����ֵ
        input;%�����������
        before_activate_hide;
        before_activate_final;
        after_activate_hide;
        after_activate_final;%������Ǽ�����
        %����Ԫ��Ӧ��ֵֻ��_hide��_final
        %����Ԫ���Ӷ�Ӧ��ֵ��_first��_hide��_final
    end
    methods(Access=public)
        function obj=Network2(inputnum,outputnum,hidenum,layernum)
            %��ʼ��,��ֵȫ�������,����ȫ��
            obj.offset_hide=zeros(hidenum,layernum+1);
            obj.offset_final=zeros(outputnum,1);
            obj.input=zeros(inputnum,1);%�����������
            obj.before_activate_hide=zeros(hidenum,layernum+1);
            obj.before_activate_final=zeros(outputnum,1);
            obj.after_activate_hide=zeros(hidenum,layernum+1);
            obj.after_activate_final=zeros(outputnum,1);%����������
            obj.inputnum=inputnum;
            obj.outputnum=outputnum;
            obj.hidenum=hidenum;
            obj.layernum=layernum;
            while(1)
                obj.weight_first=(rand(hidenum,inputnum)-0.5);
                obj.weight_hide=(rand(hidenum,hidenum,layernum)-0.5);%���һλ�ǲ�������Ȼ�����
                obj.weight_final=(rand(outputnum,hidenum)-0.5);%(������Ԫ����,��һ����Ԫ����)
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
            %���������һ�ν��
            obj.input=input;
            obj.before_activate_hide(:,1)=obj.weight_first*obj.input+obj.offset_hide(:,1);
            obj.after_activate_hide(:,1)=activate(obj.before_activate_hide(:,1));%�����
            for i=1:obj.layernum
                obj.before_activate_hide(:,i+1)=obj.weight_hide(:,:,i)*obj.after_activate_hide(:,i)+obj.offset_hide(:,i+1);
                obj.after_activate_hide(:,i+1)=activate(obj.before_activate_hide(:,i+1));%���ز�
            end
            obj.before_activate_final=obj.weight_final*obj.after_activate_hide(:,i)+obj.offset_final;
            obj.after_activate_final=activate(obj.before_activate_final);
            output=obj.after_activate_final;%�����
        end
        function obj=BackPropagation(obj,input,output_wehope,degree)
            %���򴫲�,�����������������Ϊ����,���������,ѧϰ��
            obj=obj.CalculateUpdate(input);
            obj.costs=0.5*(obj.after_activate_final-output_wehope).^2;%�������
            %obj.costs=abs(errors);
            %���㵼��ֵ
            diff_activate_hide=diff_activate(obj.before_activate_hide);
            diff_activate_final=diff_activate(obj.before_activate_final);
            %�������ֵ,���ֵ���򴫲�,����Ԫ�ڵ��Ӧ
            error_final=obj.after_activate_final-output_wehope;
            error_hide=zeros(obj.hidenum,obj.layernum+1);
            error_hide(:,end)=obj.weight_final'*(error_final.*diff_activate_final);
            %�����ز�����һ��,ÿһ��ֵ����ͬ(����ָ��ͬһ����Ԫ�ıߵ�errorֵ��ͬ)
            for l=obj.layernum:-1:1%���м�����ز�
                error_hide(:,l)=obj.weight_hide(:,:,l)'*(error_hide(:,l+1).*diff_activate_hide(:,l+1));
            end
            %��仯��
            offset_change_final=error_final.*diff_activate_final;
            offset_change_hide=error_hide.*diff_activate_hide;
            weight_change_final=offset_change_final*obj.after_activate_hide(:,end)';
            weight_change_hide=zeros(obj.hidenum,obj.hidenum,obj.layernum);
            for l=obj.layernum:-1:2
                weight_change_hide(:,:,l)=offset_change_hide(:,l)*obj.after_activate_hide(:,l-1)';
            end
            weight_change_first=offset_change_hide(:,1)*obj.input';
            %��ÿ�������������
            obj.weight_first=obj.weight_first-degree*weight_change_first;
            obj.weight_hide=obj.weight_hide-degree*weight_change_hide;
            obj.weight_final=obj.weight_final-degree*weight_change_final;
            obj.offset_hide=obj.offset_hide-degree*offset_change_hide;%/10;
            obj.offset_final=obj.offset_final-degree*offset_change_final;%/10;
            %��ƫ�øı���޷�������Ϲ�ԭ�������
        end
    end
    methods(Access=private)
        function obj=CalculateUpdate(obj,input)
            %���������һ�ν�������ظ��º��obj
            obj.input=input;
            obj.before_activate_hide(:,1)=obj.weight_first*obj.input+obj.offset_hide(:,1);
            obj.after_activate_hide(:,1)=activate(obj.before_activate_hide(:,1));%�����
            for i=1:obj.layernum
                obj.before_activate_hide(:,i+1)=obj.weight_hide(:,:,i)*obj.after_activate_hide(:,i)+obj.offset_hide(:,i+1);
                obj.after_activate_hide(:,i+1)=activate(obj.before_activate_hide(:,i+1));%���ز�
            end
            obj.before_activate_final=obj.weight_final*obj.after_activate_hide(:,i)+obj.offset_final;
            obj.after_activate_final=activate(obj.before_activate_final);
        end
    end
end