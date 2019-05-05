package Jlifter;

public class Order
{
    /**
     * Order类存储呼叫信息
     * waittime的单位是毫秒
     */
        public final int floor;
        public final long waittime;

        public Order(int floor, long waittime)
        {
            this.floor = floor;
            this.waittime = waittime;
        }
        public Order(Order order)
        {
            this.floor = order.floor;
            this.waittime=order.waittime;
        }
}
