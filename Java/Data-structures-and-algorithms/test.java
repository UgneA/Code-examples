package assign1;


public class test {
    public static void main(String[] args) {
        Dequeue<Integer> myQ = new Dequeue<Integer>();

        System.out.println("Dequeue contents: " + myQ);
        System.out.println("Testing if dequeue is empty: " + myQ.isempty());//true
        System.out.println("Adding 5, 7 and then 9 to right");
        myQ.addright(5);        //<5>
        myQ.addright(7);        //<5,7>
        myQ.addright(9);        //<5,7,9>
        System.out.println("Dequeue contents: " + myQ);

        System.out.println("Removing right item");
        myQ.removeright();      //<5,7>
        System.out.println("Dequeue contents: " + myQ);

        System.out.println("Removing left item");
        myQ.removeleft();      //<7>
        System.out.println("Dequeue contents: " + myQ);

        System.out.println("Adding 31, 14 and then 2 to left");
        myQ.addleft(31);        //<31,7>
        myQ.addleft(14);        //<14,31,7>
        myQ.addleft(2);         //<2,14,31,7>
        System.out.println("Dequeue contents: " + myQ);

        System.out.println("Calling right: " + myQ.right() + " returned");  //7
        System.out.println("Calling left: " + myQ.left() + " returned");    //2

        System.out.println("Testing if dequeue is empty: " + myQ.isempty());//false


        System.out.println("Testing operations on an empty dequeue\n");
        Dequeue<Integer> myQ2 = new Dequeue<Integer>();

        try {
            myQ2.left();
        } catch (QueueException qe) {
            System.out.println(qe);
        }
        try {
            myQ2.right();
        } catch (QueueException qe) {
            System.out.println(qe);
        }
        try {
            myQ2.removeleft();
        } catch (QueueException qe) {
            System.out.println(qe);
        }
        try {
            myQ2.removeright();
        } catch (QueueException qe) {
            System.out.println(qe);
        }

    }
}
