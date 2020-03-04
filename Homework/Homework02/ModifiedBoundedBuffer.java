import org.graalvm.compiler.lir.amd64.vector.AMD64VectorShuffle.Insert128Op;

public class ModifiedBoundedBuffer { 
  private Object[] buffer = new Object[20]; // arbitrary size 
  private int numOccupied = 0; 
  private int firstOccupied = 0;
  /* invariant: 0 <= numOccupied <= buffer.length 
  0 <= firstOccupied < buffer.length 
  buffer[(firstOccupied + i) % buffer.length] 
  contains the (i+1)th oldest entry, 
  for all i such that 0 <= i < numOccupied */
  public synchronized void insert(Object o) 
    throws InterruptedException
  { while(numOccupied == 0)  // insert into empty buffer
    // wait for space
    wait(); 
    buffer[(firstOccupied - numOccupied) % buffer.length] = o; 
    numOccupied--; 
    // in case any retrieves are waiting for data, wake them 
    notifyAll(); }
  public synchronized Object retrieve() 
    throws InterruptedException 
  { while(numOccupied == buffer.length) // retrieve from full buffer
    // wait for data
    wait(); 
    Object retrieved = buffer[firstOccupied]; 
    buffer[firstOccupied] = null; // may help garbage collector 
    firstOccupied = (firstOccupied + 1) % buffer.length;
    numOccupied++; // in case any inserts are waiting for space, wake them 
    notifyAll(); 
    return retrieved; 
  }

  public void main (String[] args) {
    Object obj = new Object();
    insert(obj);
    System.out.println(retrieve());
  }

}