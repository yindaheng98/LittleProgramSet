import Jlifter.Conditions;
import Jlifter.Jlifter;
import Jlifter.Jlifter_simulator;
import Jlifter.Order;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;

import java.sql.SQLException;


public class MySimulator_FCFStest extends Jlifter_simulator
{
    public MySimulator_FCFStest(Jlifter lifter) throws SQLException
    {
        super(lifter);
        RandomOrders(10, lifter.getCondition().time, lifter.lifter.top_floor, lifter.lifter.bottom_floor);
    }

    protected void record(Date time, Order order)
    {
        String timestring = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss").format(time);
        String SQL = "insert into 响应信息(时间,楼层,等待时间)values('" + timestring + "'," + order.floor + "," + order.waittime + ")";
        Main.writeData(SQL);
    }


    protected int dispatch(Conditions condition, Map<Date, Order> nextorders)
    {
        if (nextorders.isEmpty()) return 1;
        return nextorders.entrySet().iterator().next().getValue().floor;
    }

    private void RandomOrders(int n, Date starttime, int topfloor, int bottomfloor)
    {
        Date time = starttime;
        Map<Date, Order> orders = new HashMap<Date, Order>();
        for (int i = 0; i < n; i++)
        {
            time = new Date(time.getTime() + (long) (Math.random() * 100000));
            int floor = (int) (Math.random() * (topfloor - bottomfloor)) + bottomfloor;
            long waittime = (long) (Math.random() * 100000);
            orders.put(time, new Order(floor, waittime));
            //orders.put(new Date(time.getTime()+1),new Order(floor,waittime));
        }
        super.addOrders(orders);
    }
}
