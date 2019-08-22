package assign1;


public class Dequeue<T> implements Queue<T>{

    private QCell<T> leftCell, rightCell;

    public Dequeue(){
        leftCell = rightCell = null;
    }

    public boolean isempty(){
        return (leftCell==null);
    }

    //returns leftmost element of a dequeue
    public T left(){
      if (leftCell==null)
        throw new QueueException("left");
      return leftCell.data;
    }

    //returns rightmost element of a dequeue
    public T right(){
      if (rightCell==null)
        throw new QueueException("right");
      return rightCell.data;
    }

    //removes element from the left side of a dequeue
    public void removeleft(){
      if (leftCell==null)
        throw new QueueException("removeleft");
      leftCell = leftCell.next;
        QCell<T> c = rightCell;
        while (c.prev.prev != null)  {c = c.next;}
        c.prev=null;
      if (leftCell==null) rightCell = null;
    }

    //removes one element from the right side of a dequeue
    public void removeright(){
        if(rightCell==null)
            throw new QueueException("removeright");
        rightCell = rightCell.prev;
        QCell<T> c = leftCell;
        while (c.next.next != null)  {c = c.next;}
        c.next=null;
        if (rightCell==null) leftCell = null;
    }

    //adds an element to the left side of a dequeue
    public void addleft(T x){
        QCell<T> newCell = new QCell<T>(x);
        if (leftCell==null)
            leftCell = rightCell = newCell;
        else
        {   QCell<T> temp = leftCell;
            leftCell.prev = newCell;
            leftCell = newCell;
            leftCell.next = temp;
        }
    }

    //adds an element to the right side of a dequeue
    public void addright(T x){
        QCell<T> newCell = new QCell<T>(x);
        if (leftCell==null)
            leftCell = rightCell = newCell;
        else
        {   QCell<T> temp = rightCell;
            rightCell.next = newCell;
            rightCell = newCell;
            rightCell.prev = temp;
        }
    }

    public String toString()
    { StringBuffer sb = new StringBuffer("<");
        QCell<T> c = leftCell;
        while (c != null)
        { sb.append(c.data);
            c = c.next;
            if(c!=null) sb.append(',');
        }
        return(sb+">");
    }
}

class QCell<T>{
    T data;
    QCell<T> next;
    QCell<T> prev;
    QCell(T x){
        data = x;
        next = prev = null;
    }
}