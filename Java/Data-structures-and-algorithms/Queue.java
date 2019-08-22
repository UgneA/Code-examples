package assign1;

public interface Queue<T>
{ public void addleft(T o);
  public void removeleft();
  public T left();
  public void addright(T o);
  public void removeright();
  public T right();
  public boolean isempty();
}

class QueueException extends RuntimeException
{ QueueException(String s)
  { super("Tried to apply " + s + " to empty dequeue");
  }
}