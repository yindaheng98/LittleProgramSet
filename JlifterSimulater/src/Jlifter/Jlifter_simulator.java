package Jlifter;

import java.util.*;

public abstract class Jlifter_simulator
{
    private Map<Date, Order> orders;
    protected final Jlifter lifter;

    public Jlifter_simulator(Jlifter lifter)
    {
        this.lifter = lifter;
        orders = new TreeMap<Date, Order>(
                new Comparator<Date>()
                {
                    @Override
                    public int compare(Date o1, Date o2)
                    {
                        return (int) Math.copySign(1, o1.getTime() - o2.getTime());
                    }
                }
        );
    }

    /**
     * 增加指令序列
     *
     * @param orderline 要增加的指令序列
     */
    public void addOrders(Map<Date, Order> orderline)
    {
        for (Map.Entry<Date, Order> entry : orderline.entrySet())
        {
            Date key = entry.getKey();
            Order value = entry.getValue();
            if (value.floor > lifter.lifter.top_floor || value.floor < lifter.lifter.bottom_floor)
                throw new IllegalArgumentException("楼层数越界");
            orders.put(new Date(key.getTime()), new Order(value));
        }
    }

    /**
     * 重置指令序列
     *
     * @param orderline 把指令序列重置成orderline
     */
    public void resetOrders(Map<Date, Order> orderline)
    {
        orders.clear();
        addOrders(orderline);
    }

    public void resetOrders()
    {
        orders.clear();
    }

    /**
     * 运行模拟
     */
    public void runSimulator()
    {
        Map<Date, Order> nextorders = new LinkedHashMap<Date, Order>();
        //迭代
        while (!orders.isEmpty())
        {
            Conditions condition = lifter.getCondition();//获取当前状态
            int nextfloor = dispatch(condition, nextorders);//判断接下来去哪

            lifter.giveOrder(nextfloor, 0);
            lifter.runAll();//先让电梯到目标楼层
            long waittime = 0;
            nextorders.clear();//初始化

            condition = lifter.getCondition();//再获取当前状态
            Iterator<Map.Entry<Date, Order>> entries = orders.entrySet().iterator();
            while (entries.hasNext())
            {
                Map.Entry<Date, Order> entry = entries.next();
                Date key = entry.getKey();
                Order value = entry.getValue();//从头遍历

                if (key.getTime() <= condition.time.getTime() + waittime)//只管在当前等待时间内已经到达的orders
                {
                    if (value.floor == nextfloor)//找到order.floor==nextfloor的元素,即已经到达的在本层的orders
                    {
                        waittime += value.waittime;//把他们的等待时间相加作为本次order的等待时间
                        record(new Date(key.getTime()), new Order(value));//记录下这些已响应的指令
                        entries.remove();//同时在Map里删去这些元素
                    }
                    else nextorders.put(new Date(key.getTime()), new Order(value));//其他的已到达orders加入nextorders列表
                }
                else break;
            }
            if (waittime == 0 && nextorders.isEmpty())//如果这一层没有要响应的指令而且接下来的指令还没有到达
                if (!orders.isEmpty())//那就一直等到下一条指令到达
                    waittime = orders.entrySet().iterator().next().getKey().getTime() - condition.time.getTime();
            lifter.giveOrder(nextfloor, waittime);//让电梯在这一层等待
            lifter.runAll();
        }
    }

    /**
     * 抽象的记录类，用于给用户自定义记录方式
     *
     * @param time  要记录的指令的时间
     * @param order 要记录的指令
     */
    protected abstract void record(Date time, Order order);

    /**
     * 抽象调度方法，用于给用户自定义电梯调度算法
     *
     * @param condition  当前情况
     * @param nextorders 当前可见的未响应指令序列
     * @return int指示要去的楼层
     */
    protected abstract int dispatch(Conditions condition, Map<Date, Order> nextorders);
}
