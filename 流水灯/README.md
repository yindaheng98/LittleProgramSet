# 嵌入式课程设计操作报告

## 设计要求

1. 利用P0口的一个管脚作为一个按键信号输入，其作用是启动流水灯的开始和停止。（第一次按启动，第二次停止，第三次启动，以此类推)

2. 利用P0口的一个管脚作为一个按键信号输入，其作用是设置灯亮的时间，分三档1秒，2秒，3秒（第一次按1，第二次2秒，第三次3秒，第四次1秒，以此类推）

3. 基于uc/os-II操作系统，完成以上程序设计。

## 芯片型号

STM32F103C8T6，48脚封装，64K flash

## uCOS-II的移植

1. 构造一个裸机Demo，实现基本的流水灯

2. 至Micrium官网下载并解压STM32F107官方移植的uCOS，其中Keil MDK4的版本是uCOS 2.92.07

3. 将下列文件夹中的文件复制到裸机Demo下：
   * Micrium\Software\uCOS-II\Ports：与硬件有关的操作系统核心文件，是移植时需要修改的文件
   * Micrium\Software\uCOS-II\Source：与硬件无关的操作系统核心文件，移植时不需要修改
   * Micrium\Software\EvalBoards\Micrium\uC-Eval-STM32F107\uCOS-II复制如下文件：
     * os_cfg.h：定义要开启哪些操作系统模块
     * app_cfg.h：操作系统基本设置
     * app_hooks.c：系统hooks支持
     * includes.h：必要的头文件

4. 在Keil工程中添加上一步中复制的文件（增加一个groups，向其中添加.c文件；在设置中将.h文件路径添加至include path）

5. 修改includes.h：删去bsp(Board Support Pack,开发板支持)和lib相关的include引用

6. 修改stm32f10x_it.c：
   * 在SysTick中断处理函数SysTick_Handler()中调用操作系统的SysTick函数OS_CPU_SysTickHandler()，该函数用于处理系统的时间片轮转
   * 删去原有的PendSV异常处理函数PendSV_Handler()，防止下一步中修改uCOS的os_cpu_a.asm后出现重定义错误

7. 修改os_cpu_a.asm：
   * 将操作系统原有的PendSV处理函数OS_CPU_PendSVHandler重命名为PendSVHandler，该函数用于在时间片轮转或系统出错时保存现场
   * 将文件开头的EXPORT OS_CPU_PendSVHandler改为EXPORT PendSVHandler，使得编译器进行link操作时能识别PendSVHandler函数

8. 编译，若无报错即表示移植成功

## uCOS-II的Task(进程)概念

* 设计方案中涉及到的uCOS-II Task(进程)都是内部有while(1)循环的函数，while(1)循环中是Task每次运行时要执行的代码，while循环的结尾或者开头加上操作系统延迟函数OSTimeDly（操作系统时间定时）或OSTimeDlyHMSM（毫秒级精确定时）使得任务每隔一段时间运行一次。
* OSStart()启动操作系统之前要用OSTaskCreate传入Task对应函数创建进程
  
## 程序设计方案

两个标志位+两个进程：

* 两个标志位：一个标志位标志流水灯速度，一个标志位标志流水灯启停
* 按键进程：每0.1秒轮询按键状态+改变标志位
* 流水进程：每1秒读取标志位改变流水灯状态达到流水效果

## 设计方案中使用到的uCOS-II函数

1. void OSInit(void)：初始化操作系统
2. void OSStart(void)：启动操作系统
3. INT8U OSTaskCreate(void (*task)(void *p_arg), void *p_arg, OS_STK *ptos, INT8U prio)：创建任务
   * void (*task)(void *p_arg)：任务代码的入口地址，一般传入一个函数
   * void *p_arg：任务的参数，即在向任务代码函数传递的参数
   * OS_STK *ptos：任务堆栈栈顶指针
   * INT8U prio：任务的优先级
4. INT8U OSTimeDlyHMSM(INT8U hours, INT8U minutes, INT8U seconds, INT16U milli)：按时分秒延时函数
   * INT8U hours：要延迟的小时数
   * INT8U minutes：要延迟的分钟数
   * INT8U seconds：要延迟的秒数
   * INT16U milli：要延迟的毫秒数

## 基于uCOS-II的程序设计

1. 修改裸机Demo中的流水灯程序，使之能根据标志位的值改变速度和启停
2. 将原有的流水灯程序中的延迟函数换成uCOS操作系统的延迟函数OSTimeDlyHMSM，并将流水灯的while(1)循环放入一个函数中
3. 编写按键扫描程序，该程序在一个while(1)循环中读取按键状态并根据按键状态改变标志位的值
4. 在主函数内适当位置依次调用OSInit()，OSTaskCreate和OSStart()启动操作系统，在创建进程时将流水灯程序设置为最高优先级进程，按键扫描程序设置为次高优先级
5. 编译，下载，运行，调试
