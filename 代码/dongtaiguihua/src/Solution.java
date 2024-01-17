
public class Solution {
    static final int s = 5;  //自定义的台阶数
    static int len = 0, sum = 0;

    //最多也只有走5步就到了
    static int step[] = new int[s];

    static void compute(final int stair) {
        if (stair < 0)
            return;

        //表示已经走完了
        if (stair == 0) {
            printSum();
            sum++;
            return;
        }

        //每次到下一步选择时都可以走1-2步
        for (int i = 1; i <= 2; i++) {
            step[len] = i;
            len++;

            //进行下一步的迭代，迭代完之后将每后加上的一步去掉，换成其它的步数(如从1换成2)
            compute(stair - i);
            len--;
        }
    }

    static void printSum() {
        System.out.print("走法:");
        for (int i = 0; i < len; i++)
            System.out.print(step[i] + " ");
        System.out.println();
    }

    public static void main(String args[]) {
        compute(s);
        System.out.println("共有" + sum + "种走法");
    }

}