package Jlifter;

import java.util.Date;
import java.util.LinkedList;
import java.util.Queue;

/**
 * 这是一个带有基本控制单元的电梯类
 */
public class Jlifter extends Jlifter_basic
{
    /**
     * Order类存储呼叫信息
     * waittime的单位是毫秒
     */
    public class Order
    {
        int floor;
        long waittime;

        public Order(int floor, long waittime)
        {
            this.floor = floor;
            this.waittime = waittime;
        }
    }

    private Queue<Order> orders;

    private Date currenttime;
    private int recordtime;

    /**
     * 构造函数
     *
     * @param vmax         最大运行速度
     * @param acceleration 运行时加速度
     * @param h_prefloor   层高
     * @param topfloor     最高层数
     * @param bottomfloor  最低层数
     * @param recordt      采样周期,单位毫秒
     * @param starttime    起始时间
     */
    public Jlifter(double vmax, double acceleration, double h_prefloor, int topfloor, int bottomfloor, int recordt, Date starttime)
    {
        super(vmax, acceleration, h_prefloor, topfloor, bottomfloor);
        if (Math.pow(vmax, 2) / acceleration > h_prefloor)
            throw new IllegalArgumentException("电梯在任何楼层之间的运行都要能加速到最大速度");
        orders = new LinkedList<Order>();
        currenttime = starttime;
        recordtime = recordt;
    }

    public Jlifter(double vmax, double acceleration, double h_prefloor, int topfloor, int bottomfloor, int recordt)
    {
        super(vmax, acceleration, h_prefloor, topfloor, bottomfloor);
        if (Math.pow(vmax, 2) / acceleration > h_prefloor)
            throw new IllegalArgumentException("电梯在任何楼层之间的运行都要能加速到最大速度");
        orders = new LinkedList<Order>();
        currenttime = new Date();
        recordtime = recordt;
    }

    public Jlifter(double vmax, double acceleration, double h_prefloor, int topfloor, int bottomfloor)
    {
        super(vmax, acceleration, h_prefloor, topfloor, bottomfloor);
        orders = new LinkedList<Order>();
        currenttime = new Date();
        recordtime = 500;
    }

    /**
     * 设置采样周期
     *
     * @param recordtime 采样周期,单位毫秒
     */
    public void setRecordtime(int recordtime)
    {
        this.recordtime = recordtime;
    }

    /**
     * 设置当前状态
     *
     * @param time  当前时间
     * @param floor 当前停在哪一层
     */
    public void setCondition(Date time, int floor)
    {
        if (floor > top_floor || floor < bottom_floor)
            throw new IllegalArgumentException("不存在此楼层");
        super.setCondition(floor * height_prefloor, 0, 0, CommandList.stop, time);
        currenttime = time;
    }

    /**
     * 向预定队列插入数据
     *
     * @param floor    预定所在楼层
     * @param waittime 预计等待时间
     */
    public void giveOrder(int floor, long waittime)
    {
        if (floor > top_floor || floor < bottom_floor)
            throw new IllegalArgumentException("不存在此楼层");
        orders.add(new Order(floor, waittime));
    }

    /**
     * 存储电梯状态信息的类
     * 只用在getState函数的返回值中
     */
    class States
    {
        public final double h;
        public final double v;
        public final int floor;
        public final Date time;

        public States(Date currenttime, double[] r)
        {
            time = currenttime;
            h = r[0];
            v = r[1];
            floor = (int) (h / height_prefloor);
        }
    }

    /**
     * 获取指定时间的电梯状态
     *
     * @param time 指定的时间
     * @return Status类型, 包含当前时间，当前楼层，当前位置速度加速度
     */
    public States getState(Date time)
    {
        if (time.before(currenttime))
            throw new IllegalArgumentException("无法获取" + currenttime.toString() + "之前的电梯状态");
        return new States(time, getCondition(time));
    }


    /**
     * 从预定队列中取出一个order运行一次
     */
    public void runOne()
    {
        Order order = orders.poll();
        if (order != null) run(order);
        else throw new NullPointerException("没有更多的指令可以运行");
    }

    /**
     * 运行预定队列里的所有order
     */
    public void runAll()
    {
        for (Order order = orders.poll(); order != null; order = orders.poll())
            run(order);
    }


    /**
     * 运行一个order并生成历史记录
     *
     * @param order 要运行的order
     */
    private void run(Order order)
    {
        if (order.floor > top_floor || order.floor < bottom_floor)
            throw new IllegalArgumentException("不存在此楼层");
        States states = getState(currenttime);
        int floor_diff = order.floor - states.floor;
        if (floor_diff == 0)//如果就在当前位置有预定
            runStop(order.waittime);
        else//要上或要下
            runNotStop(order, floor_diff);
    }

    /**
     * 如果不需要上行或下行
     *
     * @param waittime 等待时间
     */
    private void runStop(long waittime)
    {
        giveCommand(currenttime, CommandList.stop);
        Date endtime = new Date(currenttime.getTime() + waittime);
        for (Date t = currenttime; t.before(endtime); t.setTime(t.getTime() + recordtime))
            Record(getState(t));
        currenttime = endtime;
    }

    /**
     * 如果需要上行或下行
     *
     * @param order      要响应的order
     * @param floor_diff 上/下楼层数
     */
    private void runNotStop(Order order, int floor_diff)
    {
        // 上行/下行时间
        long dt_run;
        long dt_stop;
        //总的移动距离
        double dh = Math.abs(floor_diff * height_prefloor);
        if (dh < 2 * height_brake)//如果运行过程到不了最大速度
        {
            dt_run = (long) (Math.sqrt(dh / a) * 1000);
            dt_stop = dt_run;
        }
        else
        {
            dt_run = (long) ((accelerate_time + (dh - height_brake * 2) / vMax) * 1000);
            dt_stop = (long) (accelerate_time * 1000);
        }

        //减速命令时间点
        Date t_stopcmd = new Date(currenttime.getTime() + dt_run);
        //停机校准时间点
        Date t_calibration = new Date(t_stopcmd.getTime() + dt_stop);
        //停止测量时间点
        Date t_end = new Date(t_calibration.getTime() + order.waittime);
        giveCommand(currenttime, floor_diff > 0 ? CommandList.up : CommandList.down);
        for (Date t = currenttime; t.before(t_stopcmd); t.setTime(t.getTime() + recordtime))
            Record(getState(t));
        giveCommand(t_stopcmd, CommandList.stop);
        for (Date t = currenttime; t.before(t_calibration); t.setTime(t.getTime() + recordtime))
            Record(getState(t));
        setCondition(t_calibration, order.floor);
        for (Date t = currenttime; t.before(t_end); t.setTime(t.getTime() + recordtime))
            Record(getState(t));
        setCondition(t_end, order.floor);
    }


    protected void Record(States states)
    {
        String out = "";
        out += "当前时间";
        out += states.time.toString();
        out += "当前楼层";
        out += states.floor;
        out += "当前位置";
        out += states.h;
        out += "当前速度";
        out += states.v;
        System.out.println(out);
    }
}
