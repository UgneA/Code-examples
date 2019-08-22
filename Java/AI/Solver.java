package Modified;
import java.io.File;
import java.io.PrintWriter;
import java.util.ArrayList;

/*
   Solver is a class that contains the methods used to search for and print solutions
   plus the data structures needed for the search.
 */

public class Solver {

    ArrayList<Node> unexpanded = new ArrayList<Node>();
    ArrayList<Node> expanded = new ArrayList<Node>();
    Node rootNode;

    /*
       Solver is a constructor that sets up an instance of the class with a node corresponding
       to the initial state as the root node.
     */
    public Solver(char[] initialBoard) {
        GameState initialState = new GameState(initialBoard);
        rootNode = new Node(initialState);
    }

    /*
       The method solve searches for a solution.
       The Printwriter argument is used to specify where the output should be directed.
     */


    /*
       printSolution is a recursive method that prints all the states in a solution.
     */
    public void printSolution(Node n, PrintWriter output) {
        if (n.parent != null) printSolution(n.parent, output);
        output.println(n.state);
    }

    /*
       reportSolution prints the solution together with statistics on the number of moves
       and the number of expanded and unexpanded nodes.
     */
    public void reportSolution(Node n, PrintWriter output) {
        output.println("Solution found!");
        printSolution(n, output);
        output.println(n.getCost() + " Moves");
        output.println("Nodes expanded: " + this.expanded.size());
        output.println("Nodes unexpanded: " + this.unexpanded.size());
        output.println();
    }

    public void solve(PrintWriter output) {
        unexpanded.add(rootNode);                                               // add initial node
        while (unexpanded.size() > 0) {                                         // while unexpanded list not empty
            Node n = unexpanded.get(unexpanded.size()-1);                       // get most recently generated node
            expanded.add(n);                                                    // add that node to expanded list
            unexpanded.remove(unexpanded.size()-1);                             // remove that node from unexpanded list
            if (n.state.isGoal()) {                                             // if node is goal state
                reportSolution(n, output);                                      // report success
                return;                                                         // terminates the search
            } else {
                ArrayList<GameState> moveList = n.state.possibleMoves();        // creates a list of all game states that can be reached in a single move from the current game state
                for (GameState gs : moveList) {                                 // for every state in a possible move list
                    if ((Node.findNodeWithState(unexpanded, gs) == null) &&     // if possible move is not within unexpanded nodes list
                            (Node.findNodeWithState(expanded, gs) == null)) {   // if possible move is not within expanded nodes list
                        int newCost = n.getCost()+ 1;                           // update number of moves
                        Node newNode = new Node(gs, n, newCost);                // creates new node
                        unexpanded.add(newNode);                                // add new node to the end of unexpanded nodes list
                    }
                }
            }
        }
        output.println("No solution found");                                    // output to be displayed if no solution is found
    }

    public static void main(String[] args) throws Exception {
        Solver problem = new Solver(GameState.INITIAL_BOARD);
        File outFile = new File("output.txt");
        PrintWriter output = new PrintWriter(outFile);
        problem.solve(output);
        output.close();
    }

}

