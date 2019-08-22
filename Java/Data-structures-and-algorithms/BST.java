package assign1;

public class BST
{ private BTNode<Integer> root;

  public BST()
  { root = null;
  }

  public boolean find(Integer i)
  { BTNode<Integer> n = root;
    boolean found = false;

    while (n!=null && !found)
    { int comp = i.compareTo(n.data);
      if (comp==0)
        found = true;
      else if (comp<0)
        n = n.left;
      else
        n = n.right;
	}

    return found;
  }

  public boolean insert(Integer i)
  { BTNode<Integer> parent = root, child = root;
    boolean goneLeft = false;

    while (child!=null && i.compareTo(child.data)!=0)
    { parent = child;
      if (i.compareTo(child.data)<0)
	  { child = child.left;
	    goneLeft = true;
	  }
	  else
	  { child = child.right;
	    goneLeft = false;
      }
	}

    if (child!=null)
      return false;  // number already present
    else
    { BTNode<Integer> leaf = new BTNode<Integer>(i);
      if (parent==null) // tree was empty
        root = leaf;
      else if (goneLeft)
        parent.left = leaf;
      else
        parent.right = leaf;
      return true;
    }
  }

  //returns number of non leaf nodes
  public int nonleaves() {
    if(root==null) return 0;
    return root.nLeaves();
     }

  //returns the maximum depth of the tree
  public int depth() {
   return BTNode.maxD(root);
  }

  public int range(int min, int max) {
    BTNode<Integer> n = root;
    int count = 0;
    if(max<min) throw new IllegalArgumentException("Supplied max value is smaller than min value") ;
    if (n==null) return 0;
    for(int i = min; i<= max; i++){
      if(this.find(i)) count++;
    }
    return count;}

}

class BTNode<T>
{ T data;
  BTNode<T> left, right;

  BTNode(T o)
  { data = o; left = right = null;
  }

  //counts how many nodes are non leaves
  int nLeaves(){
    int answer = 1;
    if(left==null && right==null) //if node is a leaf method returns zero
      return 0;
    if(left!= null)
      answer += left.nLeaves();
    if(right!=null)
      answer += right.nLeaves();
    return answer;
  }

  //calculates the max depth of a node
  static int maxD(BTNode<Integer> x){
     if (x==null) return 0;
    else{
       int lDepth = maxD(x.left);
       int rDepth = maxD(x.right);
       if(lDepth>rDepth)
         return lDepth+1;
       else
         return rDepth+1;
     }

  }

}
