# 嵌入式课设方案

## 课设要求

1. 利用P0口的一个管脚作为一个按键信号输入，其作用是启动流水灯的开始和停止。（第一次按启动，第二次停止，第三次启动，以此类推)

2. 利用P0口的一个管脚作为一个按键信号输入，其作用是设置灯亮的时间，分三档1秒，2秒，3秒（第一次按1，第二次2秒，第三次3秒，第四次1秒，以此类推）

3. 基于uc/os-II操作系统，完成以上程序设计。

## STM32芯片型号

STM32F103C8T6：48脚封装，64K flash

## uCOS-II的移植

1. 构造一个裸机Demo，实现基本的流水灯

2. 至Micrium官网下载STM32F107的$\mu$COS，Keil MDK4的版本是$\mu$COS 2.92.07

3. 将下列文件夹中的文件复制到裸机Demo下：
   * Micrium\Software\uCOS-II\Ports：与硬件有关的操作系统核心文件，是移植时需要修改的文件
   * Micrium\Software\uCOS-II\Source：与硬件无关的操作系统核心文件，不需要修改
   * Micrium\Software\EvalBoards\Micrium\uC-Eval-STM32F107\uCOS-II复制如下文件：
     * os_cfg.h：定义要开启哪些操作系统模块
     * app_cfg.h：操作系统基本设置
     * app_hooks.c：系统hooks支持
     * includes.h：必要的头文件

4. 在Keil工程中添加上一步中复制的文件（增加一个groups，向其中添加.c文件；在设置中添加.h文件的include path）

5. 修改includes.h：删去bsp(Board Support Pack,开发板支持)和lib相关的include

6. 修改stm32f10x_it.c：
   * 在SysTick中断处理函数SysTick_Handler()中调用操作系统的SysTick函数OS_CPU_SysTickHandler()
   * 删去原有的PendSV异常处理函数PendSV_Handler()

7. 修改os_cpu_a.asm：
   * 将操作系统原有的PendSV处理函数OS_CPU_PendSVHandler重命名为PendSVHandler
   * 将文件开头的EXPORT OS_CPU_PendSVHandler改为EXPORT PendSVHandler

8. 主函数内调用OSInit()、OSTaskCreate和OSStart()即启动操作系统

## uCOS-II的启动方法

1. OSInit()：操作系统初始化
2. OSTaskCreate：创建Task(进程)
3. OSStart()：启动操作系统
   
## uCOS-II的Task(进程)

* uCOS-II的Task(进程)是一个内部有while(1)循环的函数，while(1)循环中是Task每次运行时要执行的代码，while循环的结尾或者开头一般要加上操作系统延迟函数OSTimeDly（操作系统时间定时）或OSTimeDlyHMSM（毫秒级精确定时）。
* OSStart()启动操作系统之前要用OSTaskCreate传入Task对应函数创建进程并指定优先级
  
## 进程设计方案

两标志位两进程

* 两个标志位：一个标志位标志流水灯速度，一个标志位标志流水灯启停
* 按键进程：每0.1秒轮询按键状态+改变标志位
* 流水进程：每1秒读取标志位改变流水灯状态达到流水效果
